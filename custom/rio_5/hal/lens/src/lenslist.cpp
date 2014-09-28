
#include <utils/Log.h>
#include <utils/Errors.h>
#include <fcntl.h>
#include <math.h>

#include "MediaHal.h"

//#include "lens_custom_cfg.h"
//#include "msdk_lens_exp.h"
#include "camera_custom_lens.h"
//#include "lens.h"
//nclude "image_sensor.h"
#include "kd_imgsensor.h"

extern PFUNC_GETLENSDEFAULT pDummy_getDefaultData;

#if defined(SENSORDRIVE)
extern PFUNC_GETLENSDEFAULT pSensorDrive_getDefaultData;
#endif

#if defined(FM50AF)
extern PFUNC_GETLENSDEFAULT pFM50AF_getDefaultData;
#endif

#if defined(BU6424AF)
extern PFUNC_GETLENSDEFAULT pBU6424AF_getDefaultData;
#endif
//begin zhaozhen.wu@tcl.com add for ov5648 compatibility
#if defined(BU6424QTAF)
extern PFUNC_GETLENSDEFAULT pBU6424QTAF_getDefaultData;
#endif
#if defined(BU6424STAF)
extern PFUNC_GETLENSDEFAULT pBU6424STAF_getDefaultData;
#endif
//end

MSDK_LENS_INIT_FUNCTION_STRUCT LensList[MAX_NUM_OF_SUPPORT_LENS] =
{
	{DUMMY_SENSOR_ID, DUMMY_LENS_ID, "Dummy", pDummy_getDefaultData},

#if defined(SENSORDRIVE)
    //	{DUMMY_SENSOR_ID, SENSOR_DRIVE_LENS_ID, "kd_camera_hw", pSensorDrive_getDefaultData},	

    //  for backup lens, need assign correct SensorID
    {OV3640_SENSOR_ID, SENSOR_DRIVE_LENS_ID, "kd_camera_hw", pSensorDrive_getDefaultData},
#endif

#if defined(FM50AF)
	{S5K3H7Y_SENSOR_ID, FM50AF_LENS_ID, "FM50AF", pFM50AF_getDefaultData},
#endif

#if defined(BU6424AF)
	{OV5648MIPI_SENSOR_ID, BU6424AF_LENS_ID, "BU6424AF", pBU6424AF_getDefaultData},
#endif
//begin zhaozhen.wu@tcl.com add for ov5648 compatibility
#if defined(BU6424QTAF)
		{OV5648QTMIPI_SENSOR_ID, BU6424QTAF_LENS_ID, "BU6424QTAF", pBU6424QTAF_getDefaultData},
#endif
#if defined(BU6424STAF)
		{OV5648STMIPI_SENSOR_ID, BU6424STAF_LENS_ID, "BU6424STAF", pBU6424STAF_getDefaultData},
#endif
//end

    //  for new added lens, need assign correct SensorID

};

UINT32 GetLensInitFuncList(PMSDK_LENS_INIT_FUNCTION_STRUCT pLensList)
{
    memcpy(pLensList, &LensList[0], sizeof(MSDK_LENS_INIT_FUNCTION_STRUCT)* MAX_NUM_OF_SUPPORT_LENS);
    return MHAL_NO_ERROR;
} // GetLensInitFuncList()






