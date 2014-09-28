#ifndef _CFG_SETTING_IMGSENSOR_H_
#define _CFG_SETTING_IMGSENSOR_H_


SensorOrientation_T const&
getSensorOrientation()
{
    static SensorOrientation_T const inst = {
        u4Degree_0  : 90,   //  main sensor in degree (0, 90, 180, 270)
        u4Degree_1  : 0,    //  sub  sensor in degree (0, 90, 180, 270)
        u4Degree_2  : 90,   //  main2 sensor in degree (0, 90, 180, 270) 
    };
    return inst;
}


MBOOL isRetFakeSubOrientation()  
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

#endif //  _CFG_SETTING_IMGSENSOR_H_

