/******************** (C) COPYRIGHT 2014  **************************************
 * �ļ���  ��led.c        
 * ʵ��ƽ̨��STM32������
 * Ӳ�����ӣ�-----------------
 *          | PC1  - LED1     |
 *          | PC3  - LED2     |
 *          | PC13 - LED3     |
 *           -----------------
 * ��汾  ��ST3.5.0
 * ����    ��WuMing
 * QQȺ	   ��131650262
 * ����	   ��2014/03/24
**********************************************************************************/
#include "led.h"

/*
 * ��������LED_GPIO_Config
 * ����  ������LED�õ���I/O��
 * ����  ����
 * ���  ����
 */

void LED_GPIO_Config(void)
{
	/*
	GPIO_InitTypeDef GPIO_InitStructure;//����GPIO�ṹ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
	
	//LED1->PC2,LED2->PC3,LED3->PC13 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������ģʽ
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ������GPIO
	
	GPIO_SetBits(GPIOC, GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_13);	 // turn off all led
	*/
}

/******************* Future I am ~~~ *****END OF FILE****/
