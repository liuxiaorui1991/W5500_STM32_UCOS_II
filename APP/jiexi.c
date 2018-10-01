#include"jiexi.h"

void Response_warnning(unsigned char warn_num){}//警告
void Response_fault(void){}           //校验不合格
void Response_0x03(int comnum) //2、读取单个寄存器，回复帧一共七个字节
{
	USART_SendData(USART1, 0x28);
}
void Response_0x04(int comnum) //3、读取多个寄存器
{
	USART_SendData(USART1, 0x28);
}
void Response_0x06(int comnum) //4、写入单个寄存器
{
	USART_SendData(USART1, 0x28);
}
void Response_0x10(int comnum) //5、写入多个寄存器
{
	USART_SendData(USART1, 0x28);
}
void Send_frame_ct0(unsigned char num)
{
	USART_SendData(USART1, 0x28);
}
void Send_frame_ct1(unsigned char num)
{
 USART_SendData(USART1, 0x28);
}
