#include "motor.h"
#include "includes.h"
#include "user_config.h"

volatile u8 motor_sta = MOTOR_STA_NONE;

void motor_init(void)
{
    struct pwm_platform_data mcpwm_init_param;
    motor_sta = MOTOR_STA_NONE;

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

    // 电机电源控制脚：
    gpio_set_pull_down(MOTOR_PWR_PIN, 0);
    gpio_set_pull_up(MOTOR_PWR_PIN, 0);
    gpio_set_die(MOTOR_PWR_PIN, 1); // 关闭模拟输入通道
    gpio_set_hd(MOTOR_PWR_PIN,
                0); // 看需求是否需要开启强推,会导致芯片功耗大
    gpio_set_hd0(MOTOR_PWR_PIN, 0);
    gpio_set_direction(MOTOR_PWR_PIN, 0); // 输出模式

    // 脉冲检测脚
    adc_add_sample_ch(AD_CH_PA7);
    gpio_set_pull_down(IO_PORTA_07, 0); // 关闭下拉
    gpio_set_pull_up(IO_PORTA_07, 0);   // 关闭上拉
    gpio_set_die(IO_PORTA_07, 0);       // 模拟输入
    gpio_set_direction(IO_PORTA_07, 1); // 输入模式

    mcpwm_init_param.pwm_aligned_mode = pwm_edge_aligned; // 边沿对齐
    mcpwm_init_param.pwm_ch_num = pwm_ch3;                // 通道号
    mcpwm_init_param.frequency = 10000;                   //
    mcpwm_init_param.duty = 0;                            // 上电输出 0% 占空比
    mcpwm_init_param.h_pin = MOTOR_RISE_PIN;              // 任意引脚
    mcpwm_init_param.l_pin = -1; // 任意引脚,不需要就填-1
    mcpwm_init_param.complementary_en =
        0; // 两个引脚的波形, 0: 同步,  1: 互补，互补波形的占空比体现在H引脚上
    mcpwm_init(&mcpwm_init_param);

    timer_pwm_init(JL_TIMER3, MOTOR_FALL_PIN, 10000, 0); //

    // 初始化完成后，默认关闭电机
    gpio_set_output_value(MOTOR_PWR_PIN, MOTOR_PWR_OFF_LEV);
    // gpio_set_output_value(MOTOR_RISE_PIN, MOTOR_OFF_LEV);
    // gpio_set_output_value(MOTOR_FALL_PIN, MOTOR_OFF_LEV);
    motor_stop();
}

void motor_pwr_on(void)
{
    gpio_set_output_value(MOTOR_PWR_PIN, MOTOR_PWR_ON_LEV);
}

void motor_pwr_off(void)
{
    gpio_set_output_value(MOTOR_PWR_PIN, MOTOR_PWR_OFF_LEV);
}

void motor_stop(void)
{
    mcpwm_set_duty(pwm_ch3, 0);
    set_timer_pwm_duty(JL_TIMER3, 0);

#if USER_DEBUG_ENABLE
    // printf("%s\n", __FUNCTION__);
#endif
}

// 调用前，确保电机已经停止
void motor_rise(void)
{
    mcpwm_set_duty(pwm_ch3, (u16)((u32)10000 * 100 / 100));
}

void motor_fall(void)
{
    set_timer_pwm_duty(JL_TIMER3, (u16)((u32)10000 * 100 / 100));
}

void motor_set_dir(u8 dir)
{
    motor_stop();

    if (dir == MOTOR_DIR_RISE) {
        // gpio_set_output_value(MOTOR_RISE_PIN, MOTOR_ON_LEV);
        // gpio_set_output_value(MOTOR_FALL_PIN, MOTOR_OFF_LEV);
        motor_rise();
        motor_sta = MOTOR_STA_RISING;
    } else if (dir == MOTOR_DIR_FALL) {
        // gpio_set_output_value(MOTOR_RISE_PIN, MOTOR_OFF_LEV);
        // gpio_set_output_value(MOTOR_FALL_PIN, MOTOR_ON_LEV);
        motor_fall();
        motor_sta = MOTOR_STA_FALLING;
    } else {
        motor_stop();
        motor_sta = MOTOR_STA_NONE;
    }
}

// void motor_process_task(void *p)
// {
//     while (1) {
//         // if ()

//         os_time_dly(1);
//     }
// }
