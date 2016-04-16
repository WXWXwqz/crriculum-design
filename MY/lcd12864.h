/***********************************************************/
/*  本程序只供学习使用，未经作者许可，不得用于其它任何用途 */
/*  miniSTMF103ZX-EX开发板                                 */
/*  我想我笑 ＱＱ５２３８８５０１９                        */
/*  修改日期: 2014/7/3-4                                   */
/***********************************************************/
#ifndef _LCD12864_H
#define _LCD12864_H
#include "stm32f10x.h"  
#define E GPIO_Pin_5        
#define SID GPIO_Pin_6      
#define SCLK GPIO_Pin_7
#define PSB  GPIO_Pin_12
//#define DB(x)     Data_Bit(x)
#define LCD_CLEAR			0x01	    //清除显示
#define LCD_CURSOR			0x02	    //位址归位，游标回原点
#define LCD_CURSOR_RLF		0x04    	//光标左移，整体显示不移动
#define LCD_CURSOR_RRF		0x06    	//光标右移，整体显示不移动
#define LCD_CURSOR_RLN		0x05       	//光标左移，整体显示移动
#define LCD_CURSOR_RRN		0x07    	//光标右移，整体显示移动
#define LCD_DIS_OFF		    0x08    	//显示状态全关
#define LCD_DIS_ON			0x0E    	//显示状态开
#define LCD_DIS_CUR_ON		0x0E    	//游标显示开
#define LCD_DIS_CURS_ON	    0x0F    	//游标位置显示开
#define LCD_CURSOR_RL		0x10    	//游标左移
#define LCD_CURSOR_RR		0x14      	//游标右移
#define LCD_CURDIS_RL		0x18    	//整体显示左移，光标跟随
#define LCD_CURDIS_RR		0x1C    	//整体显示又移，光标跟随
#define LCD_COM_BASIC		0x30    	//基本指令集动作
#define LCD_COM_PLOT_ON	    0x36    	//扩展指令集动作，绘图显示ON
#define LCD_COM_PLOT_OFF	0x34    	//扩展指令集动作，绘图显示OFF
#define LCD_STAND_TO		0x31    	//进入待命模式
#define LCD_PLACE_ROLL		0x03      	//允许输入卷动位址
#define LCD_PLACE_IRAM		0x02    	//允许输入IRAM位址
#define LCD_REVERES_13		0x04    	//选择一、三行同时作反白显示
#define LCD_REVERES_24		0x05    	//选择二、四行同时作反白显示
#define LCD_REST_ON		    0x08    	//进入睡眠模式
#define LCD_REST_OFF		  0x0C    	//脱离睡眠模式
#define LCD_Line1           0x80
#define LCD_Line2           0x90
#define LCD_Line3           0x88
#define LCD_Line4           0x98
#define LCD_Flag_Cmd 0
#define LCD_Flag_Data 1  
#define LCD_SetBits(n) GPIOA->BSRR=(n)
#define LCD_ResetBits(n) GPIOA->BRR=(n) 
 
void LCD_GPIOInit(void);
void LCD_Init(void);
void LCD_GPIO_Init(void);
void LCD_Write(u8 LCD_Flag,u8 LCD_Data);
void LCD_Test(void);
void LCD_Cls(void);
void LCD_DisChar(u8,char *);
void LCD_DisNum(u8,u32);
void LCD_DisXiaoShu(u8 ,double Num);
void LCD_WriteAddr(u8 ,u8);
void LCD_WriteBmp(u8 *);
void LCD_DisPel(u8,u8,u8);
//u8   LCD_Read(void);

#endif
