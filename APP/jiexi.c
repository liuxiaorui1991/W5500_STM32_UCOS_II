#include"jiexi.h"

void Response_warnning(unsigned char warn_num){}//����
void Response_fault(void){}           //У�鲻�ϸ�
void Response_0x03(int comnum) //2����ȡ�����Ĵ������ظ�֡һ���߸��ֽ�
{
	USART_SendData(USART1, 0x28);
}
void Response_0x04(int comnum) //3����ȡ����Ĵ���
{
	USART_SendData(USART1, 0x28);
}
void Response_0x06(int comnum) //4��д�뵥���Ĵ���
{
	USART_SendData(USART1, 0x28);
}
void Response_0x10(int comnum) //5��д�����Ĵ���
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
