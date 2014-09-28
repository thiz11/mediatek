

#ifndef _DBG_CAM_MF_PARAM_H
#define _DBG_CAM_MF_PARAM_H

// MF debug info
#define MF_DEBUG_TAG_SIZE     10
#define MF_DEBUG_TAG_VERSION  0


typedef struct DEBUG_MF_INFO_S
{
    DEBUG_CAM_TAG_T Tag[MF_DEBUG_TAG_SIZE];
} DEBUG_MF_INFO_T;


//MF Parameter Structure
typedef enum
{
    MF_TAG_VERSION = 0
    
    /* add tags here */
    
}DEBUG_MF_TAG_T;

#endif //_DBG_CAM_MF_PARAM_H