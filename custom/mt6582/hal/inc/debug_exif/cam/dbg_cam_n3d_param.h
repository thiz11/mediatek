

#ifndef _DBG_CAM_N3D_PARAM_H
#define _DBG_CAM_N3D_PARAM_H

// Native3D debug info
#define N3D_DEBUG_TAG_SIZE     10
#define N3D_DEBUG_TAG_VERSION  0


typedef struct DEBUG_N3D_INFO_S
{
    DEBUG_CAM_TAG_T Tag[N3D_DEBUG_TAG_SIZE];
} DEBUG_N3D_INFO_T;


//Common Parameter Structure
typedef enum
{
    N3D_TAG_VERSION = 0,
    
}DEBUG_N3D_TAG_T;

#endif //_DBG_CAM_N3D_PARAM_H