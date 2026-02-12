#ifndef _FSP_ICU_KEY_H__
#define _FSP_ICU_KEY_H__

#include "hal_data.h"
#define KEY1_SW2_Pin BSP_IO_PORT_00_PIN_04
#define KEY2_SW2_Pin BSP_IO_PORT_00_PIN_05
void Key_IRQ_Init();
void key_external_irq (external_irq_callback_args_t *p_args);
#endif