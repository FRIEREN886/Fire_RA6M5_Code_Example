#ifndef _FSP_Button_H__
#define _FSP_Button_H__

#include "hal_data.h"

#define FSP_KEY1_SW2_Pin BSP_IO_PORT_00_PIN_04
#define FSP_KEY2_SW3_Pin BSP_IO_PORT_00_PIN_05
#define Button_ON 1
#define Button_OFF 0

uint32_t FSP_Scan_Key(bsp_io_port_pin_t Key);
void FSP_Button_Init();

#endif