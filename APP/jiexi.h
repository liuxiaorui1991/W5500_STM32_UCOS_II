
#ifndef _JIEXI_H_ 
#define _JIEXI_H_ 

#include "stm32f10x.h"
#include "modbus.h"
//#include "adc.h"

void Response_warnning(unsigned char warn_num);//����
void Response_fault(void);           //У�鲻�ϸ�
void Response_0x03(int comnum); //2����ȡ�����Ĵ������ظ�֡һ���߸��ֽ�
void Response_0x04(int comnum); //3����ȡ����Ĵ���
void Response_0x06(int comnum); //4��д�뵥���Ĵ���
void Response_0x10(int comnum); //5��д�����Ĵ���

void Send_frame_ct0(unsigned char num);
void Send_frame_ct1(unsigned char num);
#endif



