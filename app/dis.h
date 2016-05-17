/**
  ******************************************************************************
  * @file     dis
  * @author   Œ“œÎŒ“–¶
  * @version  V1
  * @date     2016.5.8
  * @chip		  STM32f103zet6
  * @lib		  
  * @note   
  * @source
  * @Pin	
  * @history		  
  ******************************************************************************
  */
#ifndef __DIS_H
#define __DIS_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "touch.h"
#include "lcd.h"
#include "sys.h"
extern T_Dis_Flag DisFlag;
void LCD_Show_Main_Page(void);
void LCD_Show_Login_Page(void);
void Dis(void);
void WorkingSta_Page_Ref(short num,u8 n);
void LCD_Show_InPut_Page(char *title);
#ifdef __cplusplus
}
#endif

#endif  //__DIS_H
