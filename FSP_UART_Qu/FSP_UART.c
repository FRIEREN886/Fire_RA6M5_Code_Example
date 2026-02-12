#include "FSP_UART.h"
#include "circular_queue.h"
volatile bool Uart_Send_Seccuse_Ack = false;

void FSP_UART_Init()
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_SCI_UART_Open(&UART_4_ctrl,&UART_4_cfg);
    assert(FSP_SUCCESS == err);
}


void UART4_Int_Callback(uart_callback_args_t * p_args)
{
    switch(p_args -> event)
    {
        case UART_EVENT_RX_CHAR:
        {
//            R_SCI_UART_Write(&UART_4_ctrl, (uint8_t *)(p_args -> data), 1);
//            break;
            Queue_Wirte(&Circular_queue,(uint8_t *)&(p_args->data),1);
//             static uint8_t rx_temp; 
//            rx_temp = (uint8_t)(p_args->data); // 获取接收到的数据
    
            // 发送回去
//            R_SCI_UART_Write(&UART_4_ctrl, &rx_temp, 1);
            break;
        }
        case UART_EVENT_TX_COMPLETE:
        {
            Uart_Send_Seccuse_Ack = true;
            break;
        }
        default:
            break;
    }
}


#if defined __GNUC__ && !defined __clang__
int _write(int fd,char *pBuffer,int size);
int _write(int fd,char *pBuffer,int size)
{
    (void)fd;
    R_SCI_UART_Write(&UART_4_ctrl,(uint8_t *)pBuffer,(uint32_t)size);
    while(Uart_Send_Seccuse_Ack == false);
    Uart_Send_Seccuse_Ack = false;
    return size;
}
#else
int fputc(int ch, FILE *f)
{
    (void)f;
    R_SCI_UART_Write(&UART_4_ctrl,(uint8_t *)&ch,1);
    while(Uart_Send_Seccuse_Ack == false);
    Uart_Send_Seccuse_Ack = false;
    
    return ch;
}
#endif