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

#include <cust_acc.h>
#include <linux/hwmsensor.h>
#include <linux/hwmsen_dev.h>
#include <linux/sensors_io.h>
#include <linux/hwmsen_helper.h>

#include <mach/mt_typedefs.h>
#include <mach/mt_gpio.h>
#include <mach/mt_pm_ldo.h>

#include "bq27541.h"

/**********************************************************
  *
  *   [I2C Slave Setting] 
  *
  *********************************************************/
#define bq27541_SLAVE_ADDR_WRITE   0xAA
#define bq27541_SLAVE_ADDR_READ    0xAB
#define BQ27541_DEVICE_HAS_FOUND  1
#define BQ27541_DRIVER_NOT_PROBE   -1
#define BQ27541_DEVICE_NOT_FOUND   0

int bq27541_state=BQ27541_DRIVER_NOT_PROBE;
static struct i2c_client *new_client = NULL;
static const struct i2c_device_id bq27541_i2c_id[] = {{"bq27541",0},{}};   

static int bq27541_driver_probe(struct i2c_client *client, const struct i2c_device_id *id);

static struct i2c_driver bq27541_driver = {
    .driver = {
        .name    = "bq27541",
    },
    .probe       = bq27541_driver_probe,
    .id_table    = bq27541_i2c_id,
};

/**********************************************************
  *
  *   [Global Variable] 
  *
  *********************************************************/
static DEFINE_MUTEX(bq27541_i2c_access);
/**********************************************************
  *
  *   [I2C Function For Read/Write bq27541] 
  *
  *********************************************************/  

int bq27541_set_cmd_read(kal_uint8 cmd, int *returnData)
{
	int ret;
	u8 buffer[2];
 	int      readData = 0;

	struct i2c_msg msg[2] =
	{
		{
			.addr = new_client->addr,
			.flags = 0,
			.buf = buffer,
			.len = 1,
			.timing = 400
		},
		{
			.addr = new_client->addr,
			.flags = I2C_M_RD,
			.buf = buffer,
			.len = 2,
			.timing = 400
		},
	};

	buffer[0] = cmd;

	if (returnData == NULL)
		return -1;

	ret = i2c_transfer(new_client->adapter, &msg[0], 2);


	if (ret < 0)
		dev_err(&new_client->dev, "%s i2c dma read error.\n", __func__);

	    readData = (buffer[1] << 8) | buffer[0];
    *returnData = readData;
	return 0;
}

#if 0
int bq27541_set_cmd_read(kal_uint8 cmd, int *returnData)
{
    char     cmd_buf[2]={0x00, 0x00};
    int      readData = 0;
    int      ret=0;

    mutex_lock(&bq27541_i2c_access);



    //new_client->addr = ((new_client->addr) & I2C_MASK_FLAG) | I2C_WR_FLAG;    
   // new_client->ext_flag=((new_client->ext_flag ) & I2C_MASK_FLAG ) | I2C_WR_FLAG | I2C_DIRECTION_FLAG;
    new_client->flags=I2C_M_RD;
    cmd_buf[0] = cmd;
    ret = i2c_master_send(new_client, &cmd_buf[0], 2/*(2<<8 | 1)*/);

	
    //new_client->addr = ((new_client->addr) & I2C_MASK_FLAG) | I2C_WR_FLAG;    
/*    new_client->ext_flag=((new_client->ext_flag ) & I2C_MASK_FLAG ) | I2C_WR_FLAG | I2C_DIRECTION_FLAG | I2C_RS_FLAG;
*/
//    cmd_buf[0] = cmd;
  //  ret = mt_i2c_master_send(new_client, &cmd_buf[0], (2<<8 | 1), new_client->ext_flag);
//    ret = i2c_master_send(new_client, &cmd_buf[0], (2<<8 | 1));
    if (ret < 0) 
    {    
        //new_client->addr = new_client->addr & I2C_MASK_FLAG;
   //     new_client->ext_flag=0;
	    new_client->flags=0;
	
        mutex_unlock(&bq27541_i2c_access);
        return 0;
    }
    
    readData = (cmd_buf[1] << 8) | cmd_buf[0];
    *returnData = readData;

    //new_client->addr = new_client->addr & I2C_MASK_FLAG;
     new_client->flags=0;
	
    mutex_unlock(&bq27541_i2c_access);    
    return 1;
} 
#endif

int bq27541_set_cmd_write(kal_uint8 cmd, int WriteData)
{
    char     cmd_buf[3]={0x00, 0x00, 0x00};
    int      ret=0;

    mutex_lock(&bq27541_i2c_access);
    
    //new_client->addr = ((new_client->addr) & I2C_MASK_FLAG) | I2C_WR_FLAG;    
 //   new_client->ext_flag=((new_client->ext_flag ) & I2C_MASK_FLAG ) | I2C_DIRECTION_FLAG;
 new_client->flags=0;
    cmd_buf[0] = cmd;
	cmd_buf[1] = WriteData & 0xFF;
	cmd_buf[2] = (WriteData >> 8) & 0xFF;
//    ret = mt_i2c_master_send(new_client, cmd_buf, 3, new_client->ext_flag);



    
    ret = i2c_master_send(new_client, cmd_buf, 3);



	
//    ret = i2c_master_send(new_client, &cmd_buf[0], (2<<8 | 1));
    if (ret < 0) 
    {    
        //new_client->addr = new_client->addr & I2C_MASK_FLAG;
        	    new_client->flags=0;
		
        mutex_unlock(&bq27541_i2c_access);
        return 0;
    }
    
    new_client->ext_flag=0;
	
    mutex_unlock(&bq27541_i2c_access);    
    return 1;
} 


int read_battery_temp(void)
{
	int ret = 0;
	int data = -255;
	if(bq27541_state==BQ27541_DRIVER_NOT_PROBE)
	{
		return 25;
	}
	if(bq27541_state==BQ27541_DEVICE_HAS_FOUND)
	{
		ret = bq27541_set_cmd_read(BQ27541_CMD_Temperature, &data);
		data -= 2731;
		data = data/10;
		printk("[BQ27541]Temperature = %d C\n", data);
	}
	return data;
}

EXPORT_SYMBOL(read_battery_temp);

int read_battery_soc(void)
{
	int ret = 0;
	int data = -255;
	if(bq27541_state==BQ27541_DRIVER_NOT_PROBE)
	{
		return 50;
	}
	if(bq27541_state==BQ27541_DEVICE_HAS_FOUND)
	{
		ret = bq27541_set_cmd_read(BQ27541_CMD_StateOfCharge, &data);
		printk("[BQ27541]StateOfCharge = %X\n", data);
	}
	return data;
}

EXPORT_SYMBOL(read_battery_soc);

int check_bq27541_state(void)
{
	return bq27541_state;
}

EXPORT_SYMBOL(check_bq27541_state);

#if 0
void bq27541_parameter_dump(void)
{
    int ret = 0;
    int data = 0;
	if(new_client==NULL)
	{
		return;
	}
//BQ27541_CMD_AtRate  	
 //  ret = bq27541_set_cmd_read(BQ27541_CMD_AtRate, &data);
//	printk("[BQ27541]AtRate = %X\n", data);
//	data = 0x2BC; //700mA
//    ret = bq27541_set_cmd_write(BQ27541_CMD_AtRate, data);
//    ret = bq27541_set_cmd_read(BQ27541_CMD_AtRate, &data);
//	printk("[BQ27541]AtRate-Wrote = %X\n", data);
	
    //BQ27541_CMD_AtRateTimeToEmpty  	
 //   ret = bq27541_set_cmd_read(BQ27541_CMD_AtRateTimeToEmpty, &data);
//	printk("[BQ27541]AtRateTimeToEmpty = %X\n", data);


    ret = bq27541_set_cmd_read(BQ27541_CMD_StateOfCharge, &data);
	printk("[BQ27541]StateOfCharge = %X\n", data);
	
    //BQ27541_CMD_Temperature  	
    ret = bq27541_set_cmd_read(BQ27541_CMD_Temperature, &data);
	data -= 2731;
	data = data/10;
	printk("[BQ27541]Temperature = %d C\n", data);

	/*
    //BQ27541_CMD_Voltage  	
    ret = bq27541_set_cmd_read(BQ27541_CMD_Voltage, &data);
	printk("[BQ27541]Voltage = %d\n", data);
    
    //BQ27541_CMD_Flags  	
    ret = bq27541_set_cmd_read(BQ27541_CMD_Flags, &data);
	printk("[BQ27541]Flags = %X\n", data);
    
    //BQ27541_CMD_NominalAvailableCapacity  	
    ret = bq27541_set_cmd_read(BQ27541_CMD_NominalAvailableCapacity, &data);
	printk("[BQ27541]NominalAvailableCapacity = %X\n", data);
    
    //BQ27541_CMD_FullAvailableCapacity  		
    ret = bq27541_set_cmd_read(BQ27541_CMD_FullAvailableCapacity, &data);
	printk("[BQ27541]FullAvailableCapacity = %X\n", data);
    
    //BQ27541_CMD_RemainingCapacity  			
    ret = bq27541_set_cmd_read(BQ27541_CMD_RemainingCapacity, &data);
	printk("[BQ27541]RemainingCapacity = %X\n", data);
    
    //BQ27541_CMD_FullChargeCapacity  	
    ret = bq27541_set_cmd_read(BQ27541_CMD_FullChargeCapacity, &data);
	printk("[BQ27541]FullChargeCapacity = %X\n", data);
    
    //BQ27541_CMD_AverageCurrent	
    ret = bq27541_set_cmd_read(BQ27541_CMD_AverageCurrent, &data);
	printk("[BQ27541]AverageCurrent = %X\n", data);
    
    //BQ27541_CMD_TimeToEmpty		
    ret = bq27541_set_cmd_read(BQ27541_CMD_TimeToEmpty, &data);
	printk("[BQ27541]TimeToEmpty = %X\n", data);
    
    //BQ27541_CMD_TimeToFull 				
    ret = bq27541_set_cmd_read(BQ27541_CMD_TimeToFull, &data);
	printk("[BQ27541]TimeToFull = %X\n", data);
    
    //BQ27541_CMD_StandbyCurrent		
    ret = bq27541_set_cmd_read(BQ27541_CMD_StandbyCurrent, &data);
	printk("[BQ27541]StandbyCurrent = %X\n", data);
    
    //BQ27541_CMD_StandbyTimeToEmpty	
    ret = bq27541_set_cmd_read(BQ27541_CMD_StandbyTimeToEmpty, &data);
	printk("[BQ27541]StandbyTimeToEmpty = %X\n", data);
    
    //BQ27541_CMD_MaxLoadCurrent		
    ret = bq27541_set_cmd_read(BQ27541_CMD_MaxLoadCurrent, &data);
	printk("[BQ27541]MaxLoadCurrent = %X\n", data);
    
    //BQ27541_CMD_MaxLoadTimeToEmpty	
    ret = bq27541_set_cmd_read(BQ27541_CMD_MaxLoadTimeToEmpty, &data);
	printk("[BQ27541]MaxLoadTimeToEmpty = %X\n", data);
    
    //BQ27541_CMD_AvailableEnergy			
    ret = bq27541_set_cmd_read(BQ27541_CMD_AvailableEnergy, &data);
	printk("[BQ27541]AvailableEnergy = %X\n", data);
    
    //BQ27541_CMD_AveragePower		
    ret = bq27541_set_cmd_read(BQ27541_CMD_AveragePower, &data);
	printk("[BQ27541]AveragePower = %X\n", data);
    
    //BQ27541_CMD_TimeToEmptyAtConstantPower	
    ret = bq27541_set_cmd_read(BQ27541_CMD_TimeToEmptyAtConstantPower, &data);
	printk("[BQ27541]TimeToEmptyAtConstantPower = %X\n", data);
    
    //BQ27541_CMD_Internal_Temp			
    ret = bq27541_set_cmd_read(BQ27541_CMD_Internal_Temp, &data);
	data -= 2731;
	data = data/10;	
	printk("[BQ27541]Internal_Temp = %d C\n", data);
    
    //BQ27541_CMD_CycleCount	
    ret = bq27541_set_cmd_read(BQ27541_CMD_CycleCount, &data);
	printk("[BQ27541]CycleCount = %X\n", data);
    */
    //BQ27541_CMD_StateOfCharge		
    ret = bq27541_set_cmd_read(BQ27541_CMD_StateOfCharge, &data);
	printk("[BQ27541]StateOfCharge = %X\n", data);
    /*
    //BQ27541_CMD_StateOfHealth		
    ret = bq27541_set_cmd_read(BQ27541_CMD_StateOfHealth, &data);
	printk("[BQ27541]StateOfHealth = %X\n", data);
    
    //BQ27541_CMD_PassedCharge		
    ret = bq27541_set_cmd_read(BQ27541_CMD_PassedCharge, &data);
	printk("[BQ27541]PassedCharge = %X\n", data);
    
    //BQ27541_CMD_DOD0		
    ret = bq27541_set_cmd_read(BQ27541_CMD_DOD0, &data);
	printk("[BQ27541]DOD0 = %X\n", data);        */
}

EXPORT_SYMBOL(bq27541_parameter_dump);
#endif

static int bq27541_driver_probe(struct i2c_client *client, const struct i2c_device_id *id) 
{             
    int err=0; 
    int device_id=0;
    int retry_count=4; 
    printk("[bq27541_driver_probe] \n");
    if (!(new_client = kmalloc(sizeof(struct i2c_client), GFP_KERNEL))) {
        err = -ENOMEM;
        goto exit;
    }    
    memset(new_client, 0, sizeof(struct i2c_client));

    new_client = client;    
while(retry_count)
{
	retry_count--;
	bq27541_set_cmd_write(0,1);
	bq27541_set_cmd_read(0,&device_id);
	printk("bq27541_driver_probe device id=0x%x \n",device_id);

	if(device_id==0x541){
			bq27541_state=BQ27541_DEVICE_HAS_FOUND;
			break;
		}
	else{
			bq27541_state=BQ27541_DEVICE_NOT_FOUND;
		}	
}
#if  0
    //---------------------
bq27541_parameter_dump();
#endif
    return 0;                                                                                       

exit:
    return err;

}

/**********************************************************
  *
  *   [platform_driver API] 
  *
  *********************************************************/
#define BQ24196_BUSNUM 3
static struct i2c_board_info __initdata i2c_bq27541 = { I2C_BOARD_INFO("bq27541", (0xaa>>1))};

static int __init bq27541_init(void)
{  
    printk("[bq27541_init] init start\n");
    
    i2c_register_board_info(BQ24196_BUSNUM, &i2c_bq27541, 1);

    if(i2c_add_driver(&bq27541_driver)!=0)
    {
        printk("[bq27541_init] failed to register bq27541 i2c driver.\n");
    }
    else
    {
        printk("[bq27541_init] Success to register bq27541 i2c driver.\n");
    }
    
    return 0;        
}

static void __exit bq27541_exit(void)
{
    i2c_del_driver(&bq27541_driver);
}

module_init(bq27541_init);
module_exit(bq27541_exit);
   
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("I2C bq27541 Driver");
MODULE_AUTHOR("YT Lee<yt.lee@mediatek.com>");
