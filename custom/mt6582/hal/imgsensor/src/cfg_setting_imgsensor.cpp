//#ifndef _CFG_SETTING_IMGSENSOR_H_
//#define _CFG_SETTING_IMGSENSOR_H_
#include "camera_custom_imgsensor_cfg.h"
using namespace NSCamCustomSensor;

namespace NSCamCustomSensor {
SensorOrientation_T const&
getSensorOrientation()
{
    static SensorOrientation_T const inst = {
        u4Degree_0  : 90,   //  main sensor in degree (0, 90, 180, 270)
        u4Degree_1  : 270,    //  sub  sensor in degree (0, 90, 180, 270)
        u4Degree_2  : 90,   //  main2 sensor in degree (0, 90, 180, 270) 
    };
    return inst;

}


MBOOL isRetFakeSubOrientation()  
{
	return MFALSE;
}

MBOOL isRetFakeMainOrientation()  
{
	return MFALSE;
}

MBOOL isRetFakeMain2Orientation()  
{
	return MFALSE;
}


MINT32
getSensorInputDataBitOrder(EDevId const eDevId)
{
    switch  (eDevId)
    {
    case eDevId_ImgSensor0:
        return  0;
    case eDevId_ImgSensor1:
        return  0;       
    case eDevId_ImgSensor2:
        return  0;        
    default:
        break;
    }
    return  -1;
}


MINT32
getSensorPadPclkInv(EDevId const eDevId)
{
    switch  (eDevId)
    {
    case eDevId_ImgSensor0:
        return  0;
    case eDevId_ImgSensor1:
        return  0;      
    case eDevId_ImgSensor2:
        return  0;        
    default:
        break;
    }
    return  -1;
}

MINT32  
getSensorFacingDirection(EDevId const eDevId)
{
    switch  (eDevId)
    {
    case eDevId_ImgSensor0:
        return  0;
    case eDevId_ImgSensor1:
        return  1;
    case eDevId_ImgSensor2:
        return  0;
    default:
        break;
    }
    return  -1;
}
SensorViewAngle_T const&
getSensorViewAngle()
{
    static SensorViewAngle_T const inst = {
        MainSensorHorFOV  : 63,   
        MainSensorVerFOV  : 49,    
        SubSensorHorFOV  : 60,   
        SubSensorVerFOV  : 40,
        Main2SensorHorFOV  : 0,   //not support
        Main2SensorVerFOV  : 0,
    };
    return inst;

}

};

//#endif //  _CFG_SETTING_IMGSENSOR_H_

