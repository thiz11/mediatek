




#ifndef _CFG_GPS_FILE_H
#define _CFG_GPS_FILE_H


// the record structure define of bt nvram file
typedef struct
{
    char dsp_dev[20];
    unsigned char gps_if_type;
    
    unsigned int gps_tcxo_hz;
    unsigned int gps_tcxo_ppb;
    unsigned char gps_tcxo_type;
    
    unsigned char gps_lna_mode;
    
    unsigned char gps_sbas_mode;
    unsigned int C0;
    unsigned int C1;
    unsigned int initU;
    unsigned int lastU;
} ap_nvram_gps_config_struct;


//the record size and number of bt nvram file
#define CFG_FILE_GPS_CONFIG_SIZE    sizeof(ap_nvram_gps_config_struct)
#define CFG_FILE_GPS_CONFIG_TOTAL   1

#endif /* _CFG_GPS_FILE_H */
