#ifndef TOUCHPANEL_H__
#define TOUCHPANEL_H__

/* Pre-defined definition */
#define TPD_TYPE_CAPACITIVE

/* Register */
//#define FD_ADDR_MAX    	0xE9
//#define FD_ADDR_MIN    	0xDD
//#define FD_BYTE_COUNT 	6

#define CUSTOM_MAX_WIDTH (720)
#define CUSTOM_MAX_HEIGHT (1280)

//#define TPD_UPDATE_FIRMWARE

#define TPD_HAVE_BUTTON
#define TPD_BUTTON_HEIGH        (100)
#define TPD_KEY_COUNT           3
//#define TPD_KEYS                { KEY_BACK, KEY_HOMEPAGE, KEY_MENU}
#define TPD_KEYS                { KEY_MENU, KEY_HOMEPAGE, KEY_BACK}
/*#define TPD_KEYS_DIM		{{100,830,100,TPD_BUTTON_HEIGH},\
							{250,830,100,TPD_BUTTON_HEIGH},\
							{400,830,100,TPD_BUTTON_HEIGH}}*/

#define TPD_KEYS_DIM		{{175,2100,100,TPD_BUTTON_HEIGH},\
							{550,2100,100,TPD_BUTTON_HEIGH},\
							{890,2100,100,TPD_BUTTON_HEIGH}}

#define TPD_POWER_SOURCE         MT65XX_POWER_LDO_VGP4
//#define LCD_X           480
//#define LCD_Y           800
#define LCD_X           720
#define LCD_Y           1280

#define TPD_UPDATE_FIRMWARE
#define HAVE_TOUCH_KEY

//#define TPD_HAVE_CALIBRATION
#define TPD_CALIBRATION_MATRIX  {2680,0,0,0,2760,0,0,0};
//#define TPD_WARP_START
//#define TPD_WARP_END

#define TPD_RESET_ISSUE_WORKAROUND
#define TPD_MAX_RESET_COUNT 3
#define TPD_WARP_Y(y) ( TPD_Y_RES - 1 - y )
#define TPD_WARP_X(x) ( x )

#endif /* TOUCHPANEL_H__ */
