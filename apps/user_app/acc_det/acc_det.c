#include "acc_det.h"
#include "includes.h"

void acc_det_pin_init(void)
{ 
    gpio_set_pull_down(ACC_DET_PIN, 0); // 关闭下拉
    gpio_set_pull_up(ACC_DET_PIN, 0);   // 关闭上拉
    gpio_set_die(ACC_DET_PIN, 1);
    gpio_set_direction(ACC_DET_PIN, 1); // 输入模式 
}

// 检测是否接通了acc，返回1表示接通
u8 acc_is_det(void)
{
    return gpio_read(ACC_DET_PIN);
}
