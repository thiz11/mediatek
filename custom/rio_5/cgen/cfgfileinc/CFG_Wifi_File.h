




#ifndef _CFG_WIFI_FILE_H
#define _CFG_WIFI_FILE_H

// the record structure define of wifi nvram file



typedef signed char             INT_8, *PINT_8, **PPINT_8;
typedef unsigned char           UINT_8, *PUINT_8, **PPUINT_8, *P_UINT_8;
typedef unsigned short          UINT_16, *PUINT_16, **PPUINT_16;
typedef unsigned long           ULONG, UINT_32, *PUINT_32, **PPUINT_32;


// duplicated from nic_cmd_event.h to avoid header dependency
typedef struct _TX_PWR_PARAM_T {
    INT_8       cTxPwr2G4Cck;		/* signed, in unit of 0.5dBm */
    INT_8       acReserved[3];      /* acReserved[0]:cTxPwr2G4Dsss for MT6628*/
    INT_8       cTxPwr2G4OFDM_BPSK;
    INT_8       cTxPwr2G4OFDM_QPSK;
    INT_8       cTxPwr2G4OFDM_16QAM;
    INT_8       cTxPwr2G4OFDM_Reserved;
    INT_8       cTxPwr2G4OFDM_48Mbps;
    INT_8       cTxPwr2G4OFDM_54Mbps;

    INT_8       cTxPwr2G4HT20_BPSK;
    INT_8       cTxPwr2G4HT20_QPSK;
    INT_8       cTxPwr2G4HT20_16QAM;
    INT_8       cTxPwr2G4HT20_MCS5;
    INT_8       cTxPwr2G4HT20_MCS6;
    INT_8       cTxPwr2G4HT20_MCS7;

    INT_8       cTxPwr2G4HT40_BPSK;
    INT_8       cTxPwr2G4HT40_QPSK;
    INT_8       cTxPwr2G4HT40_16QAM;
    INT_8       cTxPwr2G4HT40_MCS5;
    INT_8       cTxPwr2G4HT40_MCS6;
    INT_8       cTxPwr2G4HT40_MCS7;

    INT_8       cTxPwr5GOFDM_BPSK;
    INT_8       cTxPwr5GOFDM_QPSK;
    INT_8       cTxPwr5GOFDM_16QAM;
    INT_8       cTxPwr5GOFDM_Reserved;
    INT_8       cTxPwr5GOFDM_48Mbps;
    INT_8       cTxPwr5GOFDM_54Mbps;

    INT_8       cTxPwr5GHT20_BPSK;
    INT_8       cTxPwr5GHT20_QPSK;
    INT_8       cTxPwr5GHT20_16QAM;
    INT_8       cTxPwr5GHT20_MCS5;
    INT_8       cTxPwr5GHT20_MCS6;
    INT_8       cTxPwr5GHT20_MCS7;

    INT_8       cTxPwr5GHT40_BPSK;
    INT_8       cTxPwr5GHT40_QPSK;
    INT_8       cTxPwr5GHT40_16QAM;
    INT_8       cTxPwr5GHT40_MCS5;
    INT_8       cTxPwr5GHT40_MCS6;
    INT_8       cTxPwr5GHT40_MCS7;
} TX_PWR_PARAM_T, *P_TX_PWR_PARAM_T;

typedef struct _PWR_5G_OFFSET_T {
    INT_8       cOffsetBand0;       /* 4.915-4.980G */
    INT_8       cOffsetBand1;       /* 5.000-5.080G */
    INT_8       cOffsetBand2;       /* 5.160-5.180G */
    INT_8       cOffsetBand3;       /* 5.200-5.280G */
    INT_8       cOffsetBand4;       /* 5.300-5.340G */
    INT_8       cOffsetBand5;       /* 5.500-5.580G */
    INT_8       cOffsetBand6;       /* 5.600-5.680G */
    INT_8       cOffsetBand7;       /* 5.700-5.825G */
} PWR_5G_OFFSET_T, *P_PWR_5G_OFFSET_T;

typedef struct _PWR_PARAM_T {
    UINT_32     au4Data[28];
    UINT_32     u4RefValue1;
    UINT_32     u4RefValue2;
} PWR_PARAM_T, *P_PWR_PARAM_T;

typedef struct _MT6620_CFG_PARAM_STRUCT {
    /* 256 bytes of MP data */
    UINT_16             u2Part1OwnVersion;
    UINT_16             u2Part1PeerVersion;
    UINT_8              aucMacAddress[6];
    UINT_8              aucCountryCode[2];
    TX_PWR_PARAM_T      rTxPwr;
    UINT_8              aucEFUSE[144];
    UINT_8              ucTxPwrValid;
    UINT_8              ucSupport5GBand;
    UINT_8              fg2G4BandEdgePwrUsed;
    INT_8               cBandEdgeMaxPwrCCK;
    INT_8               cBandEdgeMaxPwrOFDM20; 
    INT_8               cBandEdgeMaxPwrOFDM40;

    UINT_8              ucRegChannelListMap;
    UINT_8              ucRegChannelListIndex;
    UINT_8              aucRegSubbandInfo[36];

    UINT_8              aucReserved2[256-240];

    /* 256 bytes of function data */
    UINT_16             u2Part2OwnVersion;
    UINT_16             u2Part2PeerVersion;
    UINT_8              uc2G4BwFixed20M;
    UINT_8              uc5GBwFixed20M;
    UINT_8              ucEnable5GBand;
    UINT_8              aucPreTailReserved;
    UINT_8              aucTailReserved[256-8];
} MT6620_CFG_PARAM_STRUCT, *P_MT6620_CFG_PARAM_STRUCT, 
    WIFI_CFG_PARAM_STRUCT, *P_WIFI_CFG_PARAM_STRUCT;

typedef struct _WIFI_CUSTOM_PARAM_STRUCT
{
    UINT_32             u4Resv;         /* Reserved */
} WIFI_CUSTOM_PARAM_STRUCT;




#define CFG_FILE_WIFI_REC_SIZE           sizeof(WIFI_CFG_PARAM_STRUCT)
#define CFG_FILE_WIFI_REC_TOTAL		       1

#define CFG_FILE_WIFI_CUSTOM_REC_SIZE    sizeof(WIFI_CUSTOM_PARAM_STRUCT)
#define CFG_FILE_WIFI_CUSTOM_REC_TOTAL   1

	


#endif


