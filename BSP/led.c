/******************** (C) COPYRIGHT 2014  **************************************
 * 文件名  ：led.c        
 * 实验平台：STM32开发板
 * 硬件连接：-----------------
 *          | PC1  - LED1     |
 *          | PC3  - LED2     |
 *          | PC13 - LED3     |
 *           -----------------
 * 库版本  ：ST3.5.0
 * 作者    ：WuMing
 * QQ群	   ：131650262
 * 日期	   ：2014/03/24
**********************************************************************************/
#include "led.h"

/*
 * 函数名：LED_GPIO_Config
 * 描述  ：配置LED用到的I/O口
 * 输入  ：无
 * 输出  ：无
 */

void LED_GPIO_Config(void)
{
	/*
	GPIO_InitTypeDef GPIO_InitStructure;//声明GPIO结构
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
	
	//LED1->PC2,LED2->PC3,LED3->PC13 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出模式
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化外设GPIO
	
	GPIO_SetBits(GPIOC, GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_13);	 // turn off all led
	*/
}

/******************* Future I am ~~~ *****END OF FILE****/
