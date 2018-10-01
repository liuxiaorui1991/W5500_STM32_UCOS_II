
#include"modbus.h"
#include"jiexi.h"

//********************������ı������Թ���*************************//

unsigned char Interrupt_Flag=0;      //�жϱ�־

char register_address=0;             //ָ��Ҫ��ļĴ����׵�ַ
char read_len=0;  //ָ��Ҫ����ͨ����
unsigned char *T;
unsigned char TBUF[Process_buffer];
unsigned short Tcrc=0;               //���㷢������֡��CRC16��

//******************************����0���ò���***********************************//
//����ͨѶջ�ṹ0
unsigned char Rstack_ct0[Read_buffer]; //����ջ���洢��ʼ����
int frame_amount_ct0=0;                //�ϸ��˵��֡��������֡�ĸ���
int Rstack_pointer_ct0=0;              //����ջ����ջ��ջͷ
int frame_length_ct0=0;                //������֡���ȼ�����
int frame_com_ct0=0;                   //������֡��Դ 0-�հ� 1-com0 2-com1

int frame_address_ct0[Frame_line];     //��Ż���ջ��ÿ��֡��֡ͷ��ַ��
int frame_len_ct0[Frame_line];         //����ջ��ÿ������֡�ĳ��ȱ�
int Com_num_ct0[Frame_line];           //���ÿ��֡�����ĸ�����,0-�հ� 1-com0 2-com1

unsigned long Broken_frame_ct0=0;//��֡��־λct0

//ͨѶ��־λ0
  
unsigned char frame_recieve_ct0=0;       //1_�յ�֡ 0_��֡
unsigned char data_come_ct0=0;           //1_���������� 0_����������
unsigned char first_frame_ct0=0;         //��������֡��־
unsigned char RBUF_length_ct0=0;         //ת����������֡����
int  Uartnum_ct0=0;                     //����֡�Ĵ�����Դ

unsigned char RBUF_ct0[Process_buffer];
unsigned char *R_ct0;
unsigned short Rcrc_ct0=0;               //�����������֡��CRC16��
unsigned char crchi_ct0=0;
unsigned char crclo_ct0=0;


//*******************************����1���ò���*********************************//
//����ͨѶջ�ṹ1
unsigned char Rstack_ct1[Read_buffer]; //����ջ���洢��ʼ����
int frame_amount_ct1=0;                //�ϸ��˵��֡��������֡�ĸ���
int Rstack_pointer_ct1=0;              //����ջ����ջ��ջͷ
int frame_length_ct1=0;                //������֡���ȼ�����
int frame_com_ct1=0;                   //������֡��Դ 0-�հ� 1-com0 2-com1

int frame_address_ct1[Frame_line];     //��Ż���ջ��ÿ��֡��֡ͷ��ַ��
int frame_len_ct1[Frame_line];         //����ջ��ÿ������֡�ĳ��ȱ�
int Com_num_ct1[Frame_line];           //���ÿ��֡�����ĸ�����,0-�հ� 1-com0 2-com1

unsigned long Broken_frame_ct1=0;//��֡��־λct1


//ͨѶ��־λ1
unsigned char frame_recieve_ct1=0;       //1_�յ�֡ 0_��֡
unsigned char data_come_ct1=0;           //1_���������� 0_����������
unsigned char first_frame_ct1=0;         //��������֡��־
unsigned char RBUF_length_ct1=0;         //ת����������֡����
int  Uartnum_ct1 =0;                     //����֡�Ĵ�����Դ


unsigned char RBUF_ct1[Process_buffer];
unsigned char *R_ct1;
unsigned short Rcrc_ct1=0;               //�����������֡��CRC16��
unsigned char crchi_ct1=0;
unsigned char crclo_ct1=0;


/* CRC ��λ�ֽ�ֵ�� */
static unsigned char auchCRCHi[] = {
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
} ;
/* CRC��λ�ֽ�ֵ��*/
static unsigned char auchCRCLo[] = {
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};

unsigned short do_crc_16(unsigned char *puchMsg,int usDataLen)
{
  unsigned short crc=0;
  unsigned char uchCRCHi = 0xFF ; /* ��CRC�ֽڳ�ʼ�� */
  unsigned char uchCRCLo = 0xFF ; /* ��CRC �ֽڳ�ʼ�� */
  unsigned uIndex =0; /* CRCѭ���е����� */
  usDataLen=usDataLen-2;//���������֡��CRC�룬������������

  while (usDataLen--) /* ������Ϣ������ */
  {
    uIndex = uchCRCHi ^ *puchMsg++ ; /* ����CRC */
    uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
    uchCRCLo = auchCRCLo[uIndex] ;
    
  }
    
    crc=(uchCRCHi<<8|uchCRCLo);
    return(crc);
  }


void modbus_service_ct0(void)
{
  int address=frame_address_ct0[0];
  //S1:��֡����(FIFO)����֡����RBUF�У�֡��������ջ��������֡����һ
    //����RBUF
    int i=0;
    for(;i<frame_len_ct0[0]-3;i++)
    {
      if((address+2+i)==Read_buffer)//������֡�Ǻ��ջͷ��ջβ��
      {RBUF_ct0[i]=Rstack_ct0[(address+i+1)];
       address=-1*(i+2);}
      else
       RBUF_ct0[i]=Rstack_ct0[(address+i+1)];      
    }
    RBUF_length_ct0=frame_len_ct0[0]-3;
    Uartnum_ct0=Com_num_ct0[0];
    //֡������ջ
     //_disable_interrupt();
		__disable_irq();//����core_cm3.h��(#define __disable_irq __disable_interrupt)
		
    for(i=0;i<=(frame_amount_ct0-1);i++) //����Ҫע�⣬����֡����Ϊ�˴�֡ͷ��ַ���õ�
    {                              //��Ԥ����ԣ�������<=
      frame_address_ct0[i]=frame_address_ct0[i+1];
    }
    frame_address_ct0[frame_amount_ct0]=0;
    for(i=0;i<(frame_amount_ct0-1);i++)  //����ջ����Ԥ��ģʽ��������<
    {frame_len_ct0[i]=frame_len_ct0[i+1];
    }  
    frame_len_ct0[frame_amount_ct0-1]=0;
    for(i=0;i<(frame_amount_ct0-1);i++)  //������Դջ����Ԥ��ģʽ��������<
    {Com_num_ct0[i]=Com_num_ct0[i+1];
    }  
    Com_num_ct0[frame_amount_ct0-1]=0;    
    
    frame_amount_ct0--;       //���430ϵͳ�ڴ�ָ��ִ��ǰ˲������֡�жϣ��������ֶ�֡��
    //enable_interrupt();  //���ж�//������Ƶ���Ʋ�����������ֵĸ�����˵Ҳ�м�ǧ���֮һ
                           //.....��������򵥴ֱ���ֱ��ͣ���жϣ�����ȡ����֮��
                          //�Ǵ�֡�������յ�����Բ���FAULT�ظ�Ҫ��֡�ط�  
    __enable_irq();        //����core_cm3.h��(#define __disable_irq __disable_interrupt)		
   //S2:����CRC��
   if(RBUF_ct0[0]==LOCAL_ID)
   { Rcrc_ct0=do_crc_16(R_ct0,RBUF_length_ct0);
     if(((Rcrc_ct0>>8)==(RBUF_ct0[RBUF_length_ct0-2]))&&((unsigned char)Rcrc_ct0)==(RBUF_ct0[RBUF_length_ct0-1]))
     { 

       switch(RBUF_ct0[1])               //����ķ��ͺ������ļ� " send_frame.c "�ļ�
       {//����ָ��
        case 0x03: Response_0x03(1);break;
        case 0x04: Response_0x04(1);break;
        case 0x06: Response_0x06(1);break;
        case 0x10: Response_0x10(1);break;
        //��Чָ��
        default:Response_warnning(3);break;       
      }
     }
   }
}

void modbus_service_ct1(void)
{
  int address=frame_address_ct1[0];
  //S1:��֡����(FIFO)����֡����RBUF�У�֡��������ջ��������֡����һ
    //����RBUF
    int i=0;
    for(;i<frame_len_ct1[0]-3;i++)
    {
      if((address+2+i)==Read_buffer)//������֡�Ǻ��ջͷ��ջβ��
      {RBUF_ct1[i]=Rstack_ct1[(address+i+1)];
       address=-1*(i+2);}
      else
       RBUF_ct1[i]=Rstack_ct1[(address+i+1)];      
    }
    RBUF_length_ct1=frame_len_ct1[0]-3;
    Uartnum_ct1=Com_num_ct1[0];
    //֡������ջ
    //_disable_interrupt();
		__disable_irq();//����core_cm3.h��(#define __disable_irq __disable_interrupt)
    for(i=0;i<=(frame_amount_ct1-1);i++) //����Ҫע�⣬����֡����Ϊ�˴�֡ͷ��ַ���õ�
    {                              //��Ԥ����ԣ�������<=
      frame_address_ct1[i]=frame_address_ct1[i+1];
    }
    frame_address_ct1[frame_amount_ct1]=0;
    for(i=0;i<(frame_amount_ct1-1);i++)  //����ջ����Ԥ��ģʽ��������<
    {frame_len_ct1[i]=frame_len_ct1[i+1];
    }  
    frame_len_ct1[frame_amount_ct1-1]=0;
    for(i=0;i<(frame_amount_ct1-1);i++)  //������Դջ����Ԥ��ģʽ��������<
    {Com_num_ct1[i]=Com_num_ct1[i+1];
    }  
    Com_num_ct1[frame_amount_ct1-1]=0;    
    
    frame_amount_ct1--;       //���430ϵͳ�ڴ�ָ��ִ��ǰ˲������֡�жϣ��������ֶ�֡��
    //enable_interrupt();  //���ж�//������Ƶ���Ʋ�����������ֵĸ�����˵Ҳ�м�ǧ���֮һ
                          //.....��������򵥴ֱ���ֱ��ͣ���жϣ�����ȡ����֮��
                          //�Ǵ�֡�������յ�����Բ���FAULT�ظ�Ҫ��֡�ط�   
		
		__enable_irq();        //����core_cm3.h��(#define __disable_irq __disable_interrupt)		
		
   //S2:����CRC��
   if(RBUF_ct1[0]==LOCAL_ID)
   { Rcrc_ct1=do_crc_16(R_ct1,RBUF_length_ct1);
     if(((Rcrc_ct1>>8)==(RBUF_ct1[RBUF_length_ct1-2]))&&((unsigned char)Rcrc_ct1)==(RBUF_ct1[RBUF_length_ct1-1]))
     {  
        switch(RBUF_ct1[1])               //����ķ��ͺ������ļ� " send_frame.c "�ļ�
        {
         //����ָ��
         case 0x03: Response_0x03(2);break;
         case 0x04: Response_0x04(2);break;
         case 0x06: Response_0x06(2);break;
         case 0x10: Response_0x10(2);break;           
         //��Чָ��
         default:Response_warnning(3);break;       
        }
      }
    }
}






