

#ifndef TSF_TUNING_CUSTOM_H_
#define TSF_TUNING_CUSTOM_H_

MVOID *getTSFTrainingData(void);

MVOID *getTSFTuningData(void);

MUINT32 isEnableTSF(MINT32 const i4SensorDev);

MUINT32 getTSFD65Idx(void);

const MINT32* getTSFAWBForceInput(void);

#endif /* TSF_TUNING_CUSTOM_H_ */
