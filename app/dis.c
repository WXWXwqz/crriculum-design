#include "dis.h"
T_Dis_Flag DisFlag;
void LCD_Show_Main_Page(void)
{
	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
	LCD_ShowPicture(1,1);
	LCD_ShowChinese((lcddev.width-24*4-1)/2,80,1,"��ҵ���");	
	LCD_ShowChinese((lcddev.width-24*9)/2,110,0,"������̫�������ܽ�");
	LCD_ShowChinese((lcddev.width-24*9)/2,110+24,0,"ͨϵͳ�����������");
	POINT_COLOR=RED;
	LCD_ShowChinese((lcddev.width-24*4)/2,200,3,"�������");
	POINT_COLOR=BLACK;
	LCD_ShowChinese(lcddev.width-24*4,250,3,"���䳯");	
}