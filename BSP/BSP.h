#ifndef __BSP_H__
#define __BSP_H__

void SysTick_init(void);
void BSP_Init(void);




void USART1_Config(void);
void NVIC_Configuration(void);
void TIM2_NVIC_Configuration(void);
void TIM2_Configuration(void);

#endif //__BSP_H__


