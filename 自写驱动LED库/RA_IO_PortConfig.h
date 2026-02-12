#ifndef _RA_IO_PortConfig_H__
#define _RA_IO_PortConfig_H__

#include "hal_data.h"                


/*========================================================*/
/*IO引脚Port*/
/*========================================================*/
typedef enum IO_Port
{
	IO_PORT_00 = 0x0000,
	IO_PORT_01 = 0x0100,
	IO_PORT_02 = 0x0200,
	IO_PORT_03 = 0x0300,
	IO_PORT_04 = 0x0400,
	IO_PORT_05 = 0x0500,
	IO_PORT_06 = 0x0600,
	IO_PORT_07 = 0x0700,
	IO_PORT_08 = 0x0800,
	IO_PORT_09 = 0x0900,
	IO_PORT_10 = 0x0A00,
	IO_PORT_11 = 0x0B00,
	IO_PORT_12 = 0x0C00,
	IO_PORT_13 = 0x0D00,
	IO_PORT_14 = 0x0E00,
	IO_PORT_15 = 0x0F00,
}IO_Port_t;

/*========================================================*/
/*IO引脚Pin*/
/*========================================================*/
typedef enum IO_Pin
{
	IO_Pin_00 = 0x0000,
	IO_Pin_01 = 0x0001,
	IO_Pin_02 = 0x0002,
	IO_Pin_03 = 0x0003,
	IO_Pin_04 = 0x0004,
	IO_Pin_05 = 0x0005,
	IO_Pin_06 = 0x0006,
	IO_Pin_07 = 0x0007,
	IO_Pin_08 = 0x0008,
	IO_Pin_09 = 0x0009,
	IO_Pin_10 = 0x000A,
	IO_Pin_11 = 0x000B,
	IO_Pin_12 = 0x000C,
	IO_Pin_13 = 0x000D,
	IO_Pin_14 = 0x000E,
	IO_Pin_15 = 0x000F,
}IO_Pin_t;

/*========================================================*/
/*IO引脚模式*/
/*========================================================*/
typedef enum
{
	IO_Mode_GPIO = 0, 	//普通GPIO功能
	IO_Mode_AF = 1, 	//复用功能
	IO_Mode_AN = 2, 	//模拟输入输出功能
}IO_Mode_t;

/*========================================================*/
/*IO引脚输入输出方向*/
/*========================================================*/
typedef enum
{
	IO_Dir_Input = 0, 	//输入模式
	IO_Dir_Output = 1,	//输出模式
}IO_Dir_t;

/*========================================================*/
/*IO引脚输出类型*/
/*========================================================*/
typedef enum
{
	IO_OutPut_Type_PP = 0x00, 	//推挽输出
	IO_OutPut_Type_OD = 0x01,	//开漏输出
}IO_OutPut_Type_t;

/*========================================================*/
/*IO引脚输出能力*/
/*========================================================*/
typedef enum
{
	IO_OutPut_Drive_Low = 0, 	//低驱动
	IO_OutPut_Drive_Middle = 1, //中驱动
	IO_OutPut_Drive_HSHD = 2, 	//次高驱动
	IO_OutPut_Drive_HIGH = 3, 	//高驱动
}IO_OutPut_Drive_t;

/*========================================================*/
/*IO引脚输出电平*/
/*========================================================*/
typedef enum
{
	IO_OUTPut_Low = 0, 		//低电平输出
	IO_OUTPut_High = 1, 	//高电平输出

}IO_OUTPut_t;

/*========================================================*/
/*IO引脚输入上下拉*/
/*========================================================*/
typedef enum
{
	IO_No_Pull = 0x00u, 	//无上下拉
	IO_Pull_Up = 0x01u, 	//上拉输入
	IO_Pull_Down = 0x02u, 	//下拉输入

}IO_Pull_Up_Down_t;

/*========================================================*/
/*IO初始化结构体*/
/*========================================================*/
typedef struct
{
	IO_Port_t Port;
	IO_Pin_t Pin;
	IO_Mode_t Mode;
	IO_Dir_t Dir;
	IO_OutPut_Type_t OutPut_type;
	IO_OutPut_Drive_t Drive;
	IO_OUTPut_t OutPut;
	IO_Pull_Up_Down_t Pull;
}IOPORT_Init_t;


uint32_t IOPORT_PinRead(IO_Port_t Port,IO_Pin_t Pin);
void IOPORT_PinWrite(IO_Port_t Port,IO_Pin_t Pin,IO_OUTPut_t OUTPut);
void IOPORT_PinToggle(IO_Port_t Port,IO_Pin_t Pin);
void IOPORT_ProtectAccessEnable();
void IOPORT_ProtectAccessDisable();
void IOPORT_Init(IOPORT_Init_t *IOport_Init);

#endif