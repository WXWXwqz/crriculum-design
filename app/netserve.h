/**
  ******************************************************************************
  * @file    netserve.h
  * @author  wxwx
  * @version v1
  * @date    2016.4.24
  * @chip		 stm32f103zet6
  * @lib		 v3.5.0
  * @note    some serve of the Internet
  * @source  lwip
  * @Pin	
  * @history		  
  ******************************************************************************
  */
#ifndef _NETSERVE_H
#define _NETSERVE_H

#ifdef __cplusplus

extern "C"
{
#endif

#include "ip_arp_udp_tcp.h"
#include "net.h"
#include "enc28j60.h"
#include <string.h>


#define BUFFER_SIZE 1500
extern unsigned char Packet_Buf[BUFFER_SIZE+1];
 // udp 监听端口号，即本地(开发板)端口号
extern unsigned int myudpport ; 



int Ping_Serve(void);	
int IPandARP_Serve(void);
int UDP_Serve(void);
void SendPacket(void);
	#ifdef __cplusplus
}
#endif

#endif     //#ifndef _NETSERVE_H

