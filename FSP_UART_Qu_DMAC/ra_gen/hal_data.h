/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_dmac.h"
#include "r_transfer_api.h"
#include "r_sci_uart.h"
            #include "r_uart_api.h"
FSP_HEADER
/* Transfer on DMAC Instance. */
extern const transfer_instance_t g_transfer_dmac0;

/** Access the DMAC instance using these structures when calling API functions directly (::p_api is not used). */
extern dmac_instance_ctrl_t g_transfer_dmac0_ctrl;
extern const transfer_cfg_t g_transfer_dmac0_cfg;

#ifndef FSP_Dmac0_Callback
void FSP_Dmac0_Callback(dmac_callback_args_t * p_args);
#endif
/** UART on SCI Instance. */
            extern const uart_instance_t      UART_4;

            /** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
            extern sci_uart_instance_ctrl_t     UART_4_ctrl;
            extern const uart_cfg_t UART_4_cfg;
            extern const sci_uart_extended_cfg_t UART_4_cfg_extend;

            #ifndef UART4_Int_Callback
            void UART4_Int_Callback(uart_callback_args_t * p_args);
            #endif
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
