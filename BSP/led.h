#ifndef __LED_H__
#define	__LED_H__

#include "stm32f10x.h"

/* the macro definition to trigger the led on or off 
 * 1 - OFF
 * 0 - ON
 */
#define ON  0
#define OFF 1

#define LED1(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_1);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_1)

#define LED2(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_3);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_3)

#define LED3(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_13);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_13)

void LED_GPIO_Config(void);

#endif /* __LED_H__ */
