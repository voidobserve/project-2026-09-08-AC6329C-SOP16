#ifndef __MOTOR_H__
#define __MOTOR_H__

// 控制电机升起和降下的引脚
#define MOTOR_RISE_PIN IO_PORTA_02
#define MOTOR_FALL_PIN IO_PORTB_05
// 电机转动时，控制脚的电平
#define MOTOR_ON_LEV  1
#define MOTOR_OFF_LEV (!(MOTOR_ON_LEV))

void motor_init(void);

#endif