
#ifndef	__12864_h__
#define	__12864_h__

#define	OFF			0							//逻辑关
#define	ON			1							//逻辑开

#define LCD12864_CS_1  	GPIOA->BSRR=GPIO_Pin_12   //片选信号输入 1 
#define LCD12864_CS_0  	GPIOA->BRR=GPIO_Pin_12   //片选信号输入 1 

#define LCD12864_STD_1  	GPIOA->BSRR=GPIO_Pin_10   //串行数据输入
#define LCD12864_STD_0  	GPIOA->BRR=GPIO_Pin_10   //串行数据输入

#define LCD12864_SCLK_1 	GPIOA->BSRR=GPIO_Pin_8  //串行移位脉冲输入
#define LCD12864_SCLK_0 	GPIOA->BRR=GPIO_Pin_8  //串行移位脉冲输入

#define LCD12864_COM 0	//输入指令
#define LCD12864_DAT 1	//输入数据
#define uchar unsigned char
#define uint  unsigned int
#define LCD12864_CLEAR			0x01	//清除显示
#define LCD12864_CURSOR			0x02	//位址归位，游标回原点
#define LCD12864_CURSOR_RLF		0x04	//光标左移，整体显示不移动
#define LCD12864_CURSOR_RRF		0x06	//光标右移，整体显示不移动
#define LCD12864_CURSOR_RLN		0x05	//光标左移，整体显示移动
#define LCD12864_CURSOR_RRN		0x07	//光标右移，整体显示移动
#define LCD12864_DIS_OFF		0x08	//显示状态全关
#define LCD12864_DIS_ON			0x0E	//显示状态开
#define LCD12864_DIS_CUR_ON		0x0E	//游标显示开
#define LCD12864_DIS_CURS_ON	0x0F	//游标位置显示开
#define LCD12864_CURSOR_RL		0x10	//游标左移
#define LCD12864_CURSOR_RR		0x14	//游标右移
#define LCD12864_CURDIS_RL		0x18	//整体显示左移，光标跟随
#define LCD12864_CURDIS_RR		0x1C	//整体显示又移，光标跟随
#define LCD12864_COM_BASIC		0x30	//基本指令集动作
#define LCD12864_COM_PLOT_ON	0x36	//扩展指令集动作，绘图显示ON
#define LCD12864_COM_PLOT_OFF	0x34	//扩展指令集动作，绘图显示OFF
#define LCD12864_STAND_TO		0x31	//进入待命模式
#define LCD12864_PLACE_ROLL		0x03	//允许输入卷动位址
#define LCD12864_PLACE_IRAM		0x02	//允许输入IRAM位址
#define LCD12864_REVERES_13		0x04	//选择一、三行同时作反白显示
#define LCD12864_REVERES_24		0x05	//选择二、四行同时作反白显示
#define LCD12864_REST_ON		0x08	//进入睡眠模式
#define LCD12864_REST_OFF		0x0C	//脱离睡眠模式

#define LCD12864_W_COM			0xF8	//写指令
#define LCD12864_R_COM			0xFC	//读指令
#define LCD12864_W_DAT			0xFA	//写数据
#define LCD12864_R_DAT			0xFE	//读数据
 
void LCD12864_IOinit(void);
void LCD12864_Init(void);			//LCD12864初始化
void LCD12864_Clear(void);			//LCD12864清屏

void LCD12864_Waddr(int x,int y);////1 2 3 4
void LCD12864_WPoss(int m,u8 *buff);	//	m=0写入字符串,m=1,写入字符
void LCD12864_Wnum(double m,unsigned int n);

void Interse(u8 y,u8 x,u8 width);
void convertChar (u8 CX,u8 CY,u8 width);

void delete1(void);
void LCD12864_W(u16 dat_com,u8 byte);//dat_com=0写指令，dat_com=1写数据
void LCD12864_Wbyte(u8 byte);	//向12864写入8位数据
void LCD12864_TXT_Clear(void);		//LCD12864清文本
void LCD12864_BMP_Clear(void);		//LCD12864清图像
void LCD12864_Wbmp(u8 *puts);	//LCD12864绘图

void Delay_1ms(u16 x) ;



#endif
