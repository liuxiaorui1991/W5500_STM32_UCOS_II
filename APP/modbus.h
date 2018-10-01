#ifndef _MODBUS_H_ 
#define _MODBUS_H_ 

//**************************************************************************//
//*********************************宏声明区*********************************//
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
#define Read_buffer     150     //接收缓冲区的大小_byte(这个栈溢出压力较小)
#define Frame_line      20      //帧队列个数//(关键怕这个溢出)
#define Process_buffer  55      //数据处理缓冲区的大小(别溢出)
#define Data_buffer     56      //寄存器列表长度

unsigned short do_crc_16(unsigned char *puchMsg,int usDataLen);
//**************************************************************************//
//***********************************变量声明区*****************************//
//**************************************************************************//

//********************发送向的变量可以共用*************************//

extern unsigned char Interrupt_Flag;      //中断标志

extern char register_address;             //指令要求的寄存器首地址
extern char read_len;  //指令要读的通道数
extern unsigned char *T;
extern unsigned char TBUF[Process_buffer];
extern unsigned short Tcrc;               //计算发送数据帧的CRC16码

//******************************串口0设置参数*******************************//
//各种通讯栈结构0
extern unsigned char Rstack_ct0[Read_buffer]; //缓冲栈，存储初始数据
extern int frame_amount_ct0;                //严格的说是帧队列里存放帧的个数
extern int Rstack_pointer_ct0;              //缓冲栈出入栈的栈头
extern int frame_length_ct0;                //缓冲区帧长度计数器
extern int frame_com_ct0;                   //缓冲区帧来源 0-空白 1-com0 2-com1

extern int frame_address_ct0[Frame_line];     //存放缓冲栈中每个帧的帧头地址表
extern int frame_len_ct0[Frame_line];         //缓冲栈中每个数据帧的长度表
extern int Com_num_ct0[Frame_line];           //标记每个帧来自哪个串口,0-空白 1-com0 2-com1

extern unsigned long Broken_frame_ct0;//断帧标志位ct0

//通讯标志位0
extern unsigned char frame_recieve_ct0;       //1_收到帧 0_无帧
extern unsigned char data_come_ct0;           //1_串口有数据 0_串口无数据
extern unsigned char first_frame_ct0;         //开机后首帧标志
extern unsigned char RBUF_length_ct0;         //转到缓存区的帧长度
extern int  Uartnum_ct0;                     //数据帧的串口来源

extern unsigned char RBUF_ct0[Process_buffer];
extern unsigned char *R_ct0;
extern unsigned short Rcrc_ct0;               //计算接收数据帧的CRC16码
extern unsigned char crchi_ct0;
extern unsigned char crclo_ct0;


//*******************************串口1设置参数******************************//
//各种通讯栈结构1
extern unsigned char Rstack_ct1[Read_buffer]; //缓冲栈，存储初始数据
extern int frame_amount_ct1;                //严格的说是帧队列里存放帧的个数
extern int Rstack_pointer_ct1;              //缓冲栈出入栈的栈头
extern int frame_length_ct1;                //缓冲区帧长度计数器
extern int frame_com_ct1;                   //缓冲区帧来源 0-空白 1-com0 2-com1

extern int frame_address_ct1[Frame_line];     //存放缓冲栈中每个帧的帧头地址表
extern int frame_len_ct1[Frame_line];         //缓冲栈中每个数据帧的长度表
extern int Com_num_ct1[Frame_line];           //标记每个帧来自哪个串口,0-空白 1-com0 2-com1

extern unsigned long Broken_frame_ct1;//断帧标志位ct1


//通讯标志位1
extern unsigned char frame_recieve_ct1;       //1_收到帧 0_无帧
extern unsigned char data_come_ct1;           //1_串口有数据 0_串口无数据
extern unsigned char first_frame_ct1;         //开机后首帧标志
extern unsigned char RBUF_length_ct1;         //转到缓存区的帧长度
extern int  Uartnum_ct1;                     //数据帧的串口来源


extern unsigned char RBUF_ct1[Process_buffer];
extern unsigned char *R_ct1;
extern unsigned short Rcrc_ct1;               //计算接收数据帧的CRC16码
extern unsigned char crchi_ct1;
extern unsigned char crclo_ct1;


//**************************************************************************//
//*****************************函数声明区***********************************//
//**************************************************************************//
void modbus_service_ct0(void);
void modbus_service_ct1(void);


void Response_warnning(unsigned char warn_num);//警告
void Response_fault(void);           //校验不合格
void Response_0x03(int comnum); //2、读取单个寄存器，回复帧一共七个字节
void Response_0x04(int comnum); //3、读取多个寄存器
void Response_0x06(int comnum); //4、写入单个寄存器
void Response_0x10(int comnum); //5、写入多个寄存器

#endif
