
#include <utils/Log.h>
#include <fcntl.h>
#include <math.h>

#include "camera_custom_nvram.h"
#include "camera_custom_sensor.h"
#include "image_sensor.h"
#include "kd_imgsensor_define.h"
#include "camera_AE_PLineTable_ov5648mipiraw.h"
#include "camera_info_ov5648mipiraw.h"
#include "camera_custom_AEPlinetable.h"
#include "camera_custom_tsf_tbl.h"
const NVRAM_CAMERA_ISP_PARAM_STRUCT CAMERA_ISP_DEFAULT_VALUE =
{{
    //Version
    Version: NVRAM_CAMERA_PARA_FILE_VERSION,

    //SensorId
    SensorId: SENSOR_ID,
    ISPComm:{
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    	}
    },
    ISPPca: {
        #include INCLUDE_FILENAME_ISP_PCA_PARAM
    },
    ISPRegs:{
        #include INCLUDE_FILENAME_ISP_REGS_PARAM
    },
    ISPMfbMixer:{{
        {//00: MFB mixer for ISO 100
            0x00000000, 0x00000000
        },
        {//01: MFB mixer for ISO 200
            0x00000000, 0x00000000
        },
        {//02: MFB mixer for ISO 400
            0x00000000, 0x00000000
        },
        {//03: MFB mixer for ISO 800
            0x00000000, 0x00000000
        },
        {//04: MFB mixer for ISO 1600
            0x00000000, 0x00000000
        },
        {//05: MFB mixer for ISO 2400
            0x00000000, 0x00000000
        },
        {//06: MFB mixer for ISO 3200
            0x00000000, 0x00000000
        }
    }},
    ISPCcmPoly22:{
        69567,    // i4R_AVG
        13536,    // i4R_STD
        82300,    // i4B_AVG
        23341,    // i4B_STD
        {  // i4P00[9]
            4913333, -1530000, -826667, -643333, 3930000, -713333, 186667, -1320000, 3683333
        },
        {  // i4P10[9]
            1046787, -1034821, -27635, 21740, 81997, -96381, 14712, -253774, 228029
        },
        {  // i4P01[9]
            554294, -925706, 366373, -60555, -333880, 411811, 34752, -599472, 538656
        },
        {  // i4P20[9]
            0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {  // i4P11[9]
            0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {  // i4P02[9]
            0, 0, 0, 0, 0, 0, 0, 0, 0
        }
    }
}};

const NVRAM_CAMERA_3A_STRUCT CAMERA_3A_NVRAM_DEFAULT_VALUE =
{
    NVRAM_CAMERA_3A_FILE_VERSION, // u4Version
    SENSOR_ID, // SensorId

    // AE NVRAM
    {
        // rDevicesInfo
        {
            1136,    // u4MinGain, 1024 base = 1x
            16384,    // u4MaxGain, 16x
            51,    // u4MiniISOGain, ISOxx  
            64,    // u4GainStepUnit, 1x/8 
            35,    // u4PreExpUnit 
            30,    // u4PreMaxFrameRate
            35,    // u4VideoExpUnit  
            30,    // u4VideoMaxFrameRate 
            1024,    // u4Video2PreRatio, 1024 base = 1x 
            35,    // u4CapExpUnit 
            15,    // u4CapMaxFrameRate
            1024,    // u4Cap2PreRatio, 1024 base = 1x
            28,    // u4LensFno, Fno = 2.8
            350    // u4FocusLength_100x
        },
        // rHistConfig
        {
            2,   // u4HistHighThres
            40,  // u4HistLowThres
            2,   // u4MostBrightRatio
            1,   // u4MostDarkRatio
            160, // u4CentralHighBound
            20,  // u4CentralLowBound
            {240, 230, 220, 210, 200}, // u4OverExpThres[AE_CCT_STRENGTH_NUM]
            {86, 108, 128, 148, 170},  // u4HistStretchThres[AE_CCT_STRENGTH_NUM]
            {18, 22, 26, 30, 34}       // u4BlackLightThres[AE_CCT_STRENGTH_NUM]
        },
        // rCCTConfig
        {
            TRUE,            // bEnableBlackLight
            TRUE,            // bEnableHistStretch
            FALSE,           // bEnableAntiOverExposure
            TRUE,            // bEnableTimeLPF
            FALSE,    // bEnableCaptureThres
            TRUE,            // bEnableVideoThres
            TRUE,            // bEnableStrobeThres
            47,                // u4AETarget
            47,                // u4StrobeAETarget

            50,                // u4InitIndex
            4,                 // u4BackLightWeight
            32,                // u4HistStretchWeight
            4,                 // u4AntiOverExpWeight
            2,                 // u4BlackLightStrengthIndex
            2,                 // u4HistStretchStrengthIndex
            2,                 // u4AntiOverExpStrengthIndex
            2,                 // u4TimeLPFStrengthIndex
            {1, 3, 5, 7, 8}, // u4LPFConvergeTable[AE_CCT_STRENGTH_NUM]
            90,                // u4InDoorEV = 9.0, 10 base
            -10,               // i4BVOffset delta BV = -2.3
            32,    // u4PreviewFlareOffset
            32,    // u4CaptureFlareOffset
            5,                 // u4CaptureFlareThres
            4,                 // u4VideoFlareOffset
            5,                 // u4VideoFlareThres
            2,                 // u4StrobeFlareOffset
            2,                 // u4StrobeFlareThres
            8,                 // u4PrvMaxFlareThres
            0,                 // u4PrvMinFlareThres
            8,                 // u4VideoMaxFlareThres
            0,                 // u4VideoMinFlareThres            
            18,                // u4FlatnessThres              // 10 base for flatness condition.
            75                 // u4FlatnessStrength
         }
    },

    // AWB NVRAM
    {
    	// AWB calibration data
    	{
    		// rUnitGain (unit gain: 1.0 = 512)
    		{
    			0,	// i4R
    			0,	// i4G
    			0	// i4B
    		},
    		// rGoldenGain (golden sample gain: 1.0 = 512)
    		{
	            0,	// i4R
	            0,	// i4G
	            0	// i4B
            },
    		// rTuningUnitGain (Tuning sample unit gain: 1.0 = 512)
    		{
	            0,	// i4R
	            0,	// i4G
	            0	// i4B
            },
            // rD65Gain (D65 WB gain: 1.0 = 512)
            {
                782,    // i4R
                512,    // i4G
                619    // i4B
            }
        },
        // Original XY coordinate of AWB light source
        {
           // Strobe
            {
                86,    // i4X
                -226    // i4Y
            },
            // Horizon
            {
                -439,    // i4X
                -293    // i4Y
            },
            // A
            {
                -332,    // i4X
                -295    // i4Y
            },
            // TL84
            {
                -161,    // i4X
                -320    // i4Y
            },
            // CWF
            {
                -108,    // i4X
                -393    // i4Y
            },
            // DNP
            {
                -19,    // i4X
                -266    // i4Y
            },
            // D65
            {
                86,    // i4X
                -226    // i4Y
            },
            // DF
            {
                86,    // i4X
                -226    // i4Y
            }
    	},
    	// Rotated XY coordinate of AWB light source
    	{
            // Strobe
            {
                46,    // i4X
                -237    // i4Y
            },
            // Horizon
            {
                -482,    // i4X
                -213    // i4Y
            },
            // A
            {
                -378,    // i4X
                -233    // i4Y
            },
            // TL84
            {
                -213,    // i4X
                -287    // i4Y
            },
            // CWF
            {
                -174,    // i4X
                -368    // i4Y
            },
            // DNP
            {
                -64,    // i4X
                -259    // i4Y
            },
            // D65
            {
                46,    // i4X
                -237    // i4Y
            },
		// DF
		{
                46,    // i4X
                -237    // i4Y
    		}
    	},
	// AWB gain of AWB light source
	{
		// Strobe
            {
                782,    // i4R
                512,    // i4G
                619    // i4B
            },
            // Horizon 
            {
                512,    // i4R
                624,    // i4G
                1681    // i4B
            },
            // A 
            {
                512,    // i4R
                538,    // i4G
                1257    // i4B
            },
            // TL84 
            {
                635,    // i4R
                512,    // i4G
                982    // i4B
            },
            // CWF 
            {
                753,    // i4R
                512,    // i4G
                1010    // i4B
            },
            // DNP 
            {
                715,    // i4R
                512,    // i4G
                753    // i4B
            },
            // D65 
            {
                782,    // i4R
                512,    // i4G
                619    // i4B
            },
            // DF 
            {
                782,    // i4R
                512,    // i4G
                619    // i4B
		}
	},
    	// Rotation matrix parameter
    	{
            10,    // i4RotationAngle
            252,    // i4Cos
            44    // i4Sin
        },
        // Daylight locus parameter
        {
            -177,    // i4SlopeNumerator
            128    // i4SlopeDenominator
        },
        // AWB light area
        {
            // Strobe:FIXME
            {
            71,    // i4RightBound
            -263,    // i4LeftBound
            -418,    // i4UpperBound
            -500    // i4LowerBound
            },
            // Tungsten
            {
            -263,    // i4RightBound
            -913,    // i4LeftBound
            -173,    // i4UpperBound
            -273    // i4LowerBound
            },
            // Warm fluorescent
            {
            -263,    // i4RightBound
            -913,    // i4LeftBound
            -273,    // i4UpperBound
            -393    // i4LowerBound
            },
            // Fluorescent
            {
            -114,    // i4RightBound
            -263,    // i4LeftBound
            -165,    // i4UpperBound
            -327    // i4LowerBound
            },
            // CWF
            {
            -114,    // i4RightBound
            -263,    // i4LeftBound
            -327,    // i4UpperBound
            -418    // i4LowerBound
            },
            // Daylight
            {
            71,    // i4RightBound
            -114,    // i4LeftBound
            -157,    // i4UpperBound
            -418    // i4LowerBound
            },
            // Shade
            {
            431,    // i4RightBound
            71,    // i4LeftBound
            -187,    // i4UpperBound
            -317    // i4LowerBound
            },
            // Daylight Fluorescent
            {
            0,    // i4RightBound
            0,    // i4LeftBound
            0,    // i4UpperBound
            0    // i4LowerBound
            }
        },
        // PWB light area
        {
            // Reference area
            {
            431,    // i4RightBound
            -913,    // i4LeftBound
            0,    // i4UpperBound
            -418    // i4LowerBound
            },
            // Daylight
            {
            96,    // i4RightBound
            -114,    // i4LeftBound
            -157,    // i4UpperBound
            -397    // i4LowerBound
            },
            // Cloudy daylight
            {
            196,    // i4RightBound
            21,    // i4LeftBound
            -157,    // i4UpperBound
            -397    // i4LowerBound
            },
            // Shade
            {
            296,    // i4RightBound
            21,    // i4LeftBound
            -157,    // i4UpperBound
            -397    // i4LowerBound
            },
            // Twilight
            {
            -114,    // i4RightBound
            -274,    // i4LeftBound
            -157,    // i4UpperBound
            -397    // i4LowerBound
            },
            // Fluorescent
            {
            96,    // i4RightBound
            -313,    // i4LeftBound
            -187,    // i4UpperBound
            -418    // i4LowerBound
            },
            // Warm fluorescent
            {
            -278,    // i4RightBound
            -478,    // i4LeftBound
            -187,    // i4UpperBound
            -418    // i4LowerBound
            },
            // Incandescent
            {
            -278,    // i4RightBound
            -478,    // i4LeftBound
            -157,    // i4UpperBound
            -397    // i4LowerBound
            },
            // Gray World
            {
            5000,    // i4RightBound
            -5000,    // i4LeftBound
            5000,    // i4UpperBound
            -5000    // i4LowerBound
            }
        },
        // PWB default gain	
        {
            // Daylight
            {
            783,    // i4R
            512,    // i4G
            705    // i4B
            },
            // Cloudy daylight
            {
            891,    // i4R
            512,    // i4G
            586    // i4B
            },
            // Shade
            {
            941,    // i4R
            512,    // i4G
            542    // i4B
            },
            // Twilight
            {
            638,    // i4R
            512,    // i4G
            942    // i4B
            },
            // Fluorescent
            {
            730,    // i4R
            512,    // i4G
            847    // i4B
            },
            // Warm fluorescent
            {
            542,    // i4R
            512,    // i4G
            1292    // i4B
            },
            // Incandescent
            {
            521,    // i4R
            512,    // i4G
            1256    // i4B
            },
            // Gray World
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            }
        },
        // AWB preference color	
        {
            // Tungsten
            {
            50,    // i4SliderValue
            4270    // i4OffsetThr
            },
            // Warm fluorescent	
            {
            50,    // i4SliderValue
            4270    // i4OffsetThr
            },
            // Shade
            {
            50,    // i4SliderValue
            345    // i4OffsetThr
            },
            // Daylight WB gain
            {
            692,    // i4R
            512,    // i4G
            735    // i4B
            },
            // Preference gain: strobe
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: tungsten
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: warm fluorescent
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: fluorescent
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: CWF
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: daylight
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: shade
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: daylight fluorescent
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            }
        },
        {// CCT estimation
            {// CCT
                2300,    // i4CCT[0]
                2850,    // i4CCT[1]
                4100,    // i4CCT[2]
                5100,    // i4CCT[3]
                6500    // i4CCT[4]
            },
            {// Rotated X coordinate
                -528,    // i4RotatedXCoordinate[0]
                -424,    // i4RotatedXCoordinate[1]
                -259,    // i4RotatedXCoordinate[2]
                -110,    // i4RotatedXCoordinate[3]
                0    // i4RotatedXCoordinate[4]
    		}
    	}
    },
	{0}
};
 
#include INCLUDE_FILENAME_ISP_LSC_PARAM
//};  //  namespace

const CAMERA_TSF_TBL_STRUCT CAMERA_TSF_DEFAULT_VALUE =
{
    #include INCLUDE_FILENAME_TSF_PARA
    #include INCLUDE_FILENAME_TSF_DATA
};


typedef NSFeature::RAWSensorInfo<SENSOR_ID> SensorInfoSingleton_T;


namespace NSFeature {
template <>
UINT32
SensorInfoSingleton_T::
impGetDefaultData(CAMERA_DATA_TYPE_ENUM const CameraDataType, VOID*const pDataBuf, UINT32 const size) const
{
    UINT32 dataSize[CAMERA_DATA_TYPE_NUM] = {sizeof(NVRAM_CAMERA_ISP_PARAM_STRUCT),
                                             sizeof(NVRAM_CAMERA_3A_STRUCT),
                                             sizeof(NVRAM_CAMERA_SHADING_STRUCT),
                                             sizeof(NVRAM_LENS_PARA_STRUCT),
                                             sizeof(AE_PLINETABLE_T),
                                              0,
                                             sizeof(CAMERA_TSF_TBL_STRUCT)};
                                            
    if (CameraDataType > CAMERA_DATA_TSF_TABLE || NULL == pDataBuf || (size < dataSize[CameraDataType]))
    {
        return 1;
    }

    switch(CameraDataType)
    {
        case CAMERA_NVRAM_DATA_ISP:
            memcpy(pDataBuf,&CAMERA_ISP_DEFAULT_VALUE,sizeof(NVRAM_CAMERA_ISP_PARAM_STRUCT));
            break;
        case CAMERA_NVRAM_DATA_3A:
            memcpy(pDataBuf,&CAMERA_3A_NVRAM_DEFAULT_VALUE,sizeof(NVRAM_CAMERA_3A_STRUCT));
            break;
        case CAMERA_NVRAM_DATA_SHADING:
            memcpy(pDataBuf,&CAMERA_SHADING_DEFAULT_VALUE,sizeof(NVRAM_CAMERA_SHADING_STRUCT));
            break;
        case CAMERA_DATA_AE_PLINETABLE:
            memcpy(pDataBuf,&g_PlineTableMapping,sizeof(AE_PLINETABLE_T));
            break;
		case CAMERA_DATA_TSF_TABLE:
            memcpy(pDataBuf,&CAMERA_TSF_DEFAULT_VALUE,sizeof(CAMERA_TSF_TBL_STRUCT));
            break;
        default:
            break;
    }
    return 0;
}};  //  NSFeature


