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
Led DS0(GPIOE,GPIO_Pin_5);
Led DS1(GPIOB,GPIO_Pin_5);
void Sys_Init(void)
{	
  delay_init();		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
  SerialPort usart1(115200);	
  SPI_Enc28j60_Init();// ENC28J60 SPI �ӿڳ�ʼ�� 
  enc28j60Init();   
	enc28j60PhyWrite(PHLCON,0x476);	
	init_ip_arp_udp_tcp(mymac,myip,80);	
	LCD_Init();	
	KEY_Init();	 
	FLASH_Unlock();
	EE_INIT();	
 	tp_dev.init();	
	TIM3_Init();
	
}
void rtp_test(void);
int main(void)
{
	Sys_Init();
	DS1.on();
	printf("helo world");
	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
	LCD_ShowString(10,50,200,16,16,"QingDao Technology University");	
	LCD_ShowString(10,70,200,16,16,"TOUCH TEST");	
	LCD_ShowString(10,90,200,16,16,"graduate project");
	LCD_ShowString(10,110,200,16,16,"Stored in the Flash");
  LCD_ShowString(10,130,200,16,16,"Press S1 to Adjust");	
	LCD_ShowNum(60,150,lcddev.id,16,16);	
  delay_ms(1500);
	delay_ms(1500);
	Load_Drow_Dialog();	 	
	rtp_test(); 						//��������
	
}

//���败�������Ժ���
void rtp_test(void)
{
	u8 key;
	u8 i=0;	  
	while(1)
	{
	 	key=KEY_Scan(0);
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)			//������������
		{	
		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			{	
				if(tp_dev.x[0]>(lcddev.width-24)&&tp_dev.y[0]<16)Load_Drow_Dialog();//���
				else TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],BLUE);		//��ͼ	  			   
			}
		}else delay_ms(10);	//û�а������µ�ʱ�� 	    
		if(key==KEY_RIGHT)	//KEY_RIGHT����,��ִ��У׼����
		{
			LCD_Clear(WHITE);//����
		    TP_Adjust();  //��ĻУ׼ 
			TP_Save_Adjdata();	 
			Load_Drow_Dialog();
		}
		i++;
		if(i%20==0)DS0.overturn();
	}
}

