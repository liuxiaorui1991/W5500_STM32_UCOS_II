#ifndef _UDP_TCP_H
#define _UDP_TCP_H

#include <stdio.h>
#include "stm32f10x.h"

#include "err.h"  
#include "lwip/init.h"
#include "etharp.h"
#include "udp.h"
#include "tcp.h"

//#include "bsp_usart1.h"
//#include "bsp_SysTick.h" 
//#include "spi.h"
//#include "bsp_led.h"
//#include "cmd.h"
//#include "httpd.h"

extern u8 Ethernet_TBUF[20];

void local_ip_config(void);

extern struct tcp_pcb *tcp_pcb;
extern struct pbuf* buff_tcp;
extern struct ip_addr ipaddr_tcp_target;
err_t TCP_APP_INIT(struct tcp_pcb *tcp_pcb,struct ip_addr *ipaddr_udp_target,uint32_t service_port);
err_t tcp_Client_connected(void *arg, struct tcp_pcb *pcb, err_t err); //服务器建立连接时的回调函数
err_t recv_callback_tcp(void *arg,struct tcp_pcb *tpcb, struct pbuf *ouc_buf,err_t err); //接收到数据帧的回调函数
err_t tcp_server_accept(void *arg, struct tcp_pcb *pcb, err_t err);


extern struct udp_pcb *udp_pcb;
extern struct pbuf* buff_udp;
extern struct ip_addr ipaddr_udp_target;
err_t UDP_APP_INIT(struct udp_pcb *udp_pcb,struct ip_addr *ipaddr_udp_target,uint32_t service_port);
void recv_callback_udp(void *arg,struct udp_pcb *upcb, struct pbuf *pkt_buf,struct ip_addr *addr,u16_t port); 


#endif




