#include "dis.h"
#include "stdio.h"
#include "key.h"
#include "delay.h"
T_Dis_Flag DisFlag;
char PassWord[10]="123321123";
void LCD_Show_Main_Page(void)
{
	static u8 flag=1;
	if(flag)
	{
		POINT_COLOR=BLUE;//设置字体为红色 
		LCD_Clear(WHITE);//清屏
		LCD_ShowPicture(1,1,240,70);
		LCD_ShowChinese((lcddev.width-24*4-1)/2,80,1,"毕业设计");	
		LCD_ShowChinese((lcddev.width-24*9)/2,110,0,"基于以太网的智能交");
		LCD_ShowChinese((lcddev.width-24*9)/2,110+24,0,"通系统控制网络设计");
		POINT_COLOR=RED;
		LCD_ShowChinese((lcddev.width-24*4)/2,200,3,"点击进入");
		POINT_COLOR=BLACK;
		LCD_ShowChinese(lcddev.width-24*4,250,3,"王其朝");	
		
		flag=0;
	}
	tp_dev.scan(0);
	if(KEY_Scan(0)==KEY_RIGHT)	//KEY_RIGHT按下,则执行校准程序
	{
		DisFlag.dis_adjust=1;		
    DisFlag.dis_main=0;		
		flag=1;
	}
	if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
	{	
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{	
			if((tp_dev.x[0]>(lcddev.width-24*4)/2)&&(tp_dev.x[0]<((lcddev.width-24*4)/2+24*4))&&tp_dev.y[0]>200&tp_dev.y[0]<224)
			{
				DisFlag.dis_main=0;
				DisFlag.dis_login=1;
				flag=1;
			}
		}
	}
}
void LCD_Show_Adjust_Page(void)
{
	  POINT_COLOR=BLUE;//设置字体为红色 
		LCD_Clear(WHITE);//清屏
		TP_Adjust();  //屏幕校准 
		TP_Save_Adjdata();	
	  TP_Get_Adjdata();
		DisFlag.dis_adjust=0;		
	  DisFlag.dis_main=1;	
}
void LCD_Show_Login_Page(void)
{
	static u8 flag=1;
	static u8 passflag=0;
	u8 sw = 0xff;
  static	char password[11]={0};
  static u8 pcnt=0;
	if(flag)         //显示界面
	{
		delay_ms(100);
		LCD_Clear(WHITE);//清屏
		POINT_COLOR=RED;//设置字体为红色 
     LCD_ShowChinese((240-24*3-3*2)/2,20,3,"请登录");
		POINT_COLOR=BLUE;//设置字体为红色 
		for(int i=0;i<6;i++)  //横线
		{
			LCD_DrawLine(15,50+i*50,225,50+i*50);
		}
		LCD_DrawLine(15,50,15,100);
		LCD_DrawLine(225,50,225,100);
		for(int i=0;i<4;i++)  //竖线
		{
			LCD_DrawLine(15+i*70,100,15+i*70,300);
		}
		for(int i=0;i<3;i++)      //行
		{
			for(int j=0;j<3;j++)      //列
			{
				LCD_ShowChar(15+j*70+(70-8)/2,100+50*i+17,'0'+i*3+j+1,16,0);
			}
		}
		LCD_ShowChar(15+1*70+(70-8)/2,100+50*3+17,'0',16,0);       //0
		LCD_ShowChinese(15+11,250+13,0,"删除");
		LCD_ShowChinese(155+11,250+13,0,"确认");
		POINT_COLOR=BLUE;//设置字体为红色 
		LCD_ShowChinese(15+11,50+13,0,"密码");
		LCD_ShowChar(15+11+48+1,50+17,':',16,0);
		flag=0;
	}
	tp_dev.scan(0);
	if(KEY_Scan(0)==KEY_RIGHT)	//KEY_RIGHT按下,则执行校准程序
	{
		DisFlag.dis_adjust=1;		
    DisFlag.dis_login=0;		
		flag=1;
	}
	if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
	{	
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{	
			tp_dev.scan(0);
		  delay_ms(100);
			if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
			{	
				if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
				{	
					if(tp_dev.x[0]>=15&&tp_dev.x[0]<85)
					{
						sw=0x01;
					}
					else if(tp_dev.x[0]>=85&&tp_dev.x[0]<155)
					{
						sw=0x02;
					}
					else if(tp_dev.x[0]>=155&&tp_dev.x[0]<=225)
					{
						sw=0x03;
					}
					if(tp_dev.y[0]>=100&&tp_dev.y[0]<150)
					{
						sw|=0x10;
					}
					else if(tp_dev.y[0]>=150&&tp_dev.y[0]<200)
					{
						sw|=0x20;
					}			
					else if(tp_dev.y[0]>=200&&tp_dev.y[0]<250)
					{
						sw|=0x30;
					}
					else if(tp_dev.y[0]>=250&&tp_dev.y[0]<=300)
					{
						sw|=0x40;
					}
					passflag=1;	
					switch(sw)
					{
						case 0x11: password[pcnt]='1';break;
						case 0x12: password[pcnt]='2';break;
						case 0x13: password[pcnt]='3';break;
						case 0x21: password[pcnt]='4';break;
						case 0x22: password[pcnt]='5';break;
						case 0x23: password[pcnt]='6';break;
						case 0x31: password[pcnt]='7';break;
						case 0x32: password[pcnt]='8';break;
						case 0x33: password[pcnt]='9';break;
						case 0x41: password[pcnt]=' ';break;
						case 0x42: password[pcnt]='0';break;
						case 0x43: password[pcnt]='O';break;
						default  : password[pcnt]=0;
					}
					if(pcnt==10&&password[pcnt]!=' '&&password[pcnt]!='O')
					{
						password[pcnt]=0;
						pcnt=9;
					}
					sw=0xff;
				}
			}
		}
	}
	if(passflag)
	{
		passflag=0;		
		if(password[pcnt]!=' '&&password[pcnt])
		{
			
			if(password[pcnt]=='O')  //确认
			{	
				int i=0;				
				while(PassWord[i]!=0)
				{
					if(PassWord[i]!=password[i])
					{
						LCD_ShowChinese(85+10,50+13,0,"密码错误");
						delay_ms(1000);
						LCD_Fill(85+10,50+13,85+10+24*4+8,50+17+24,WHITE);			
						break;
					}
					i++;
				}
				if(PassWord[i]==0&&password[i]=='O')
				{
					DisFlag.dis_login=0;
					DisFlag.dis_work=1;
					flag=1;
					passflag=0;
				}
				pcnt=0;
				for(int i=0;i<10;i++)
				{
					password[i]=0;
				}
			}
			else
			{
				LCD_ShowChar(85+10+pcnt*8,50+17,password[pcnt],16,0);
				pcnt++;
			}
		}
		else if(password[pcnt])
		{
			if(pcnt>0)
			{
				password[pcnt]=0;
				password[--pcnt]=0;
				LCD_Fill(85+10+pcnt*8,50+17,85+10+pcnt*8+8,50+17+16,WHITE);
			}
		}
		printf("password=%s\n",password);
		printf("cnt=%d\n",pcnt);
	}
}
void LCD_Show_Test_Page (void)
{	
	static u8 flag=1;
	if(flag)         //显示界面
	{
		LCD_Clear(WHITE);
	  LCD_ShowString(60,60,200,16,16,"Something need to add");
	  LCD_ShowString(60,80,200,16,16,"Please wait");
		flag=0;
	}
}
void Dis(void)
{
	if(DisFlag.dis_adjust)
	{
		LCD_Show_Adjust_Page();
	}
	else if(DisFlag.dis_main)
	{
		LCD_Show_Main_Page();			
	}
	else if(DisFlag.dis_login)
	{
		LCD_Show_Login_Page();
	}
	else if(DisFlag.dis_work)
	{		
		LCD_Show_Test_Page();
	}
	
}
