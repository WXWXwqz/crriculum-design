/*12864串口      （STM32程序）
 
 	 LCD12864_IOinit();
	 LCD12864_Init();			//LCD12864初始化
	 LCD12864_Clear();			//LCD12864清屏
	 
	 LCD12864_Waddr(int x,int y);		////写入的位置 （x行 Y列	1 2 3 4 ）

	 LCD12864_Wnum((double) m,u16 n);		//////（double、float）写入的数字要带小数点， n表示小数的个数
	 LCD12864_WPoss(int m,u8 *buff);	//	m=0写入字符串,m=1,写入字符

	 	 
	 LCD12864_TXT_Clear(void);		//LCD12864清文本
	 LCD12864_BMP_Clear(void);		//LCD12864清图像
	 LCD12864_Wbmp(u8 *puts);	//LCD12864绘图


	 LCD12864_W(u16 dat_com,u8 byte);//dat_com=0写指令，dat_com=1写数据

	 Delay_1ms(u16 x) ;

	 Interse(u8 y,u8 x,u8 width);
     convertChar (u8 CX,u8 CY,u8 width);
*/
#include <stm32f10x_lib.h>
#include "12864.h"

/*
unsigned int key=100;
unsigned char Delete_flag=1;

*/

/*
void Delete_check(void)/////（全局变量有  key  Delete_flag ）
{	
	if(key==13) 
	{
		if(Delete_flag==1) /////初始化时定义 Delete_flag） 为 1
		{
			LCD12864_W(1,0x20);
		}
		delete1();
		Delete_flag=0;
	}
	else
	{	
		if(Delete_flag==0)  /////上一次有删除键按下，Delete_flag 变为 0 
		{
	 		LCD12864_W(1,0x20);//xie kong 
	 		LCD12864_W(0,0x10);//zuo yi 	
			Delete_flag=1;
	}	}			
}
*/
///////////////////////////////////////////////////////////////////////////////
void LCD12864_IOinit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE  ); 
	
	GPIO_InitStructure.GPIO_Pin = 
							GPIO_Pin_5  |
							GPIO_Pin_6  |
							GPIO_Pin_7  ;			
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // 最高输出速率50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure); // 选择C端口
}
////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////
void Delay_1ms(u16 x) 
{ 
	u16 i,j; 
	for(j=0;j<x;j++)  
		for(i=0;i<1000;i++);
}
///////////////////////////////////////
void delete1(void)
{	
	LCD12864_W(LCD12864_COM,0x10);	//zuo yi	
	LCD12864_W(LCD12864_DAT,0x20);	//xiekong
	LCD12864_W(LCD12864_COM,LCD12864_CURSOR_RRF);	//AC自动加一，光标右移0x14，整体显示不移动	
}
/******************************************************************
名称：void LCD12864_Init(void)
功能：LCD12864初始化
*/
/******************************************************************/
void LCD12864_Init(void)
{
//	LCD12864_rst=1;	//选择串口模式
	LCD12864_W(LCD12864_COM,LCD12864_COM_BASIC);	//基本指令功能.
	Delay_1ms(50);
	LCD12864_W(LCD12864_COM,LCD12864_PLACE_ROLL);	//允许输入卷动位址
	Delay_1ms(50);
	LCD12864_W(LCD12864_COM,LCD12864_REST_OFF);		//脱离随眠状态，显示打开,关光标,反白关.
	Delay_1ms(50);
	LCD12864_W(LCD12864_COM,LCD12864_CLEAR);		//清屏指令.
	Delay_1ms(50);
	LCD12864_W(LCD12864_COM,LCD12864_CURSOR_RRF);	//AC自动加一，光标右移，整体显示不移动
	Delay_1ms(50);

}


/******************************************************************
名称：void LCD12864_Clear(void)
功能：LCD12864清屏
*/
/******************************************************************/
void LCD12864_Clear(void)	   
{
	LCD12864_W(LCD12864_COM,LCD12864_COM_BASIC);//基本指令功能.
	Delay_1ms(50);
	LCD12864_W(LCD12864_COM,LCD12864_CLEAR);	//清屏指令.
	Delay_1ms(50);
}
/******************************************************************
名称：void LCD12864_Wbyte(u8 byte)
功能：向12864写入8位数据
*/
/******************************************************************/
void LCD12864_Wbyte(u8 byte)
{
	u8 i;

	for(i=0;i<8;i++)
	{
		LCD12864_SCLK_0;
		Delay_1ms(1);
		if(byte&0x80)
			LCD12864_STD_1;
		else
		   LCD12864_STD_0; 
	//	LCD12864_STD=(byte&0x80);	//写入一位数据
		LCD12864_SCLK_1;
		Delay_1ms(1);
		byte<<=1;	 	//左移待写入数据，使最高位移至CY
		LCD12864_SCLK_0; 
		Delay_1ms(1);  
	}

}
/******************************************************************
名称：void LCD12864_W(bit dat_com,u8 byte)
功能：dat_com=0写指令，dat_com=1写数据
*****************************************************************
*/
void LCD12864_W(u16 dat_com,u8 byte)
{
	u8 temp;

	if(dat_com==0) 	//为零,写入指令 
		temp=LCD12864_W_COM;	//11111,RS(0),RW(0),0
	else    			//否则,写入数据
		temp=LCD12864_W_DAT;	//11111,RS(1),RW(0),0 

	LCD12864_CS_1;		//片选使能
	LCD12864_Wbyte(temp);	//写入模式选择，指令还是数据
	LCD12864_Wbyte(byte&0xf0);	//写入字节
//	Delay_1ms(10);
	LCD12864_Wbyte((byte<<4)&0xf0);	//写入字节
  //  Delay_1ms(10);
	LCD12864_CS_0;		//片选关闭
}
/******************************************************************
名称：void LCD12864_Waddr(int x,int y)
功能：LCD12864字符位置自定义显示
*/
/******************************************************************/
void LCD12864_Waddr(int x,int y)
{

	switch (x)
		{
		case 1:LCD12864_W(LCD12864_COM,0x80+y-1);
				break;
		case 2:LCD12864_W(LCD12864_COM,0x90+y-1);
			   break; 
			  
		case 3:LCD12864_W(LCD12864_COM,0x88+y-1);
			  break;
			  
		case 4:LCD12864_W(LCD12864_COM,0x98+y-1);
			  break;
		default: break;
		} 
//	LCD12864_W(LCD12864_COM,LCD12864_COM_BASIC);	//8BitMCU,基本指令集合
	 
						//显示在自定义位置
	
}
 
/******************************************************************
名称：void LCD12864_WPoss(int m,u8 *buff)
功能：LCD12864字符 write in
*/
/******************************************************************/
void LCD12864_WPoss( int m, u8 *buff)
{
	unsigned int i=0;
	
	if(m==0)
	{
			while(buff[i]!=('\0'))
			{	
			LCD12864_W(LCD12864_DAT,buff[i++]);
 
			}
	}
			
	for(  ;m>0;m--)
	{
		if(buff[i]!='\0')	
			LCD12864_W(LCD12864_DAT,buff[i++]);
		else
			 break;		

	}		
}

/******************************************************************
名称：void LCD12864_Wnum(float int m)
功能：向12864写入8位数据
*/
/******************************************************************/
u8 a[11]={'0','1','2','3','4','5','6','7','8','9','\0'};
void LCD12864_Wnum(double m,unsigned int n)
{
	u16 i;
	int num;
	if(m<0.0)
	{
		LCD12864_WPoss(0,"-");//dat_com=0写指令，dat_com=1写数据	 	  
		m=m*(-1.0);
	}
//////////////////////////整数部分///////////////////////////
	num=m;
	for(i=1;  ;i*=10)
	{	
		if(num/i<10)
			break;
	}
	for( ;i>0;i=i/10)
	{
		LCD12864_WPoss(1,&a[num/i]);
		num=num-(num/i)*i;
	}
//////////////////////////小数部分///////////////////////////
	if(n!=0)
	{
		LCD12864_WPoss(1,".");
		num=m;
		for( ;n>0;n--)
		{
			m=(m-num)*10;
			num=m;
			LCD12864_WPoss(1,&a[num%10]);							
		}
	}
}
///////////////////////////////////////////////
/******************************************************************
名称：void LCD12864_Wbmp(u8 *puts)
功能：LCD12864绘图
指令： 
调用：LCD12864_W()；
返回：无
*/
/******************************************************************/
void LCD12864_Wbmp(u8 *puts)
{
	u16 x=0;
	u8 i,j;

	LCD12864_W(LCD12864_COM,LCD12864_COM_PLOT_OFF);	//扩展指令集动作，绘图显示OFF

	for(i=0;i<32;i++)
		{
		LCD12864_W(LCD12864_COM,0x80|i);	//列32行,双屏结构中上半屏 
		LCD12864_W(LCD12864_COM,0x80);		//X地址坐标,自动加1.

		for(j=0;j<16;j++) 			//16*8=256
			LCD12864_W(LCD12864_DAT,puts[x++]);
		}

	for(i=0;i<32;i++)
		{
		LCD12864_W(LCD12864_COM,0x80|i);
		LCD12864_W(LCD12864_COM,0x88); //下半屏

		for(j=0;j<16;j++)
			LCD12864_W(LCD12864_DAT,puts[x++]);
		}
	LCD12864_W(LCD12864_COM,LCD12864_COM_PLOT_ON);	//扩展指令集动作，绘图显示ON

}
/******************************************************************
名称：void LCD12864_BMP_Clear( void )
功能：LCD12864清图像
指令：
调用：LCD12864_W()；
返回：无
*/
/******************************************************************/
void LCD12864_BMP_Clear( void )
{
     u8 i,j;

     LCD12864_W(LCD12864_COM,LCD12864_COM_PLOT_OFF);	//扩展指令集动作，绘图显示OFF
 
     for(i=0;i<32;i++)            //12864实际为256x32
		{
		LCD12864_W (LCD12864_COM,0x80|i);	//行位置
		LCD12864_W (LCD12864_COM,0x80);      //列位置

		for (j=0;j<32;j++)		//256/8=32 byte
			LCD12864_W(LCD12864_DAT,0);	//全部写入0即清除图像
		}
	LCD12864_W(LCD12864_COM,LCD12864_COM_PLOT_ON);		//扩展指令集动作，绘图显示ON
}

/******************************************************************
名称：void LCD12864_TXT_Clear( void )
功能：LCD12864清文本
指令：
调用：LCD12864_W()；
返回：无
*/
/******************************************************************/
void LCD12864_TXT_Clear( void )
{
	u8 i;

	LCD12864_W(LCD12864_COM,LCD12864_COM_BASIC);	//8BitMCU,基本指令集合
	LCD12864_W(LCD12864_COM,0x80);	//AC归起始位,DDROM起始地址

	for(i=0;i<64;i++)
		LCD12864_W(LCD12864_DAT,0x20);	//字符编码0x20是空白字符
}


u8 lcdPosX, lcdPosY;							//X,Y坐标
u8 halfScr, halfLineCnt, basicBlock;	//半屏,半屏行数,N*8块
void displayPhoto (u8 *bmp, u8 bmpCls) 
{
	lcdPosX = 0x80;
	halfScr = 2;
	
	for (;halfScr != 0; halfScr--)
	{
		lcdPosY = 0x80;
		halfLineCnt = 32;
		
		for (;halfLineCnt != 0; halfLineCnt--)
		{
			basicBlock = 16;
			LCD12864_W (LCD12864_COM,0x34);
			LCD12864_W (LCD12864_COM,lcdPosY);
			LCD12864_W (LCD12864_COM,lcdPosX);
			LCD12864_W (LCD12864_COM,0x30);

			for (; basicBlock != 0; basicBlock--)
			{
				if (bmpCls == OFF)
				{
					LCD12864_W(LCD12864_DAT,*bmp++);
				}
				else if (bmpCls == ON)
				{
					LCD12864_W(LCD12864_DAT,0x00);
				}
			}
			lcdPosY++;
		}
		lcdPosX = 0x88;
	}
	LCD12864_W (LCD12864_COM,0x36);
	LCD12864_W (LCD12864_COM,0x30);
}
/******************************************************************
名称：void convertChar (u8 CX,u8 CY,u8 width) 
功能：12864 反白显示
CX=要反白字符的行(0-3)
CY=要反白字符的列(0-7)
width=要反白字符的长度(1-16)
*/
/******************************************************************/
void convertChar (u8 CX,u8 CY,u8 width) 
{
	displayPhoto(OFF,ON);
	lcdPosY = 0x80;

	CX = CX - 1;
	CY = CY - 1;

	if (CX == 0)
	{
		CX = 0x80;
		halfLineCnt = 16;
	}
	else if (CX == 1)
	{
		CX = 0x80;
		halfLineCnt = 32;
	}
	else if (CX == 2)
	{
		CX = 0x88;
		halfLineCnt = 16;
	}
	else if (CX == 3)
	{
		CX = 0x88;
		halfLineCnt = 32;
	}
	lcdPosX = CX + CY;
	
    for (; halfLineCnt != 0; halfLineCnt--)
	{
		basicBlock = width;
		LCD12864_W (LCD12864_COM,0x34);
		LCD12864_W (LCD12864_COM,lcdPosY);
		LCD12864_W (LCD12864_COM,lcdPosX);
		LCD12864_W (LCD12864_COM,0x30);
	
		for (;basicBlock != 0; basicBlock--)
		{
			if (halfLineCnt > 16)
			{
				LCD12864_W(LCD12864_DAT,0x00);
			}
			else
			{
				LCD12864_W(LCD12864_DAT,0xff);
			}
		}
		lcdPosY++;
	}
	LCD12864_W (LCD12864_COM,0x36);
	LCD12864_W (LCD12864_COM,0x30);
}
/******************************************************************
名称：void Interse(u8 x,u8 y,u8 width)
功能：12864 反白显示
*/
/******************************************************************/

void Interse(u8 y,u8 x,u8 width)
{
   u8 i,j,flag=0x00;
   x = x-1;
   y = y-1;
   LCD12864_W(LCD12864_COM,0x34);//写数据时,关闭图形显示
   for(i=0;i<32;i++)
   {
      LCD12864_W(LCD12864_COM,0x80+i); //先写入水平坐标值
	  LCD12864_W(LCD12864_COM,0x80);	   //写入垂直坐标值 
	  for(j=0;j<16;j++)   //再写入两个8位元的数据
	  {
	  	  LCD12864_W(LCD12864_DAT,0x00);
	  }		
   }
   for(i=0;i<32;i++)
   {
      LCD12864_W(LCD12864_COM,0x80+i); //先写入水平坐标值
	  LCD12864_W(LCD12864_COM,0x88);	   //写入垂直坐标值 
	  for(j=0;j<16;j++)   //再写入两个8位元的数据
	  {
	  	  LCD12864_W(LCD12864_DAT,0x00);
	  }		
   }
   LCD12864_W(LCD12864_COM,0x36);
   if(y>1)
   {
      flag=0x08;
      y=y-2;
   }
   LCD12864_W(LCD12864_DAT,0x34); //写数据时,关闭图形显示,且打开扩展指令集
   for(i=0;i<16;i++)
   {
      LCD12864_W(LCD12864_COM,0x80+(y<<4)+i);
	  LCD12864_W(LCD12864_COM,0x80+flag+x);
	  for(j=0;j<width;j++)
	  {
	      LCD12864_W(LCD12864_DAT,0xff);
	  }
   //	  Delay_1ms(1);
   }
   LCD12864_W(LCD12864_COM,0x36); //写完数据,开图形显示
   LCD12864_W(LCD12864_COM,0x30);//从扩展指令到基本指令
}
///*********end*********///
