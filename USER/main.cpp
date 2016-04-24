  /**
  ***************2016青岛理工大学毕业设计 智能交通灯控制网络**************
  * @author  我想我笑
  * @version V1
  *	@chip		 stm32f103zet6
  * @lib		 V3.5.0
  * @history 		
  * @data    2016/4/16
  *************************************************************************
  */
#include "head.h"
Led DS0(GPIOE,GPIO_Pin_0);
Led DS1(GPIOE,GPIO_Pin_2);
void Sys_Init(void)
{	
  delay_init();		
  SerialPort usart1(115200);
  SPI_Enc28j60_Init();// ENC28J60 SPI 接口初始化 
  enc28j60Init();   
	enc28j60PhyWrite(PHLCON,0x476);	
	init_ip_arp_udp_tcp(mymac,myip,80);	
}
int main(void)
{
	Sys_Init();
	DS1.on();
	printf("helo world");
	while(1)
	{
		if(IPandARP_Serve())
		{
			continue;
		}
		if(Ping_Serve())
		{
			continue;
		}
	}
	
}


