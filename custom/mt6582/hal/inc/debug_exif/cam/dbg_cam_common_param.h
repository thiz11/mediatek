

#ifndef _DBG_CAM_COMMON_PARAM_H
#define _DBG_CAM_COMMON_PARAM_H

// Common debug info
#define CMN_DEBUG_TAG_SIZE     10
#define CMN_DEBUG_TAG_VERSION  0


typedef struct DEBUG_CMN_INFO_S
{
    DEBUG_CAM_TAG_T Tag[CMN_DEBUG_TAG_SIZE];
} DEBUG_CMN_INFO_T;


//Common Parameter Structure
typedef enum
{
    CMN_TAG_VERSION = 0,
    CMN_TAG_SHOT_MODE,
    CMN_TAG_CAM_MODE
    
}DEBUG_CMN_TAG_T;

#endif //_DBG_CAM_COMMON_PPARAM_H