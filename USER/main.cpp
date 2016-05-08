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
//#define MAX_ACD
//#define MAX_MAIN
//#define SAMLL_ACD
#ifdef MAX_MAIN
Led DS0(GPIOE,GPIO_Pin_5);
Led DS1(GPIOB,GPIO_Pin_5);
#endif

#ifdef MAX_ACD
Led DS0(GPIOE,GPIO_Pin_0);
Led DS1(GPIOE,GPIO_Pin_2);
#endif

#ifdef SAMLL_ACD
Led DS0(GPIOB,GPIO_Pin_8);
Led DS1(GPIOB,GPIO_Pin_9);
#endif

void Sys_Init(void)
{	
  delay_init();		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
  SerialPort usart1(115200);	
  SPI_Enc28j60_Init();// ENC28J60 SPI 接口初始化 
  enc28j60Init();   
	enc28j60PhyWrite(PHLCON,0x476);	
	init_ip_arp_udp_tcp(mymac,myip,80);	
	#ifdef MAX_MAIN          //触摸屏
	LCD_Init();	
	KEY_Init();	 
	FLASH_Unlock();
	EE_INIT();	 
 	tp_dev.init();	
	#endif
	TIM3_Init();
	
}

int main(void)
{
	Sys_Init();
	DS1.on();
	printf("helo world");
	#ifdef MAX_MAIN	
	
	LCD_Show_Main_Page();
  delay_ms(1500);	

	delay_ms(1500);
//	Load_Drow_Dialog();	 	
//	rtp_test(); 						//电阻屏测
	#endif
	while(1)
	{
		static u8 t_cnt=0;
		t_cnt++;
		if(t_cnt==100)
		{
			DS0.overturn();
			t_cnt=0;
		}
		delay_ms(10);
		if(KEY_Scan(0)==KEY_RIGHT)	//KEY_RIGHT按下,则执行校准程序
		{
			LCD_Clear(WHITE);//清屏
		  TP_Adjust();  //屏幕校准 
			TP_Save_Adjdata();	 
			LCD_Show_Main_Page();
			
		}
	}
	
}

//电阻触摸屏测试函数
void rtp_test(void)
{
	u8 key;
	u8 i=0;	  
	while(1)
	{
	 	key=KEY_Scan(0);
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{	
		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			{	
				if(tp_dev.x[0]>(lcddev.width-24)&&tp_dev.y[0]<16)Load_Drow_Dialog();//清除
				else TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],BLUE);		//画图	  			   
			}
		}else delay_ms(10);	//没有按键按下的时候 	    
		if(key==KEY_RIGHT)	//KEY_RIGHT按下,则执行校准程序
		{
			LCD_Clear(WHITE);//清屏
		    TP_Adjust();  //屏幕校准 
			TP_Save_Adjdata();	 
			Load_Drow_Dialog();
		}
		i++;
		if(i%20==0)DS0.overturn();
	}
}

