#ifndef _BSP_BSP_H_
#define _BSP_BSP_H_
#include "eeprom.h"
#ifdef __cplusplus
extern "C"
{
#endif

#define XFAC  	  0
#define XFAC_L	  0
#define XFAC_H	  1

#define YFAC  	  2
#define YFAC_L	  2
#define YFAC_H	  3

#define XOFF  	  4
#define XOFF_L	  4
#define XOFF_H	  5

#define YOFF  	  6
#define YOFF_L	  6
#define YOFF_H	  7

#define TOUCHTYPE	8
#define TOUCHFLAG 9

void EE_INIT(void);
int EE_Read_Byte(int Off);
int EE_Read_Word(int Off);
void EE_Write_Word(int Off,int data);
void EE_Write_Byte(int Off,short data);
#ifdef __cplusplus
}
#endif

#endif
