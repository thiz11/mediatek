#ifndef __CCCI_IOCTL_H__
#define __CCCI_IOCTL_H__

#include <asm/io.h>
#include "ccci_dfo.h"

//#define EEMCS_IOCTL

#define CCCI_IOC_MAGIC 'C'
// EEMCS == CCCI
#define CCCI_IOC_MD_RESET				_IO(CCCI_IOC_MAGIC, 0) // mdlogger // META // muxreport
#define CCCI_IOC_GET_MD_STATE			_IOR(CCCI_IOC_MAGIC, 1, unsigned int) // audio
#define CCCI_IOC_PCM_BASE_ADDR			_IOR(CCCI_IOC_MAGIC, 2, unsigned int) // audio
#define CCCI_IOC_PCM_LEN				_IOR(CCCI_IOC_MAGIC, 3, unsigned int) // audio
#define CCCI_IOC_FORCE_MD_ASSERT		_IO(CCCI_IOC_MAGIC, 4) // muxreport // mdlogger
#define CCCI_IOC_ALLOC_MD_LOG_MEM		_IO(CCCI_IOC_MAGIC, 5) // mdlogger
#define CCCI_IOC_DO_MD_RST				_IO(CCCI_IOC_MAGIC, 6) // md_init
#define CCCI_IOC_SEND_RUN_TIME_DATA		_IO(CCCI_IOC_MAGIC, 7) // md_init
#define CCCI_IOC_GET_MD_INFO			_IOR(CCCI_IOC_MAGIC, 8, unsigned int) // md_init

// EEMCS only
#ifdef EEMCS_IOCTL
#define CCCI_IOC_BOOT_MD                _IO(CCCI_IOC_MAGIC,  9                 /*mdinit*/
#define CCCI_IOC_GATE_MD                _IO(CCCI_IOC_MAGIC,  10)               /*nouser*/
#define CCCI_IOC_ASSERT_MD              _IO(CCCI_IOC_MAGIC,  11)               /*nouser*/
#define CCCI_IOC_CHECK_STATE            _IOR(CCCI_IOC_MAGIC, 12, unsigned int) /*nouser*/
#define CCCI_IOC_SET_STATE              _IOW(CCCI_IOC_MAGIC, 13, unsigned int) /*nouser*/
#define CCCI_IOC_GET_MD_BOOT_INFO       _IOR(CCCI_IOC_MAGIC, 14, unsigned int) /*mdinit*/
#define CCCI_IOC_START_BOOT             _IO(CCCI_IOC_MAGIC,  15)               /*mdinit*/
#define CCCI_IOC_BOOT_DONE              _IO(CCCI_IOC_MAGIC,  16)               /*mdinit*/
#define CCCI_IOC_REBOOT                 _IO(CCCI_IOC_MAGIC,  17)               /*mdinit*/
#define CCCI_IOC_MD_EXCEPTION           _IO(CCCI_IOC_MAGIC,  18)               /*nouser*/
#define CCCI_IOC_MD_EX_REC_OK           _IO(CCCI_IOC_MAGIC,  19)               /*nouser*/
#define CCCI_IOC_GET_RUNTIME_DATA       _IOR(CCCI_IOC_MAGIC, 20,char [1024])   /*mdinit*/
#define CCCI_IOC_SET_HEADER             _IO(CCCI_IOC_MAGIC,  21)               /*UT    */
#define CCCI_IOC_CLR_HEADER             _IO(CCCI_IOC_MAGIC,  22)               /*UT    */
#define CCCI_IOC_SET_EXCEPTION_DATA     _IOW(CCCI_IOC_MAGIC, 23,char [1024])   /*nouser*/
#define CCCI_IOC_GET_EXCEPTION_LENGTH   _IOR(CCCI_IOC_MAGIC, 24, unsigned int) /*nouser*/
#define CCCI_IOC_GET_EXT_MD_POST_FIX    _IOR(CCCI_IOC_MAGIC, 38,char [32])      /*eemcs_fsd*/
#define CCCI_IOC_SET_BOOT_STATE         _IOW(CCCI_IOC_MAGIC, 39, unsigned int)  /*boot_IT*/
#define CCCI_IOC_GET_BOOT_STATE         _IOR(CCCI_IOC_MAGIC, 40, unsigned int)  /*boot_IT*/
#define CCCI_IOC_WAIT_RDY_RST		    _IO(CCCI_IOC_MAGIC,  45)                /*mdinit*/ /* For MD reset flow must wait for mux/fsd/mdlogger close port */
#define CCCI_IOC_DL_TRAFFIC_CONTROL		_IOW(CCCI_IOC_MAGIC, 46, unsigned int)  /* For MD LOGER to turn on/off downlink traffic */
#endif

// EEMCS != CCCI
#ifdef EEMCS_IOCTL
#define CCCI_IOC_GET_MD_EX_TYPE			_IOR(CCCI_IOC_MAGIC, 25, unsigned int)
#define CCCI_IOC_SEND_STOP_MD_REQUEST	_IO(CCCI_IOC_MAGIC,  26) /*same as enter flight mode*/
#define CCCI_IOC_SEND_START_MD_REQUEST	_IO(CCCI_IOC_MAGIC,  27) /*same as leave flight mode*/
#define CCCI_IOC_DO_STOP_MD				_IO(CCCI_IOC_MAGIC,  28)
#define CCCI_IOC_DO_START_MD			_IO(CCCI_IOC_MAGIC,  29)
#define CCCI_IOC_ENTER_DEEP_FLIGHT		_IO(CCCI_IOC_MAGIC,  30)
#define CCCI_IOC_LEAVE_DEEP_FLIGHT		_IO(CCCI_IOC_MAGIC,  31)
#define CCCI_IOC_POWER_ON_MD			_IO(CCCI_IOC_MAGIC,  32)
#define CCCI_IOC_POWER_OFF_MD			_IO(CCCI_IOC_MAGIC,  33)
#define CCCI_IOC_POWER_ON_MD_REQUEST	_IO(CCCI_IOC_MAGIC,  34)
#define CCCI_IOC_POWER_OFF_MD_REQUEST	_IO(CCCI_IOC_MAGIC,  35)
#define CCCI_IOC_SIM_SWITCH			    _IOW(CCCI_IOC_MAGIC, 36, unsigned int)
#define CCCI_IOC_SEND_BATTERY_INFO      _IO(CCCI_IOC_MAGIC,  37)
#define CCCI_IOC_GET_MD_IMG_EXIST       _IOR(CCCI_IOC_MAGIC, 41, unsigned int[MD_IMG_MAX_CNT])  /* For META Tool world phone feature */
#define CCCI_IOC_GET_MD_TYPE            _IOR(CCCI_IOC_MAGIC, 42, unsigned int)  /* For world phone feature */
#define CCCI_IOC_RELOAD_MD_TYPE			_IO(CCCI_IOC_MAGIC,  43)                /* For world phone feature */
#define CCCI_IOC_STORE_MD_TYPE			_IOW(CCCI_IOC_MAGIC, 44, unsigned int)  /* For world phone feature */
#else
#define CCCI_IOC_GET_MD_EX_TYPE			_IOR(CCCI_IOC_MAGIC, 9, unsigned int) // mdlogger
#define CCCI_IOC_SEND_STOP_MD_REQUEST	_IO(CCCI_IOC_MAGIC, 10) // muxreport                                                     
#define CCCI_IOC_SEND_START_MD_REQUEST	_IO(CCCI_IOC_MAGIC, 11) // muxreport                                                     
#define CCCI_IOC_DO_STOP_MD				_IO(CCCI_IOC_MAGIC, 12) // md_init                                                     
#define CCCI_IOC_DO_START_MD			_IO(CCCI_IOC_MAGIC, 13) // md_init                                                      
#define CCCI_IOC_ENTER_DEEP_FLIGHT		_IO(CCCI_IOC_MAGIC, 14) // RILD
#define CCCI_IOC_LEAVE_DEEP_FLIGHT		_IO(CCCI_IOC_MAGIC, 15) // RILD
#define CCCI_IOC_POWER_ON_MD			_IO(CCCI_IOC_MAGIC, 16) // md_init                                                       
#define CCCI_IOC_POWER_OFF_MD			_IO(CCCI_IOC_MAGIC, 17) // md_init                                                       
#define CCCI_IOC_POWER_ON_MD_REQUEST	_IO(CCCI_IOC_MAGIC, 18)                                                      
#define CCCI_IOC_POWER_OFF_MD_REQUEST	_IO(CCCI_IOC_MAGIC, 19)                                                      
#define CCCI_IOC_SIM_SWITCH			    _IOW(CCCI_IOC_MAGIC, 20, unsigned int) // RILD                                                     
#define CCCI_IOC_SEND_BATTERY_INFO      _IO(CCCI_IOC_MAGIC, 21) // md_init 
#define CCCI_IOC_RELOAD_MD_TYPE			_IO(CCCI_IOC_MAGIC, 25) // META // md_init // muxreport
#define CCCI_IOC_GET_MD_IMG_EXIST		_IOR(CCCI_IOC_MAGIC, 30, unsigned int[MAX_IMG_NUM])
#define CCCI_IOC_GET_MD_TYPE			_IOR(CCCI_IOC_MAGIC, 31, unsigned int) // RILD      
#define CCCI_IOC_STORE_MD_TYPE			_IOW(CCCI_IOC_MAGIC, 32, unsigned int) // RILD
#endif

// CCCI only
#ifndef EEMCS_IOCTL
#define CCCI_IOC_SIM_SWITCH_TYPE		_IOR(CCCI_IOC_MAGIC, 22, unsigned int) // for smart sim switch
#define CCCI_IOC_STORE_SIM_MODE			_IOW(CCCI_IOC_MAGIC, 23, unsigned int) // for smart sim switch
#define CCCI_IOC_GET_SIM_MODE			_IOR(CCCI_IOC_MAGIC, 24, unsigned int) // for smart sim switch
#define CCCI_IOC_GET_SIM_TYPE			_IOR(CCCI_IOC_MAGIC, 26, unsigned int) // for regional phone boot animation                          
#define CCCI_IOC_ENABLE_GET_SIM_TYPE	_IOW(CCCI_IOC_MAGIC, 27, unsigned int) // for regional phone boot animation
#define CCCI_IOC_SEND_ICUSB_NOTIFY      _IOW(CCCI_IOC_MAGIC, 28, unsigned int) // icusbd
#define CCCI_IOC_SET_MD_IMG_EXIST		_IOW(CCCI_IOC_MAGIC, 29, unsigned int[MAX_IMG_NUM]) // md_init
#define CCCI_IOC_GET_MD_TYPE_SAVING		_IOR(CCCI_IOC_MAGIC, 33, unsigned int) // META
#endif

// merge from EEMCS to CCCI
#define CCCI_IOC_GET_EXT_MD_POST_FIX    _IOR(CCCI_IOC_MAGIC, 38,char [32]) // eemcs_fsd // mdlogger


#define CCCI_IPC_MAGIC 'P'
// EEMCS == CCCI
#define CCCI_IPC_RESET_RECV	_IO(CCCI_IPC_MAGIC,0)
#define CCCI_IPC_RESET_SEND	_IO(CCCI_IPC_MAGIC,1)
#define CCCI_IPC_WAIT_MD_READY	_IO(CCCI_IPC_MAGIC,2)

#define CCCI_FS_IOC_MAGIC 'K'
// CCCI only
#define CCCI_FS_IOCTL_GET_INDEX _IO(CCCI_FS_IOC_MAGIC, 1)
#define CCCI_FS_IOCTL_SEND      _IOR(CCCI_FS_IOC_MAGIC, 2, unsigned int)

#endif //__CCCI_IOCTL_H__