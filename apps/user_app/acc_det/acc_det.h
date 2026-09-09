#ifndef __ACC_DET_H__
#define __ACC_DET_H__

#include "typedef.h"

// acc检测脚
#define ACC_DET_PIN IO_PORTA_08

void acc_det_pin_init(void);
u8 acc_is_det(void);

#endif

