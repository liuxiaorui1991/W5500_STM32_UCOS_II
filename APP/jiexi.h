
#ifndef _JIEXI_H_ 
#define _JIEXI_H_ 

#include "stm32f10x.h"
#include "modbus.h"
//#include "adc.h"

void Response_warnning(unsigned char warn_num);//警告
void Response_fault(void);           //校验不合格
void Response_0x03(int comnum); //2、读取单个寄存器，回复帧一共七个字节
void Response_0x04(int comnum); //3、读取多个寄存器
void Response_0x06(int comnum); //4、写入单个寄存器
void Response_0x10(int comnum); //5、写入多个寄存器

void Send_frame_ct0(unsigned char num);
void Send_frame_ct1(unsigned char num);
#endif



