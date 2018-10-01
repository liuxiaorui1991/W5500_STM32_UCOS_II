
#include "includes.h"

/**
  * @brief  使能SPI时钟
  * @retval None
  */
static void SPI_RCC_Configuration(void)
{ //GPIOB,GPIOC 序列初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
}
/**
  * @brief  配置指定SPI的引脚
  * @retval None
  */
static void SPI_GPIO_Configuration(void)
{ 
	GPIO_InitTypeDef GPIO_InitStruct;
	//PB12->CS,PB13->SCK,PB14->MISO,PB15->MOSI		 					 
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_13 | GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	//初始化片选输出引脚
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	//初始化中断IO
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//带上拉电阻的IO输入
	//GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource6);
	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降延触发中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	//EXIT_GenerateSWInterrupt(EXTI_Line6);
	
	NVIC_InitTypeDef NVIC_InitStructure;    
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; //PPP外部中短线
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
/**
  * @brief  根据外部SPI设备配置SPI相关参数
  * @retval None
  */
void SPI_Configuration(void)
{
	SPI_InitTypeDef SPI_InitStruct;

	SPI_RCC_Configuration();
	SPI_GPIO_Configuration();
	
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStruct.SPI_Direction= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2,&SPI_InitStruct);
	
	SPI_SSOutputCmd(SPI2, ENABLE);
	SPI_Cmd(SPI2, ENABLE);
	
}
/**
  * @brief  写1字节数据到SPI总线
  * @param  TxData 写到总线的数据
  * @retval None
  */
void SPI_WriteByte(uint8_t TxData)
{				 
	while((SPI2->SR&SPI_I2S_FLAG_TXE)==0);	//等待发送区空		  
	SPI2->DR=TxData;	 	  									//发送一个byte 
	while((SPI2->SR&SPI_I2S_FLAG_RXNE)==0); //等待接收完一个byte  
	SPI2->DR;		
}
/**
  * @brief  从SPI总线读取1字节数据
  * @retval 读到的数据
  */
uint8_t SPI_ReadByte(void)
{			 
	while((SPI2->SR&SPI_I2S_FLAG_TXE)==0);	//等待发送区空			  
	SPI2->DR=0xFF;	 	  										//发送一个空数据产生输入数据的时钟 
	while((SPI2->SR&SPI_I2S_FLAG_RXNE)==0); //等待接收完一个byte  
	return SPI2->DR;  						    
}
/**
  * @brief  进入临界区
  * @retval None
  */
void SPI_CrisEnter(void)
{
	__set_PRIMASK(1);
}
/**
  * @brief  退出临界区
  * @retval None
  */
void SPI_CrisExit(void)
{
	__set_PRIMASK(0);
}

/**
  * @brief  片选信号输出低电平
  * @retval None
  */
void SPI_CS_Select(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}
/**
  * @brief  片选信号输出高电平
  * @retval None
  */
void SPI_CS_Deselect(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}
/*********************************END OF FILE**********************************/

