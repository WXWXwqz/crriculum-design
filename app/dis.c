#include "dis.h"
T_Dis_Flag DisFlag;
void LCD_Show_Main_Page(void)
{
	POINT_COLOR=BLUE;//设置字体为红色 
	LCD_ShowPicture(1,1);
	LCD_ShowChinese((lcddev.width-24*4-1)/2,80,1,"毕业设计");	
	LCD_ShowChinese((lcddev.width-24*9)/2,110,0,"基于以太网的智能交");
	LCD_ShowChinese((lcddev.width-24*9)/2,110+24,0,"通系统控制网络设计");
	POINT_COLOR=RED;
	LCD_ShowChinese((lcddev.width-24*4)/2,200,3,"点击进入");
	POINT_COLOR=BLACK;
	LCD_ShowChinese(lcddev.width-24*4,250,3,"王其朝");	
}