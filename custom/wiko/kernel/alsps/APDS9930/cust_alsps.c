#include <linux/types.h>
#include <mach/mt_pm_ldo.h>
#include <cust_alsps.h>
//#include <mach/mt6577_pm_ldo.h>


int APDS9930_CMM_PPCOUNT_VALUE = 0x08;   //Pulse Number
int APDS9930_CMM_CONTROL_VALUE = 0x2A;   //PS 4X gain£¬ALS 16X gain
int ZOOM_TIME = 0x01;

static struct alsps_hw cust_alsps_hw = {
    .i2c_num    = 2,
	.polling_mode_ps =0,
	.polling_mode_als =1,		//Ivan Interrupt mode not support
    .power_id   = MT65XX_POWER_NONE,    /*LDO is not used*/
    .power_vol  = VOL_DEFAULT,          /*LDO is not used*/
    .i2c_addr   = {0x0C, 0x48, 0x78, 0x00},
    
    .als_level  = {10,  20, 150, 250, 512,  1228,  1536,  2000, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535},
    .als_value  = {20,  50, 240,  300,  638,  1636, 10243, 10243, 10243, 10243, 10243, 10243, 10243, 10243, 10243, 10243},

//    .als_level  = {210,  1229, 1865, 4135, 65535,  65535,  65535,  65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535},
//   .als_value  = {134.6,  301.5, 501.9,  1003,  2003,  2003, 2003, 2003, 2003, 2003, 2003, 2003, 2003, 2003, 2003, 2003},

    
    .ps_threshold_high = 0x029D,
    .ps_threshold_low = 0x0200,
    .als_threshold_high = 0xFFFF,
    .als_threshold_low = 0x0000,
};
struct alsps_hw *get_cust_alsps_hw(void) {
    return &cust_alsps_hw;
}

