/* 
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <linux/interrupt.h>
#include <linux/i2c.h>
#include <linux/slab.h>
#include <linux/irq.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#include <linux/input.h>
#include <linux/workqueue.h>
#include <linux/kobject.h>
#include <linux/earlysuspend.h>
#include <linux/platform_device.h>
#include <asm/atomic.h>

#include <mach/mt_typedefs.h>
#include <mach/mt_gpio.h>
#include <mach/mt_pm_ldo.h>
#include <mach/irqs.h>
#include <mach/eint.h>

#include <asm/io.h>
#include <cust_eint.h>
#include "ak8789.h"
/******************************************************************************
 * configuration
*******************************************************************************/
/*----------------------------------------------------------------------------*/
#define APS_TAG                  "[AK8789] "
#define APS_FUN(f)               printk(KERN_INFO APS_TAG"%s\n", __FUNCTION__)
#define APS_ERR(fmt, args...)    printk(KERN_ERR  APS_TAG"%s %d : "fmt, __FUNCTION__, __LINE__, ##args)
#define APS_LOG(fmt, args...)    printk(KERN_ERR APS_TAG fmt, ##args)
#define APS_DBG(fmt, args...)    printk(KERN_INFO APS_TAG fmt, ##args)         


static	struct work_struct	eint_work;
static struct input_dev *ak8789_key_dev;
extern int gBackLightLevel;
#define KEY_SENSOR 238
//#define KEY_SENSOR 116  //power key
static int enable_input_key = 1;
static s32 value_hall1_rev = 1;
static s32 value_hall2_rev = 1;
static s32 hall_state = 1; //open status

static int ak8789_probe(struct platform_device *pdev);
static int ak8789_remove(struct platform_device *pdev);
/******************************************************************************
 * extern functions
*******************************************************************************/
extern void mt_eint_mask(unsigned int eint_num);
extern void mt_eint_unmask(unsigned int eint_num);
extern void mt_eint_set_hw_debounce(unsigned int eint_num, unsigned int ms);
extern void mt_eint_set_polarity(unsigned int eint_num, unsigned int pol);
extern unsigned int mt_eint_set_sens(unsigned int eint_num, unsigned int sens);
extern void mt_eint_registration(unsigned int eint_num, unsigned int flow, void (EINT_FUNC_PTR)(void), unsigned int is_auto_umask);
extern void mt_eint_print_status(void);


/*-------------------------------attribute file for debugging----------------------------------*/

/******************************************************************************
 * Sysfs attributes
*******************************************************************************/
/*----------------------------------------------------------------------------*/
static ssize_t ak8789_show_state(struct device_driver *ddri, char *buf)
{
	APS_LOG("hall_state = %d\n", hall_state);
	return snprintf(buf, PAGE_SIZE, "%d\n", hall_state);
}
/*----------------------------------------------------------------------------*/
static ssize_t ak8789_show_key(struct device_driver *ddri, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%d\n", enable_input_key);
}
/*----------------------------------------------------------------------------*/
static ssize_t ak8789_store_key(struct device_driver *ddri, const char *buf, size_t count)
{
    int enable, res;
    u8 databuf[1];
	
	if(1 == sscanf(buf, "%d", &enable))
	{
		enable_input_key = enable;
	}
	else 
	{
		APS_ERR("invalid enable content: '%s', length = %d\n", buf, count);
	}
	return count;    
}
/*---------------------------------------------------------------------------------------*/
static DRIVER_ATTR(hall_state,     S_IWUSR | S_IRUGO, ak8789_show_state, NULL);
static DRIVER_ATTR(input_key_enable,    0666, ak8789_show_key, ak8789_store_key);
/*----------------------------------------------------------------------------*/
static struct driver_attribute *ak8789_attr_list[] = {
    &driver_attr_hall_state,
    &driver_attr_input_key_enable,
};

/*----------------------------------------------------------------------------*/
static int ak8789_create_attr(struct device_driver *driver) 
{
	int idx, err = 0;
	int num = (int)(sizeof(ak8789_attr_list)/sizeof(ak8789_attr_list[0]));
	if (driver == NULL)
	{
		return -EINVAL;
	}

	for(idx = 0; idx < num; idx++)
	{
		if((err = driver_create_file(driver, ak8789_attr_list[idx])))
		{            
			APS_ERR("driver_create_file (%s) = %d\n", ak8789_attr_list[idx]->attr.name, err);
			break;
		}
	}    
	return err;
}
/*----------------------------------------------------------------------------*/
	static int ak8789_delete_attr(struct device_driver *driver)
	{
	int idx ,err = 0;
	int num = (int)(sizeof(ak8789_attr_list)/sizeof(ak8789_attr_list[0]));

	if (!driver)
	return -EINVAL;

	for (idx = 0; idx < num; idx++) 
	{
		driver_remove_file(driver, ak8789_attr_list[idx]);
	}
	
	return err;
}
/*----------------------------------------------------------------------------*/
static struct platform_driver ak8789_hall_driver = {
	.probe      = ak8789_probe,
	.remove     = ak8789_remove,    
	.driver     = {
		.name  = "hall",
	}
};

/*----------------------------------------------------------------------------*/
static void ak8789_eint1_func(void)
{

	APS_ERR("debug ak8789_eint1_func!");
	schedule_work(&eint_work);
}

static void ak8789_eint2_func(void)
{

	APS_ERR("debug ak8789_eint2_func!");
	schedule_work(&eint_work);
}


/*----------------------------------interrupt functions--------------------------------*/
static void ak8789_eint_work(struct work_struct *work)
{
	int res = 0;
	s32 value_hall1 = -1;
	s32 value_hall2 = -1;
	
	value_hall1 = mt_get_gpio_in(GPIO_HALL_1_PIN);
	//APS_LOG("AK8789_eint_work GPIO_HALL_1_PIN=%d\n",value_hall1);	
	if(!value_hall1)
		mt_eint_registration(CUST_EINT_HALL_1_NUM, EINTF_TRIGGER_HIGH, ak8789_eint1_func, 0);
	else
		mt_eint_registration(CUST_EINT_HALL_1_NUM, EINTF_TRIGGER_LOW, ak8789_eint1_func, 0);

	value_hall2 = mt_get_gpio_in(GPIO_HALL_2_PIN);
	//APS_LOG("AK8789_eint_work GPIO_HALL_2_PIN=%d\n",value_hall2);	
	if(!value_hall2)
		mt_eint_registration(CUST_EINT_HALL_2_NUM, EINTF_TRIGGER_HIGH, ak8789_eint2_func, 0);
	else
		mt_eint_registration(CUST_EINT_HALL_2_NUM, EINTF_TRIGGER_LOW, ak8789_eint2_func, 0);
	
	if((0 == value_hall1)||(0 == value_hall2))
		hall_state = 0;
	else
		hall_state = 1;		
		
	//APS_LOG("AK8789_eint_work gBackLightLevel=%d enable_input_key=%d\n",gBackLightLevel, enable_input_key);	
	//APS_LOG("AK8789_eint_work value_hall1_rev=%d value_hall1=%d\n",value_hall1_rev, value_hall1);	
	//APS_LOG("AK8789_eint_work value_hall2_rev=%d value_hall2=%d\n",value_hall2_rev, value_hall2);


	if(enable_input_key){
		if(((value_hall1_rev != value_hall1)&&((0!=gBackLightLevel) ||(value_hall1&&(0==gBackLightLevel))))
			|| ((value_hall2_rev != value_hall2)&&((0!=gBackLightLevel) ||(value_hall2&&(0==gBackLightLevel))))
		   ){
/*	if((value_hall1_rev != value_hall1) || (value_hall2_rev != value_hall2)  ){*/
		//APS_LOG("AK8789_eint_work input_report_key \n");				
			input_report_key(ak8789_key_dev, KEY_SENSOR, 1);
			input_report_key(ak8789_key_dev, KEY_SENSOR, 0);
			input_sync(ak8789_key_dev);
		}else{
			input_report_key(ak8789_key_dev, KEY_SENSOR, 1);
			input_report_key(ak8789_key_dev, KEY_SENSOR, 0);
			input_sync(ak8789_key_dev);
		}

		value_hall1_rev = value_hall1;
		value_hall2_rev = value_hall2;
	}
	
	mt_eint_unmask(CUST_EINT_HALL_1_NUM); 
	mt_eint_unmask(CUST_EINT_HALL_2_NUM); 
	return;
}

int ak8789_setup_eint()
{
	
	mt_set_gpio_dir(GPIO_HALL_1_PIN, GPIO_DIR_IN);
	mt_set_gpio_mode(GPIO_HALL_1_PIN, GPIO_HALL_1_PIN_M_EINT);
	mt_set_gpio_pull_enable(GPIO_HALL_1_PIN, TRUE);
	mt_set_gpio_pull_select(GPIO_HALL_1_PIN, GPIO_PULL_UP);


	mt_set_gpio_dir(GPIO_HALL_2_PIN, GPIO_DIR_IN);
	mt_set_gpio_mode(GPIO_HALL_2_PIN, GPIO_HALL_2_PIN_M_EINT);
	mt_set_gpio_pull_enable(GPIO_HALL_2_PIN, TRUE);
	mt_set_gpio_pull_select(GPIO_HALL_2_PIN, GPIO_PULL_UP);

	mt_eint_set_sens(CUST_EINT_HALL_1_NUM, MT_LEVEL_SENSITIVE);
	mt_eint_set_hw_debounce(CUST_EINT_HALL_1_NUM, CUST_EINT_HALL_1_DEBOUNCE_CN);
	mt_eint_registration(CUST_EINT_HALL_1_NUM, EINTF_TRIGGER_LOW, ak8789_eint1_func, 0);
	mt_eint_unmask(CUST_EINT_HALL_1_NUM); 
	
	mt_eint_set_sens(CUST_EINT_HALL_2_NUM, MT_LEVEL_SENSITIVE);
	mt_eint_set_hw_debounce(CUST_EINT_HALL_2_NUM, CUST_EINT_HALL_2_DEBOUNCE_CN);
	mt_eint_registration(CUST_EINT_HALL_2_NUM, EINTF_TRIGGER_LOW, ak8789_eint2_func, 0);
	mt_eint_unmask(CUST_EINT_HALL_2_NUM); 
    
  	return 0;
}

/*----------------------------------------------------------------------------*/

static int ak8789_probe(struct platform_device *pdev) 
{
	APS_FUN();  
	int err;

	INIT_WORK(&eint_work, ak8789_eint_work);
	if((err = ak8789_create_attr(&ak8789_hall_driver.driver)))
	{
		APS_ERR("create attribute err = %d\n", err);
		goto exit_create_attr_failed;
	}

	//------------------------------------------------------------------
	// 							Create input device 
	//------------------------------------------------------------------
	ak8789_key_dev = input_allocate_device();
	if (!ak8789_key_dev) 
	{
		APS_LOG("[APS]ak8789_key_dev : fail!\n");
		return -ENOMEM;
	}

	//define multi-key keycode
	__set_bit(EV_KEY, ak8789_key_dev->evbit);
	__set_bit(KEY_SENSOR, ak8789_key_dev->keybit);


	
	ak8789_key_dev->id.bustype = BUS_HOST;
	ak8789_key_dev->name = "AK8789";
	if(input_register_device(ak8789_key_dev))
	{
		APS_LOG("[APS]ak8789_key_dev register : fail!\n");
	}else
	{
		APS_LOG("[APS]ak8789_key_dev register : success!!\n");
	} 
	//WIKOKK-320 tonsal
	ak8789_setup_eint();
	return 0;
	
	exit_create_attr_failed:
	APS_ERR("%s: err = %d\n", __func__, err);
	return err;
}
/*----------------------------------------------------------------------------*/
static int ak8789_remove(struct platform_device *pdev)
{
	
	APS_FUN(); 
	int err;	
	
	input_unregister_device(ak8789_key_dev);
	if((err = ak8789_delete_attr(&ak8789_hall_driver.driver)))
	{
		APS_ERR("ap3220_delete_attr fail: %d\n", err);
	} 
		
	return 0;
}



/*----------------------------------------------------------------------------*/
static int __init ak8789_init(void)
{
	APS_FUN();
  if(platform_driver_register(&ak8789_hall_driver))
	{
		APS_ERR("failed to register driver");
		return -ENODEV;
	}
	return 0;
}
/*----------------------------------------------------------------------------*/
static void __exit ak8789_exit(void)
{
	APS_FUN();
	platform_driver_unregister(&ak8789_hall_driver);
}
/*----------------------------------------------------------------------------*/
module_init(ak8789_init);
module_exit(ak8789_exit);
/*----------------------------------------------------------------------------*/
MODULE_AUTHOR("cyong");
MODULE_DESCRIPTION("ak8789 driver");
MODULE_LICENSE("GPL");

