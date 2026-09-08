
#ifndef led_strip_drive_h
#define led_strip_drive_h

#include "board_ac632n_demo_cfg.h"
#include "asm/ledc.h"
#include "asm/gpio.h"

#define LEDC_PIN IO_PORTA_07

#define _R_PIN IO_PORTB_07
#define _G_PIN IO_PORTA_00
#define _B_PIN IO_PORTA_01

void led_state_init(void);
void led_gpio_init(void);
void led_pwm_init(void);

// void fc_rgbw_driver(u8 r, u8 g, u8 b, u8 w);
void fc_rgb_driver(u8 r, u8 g, u8 b);

#endif
