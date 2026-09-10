#include "acc_det.h"
#include "includes.h"

void acc_det_pin_init(void)
{
    adc_add_sample_ch(AD_CH_PA8);
    gpio_set_pull_down(ACC_DET_PIN, 0); // 关闭下拉
    gpio_set_pull_up(ACC_DET_PIN, 0);   // 关闭上拉
    gpio_set_die(ACC_DET_PIN, 0);       // 模拟输入
    gpio_set_direction(ACC_DET_PIN, 1); // 输入模式
}

// 检测是否接通了acc，返回1表示接通
u8 acc_is_det(void)
{
    u8 ret = 0;
    u32 val;
    val = adc_get_value(AD_CH_PA8);
    if (val >= 900 * 1024 / 3300) {
        // 检测到电压大于 0.9V 
        ret = 1;
    }

    return ret;
    // return gpio_read(ACC_DET_PIN);
}
