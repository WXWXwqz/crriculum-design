/**
  ******************************************************************************
  * @file    netserve.c
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
#include "netserve.h"
#include "stdio.h"
#include "delay.h"
#include "bsp.h"
#include "sys.h"
/* udp 监听端口号，即本地(开发板)端口号 */
unsigned char Packet_Buf[BUFFER_SIZE+1];
extern char Time[20];
extern char PassWord[10];
extern T_Dis_Flag DisFlag;
int IPandARP_Serve(void)
{
    Packet_Len = enc28j60PacketReceive(BUFFER_SIZE, Packet_Buf);      
      
      // Packet_Len will ne unequal to zero if there is a valid packet (without crc error)			
		if(Packet_Len==0)
		{
				return 1;
		}
	 // arp is broadcast if unknown but a host may also
		// verify the mac address by sending it to 
		// a unicast address.		     
		if(eth_type_is_arp_and_my_ip(Packet_Buf,Packet_Len))
		{
				make_arp_answer_from_request(Packet_Buf);
				return 1;
		}
		
		// check if ip packets are for us:			
		if(eth_type_is_ip_and_my_ip(Packet_Buf,Packet_Len)==0) 
		{
	//  printf("check if ip packets are for us: %d\n\n",cnt++);	
		 return 1;	
		} 
		return 0;
	
	
}

int Ping_Serve(void)
{
		if(Packet_Buf[IP_PROTO_P]==IP_PROTO_ICMP_V && Packet_Buf[ICMP_TYPE_P]==ICMP_TYPE_ECHOREQUEST_V)
		{
				// a ping packet, let's send pong  DOS 下的 ping 命令包		
//				printf("*******ping packet********************\n");
//			  SendPacket();
//			  printf("*******ping packet********************\n");
				make_echo_reply_from_request(Packet_Buf, Packet_Len); 	
				return 1;
		}	
		return 0;
}
int UDP_Serve(void)
{
//	unsigned int payloadlen = 0;
//	char *str="hello world\n";
  
	if (Packet_Buf[IP_PROTO_P]==IP_PROTO_UDP_V&&Packet_Buf[UDP_DST_PORT_H_P]==((myudpport&0xff00)>>8)&&Packet_Buf[UDP_DST_PORT_L_P]==(myudpport&0x00ff))
	{
	//	printf("********UDP Packet**************\n");
		HandleUDPPacket();
	//	printf("\n********************************");
//		payloadlen=	Packet_Buf[UDP_LEN_H_P];
//		payloadlen=payloadlen<<8;
//		payloadlen=(payloadlen+Packet_Buf[UDP_LEN_L_P])-UDP_HEADER_LEN;
//		make_udp_reply_from_request(Packet_Buf,str,strlen(str),myudpport);
		return 1;
	}
 	return 0;
}
extern u8  monitor_cnt;
int HandleUDPPacket(void)
{
	if(Packet_Buf[UDP_DATA_P]==0xff&&Packet_Buf[UDP_DATA_P+1]==0xfe)
	{
		if(Packet_Buf[UDP_DATA_P+2]==0x05)            //时间帧
		{
			for(int i=0;i<Packet_Buf[UDP_DATA_P+3];i++)
			{				
				Time[i]=Packet_Buf[UDP_DATA_P+4+i];
//				printf("%c ",Packet_Buf[UDP_DATA_P+4+i]);
			}	
			Time[9]=0;
			monitor_cnt=0;
			DisFlag.monitor=1;
			DisFlag.monitor_dis=1;
			
		}	
	  if(Packet_Buf[UDP_DATA_P+2]==0x06)             //密码帧
		{
			for(int i=0;i<Packet_Buf[UDP_DATA_P+3];i++)
			{
//				printf("%c ",Packet_Buf[UDP_DATA_P+4+i]);
				PassWord[i]=Packet_Buf[UDP_DATA_P+4+i];
			}	
			EE_Save_PassWord();
		}				
	}
	return 0;
}

void SendPacket(void)
{
	int i;
	for(i=UDP_DATA_P;i<UDP_DATA_P+25;i++)
	{
		printf("%c",Packet_Buf[i]);
		delay_ms(1);
	}
}

