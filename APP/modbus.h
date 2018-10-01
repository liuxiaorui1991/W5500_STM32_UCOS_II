#ifndef _MODBUS_H_ 
#define _MODBUS_H_ 

//**************************************************************************//
//*********************************��������*********************************//
//**************************************************************************//

#define LOCAL_ID          0x02
#define HOST_ID           0x00
#define Modbus_start      0x3A
#define Modbus_end1       0x0D
#define Modbus_end2       0x0A
/*
#define LED      P3OUT_bit.P3OUT_3
#define IO_1     P5OUT_bit.P5OUT_4
#define IO_2     P5OUT_bit.P5OUT_5
#define IO_3     P5OUT_bit.P5OUT_6
#define IO_4     P5OUT_bit.P5OUT_7
#define IO_5     P5OUT_bit.P5OUT_3
#define IO_6     P5OUT_bit.P5OUT_2
#define IO_7     P5OUT_bit.P5OUT_1
#define IO_8     P5OUT_bit.P5OUT_0
*/
#define Read_buffer     150     //���ջ������Ĵ�С_byte(���ջ���ѹ����С)
#define Frame_line      20      //֡���и���//(�ؼ���������)
#define Process_buffer  55      //���ݴ��������Ĵ�С(�����)
#define Data_buffer     56      //�Ĵ����б���

unsigned short do_crc_16(unsigned char *puchMsg,int usDataLen);
//**************************************************************************//
//***********************************����������*****************************//
//**************************************************************************//

//********************������ı������Թ���*************************//

extern unsigned char Interrupt_Flag;      //�жϱ�־

extern char register_address;             //ָ��Ҫ��ļĴ����׵�ַ
extern char read_len;  //ָ��Ҫ����ͨ����
extern unsigned char *T;
extern unsigned char TBUF[Process_buffer];
extern unsigned short Tcrc;               //���㷢������֡��CRC16��

//******************************����0���ò���*******************************//
//����ͨѶջ�ṹ0
extern unsigned char Rstack_ct0[Read_buffer]; //����ջ���洢��ʼ����
extern int frame_amount_ct0;                //�ϸ��˵��֡��������֡�ĸ���
extern int Rstack_pointer_ct0;              //����ջ����ջ��ջͷ
extern int frame_length_ct0;                //������֡���ȼ�����
extern int frame_com_ct0;                   //������֡��Դ 0-�հ� 1-com0 2-com1

extern int frame_address_ct0[Frame_line];     //��Ż���ջ��ÿ��֡��֡ͷ��ַ��
extern int frame_len_ct0[Frame_line];         //����ջ��ÿ������֡�ĳ��ȱ�
extern int Com_num_ct0[Frame_line];           //���ÿ��֡�����ĸ�����,0-�հ� 1-com0 2-com1

extern unsigned long Broken_frame_ct0;//��֡��־λct0

//ͨѶ��־λ0
extern unsigned char frame_recieve_ct0;       //1_�յ�֡ 0_��֡
extern unsigned char data_come_ct0;           //1_���������� 0_����������
extern unsigned char first_frame_ct0;         //��������֡��־
extern unsigned char RBUF_length_ct0;         //ת����������֡����
extern int  Uartnum_ct0;                     //����֡�Ĵ�����Դ

extern unsigned char RBUF_ct0[Process_buffer];
extern unsigned char *R_ct0;
extern unsigned short Rcrc_ct0;               //�����������֡��CRC16��
extern unsigned char crchi_ct0;
extern unsigned char crclo_ct0;


//*******************************����1���ò���******************************//
//����ͨѶջ�ṹ1
extern unsigned char Rstack_ct1[Read_buffer]; //����ջ���洢��ʼ����
extern int frame_amount_ct1;                //�ϸ��˵��֡��������֡�ĸ���
extern int Rstack_pointer_ct1;              //����ջ����ջ��ջͷ
extern int frame_length_ct1;                //������֡���ȼ�����
extern int frame_com_ct1;                   //������֡��Դ 0-�հ� 1-com0 2-com1

extern int frame_address_ct1[Frame_line];     //��Ż���ջ��ÿ��֡��֡ͷ��ַ��
extern int frame_len_ct1[Frame_line];         //����ջ��ÿ������֡�ĳ��ȱ�
extern int Com_num_ct1[Frame_line];           //���ÿ��֡�����ĸ�����,0-�հ� 1-com0 2-com1

extern unsigned long Broken_frame_ct1;//��֡��־λct1


//ͨѶ��־λ1
extern unsigned char frame_recieve_ct1;       //1_�յ�֡ 0_��֡
extern unsigned char data_come_ct1;           //1_���������� 0_����������
extern unsigned char first_frame_ct1;         //��������֡��־
extern unsigned char RBUF_length_ct1;         //ת����������֡����
extern int  Uartnum_ct1;                     //����֡�Ĵ�����Դ


extern unsigned char RBUF_ct1[Process_buffer];
extern unsigned char *R_ct1;
extern unsigned short Rcrc_ct1;               //�����������֡��CRC16��
extern unsigned char crchi_ct1;
extern unsigned char crclo_ct1;


//**************************************************************************//
//*****************************����������***********************************//
//**************************************************************************//
void modbus_service_ct0(void);
void modbus_service_ct1(void);


void Response_warnning(unsigned char warn_num);//����
void Response_fault(void);           //У�鲻�ϸ�
void Response_0x03(int comnum); //2����ȡ�����Ĵ������ظ�֡һ���߸��ֽ�
void Response_0x04(int comnum); //3����ȡ����Ĵ���
void Response_0x06(int comnum); //4��д�뵥���Ĵ���
void Response_0x10(int comnum); //5��д�����Ĵ���

#endif
