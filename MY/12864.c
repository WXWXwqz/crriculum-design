/*12864����      ��STM32����
 
 	 LCD12864_IOinit();
	 LCD12864_Init();			//LCD12864��ʼ��
	 LCD12864_Clear();			//LCD12864����
	 
	 LCD12864_Waddr(int x,int y);		////д���λ�� ��x�� Y��	1 2 3 4 ��

	 LCD12864_Wnum((double) m,u16 n);		//////��double��float��д�������Ҫ��С���㣬 n��ʾС���ĸ���
	 LCD12864_WPoss(int m,u8 *buff);	//	m=0д���ַ���,m=1,д���ַ�

	 	 
	 LCD12864_TXT_Clear(void);		//LCD12864���ı�
	 LCD12864_BMP_Clear(void);		//LCD12864��ͼ��
	 LCD12864_Wbmp(u8 *puts);	//LCD12864��ͼ


	 LCD12864_W(u16 dat_com,u8 byte);//dat_com=0дָ�dat_com=1д����

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
void Delete_check(void)/////��ȫ�ֱ�����  key  Delete_flag ��
{	
	if(key==13) 
	{
		if(Delete_flag==1) /////��ʼ��ʱ���� Delete_flag�� Ϊ 1
		{
			LCD12864_W(1,0x20);
		}
		delete1();
		Delete_flag=0;
	}
	else
	{	
		if(Delete_flag==0)  /////��һ����ɾ�������£�Delete_flag ��Ϊ 0 
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
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // ����������50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure); // ѡ��C�˿�
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
	LCD12864_W(LCD12864_COM,LCD12864_CURSOR_RRF);	//AC�Զ���һ���������0x14��������ʾ���ƶ�	
}
/******************************************************************
���ƣ�void LCD12864_Init(void)
���ܣ�LCD12864��ʼ��
*/
/******************************************************************/
void LCD12864_Init(void)
{
//	LCD12864_rst=1;	//ѡ�񴮿�ģʽ
	LCD12864_W(LCD12864_COM,LCD12864_COM_BASIC);	//����ָ���.
	Delay_1ms(50);
	LCD12864_W(LCD12864_COM,LCD12864_PLACE_ROLL);	//���������λַ
	Delay_1ms(50);
	LCD12864_W(LCD12864_COM,LCD12864_REST_OFF);		//��������״̬����ʾ��,�ع��,���׹�.
	Delay_1ms(50);
	LCD12864_W(LCD12864_COM,LCD12864_CLEAR);		//����ָ��.
	Delay_1ms(50);
	LCD12864_W(LCD12864_COM,LCD12864_CURSOR_RRF);	//AC�Զ���һ��������ƣ�������ʾ���ƶ�
	Delay_1ms(50);

}


/******************************************************************
���ƣ�void LCD12864_Clear(void)
���ܣ�LCD12864����
*/
/******************************************************************/
void LCD12864_Clear(void)	   
{
	LCD12864_W(LCD12864_COM,LCD12864_COM_BASIC);//����ָ���.
	Delay_1ms(50);
	LCD12864_W(LCD12864_COM,LCD12864_CLEAR);	//����ָ��.
	Delay_1ms(50);
}
/******************************************************************
���ƣ�void LCD12864_Wbyte(u8 byte)
���ܣ���12864д��8λ����
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
	//	LCD12864_STD=(byte&0x80);	//д��һλ����
		LCD12864_SCLK_1;
		Delay_1ms(1);
		byte<<=1;	 	//���ƴ�д�����ݣ�ʹ���λ����CY
		LCD12864_SCLK_0; 
		Delay_1ms(1);  
	}

}
/******************************************************************
���ƣ�void LCD12864_W(bit dat_com,u8 byte)
���ܣ�dat_com=0дָ�dat_com=1д����
*****************************************************************
*/
void LCD12864_W(u16 dat_com,u8 byte)
{
	u8 temp;

	if(dat_com==0) 	//Ϊ��,д��ָ�� 
		temp=LCD12864_W_COM;	//11111,RS(0),RW(0),0
	else    			//����,д������
		temp=LCD12864_W_DAT;	//11111,RS(1),RW(0),0 

	LCD12864_CS_1;		//Ƭѡʹ��
	LCD12864_Wbyte(temp);	//д��ģʽѡ��ָ�������
	LCD12864_Wbyte(byte&0xf0);	//д���ֽ�
//	Delay_1ms(10);
	LCD12864_Wbyte((byte<<4)&0xf0);	//д���ֽ�
  //  Delay_1ms(10);
	LCD12864_CS_0;		//Ƭѡ�ر�
}
/******************************************************************
���ƣ�void LCD12864_Waddr(int x,int y)
���ܣ�LCD12864�ַ�λ���Զ�����ʾ
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
//	LCD12864_W(LCD12864_COM,LCD12864_COM_BASIC);	//8BitMCU,����ָ���
	 
						//��ʾ���Զ���λ��
	
}
 
/******************************************************************
���ƣ�void LCD12864_WPoss(int m,u8 *buff)
���ܣ�LCD12864�ַ� write in
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
���ƣ�void LCD12864_Wnum(float int m)
���ܣ���12864д��8λ����
*/
/******************************************************************/
u8 a[11]={'0','1','2','3','4','5','6','7','8','9','\0'};
void LCD12864_Wnum(double m,unsigned int n)
{
	u16 i;
	int num;
	if(m<0.0)
	{
		LCD12864_WPoss(0,"-");//dat_com=0дָ�dat_com=1д����	 	  
		m=m*(-1.0);
	}
//////////////////////////��������///////////////////////////
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
//////////////////////////С������///////////////////////////
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
���ƣ�void LCD12864_Wbmp(u8 *puts)
���ܣ�LCD12864��ͼ
ָ� 
���ã�LCD12864_W()��
���أ���
*/
/******************************************************************/
void LCD12864_Wbmp(u8 *puts)
{
	u16 x=0;
	u8 i,j;

	LCD12864_W(LCD12864_COM,LCD12864_COM_PLOT_OFF);	//��չָ���������ͼ��ʾOFF

	for(i=0;i<32;i++)
		{
		LCD12864_W(LCD12864_COM,0x80|i);	//��32��,˫���ṹ���ϰ��� 
		LCD12864_W(LCD12864_COM,0x80);		//X��ַ����,�Զ���1.

		for(j=0;j<16;j++) 			//16*8=256
			LCD12864_W(LCD12864_DAT,puts[x++]);
		}

	for(i=0;i<32;i++)
		{
		LCD12864_W(LCD12864_COM,0x80|i);
		LCD12864_W(LCD12864_COM,0x88); //�°���

		for(j=0;j<16;j++)
			LCD12864_W(LCD12864_DAT,puts[x++]);
		}
	LCD12864_W(LCD12864_COM,LCD12864_COM_PLOT_ON);	//��չָ���������ͼ��ʾON

}
/******************************************************************
���ƣ�void LCD12864_BMP_Clear( void )
���ܣ�LCD12864��ͼ��
ָ�
���ã�LCD12864_W()��
���أ���
*/
/******************************************************************/
void LCD12864_BMP_Clear( void )
{
     u8 i,j;

     LCD12864_W(LCD12864_COM,LCD12864_COM_PLOT_OFF);	//��չָ���������ͼ��ʾOFF
 
     for(i=0;i<32;i++)            //12864ʵ��Ϊ256x32
		{
		LCD12864_W (LCD12864_COM,0x80|i);	//��λ��
		LCD12864_W (LCD12864_COM,0x80);      //��λ��

		for (j=0;j<32;j++)		//256/8=32 byte
			LCD12864_W(LCD12864_DAT,0);	//ȫ��д��0�����ͼ��
		}
	LCD12864_W(LCD12864_COM,LCD12864_COM_PLOT_ON);		//��չָ���������ͼ��ʾON
}

/******************************************************************
���ƣ�void LCD12864_TXT_Clear( void )
���ܣ�LCD12864���ı�
ָ�
���ã�LCD12864_W()��
���أ���
*/
/******************************************************************/
void LCD12864_TXT_Clear( void )
{
	u8 i;

	LCD12864_W(LCD12864_COM,LCD12864_COM_BASIC);	//8BitMCU,����ָ���
	LCD12864_W(LCD12864_COM,0x80);	//AC����ʼλ,DDROM��ʼ��ַ

	for(i=0;i<64;i++)
		LCD12864_W(LCD12864_DAT,0x20);	//�ַ�����0x20�ǿհ��ַ�
}


u8 lcdPosX, lcdPosY;							//X,Y����
u8 halfScr, halfLineCnt, basicBlock;	//����,��������,N*8��
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
���ƣ�void convertChar (u8 CX,u8 CY,u8 width) 
���ܣ�12864 ������ʾ
CX=Ҫ�����ַ�����(0-3)
CY=Ҫ�����ַ�����(0-7)
width=Ҫ�����ַ��ĳ���(1-16)
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
���ƣ�void Interse(u8 x,u8 y,u8 width)
���ܣ�12864 ������ʾ
*/
/******************************************************************/

void Interse(u8 y,u8 x,u8 width)
{
   u8 i,j,flag=0x00;
   x = x-1;
   y = y-1;
   LCD12864_W(LCD12864_COM,0x34);//д����ʱ,�ر�ͼ����ʾ
   for(i=0;i<32;i++)
   {
      LCD12864_W(LCD12864_COM,0x80+i); //��д��ˮƽ����ֵ
	  LCD12864_W(LCD12864_COM,0x80);	   //д�봹ֱ����ֵ 
	  for(j=0;j<16;j++)   //��д������8λԪ������
	  {
	  	  LCD12864_W(LCD12864_DAT,0x00);
	  }		
   }
   for(i=0;i<32;i++)
   {
      LCD12864_W(LCD12864_COM,0x80+i); //��д��ˮƽ����ֵ
	  LCD12864_W(LCD12864_COM,0x88);	   //д�봹ֱ����ֵ 
	  for(j=0;j<16;j++)   //��д������8λԪ������
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
   LCD12864_W(LCD12864_DAT,0x34); //д����ʱ,�ر�ͼ����ʾ,�Ҵ���չָ�
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
   LCD12864_W(LCD12864_COM,0x36); //д������,��ͼ����ʾ
   LCD12864_W(LCD12864_COM,0x30);//����չָ�����ָ��
}
///*********end*********///
