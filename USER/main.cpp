  /**
  ***************2016�ൺ����ѧ��ҵ��� ���ܽ�ͨ�ƿ�������**************
  * @author  ������Ц
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
  SPI_Enc28j60_Init();// ENC28J60 SPI �ӿڳ�ʼ�� 
}

int main(void)
{
	Sys_Init();
	DS1.on();
	printf("helo world");
	return 0;
}

