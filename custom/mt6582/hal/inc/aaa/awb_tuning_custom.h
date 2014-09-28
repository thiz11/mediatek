

#ifndef _AWB_TUNING_CUSTOM_H
#define _AWB_TUNING_CUSTOM_H


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//         P U B L I C    F U N C T I O N    D E C L A R A T I O N              //
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
MBOOL isAWBEnabled();
MBOOL isAWBCalibrationBypassed();
AWB_PARAM_T const& getAWBParam();
AWB_STAT_PARAM_T const& getAWBStatParam();
const MINT32* getAWBActiveCycle_Preview(MINT32 i4SceneLV);
const MINT32* getAWBActiveCycle_Video(MINT32 i4SceneLV);
MINT32 getAWBCycleNum_Preview();
MINT32 getAWBCycleNum_Video();

#endif

