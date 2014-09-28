

#include "camera_custom_types.h"
#include "tsf_tuning_custom.h"
#include "TSF_data.h"
#include "TSF_para.h"

MVOID *
getTSFTrainingData(void)
{
    return tsf_data;
}

MVOID *
getTSFTuningData(void)
{

    return TSF_para;
}

MUINT32
isEnableTSF(MINT32 const i4SensorDev)
{
    if (i4SensorDev == 1)
    {
        // 0: LSC
        // 1: TSF
        // 2: TSF, flash switch to LSC
        return 0;
    }
    else
    {
        return 0;
    }
}

MUINT32
getTSFD65Idx(void)
{
#define D65_IDX     (2)
    return D65_IDX;
}

const MINT32* getTSFAWBForceInput(void)
{
    // lv, cct, fluo, day fluo, rgain, bgain, ggain, rsvd
    static MINT32 rAWBInput[8] =
    {20, 2000, -110, -110, 512, 512, 512, 0};

    return rAWBInput;
}


