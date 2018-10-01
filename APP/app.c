#include "includes.h"

//void Task_LED(void *p_arg)
//{
// 	(void)p_arg;//并没有用到，为防止编译器提示警告
//	while(1)
//	{
		
//		LED1(ON);
//		OSTimeDlyHMSM(0,0,0,500);
//		LED1(OFF);
//		OSTimeDlyHMSM(0,0,0,500);
		
//	}	
//}

void Task_MODBUS(void *p_arg)
{
  long r=0;
	R_ct0=RBUF_ct0;
  R_ct1=RBUF_ct1;
  T=TBUF;		
	

  for(;;r++)
  { 
    if(frame_amount_ct0!=0)
    {                     //1、串口0来数据帧了
      modbus_service_ct0();    //modbus_servic的功能不是处理一条帧，
      if(frame_amount_ct0>0)   //而是逐次清理数据栈中的所有数据帧
      frame_amount_ct0--;      
    }
    if(frame_amount_ct1!=0)    //2、串口1来数据帧了
    {                   //modbus_servic的功能不是处理一条帧，
      modbus_service_ct1();    //而是逐次清理数据栈中的所有数据帧          
      if(frame_amount_ct1>0)
      frame_amount_ct1--;      
    }
   if(r>=3000)                //4、开机频闪灯，指示正常-上电后常亮，激活后闪烁
   { //if(LED==0)LED=1;
     //else LED=0;
     r=0;    
   }
  }

}


void Task_TCP_UDP(void *p_arg)
{
/********************************************************/
	OSTimeDlyHMSM(0,0,0,50);//空出50ms给modbus_task完成初始化
	
		
	  SPI_Configuration();
	
		reg_wizchip_cris_cbfunc(SPI_CrisEnter, SPI_CrisExit);	
#if   _WIZCHIP_IO_MODE_ == _WIZCHIP_IO_MODE_SPI_VDM_
	reg_wizchip_cs_cbfunc(SPI_CS_Select, SPI_CS_Deselect);
#elif _WIZCHIP_IO_MODE_ == _WIZCHIP_IO_MODE_SPI_FDM_
	reg_wizchip_cs_cbfunc(SPI_CS_Select, SPI_CS_Deselect);  
#else
   #if (_WIZCHIP_IO_MODE_ & _WIZCHIP_IO_MODE_SIP_) != _WIZCHIP_IO_MODE_SIP_
      #error "Unknown _WIZCHIP_IO_MODE_"
   #else
      reg_wizchip_cs_cbfunc(wizchip_select, wizchip_deselect);
   #endif
#endif
	reg_wizchip_spi_cbfunc(SPI_ReadByte, SPI_WriteByte);	
	
	network_init();

  while ( 1 )
	{	long ret = 0;
	if( (ret = loopback_tcps(SOCK_TCPS, gDATABUF, 5000)) < 0) {
	printf("SOCKET ERROR : %ld\r\n", ret);
	 }//配置端口
	} // end of Main loop		          	  
}// end of Main function	    
















