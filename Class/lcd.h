#ifndef __LCD_H
#define __LCD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f10x.h"
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
typedef struct TypeLCDIO
{
	GPIO_TypeDef *DataPort,*ControlPort;
	uint16_t E,Rw,Rs;
} TypeLCDIO;
	
	
class lcd
{
	private:		
		TypeLCDIO io;
	public:
		lcd(TypeLCDIO);
	  void writedata(u8);
		void writecmd(u8);
		void readdata(u8);
		void readcmd(u8);
	  void write(u8);
	  void Reset(uint16_t);
		void Set(uint16_t);
		void Init(void);
	  
};

	
	
	
#ifdef __cplusplus
}
#endif

#endif
