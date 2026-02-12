/*
 * FSP_KEY_IRQ.c
 *
 *  Created on: 2026年1月30日
 *      Author: frieren
 */
#include "FSP_KEY_IRQ.h"

void Key_IRQ_Init()
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_ICU_ExternalIrqOpen(&irq9_ctrl, &irq9_cfg);
    err = R_ICU_ExternalIrqOpen(&irq10_ctrl, &irq10_cfg);
    err = R_ICU_ExternalIrqEnable(&irq9_ctrl);
    err = R_ICU_ExternalIrqEnable(&irq10_ctrl);
}

volatile bool key1_sw2_press = false;
volatile bool key2_sw3_press = false;


void key_external_irq (external_irq_callback_args_t *p_args)
{
    if(p_args->channel == 9)
    {
        key1_sw2_press = true;
    }
    else if(p_args->channel == 10)
    {
        key2_sw3_press = true;
    }
}
