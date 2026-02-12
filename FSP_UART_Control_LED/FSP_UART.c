#include "FSP_UART.h"

volatile bool Uart_Send_Seccuse_Ack = false;


static uint8_t rx_buffer[10]; // 缓冲区要足够大，能放下最长命令和结束符
static uint8_t rx_index = 0;
    
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
            if (rx_index < (sizeof(rx_buffer) - 1))
            {
                rx_buffer[rx_index++] = (uint8_t)p_args->data;
            }

            // 2. 检查刚收到的字符是否是结束符 '\n'
            if ('\n' == (uint8_t)p_args->data)
            {
                // 3. 接收到结束符，一条命令接收完毕
                //    在缓冲区末尾添加字符串结束符 '\0'，以便 strcmp 等函数使用
                rx_buffer[rx_index] = '\0';

                // --- 在这里处理你的命令 ---
                if (0 == strcmp((char *)rx_buffer, "hello\n"))
                {
                    // 收到 "hello\n"，把它发回去
                    R_SCI_UART_Write(&UART_4_ctrl, (uint8_t *)"RECEIVED: hello\n", strlen("RECEIVED: hello\n"));
                }
                else if (0 == strcmp((char *)rx_buffer, "led_on\n"))
                {
                    FSP_LED1_TOGGLE;
                }
                else
                {
                    // 收到未知命令
                    R_SCI_UART_Write(&UART_4_ctrl, (uint8_t *)"RECEIVED: CMD\n", strlen("RECEIVED: CMD\n"));
                }
                // --- 命令处理结束 ---

                // 4. 重置索引和缓冲区，准备接收下一条命令
                rx_index = 0;
                memset(rx_buffer, 0, sizeof(rx_buffer));
            }
//            switch(p_args->data)
//            {
//                case '1':
//                {
//                    FSP_LED1_TOGGLE;
//                }
//                case '2':
//                {
//                    static uint8_t rx_temp; 
//                    rx_temp = (uint8_t)(p_args->data); // 获取接收到的数据
//            
//                    R_SCI_UART_Write(&UART_4_ctrl, &rx_temp, 1);
//                    // 发送回去
//                }
//            }       
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