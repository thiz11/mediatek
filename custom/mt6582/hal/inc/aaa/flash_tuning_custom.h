

#ifndef __FLASH_TUNING_CUSTOM_H__
#define __FLASH_TUNING_CUSTOM_H__



int getDefaultStrobeNVRam_main2(void* data, int* ret_size);
int getDefaultStrobeNVRam_sub2(void* data, int* ret_size);
int getDefaultStrobeNVRam(int sensorType, void* data, int* ret_size);

FLASH_PROJECT_PARA& cust_getFlashProjectPara_main2(int AEMode, NVRAM_CAMERA_STROBE_STRUCT* nvrame);
FLASH_PROJECT_PARA& cust_getFlashProjectPara_sub2(int AEMode, NVRAM_CAMERA_STROBE_STRUCT* nvrame);
FLASH_PROJECT_PARA& cust_getFlashProjectPara(int AEMode, NVRAM_CAMERA_STROBE_STRUCT* nvrame);
int cust_isNeedAFLamp(int flashMode, int afLampMode, int isBvHigherTriger);


int cust_getFlashModeStyle(int sensorType, int flashMode);
int cust_getVideoFlashModeStyle(int sensorType, int flashMode);
void cust_getEvCompPara(int& maxEvTar10Bit, int& indNum, float*& evIndTab, float*& evTab, float*& evLevel);

int cust_isSubFlashSupport();

FLASH_PROJECT_PARA& cust_getFlashProjectPara_sub(int AEMode, NVRAM_CAMERA_STROBE_STRUCT* nvrame);

enum
{
    e_PrecapAf_None,
    e_PrecapAf_BeforePreflash,
    e_PrecapAf_AfterPreflash,
};
int cust_getPrecapAfMode();

int cust_isNeedDoPrecapAF_v2(int isFocused, int flashMode, int afLampMode, int isBvLowerTriger);

void cust_setFlashPartId_main(int id);
void cust_setFlashPartId_sub(int id);

int cust_getDefaultStrobeNVRam_V2(int sensorType, void* data, int* ret_size);
FLASH_PROJECT_PARA& cust_getFlashProjectPara_V2(int sensorDev, int AEMode, NVRAM_CAMERA_STROBE_STRUCT* nvrame);


#endif //#ifndef __FLASH_TUNING_CUSTOM_H__

