/******************** (C) COPYRIGHT 2014  **************************************
 * 文件名  ：BSP.c        
 * 实验平台：STM32开发板
 * 库版本  ：ST3.5.0
 * 作者    ：WuMing
 * QQ群	   ：131650262
 * 日期	   ：2014/03/24
 * 描述	   ：包含所有的初始化
**********************************************************************************/
#include "includes.h"
/*
 * 函数名：BSP_Init
 * 描 述 ：时钟初始化、硬件初始化
 * 输 入 ：无
 * 输 出 ：无
 */
void BSP_Init(void)
{
	SystemInit();	  /*配置系统时钟为72M*/
  SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC);//初始化并使能SysTick定时器
}

void SysTick_init(void)
{
}

/**
  * @brief  USART1 GPIO 配置,工作模式配置。9600 8-N-1
  * @param  无
  * @retval 无
  */
void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	/* config USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	/* USART1 GPIO config */
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    
	/* Configure USART1 Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* USART1 mode config */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	
	/* 使能串口1接收中断 */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART1, ENABLE);
}

/// 配置USART1接收中断
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure_TIM; 
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
    NVIC_InitStructure_TIM.NVIC_IRQChannel = TIM2_IRQn;	  
    NVIC_InitStructure_TIM.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure_TIM.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure_TIM.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure_TIM);
}


/// 重定向c库函数printf到USART1
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);		
	
		return (ch);
}

/// 重定向c库函数scanf到USART1
int fgetc(FILE *f)
{
		/* 等待串口1输入数据 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}

void TIM2_NVIC_Configuration(void)
{

}

/*
 * TIM_Period / Auto Reload Register(ARR) = 1000   TIM_Prescaler--71 
 * 中断周期为 = 1/(72MHZ /72) * 10000 = 10ms
 *
 * TIMxCLK/CK_PSC --> TIMxCNT --> TIM_Period(ARR) --> 中断 且TIMxCNT重置为0重新计数 
 */
void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		/* 设置TIM2CLK 为 72MHZ */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    //TIM_DeInit(TIM2);
	
	/* 自动重装载寄存器周期的值(计数值) */
    TIM_TimeBaseStructure.TIM_Period=10000;
	
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
	  /* 时钟预分频数为72 */
    TIM_TimeBaseStructure.TIM_Prescaler= 71;
	
		/* 对外部时钟进行采样的时钟分频,这里没有用到 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
		
    TIM_Cmd(TIM2, ENABLE);																		
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE);		/*先关闭等待使用*/    
}



















