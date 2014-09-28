#ifndef __MODEM_CD_H__
#define __MODEM_CD_H__

#include <linux/wakelock.h>
#include <linux/dmapool.h>

#define DUMP_GPD_LAYOUT // dump the address of GPD ring buffer

#ifdef MT6290
#define MD_CD_MAJOR 190
#else
#define MD_CD_MAJOR 184
#endif
#define RING_BUFF_SIZE 16
#define QUEUE_BUDGET RING_BUFF_SIZE
#define CHECKSUM_SIZE 12

struct md_cd_queue {
	DIRECTION dir;
	unsigned char index;
	struct ccci_modem *modem;
	struct ccci_port *napi_port;

	struct list_head *tr_ring; // a "pure" ring of request, NO "head"
	struct ccci_request *tr_done;
	/*
	 * Tx has 2 writers: 1 for packet fill and 1 for packet free, so an extra pointer and a lock 
	 * is used. Tx also has 1 reader: CLDMA OUT.
	 * Rx has 1 reader: packet read&free, and 1 writer: CLDMA IN.
	 */
	struct ccci_request *tx_xmit;
	int free_slot; // counter, only for Tx
	spinlock_t ring_lock; // lock for the counter, only for Tx
	wait_queue_head_t req_wq; // only for Tx
	int budget;
	struct work_struct cldma_work;
	struct workqueue_struct *worker;
	u16 debug_id;
};

struct md_cd_ctrl{
	struct md_cd_queue txq[8];
	struct md_cd_queue rxq[8];
	wait_queue_head_t sched_thread_wq;
	unsigned char sched_thread_kick;
	atomic_t reset_on_going;
	struct wake_lock trm_wake_lock;
	struct work_struct ccif_work;
	struct timer_list bus_timeout_timer;

	struct dma_pool *tgpd_dmapool;
	struct dma_pool *rgpd_dmapool;
	void __iomem * cldma_ap_base;
	void __iomem * md_rgu_base;
	void __iomem * md_boot_slave_Vector;
	void __iomem * md_boot_slave_Key;
	void __iomem * md_boot_slave_En;
	void __iomem * md_global_con0;
	void __iomem * md_peer_wakeup;
};

#define QUEUE_LEN(a) (sizeof(a)/sizeof(struct md_cd_queue))

struct cldma_tgpd{
	u8	gpd_flags;
	u8	gpd_checksum;
	u16	debug_id;
	u32	next_gpd_ptr;
	u32	data_buff_bd_ptr;
	u16	data_buff_len;
	u8	desc_ext_len;
	u8	non_used;
} __attribute__ ((packed));

struct cldma_rgpd {
	u8	gpd_flags;
	u8	gpd_checksum;
	u16	data_allow_len;
	u32	next_gpd_ptr;
	u32	data_buff_bd_ptr;
	u16	data_buff_len;
	u16	debug_id;
} __attribute__ ((packed));

// runtime data format uses EEMCS's version, NOT the same with legacy CCCI
struct modem_runtime {
    int Prefix;             // "CCIF"
    int Platform_L;         // Hardware Platform String ex: "TK6516E0"
    int Platform_H;
    int DriverVersion;      // 0x00000923 since W09.23
    int BootChannel;        // Channel to ACK AP with boot ready
    int BootingStartID;     // MD is booting. NORMAL_BOOT_ID or META_BOOT_ID 
#if 1 // not using in EEMCS
    int BootAttributes;     // Attributes passing from AP to MD Booting
    int BootReadyID;        // MD response ID if boot successful and ready
    int MdlogShareMemBase;
    int MdlogShareMemSize; 
    int PcmShareMemBase;
    int PcmShareMemSize;
    int UartPortNum;
    int UartShareMemBase[8];
    int UartShareMemSize[8];    
    int FileShareMemBase;
    int FileShareMemSize;
    int RpcShareMemBase;
    int RpcShareMemSize;	
    int PmicShareMemBase;
    int PmicShareMemSize;
    int ExceShareMemBase;
    int ExceShareMemSize;
    int SysShareMemBase;
    int SysShareMemSize;
    int IPCShareMemBase;
    int IPCShareMemSize;
    int CheckSum;
#endif
    int Postfix;            //"CCIF" 
#if 1 // misc region
    unsigned int misc_prefix;	// "MISC"
	unsigned int support_mask;
	unsigned int index;
	unsigned int next;
	unsigned int feature_0_val[4];
	unsigned int feature_1_val[4];
	unsigned int feature_2_val[4];
	unsigned int feature_3_val[4];
	unsigned int feature_4_val[4];
	unsigned int feature_5_val[4];
	unsigned int feature_6_val[4];
	unsigned int feature_7_val[4];
	unsigned int feature_8_val[4];
	unsigned int feature_9_val[4];
	unsigned int feature_10_val[4];
	unsigned int feature_11_val[4];
	unsigned int feature_12_val[4];
	unsigned int feature_13_val[4];
	unsigned int feature_14_val[4];
	unsigned int feature_15_val[4];
	unsigned int reserved_2[3];
	unsigned int misc_postfix;	// "MISC"
#endif
} __attribute__ ((packed));

typedef enum
{
	FEATURE_NOT_EXIST = 0,
	FEATURE_NOT_SUPPORT,
	FEATURE_SUPPORT,
	FEATURE_PARTIALLY_SUPPORT,
} MISC_FEATURE_STATE; 

typedef enum
{
	MISC_DMA_ADDR = 0,
	MISC_32K_LESS,
	MISC_RAND_SEED,
	MISC_MD_COCLK_SETTING,
} MISC_FEATURE_ID;

typedef enum {
    MODE_UNKNOWN = -1,      // -1
    MODE_IDLE,              // 0
    MODE_USB,               // 1
    MODE_SD,                // 2
    MODE_POLLING,           // 3
    MODE_WAITSD,            // 4
} LOGGING_MODE;

typedef enum {
	HIF_EX_INIT = 0, // interrupt
	HIF_EX_ACK, // AP->MD
	HIF_EX_INIT_DONE, // polling
	HIF_EX_CLEARQ_DONE, //interrupt
	HIF_EX_CLEARQ_ACK, // AP->MD
	HIF_EX_ALLQ_RESET, // polling
}HIF_EX_STAGE;

#define MDLOGGER_FILE_PATH "/data/mdl/mdl_config"

static void inline md_cd_queue_struct_init(struct md_cd_queue *queue, struct ccci_modem *md,
	DIRECTION dir, unsigned char index, int bg)
{
	queue->dir = OUT;
	queue->index = index;
	queue->modem = md;
	queue->napi_port = NULL;
	
	queue->tr_ring = NULL;
	queue->tr_done = NULL;
	queue->tx_xmit = NULL;
	queue->free_slot = RING_BUFF_SIZE;
	init_waitqueue_head(&queue->req_wq);
	queue->budget = bg;
	spin_lock_init(&queue->ring_lock);
	queue->debug_id = 0;
}

#endif //__MODEM_CD_H__