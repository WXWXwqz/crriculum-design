/***********************************************************/
/*  本程序只供学习使用，未经作者许可，不得用于其它任何用途 */
/*  miniSTMF103ZX-EX开发板                                 */
/*  我想我笑 ＱＱ５２３８８５０１９                        */
/*  修改日期: 2014/7/3-4                                   */
/***********************************************************/
#include "lcd12864.h"
#include "delay.h"
void LCD_SendByte(u8 LCD_Byte)         //发送一个字节
{
    u8 i=0;
    LCD_ResetBits(PSB);
    for(i=0;i<8;i++)
    {  
        LCD_ResetBits(SCLK);
        delay_us(30);
        if(LCD_Byte&0x80)
        {
            LCD_SetBits(SID);
        }
        else
        {
            LCD_ResetBits(SID);
        }            
        LCD_SetBits(SCLK);
        delay_us(30);    
        LCD_Byte=LCD_Byte<<1;           //左移
       
    }  
  
} 

void LCD_Write(u8 LCD_Flag,u8 LCD_Data)
{
    u8 LCD_Start_Data;
    //delay_ms(5);
    if(LCD_Flag==LCD_Flag_Cmd)
    {
        LCD_Start_Data=0xf8;   //写指令
    }
    if(LCD_Flag==LCD_Flag_Data)
    {
        LCD_Start_Data=0xfa;   //写数据
    }
    //delay_ms(5);
    LCD_SendByte(LCD_Start_Data);
    //delay_ms(5);
    LCD_SendByte(LCD_Data&0xf0);
 //   delay_ms(1);
    LCD_SendByte((LCD_Data<<4)&0xf0);
   // delay_ms(5);
}

void LCD_GPIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    //GPIOA端口时钟使能

    GPIO_InitStructure.GPIO_Pin=PSB|CS|RESET|SID|SCLK;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;          //上拉输入
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
//    GPIO_SetBits(GPIOA,CS|RESET|SID|SCLK); 
//    
//    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|
//                                GPIO_Pin_4|
//                                GPIO_Pin_11|
//                                GPIO_Pin_15;
//    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;             //上拉输入
//    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;     
//    GPIO_Init(GPIOD,&GPIO_InitStructure);



//    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|
//                                GPIO_Pin_10|
//                                GPIO_Pin_12|
//                                GPIO_Pin_14;
//    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;             //上拉输入
//    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//    GPIO_Init(GPIOE,&GPIO_InitStructure);

}

void LCD_Init(void)
{

    LCD_SetBits(CS); 
    delay_ms(100);
    LCD_Write(LCD_Flag_Cmd,0x30);                       //8 位介面，基本指令集
    delay_ms(10);
    LCD_Write(LCD_Flag_Cmd,0x30);    
    delay_ms(10);                       
    LCD_Write(LCD_Flag_Cmd,0x0c);                       //显示打开，光标关，反白关
    delay_ms(10); 
    LCD_Write(LCD_Flag_Cmd,0x01);                       //清屏，将DDRAM的地址计数器归零
    delay_ms(10); 
}

void LCD_Test(void)
{
    u8 i,j;
    for(i=0;i<32;i++)
    { 
        LCD_Write(0,0x80+i);LCD_Write(0,0x80);
        for(j=0;j<16;j++) 
            LCD_Write(1,0xff);
    }
    
}
void LCD_Cls(void)
{
    u8 i,j;
    for(i=0;i<32;i++)
    { LCD_Write(0,0x80+i);LCD_Write(0,0x80);
    for(j=0;j<16;j++) LCD_Write(1,0x00);
    }

    for(i=0;i<32;i++)
    { LCD_Write(0,0x80+i);LCD_Write(0,0x88);
    for(j=0;j<16;j++) LCD_Write(1,0x00);
    }
}

/******************************************************************
名称：void LCD_DisNum(u8 Line,u32 Num)
功能：将输入的数字显示在12864上
调用：LCD_Write();
入口参数说明:
             Line 为所要显示在的行数,取值为1-4,若输入0则默认为紧随上一个地址写
             Num 为所显示数字，32位大小
******************************************************************/
void LCD_DisNum(u8 Line,u32 Num)
{
    u8 i=0;
    char Dis_Num[12]={'\0'};
    char LCD_Num[]={'0','1','2','3','4','5','6','7','8','9','\0'};
    Dis_Num[0]='0';     
    if(Num==0)
        i=1;
    while(Num!=0)
    {
        Dis_Num[i++]=LCD_Num[Num%10];
        Num/=10;
    } 
    if(Line!=0)
    {   
       LCD_Write(LCD_Flag_Cmd,Line);
    }
        
    do
    {
    LCD_Write(LCD_Flag_Data,Dis_Num[--i]);
    }while(i>0);

}
/******************************************************************
名称：void LCD_DisNum(u8 Line,u32 Num)
功能：将输入的数字显示在12864上
调用：LCD_DisNum();
      LCD_Write();
入口参数说明:
             Line 为所要显示在的行数,取值为1-4,若输入0则默认为紧随上一个地址写
             Num 为所显示浮点数，六位精度
******************************************************************/
void LCD_DisXiaoShu(u8 Line,double Num)
{
    u32 Zheng;                  //储存整数部分
    u32 Xiao;                   //储存小数部分
    u32 temp;
    temp=Num*1000000;
    Zheng=(u32)(Num);
    Xiao=temp-Zheng*1000000;     
    if(Xiao!=0)
    {
        u8 i=0;
        u32 j=100000;
        while(Xiao<j)
        {
        i++;
        j/=10;
        }
       
        while(Xiao%10==0)
        {
                Xiao/=10;
        }       
        LCD_DisNum(Line,Zheng);
        LCD_Write(LCD_Flag_Data,'.');
        while(i>0)
        {
        LCD_Write(LCD_Flag_Data,'0');
        i--;
        }
        LCD_DisNum(0,Xiao);
        
    }
    else
    {
    LCD_DisNum(Line,Zheng);  
    }



}
/******************************************************************
名称：void LCD_DisChar(u8 Line,char *Hanzi)
功能：将输入的字符显示在12864上
调用：LCD_Write();
入口参数说明: Line 为所要显示在的行数,若输入0则默认为紧随上一个地址写
******************************************************************/
void LCD_DisChar(u8 Line,char *Hanzi)
{
    u8 i;
    if(Line!=0)
    {   
       LCD_Write(LCD_Flag_Cmd,Line);
    }
		
        
    i=0;
    while(Hanzi[i]!='\0')
    LCD_Write(LCD_Flag_Data,Hanzi[i++]);
}
/******************************************************************
名称：void LCD_WriteAddr(u8 x ,u8 y)
功能：在制定地址显示数字
入口参数说明: x取值为1-4，y取值为1-8
******************************************************************/
void LCD_WriteAddr(u8 x ,u8 y)
{
    if(x>=1&&x<=4&&y>=1&&y<=8)
    {
        switch(x)
        {
            case 1: LCD_Write(0,0x80+y-1); break;
            case 2: LCD_Write(0,0x90+y-1); break;
            case 3: LCD_Write(0,0x88+y-1); break;
            case 4: LCD_Write(0,0x98+y-1); break;
        }
     }
}
/******************************************************************
名称：void LCD_WriteBmp(u8 *puts)
功能：LCD12864绘图
指令： 
调用：LCD_Write()；
返回：无
*/
/******************************************************************/
void LCD_WriteBmp(u8 *puts)
{
//	u16 x=0;
	u8 i,j;

	LCD_Write(LCD_Flag_Cmd,LCD_COM_PLOT_OFF);	//扩展指令集动作，绘图显示OFF

	for(i=0;i<32;i++)
		{
		LCD_Write(LCD_Flag_Cmd,0x80|i);	//列32行,双屏结构中上半屏   y   1-32 
		LCD_Write(LCD_Flag_Cmd,0x80);		//X地址坐标,自动加1.    x   1-8 

		for(j=0;j<16;j++) 			//16*8=256
			LCD_Write(LCD_Flag_Data,0xf0);
		}

	for(i=0;i<32;i++)
		{
		LCD_Write(LCD_Flag_Cmd,0x80|i);
		LCD_Write(LCD_Flag_Cmd,0x88); //下半屏

		for(j=0;j<16;j++)
			LCD_Write(LCD_Flag_Data,0xf0);
		}
	LCD_Write(LCD_Flag_Cmd,LCD_COM_PLOT_ON);	//扩展指令集动作，绘图显示ON

}

/******************************************************************
名称：LCD_DisPel(u8 x,u8 y,u8 flag)
功能：显示12864上任意一个像素点
指令： 
调用：LCD_Write()；
入口参数说明：
            x,y为坐标，flag为显示或非显示 x:1-128 y:1-64

******************************************************************/
void LCD_DisPel(u8 x,u8 y,u8 flag)
{
	
	

	LCD_Write(LCD_Flag_Cmd,LCD_COM_PLOT_OFF);	//扩展指令集动作，绘图显示OFF 
    
    if(y<=32)
    {   
        LCD_Write(LCD_Flag_Cmd,0x80|(y-1));
        LCD_Write(LCD_Flag_Cmd,0x80+x/8);
    }
    if(y>32)
    {
        LCD_Write(LCD_Flag_Cmd,0x80|(y-33));
        LCD_Write(LCD_Flag_Cmd,0x88+x/8);
    }
    LCD_Write(LCD_Flag_Data,flag<<(8-(x%8)));




	LCD_Write(LCD_Flag_Cmd,LCD_COM_PLOT_ON);	//扩展指令集动作，绘图显示ON
   
}

/******************************************************************
名称：LCD_DisPel(u8 x,u8 y,u8 flag)
功能：显示12864上任意一个像素点
指令： 
调用：LCD_Write()；
入口参数说明：
            x,y为坐标，flag为显示或非显示 x:1-128 y:1-64

******************************************************************/
//u8   LCD_Read(void)
//{
//    u8 temp=0,i;
//    for(i=0;i<8;i++)
//    {
//        temp=temp|DB(8-i);
//        temp<<=1;
//    } 
//    return temp;   
//}



/**************************END****************************************/

