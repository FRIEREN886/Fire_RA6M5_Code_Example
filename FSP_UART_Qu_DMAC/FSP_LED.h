#ifndef _FSP_LED_H__
#define _FSP_LED_H__

#include "hal_data.h"

#define LED1_ON R_IOPORT_PinWrite(&g_ioport_ctrl ,BSP_IO_PORT_04_PIN_00,BSP_IO_LEVEL_LOW);
#define LED2_ON R_IOPORT_PinWrite(&g_ioport_ctrl ,BSP_IO_PORT_04_PIN_03,BSP_IO_LEVEL_LOW);
#define LED3_ON R_IOPORT_PinWrite(&g_ioport_ctrl ,BSP_IO_PORT_04_PIN_04,BSP_IO_LEVEL_LOW);

#define LED1_OFF R_IOPORT_PinWrite(&g_ioport_ctrl ,BSP_IO_PORT_04_PIN_00,BSP_IO_LEVEL_HIGH);
#define LED2_OFF R_IOPORT_PinWrite(&g_ioport_ctrl ,BSP_IO_PORT_04_PIN_03,BSP_IO_LEVEL_HIGH);
#define LED3_OFF R_IOPORT_PinWrite(&g_ioport_ctrl ,BSP_IO_PORT_04_PIN_04,BSP_IO_LEVEL_HIGH);

#define FSP_LED1_TOGGLE R_PORT4->PODR ^= 1 << (BSP_IO_PORT_04_PIN_00 & 0xFF)
#define FSP_LED2_TOGGLE R_PORT4->PODR ^= 1 << (BSP_IO_PORT_04_PIN_03 & 0xFF)
#define FSP_LED3_TOGGLE R_PORT4->PODR ^= 1 << (BSP_IO_PORT_04_PIN_04 & 0xFF)

#endif