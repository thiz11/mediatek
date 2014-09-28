
#ifndef __ARCH_ARM_MACH_MT6573_INCLUDE_MACHINE_MT6573_BT_H
#define __ARCH_ARM_MACH_MT6573_INCLUDE_MACHINE_MT6573_BT_H

#include <linux/types.h>
#include <linux/rfkill.h>

#define MT_BT_OK    (0)
#define MT_BT_FAIL  (-1)

typedef void (*btpm_handler_t)(void*);  /* external irq handler */

extern void mt_bt_power_on(void);
extern void mt_bt_power_off(void);
extern int mt_bt_suspend(pm_message_t state);
extern int mt_bt_resume(pm_message_t state);

extern void mt_bt_eirq_handler(void* par);
extern void mt_bt_pm_init(void* hdev);
extern void mt_bt_pm_deinit(void* hdev);

extern void mt_bt_enable_irq(void);
extern void mt_bt_disable_irq(void);

#endif

