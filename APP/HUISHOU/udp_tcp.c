
#include "udp_tcp.h"


u8 Ethernet_TBUF[20]={0x3a,0x02,0x6,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0xff};

/*************************************����IP��������***************************************************/		
void local_ip_config()
{
 IP4_ADDR(&ipaddr_tcp_target,10,0,0,182);//ԭ����������IP�ű�����ͬ
 IP4_ADDR(&ipaddr_udp_target,10,0,0,182);//��ΪҪ���ݵ�һ����
}
	
/*************************************UDP�������***************************************************/	
	
struct udp_pcb *udp_pcb;
struct pbuf* buff_udp;
struct ip_addr ipaddr_udp_target;
	
err_t UDP_APP_INIT(struct udp_pcb *udp_pcb,struct ip_addr *ipaddr_udp_target,uint32_t service_port)
{
 err_t err_udp;
	
 udp_pcb= udp_new();
 if(!udp_pcb)
	{ return 1;} //ERR_OK��0�����Է���1������ζ��ʧ��

   //err_udp=udp_bind(udp_pcb,ipaddr_udp_target,service_port);	//ֻ�����ض�IP������֡
	err_udp=udp_bind(udp_pcb,IP_ADDR_ANY,service_port); //��������IP������֡
	//udp_connect(udp_pcb, IP_ADDR_ANY, service_port);   // ��Զ��������������
	udp_connect(udp_pcb, ipaddr_udp_target, service_port);
	if(err_udp!=ERR_OK)
	{return 1;}
	
	udp_recv(udp_pcb,recv_callback_udp,NULL);
	
	return ERR_OK;
}


void recv_callback_udp(void *arg,struct udp_pcb *upcb,struct pbuf *ouc_buf,struct ip_addr *addr,u16_t port)
{ 
    struct ip_addr destAddr = *addr;  
     struct pbuf *buf; //Ҫ���͵�����
	
    //if(pkt_buf != NULL)                     
    //{udp_sendto(upcb,pkt_buf,&destAddr,port);}
    pbuf_free(ouc_buf);

		
		buf = pbuf_alloc(PBUF_RAW,sizeof(Ethernet_TBUF),PBUF_POOL); 
		//memcpy(TBUF, (char *)buf->payload, buf->len);
		buf->next=0x00000000;
		buf->payload=Ethernet_TBUF;
		buf->tot_len=0x14;
		buf->len=0x14;
		buf->type=0x03;
		buf->flags=0x00;
		buf->ref=0x0001;
    if(buf != NULL)                     
    {udp_sendto(upcb,buf,&destAddr,port);}
    pbuf_free(buf);
  }

	

	
	
/*************************************TCP�������***************************************************/
	
struct tcp_pcb *tcp_pcb;
struct pbuf* buff_tcp;
struct ip_addr ipaddr_tcp_target;	
	
err_t TCP_APP_INIT(struct tcp_pcb *tcp_pcb,struct ip_addr *ipaddr_tcp_target,uint32_t service_port)
{
 err_t err_tcp;
 struct tcp_pcb *tcp_pcb_listening;	

 tcp_pcb= tcp_new();
 if(tcp_pcb==NULL)
	{ return 1;} //ERR_OK��0�����Է���1������ζ��ʧ��

   err_tcp=tcp_bind(tcp_pcb,ipaddr_tcp_target,service_port);	//ֻ�����ض�IP������֡
   //�������Ĵ󲿷ִ������ڼ�������Ĳ����Ƿ���ʣ�������ʽ�������ָ����
	 //pcb���ƿ飬����ERR_OK. ��������ʽ�����ERR_USE(�˿��ѱ�ʹ��)
	
	/**********************���÷�����/�ͻ���(����������)*******************************/
	tcp_pcb_listening=tcp_listen(tcp_pcb);
	//���º�ԭ�������ͷţ�������һ���µ�TCPָ��
	//tcp_pcb_listening=tcp_listen_with_backlog(tcp_pcb,3);
	//���������tcp_listen()����һ�£�ֻ��������TCP�����ĸ���
	//Ҫ�������������Ҫ��lwippopt.h������TCP_LISTEN_BACKLOG=1	
	tcp_accept(tcp_pcb_listening, tcp_Client_connected);  /* Specify the function to be called when a connection is established */   
	//��TCP���Ӳ��������״̬
	
	
	
	//�����ǿͻ��˵����ã����ܲ�����
	 //tcp_connect(tcp_pcb_listening, ipaddr_tcp_target, service_port, tcp_server_accept);  
	//���ﲻ��һ�����������Ǽ���listening���ͻ��������������ӷ�����
/***********************************************************************************/

	
	if((err_tcp!=ERR_OK)||(tcp_pcb_listening==NULL))
	{return 1;}

	return ERR_OK;

}


err_t tcp_Client_connected(void *arg, struct tcp_pcb *pcb, err_t err)//�������������Ӻ�Ļص�����
{
 tcp_setprio(pcb, TCP_PRIO_MIN);//�������ȼ������ж������ʱ�������
 tcp_recv(pcb, recv_callback_tcp); //��tcp�����½��յ����ݵĻص�����	 
	
	return ERR_OK;
}


err_t recv_callback_tcp(void *arg,struct tcp_pcb *tpcb, struct pbuf *ouc_buf,err_t err) //���յ�����֡ʱ�Ļص�����
{

	tcp_write(tpcb,Ethernet_TBUF,sizeof(Ethernet_TBUF),0);//0��ʾ���͵����ݲ��ظ��Ƶ��ڴ滺����
	pbuf_free(ouc_buf);
 return ERR_OK;
}


err_t tcp_server_accept(void *arg, struct tcp_pcb *pcb, err_t err)//��Ϊ�ͻ���ʱ���ӵ�������ʱ�Ļص�����
{
/*�˺�����TCP������SYN_RECV״̬ת��ESTABLISED֮��ʱ������
Ӧ�ò����������ص���������һЩ��ʼ����filter�Ĺ�������ͨ������
��鷵��ERR_OK��֪ͨ�Զ�ջ���ܴ����ӣ����򷵻����������룬֪ͨ��ջRST
��ǰ����	
*/

return ERR_OK;
}	
	
	
	


	
	
	
	
