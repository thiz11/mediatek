

#ifndef BWCS_CUSTOM_H
#define BWCS_CUSTOM_H


#define RT_RSSI_TH_BT            73
#define RT_RSSI_TH_WIFI1         73
#define RT_RSSI_TH_WIFI2         73

#define NRT_RSSI_TH_BT           73
#define NRT_RSSI_TH_WIFI1        73
#define NRT_RSSI_TH_WIFI2        73
#define ANT_PATH_COMP            10
#define ANT_SWITCH_PROT_TIME     10
#define BT_RX_RANGE              {0xC4, 0xE2}
#if defined (MTK_MT6611)
#define WIFI_TX_FLOW_CTRL        {0x0E00, 0x0001}
#define BT_TX_PWR_WIFI_OFF       0x7
#define BT_TX_PWR_SCO            0x4
#define BT_TX_PWR_ACL            0x4
#elif defined (MTK_MT6612)
#define WIFI_TX_FLOW_CTRL        {0x0E00, 0x0001}
#define BT_TX_PWR_WIFI_OFF       0x7
#define BT_TX_PWR_SCO            0x4
#define BT_TX_PWR_ACL            0x3
#elif defined (MTK_MT6616)
#define WIFI_TX_FLOW_CTRL        {0x1100, 0x0001}
#define BT_TX_PWR_WIFI_OFF       0x7
#define BT_TX_PWR_SCO            0x4
#define BT_TX_PWR_ACL            0x3
#else
#define WIFI_TX_FLOW_CTRL        {0x1100, 0x0001}
#define BT_TX_PWR_WIFI_OFF       0x7
#define BT_TX_PWR_SCO            0x4
#define BT_TX_PWR_ACL            0x4
#endif
#define RESERVED                 {0x00, 0x00, 0x00, 0x00, 0x00}
#endif 
