#include "motor.h"
#include "includes.h"

void motor_init(void)
{
    gpio_set_pull_down(MOTOR_RISE_PIN, 0);
    gpio_set_pull_up(MOTOR_RISE_PIN, 0);
    gpio_set_die(MOTOR_RISE_PIN, 1); // 关闭模拟输入通道
    gpio_set_hd(MOTOR_RISE_PIN,
                0); // 看需求是否需要开启强推,会导致芯片功耗大
    gpio_set_hd0(MOTOR_RISE_PIN, 0);
    gpio_set_direction(MOTOR_RISE_PIN, 0); // 输出模式

    gpio_set_pull_down(MOTOR_FALL_PIN, 0);
    gpio_set_pull_up(MOTOR_FALL_PIN, 0);
    gpio_set_die(MOTOR_FALL_PIN, 1); // 关闭模拟输入通道
    gpio_set_hd(MOTOR_FALL_PIN,
                0); // 看需求是否需要开启强推,会导致芯片功耗大
    gpio_set_hd0(MOTOR_FALL_PIN, 0);
    gpio_set_direction(MOTOR_FALL_PIN, 0); // 输出模式

	gpio_set_output_value(MOTOR_RISE_PIN, MOTOR_OFF_LEV);
	gpio_set_output_value(MOTOR_FALL_PIN, MOTOR_OFF_LEV);
}

void motor_set_dir(u8 dir)
{
	

    // if (dir == MOTOR_RISE) {
    //     gpio_set_output_value(MOTOR_RISE_PIN, MOTOR_ON_LEV);
    //     gpio_set_output_value(MOTOR_FALL_PIN, MOTOR_OFF_LEV);
    // } else {
    //     gpio_set_output_value(MOTOR_RISE_PIN, MOTOR_OFF_LEV);
    //     gpio_set_output_value(MOTOR_FALL_PIN, MOTOR_ON_LEV);
    // }
}

void motor_process_task(void *p)
{


    while (1) {



        os_time_dly(1);
    }
}
