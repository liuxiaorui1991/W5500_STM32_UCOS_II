
#include "udp_tcp.h"


u8 Ethernet_TBUF[20]={0x3a,0x02,0x6,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0xff};

/*************************************本地IP配置配置***************************************************/		
void local_ip_config()
{
 IP4_ADDR(&ipaddr_tcp_target,10,0,0,182);//原则上这两个IP号必须相同
 IP4_ADDR(&ipaddr_udp_target,10,0,0,182);//因为要兼容单一网卡
}
	
/*************************************UDP相关配置***************************************************/	
	
struct udp_pcb *udp_pcb;
struct pbuf* buff_udp;
struct ip_addr ipaddr_udp_target;
	
err_t UDP_APP_INIT(struct udp_pcb *udp_pcb,struct ip_addr *ipaddr_udp_target,uint32_t service_port)
{
 err_t err_udp;
	
 udp_pcb= udp_new();
 if(!udp_pcb)
	{ return 1;} //ERR_OK是0，所以返回1就是意味着失败

   //err_udp=udp_bind(udp_pcb,ipaddr_udp_target,service_port);	//只接受特定IP的数据帧
	err_udp=udp_bind(udp_pcb,IP_ADDR_ANY,service_port); //接受所有IP的数据帧
	//udp_connect(udp_pcb, IP_ADDR_ANY, service_port);   // 与远端主机建立连接
	udp_connect(udp_pcb, ipaddr_udp_target, service_port);
	if(err_udp!=ERR_OK)
	{return 1;}
	
	udp_recv(udp_pcb,recv_callback_udp,NULL);
	
	return ERR_OK;
}


void recv_callback_udp(void *arg,struct udp_pcb *upcb,struct pbuf *ouc_buf,struct ip_addr *addr,u16_t port)
{ 
    struct ip_addr destAddr = *addr;  
     struct pbuf *buf; //要发送的数据
	
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

	

	
	
/*************************************TCP相关配置***************************************************/
	
struct tcp_pcb *tcp_pcb;
struct pbuf* buff_tcp;
struct ip_addr ipaddr_tcp_target;	
	
err_t TCP_APP_INIT(struct tcp_pcb *tcp_pcb,struct ip_addr *ipaddr_tcp_target,uint32_t service_port)
{
 err_t err_tcp;
 struct tcp_pcb *tcp_pcb_listening;	

 tcp_pcb= tcp_new();
 if(tcp_pcb==NULL)
	{ return 1;} //ERR_OK是0，所以返回1就是意味着失败

   err_tcp=tcp_bind(tcp_pcb,ipaddr_tcp_target,service_port);	//只接受特定IP的数据帧
   //本函数的大部分代码用于检验给出的参数是否合适，如果合适将被付给指定的
	 //pcb控制块，返回ERR_OK. 如果不合适将返回ERR_USE(端口已被使用)
	
	/**********************配置服务器/客户端(两者有区别)*******************************/
	tcp_pcb_listening=tcp_listen(tcp_pcb);
	//完事后原参数被释放，并赋给一个新的TCP指针
	//tcp_pcb_listening=tcp_listen_with_backlog(tcp_pcb,3);
	//这个函数和tcp_listen()功能一致，只是限制了TCP监听的个数
	//要是用这个函数需要在lwippopt.h里设置TCP_LISTEN_BACKLOG=1	
	tcp_accept(tcp_pcb_listening, tcp_Client_connected);  /* Specify the function to be called when a connection is established */   
	//绑定TCP链接并进入监听状态
	
	
	
	//以下是客户端的配置，还很不完善
	 //tcp_connect(tcp_pcb_listening, ipaddr_tcp_target, service_port, tcp_server_accept);  
	//这里不大一样，服务器是监听listening，客户端则是主动链接服务器
/***********************************************************************************/

	
	if((err_tcp!=ERR_OK)||(tcp_pcb_listening==NULL))
	{return 1;}

	return ERR_OK;

}


err_t tcp_Client_connected(void *arg, struct tcp_pcb *pcb, err_t err)//服务器建立连接后的回调函数
{
 tcp_setprio(pcb, TCP_PRIO_MIN);//设置优先级，在有多个链接时必须加上
 tcp_recv(pcb, recv_callback_tcp); //绑定tcp连接下接收到数据的回调函数	 
	
	return ERR_OK;
}


err_t recv_callback_tcp(void *arg,struct tcp_pcb *tpcb, struct pbuf *ouc_buf,err_t err) //接收到数据帧时的回调函数
{

	tcp_write(tpcb,Ethernet_TBUF,sizeof(Ethernet_TBUF),0);//0表示发送的数据不必复制到内存缓冲区
	pbuf_free(ouc_buf);
 return ERR_OK;
}


err_t tcp_server_accept(void *arg, struct tcp_pcb *pcb, err_t err)//作为客户端时连接到服务器时的回调函数
{
/*此函数在TCP链接由SYN_RECV状态转到ESTABLISED之间时被调用
应用层可以在这个回调函数中做一些初始化和filter的工作，若通过所有
检查返回ERR_OK，通知对堆栈接受次连接，否则返回其他错误码，通知堆栈RST
当前连接	
*/

return ERR_OK;
}	
	
	
	


	
	
	
	
