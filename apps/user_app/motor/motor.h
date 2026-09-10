#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "typedef.h"

// 控制电机升起和降下的引脚
#define MOTOR_RISE_PIN IO_PORTA_02
#define MOTOR_FALL_PIN IO_PORTB_05

// 电机转动时，控制脚的电平
#define MOTOR_ON_LEV  1
#define MOTOR_OFF_LEV (!(MOTOR_ON_LEV))

// 电机电源控制脚
#define MOTOR_PWR_PIN     IO_PORTB_06
#define MOTOR_PWR_ON_LEV  1 // 控制电机电源开启对应的引脚电平
#define MOTOR_PWR_OFF_LEV (!(MOTOR_PWR_ON_LEV))

#define MOTOR_DIR_RISE 1
#define MOTOR_DIR_FALL 0

enum
{
    MOTOR_STA_NONE = 0x00,
    MOTOR_STA_RISING,   // 正在上升
    MOTOR_STA_RISE_END, // 上升结束
    MOTOR_STA_FALLING,  // 正在下降
    MOTOR_STA_FALL_END, // 下降结束
};
typedef u8 motor_sta_t;

extern volatile u8 motor_sta;

void motor_init(void);
void motor_pwr_on(void);
void motor_pwr_off(void);
void motor_stop(void);
void motor_set_dir(u8 dir);

#endif
