#include "includes.h"

//void Task_LED(void *p_arg)
//{
// 	(void)p_arg;//��û���õ���Ϊ��ֹ��������ʾ����
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
    {                     //1������0������֡��
      modbus_service_ct0();    //modbus_servic�Ĺ��ܲ��Ǵ���һ��֡��
      if(frame_amount_ct0>0)   //���������������ջ�е���������֡
      frame_amount_ct0--;      
    }
    if(frame_amount_ct1!=0)    //2������1������֡��
    {                   //modbus_servic�Ĺ��ܲ��Ǵ���һ��֡��
      modbus_service_ct1();    //���������������ջ�е���������֡          
      if(frame_amount_ct1>0)
      frame_amount_ct1--;      
    }
   if(r>=3000)                //4������Ƶ���ƣ�ָʾ����-�ϵ�������������˸
   { //if(LED==0)LED=1;
     //else LED=0;
     r=0;    
   }
  }

}


void Task_TCP_UDP(void *p_arg)
{
/********************************************************/
	OSTimeDlyHMSM(0,0,0,50);//�ճ�50ms��modbus_task��ɳ�ʼ��
	
		
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
	 }//���ö˿�
	} // end of Main loop		          	  
}// end of Main function	    
















