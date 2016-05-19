#include "stm32f10x.h"
#include "bsp.H"
#include "delay.h"
#include "stdio.h"
//ErrorStatus  HSEStartUpStatus;
//FLASH_Status FlashStatus;
uint16_t VirtAddVarTab[NumbOfVar] = {0xAA00, 0xAA01, 0xAA02, 0xAA03, 0xAA04, 0xAA05, 0xAA06, 0xAA07, 0xAA08, 0xAA09, 
																		 0xAA0A,0xAA0B, 0xAA0C, 0xAA0D, 0xAA0E,0xAA0F,0xAA10,0xAA11,0xAA12,0xAA12,0xAA14};

void EE_INIT(void)
{
	EE_Init();
}
void EE_Write_Word(int Off,int data)
{
	int temp;
	temp=data&0x0000ffff;
	EE_WriteVariable(VirtAddVarTab[Off],temp);
	delay_ms(10);
	temp=((data&0xffff0000)>>16);
	EE_WriteVariable(VirtAddVarTab[Off+1],temp);
	delay_ms(10);
}

int EE_Read_Word(int Off)
{
	short temp;
	int   data;
	EE_ReadVariable(VirtAddVarTab[Off+1],&temp);
	data=(u16)(temp);
	data<<=16;
	EE_ReadVariable(VirtAddVarTab[Off],&temp);
	data=data|(u16)temp;
	return (int)data;
}
int EE_Read_Byte(int Off)
{
	short temp;
	EE_ReadVariable(VirtAddVarTab[Off],&temp);
	return temp;
}
void EE_Write_Byte(int Off,short data)
{
	EE_WriteVariable(VirtAddVarTab[Off],data);
}

void EE_Save_PassWord(void)
{
	u16 temp;
	for(int i=0;i<5;i++)
	{
		temp=PassWord[i*2];
		temp<<=8;
		temp|=PassWord[i*2+1];
		EE_WriteVariable(VirtAddVarTab[PASSWORD+i],temp);
	}
}
int EE_Read_PassWord(void)
{
	short temp;
	char  t;
	for(int i=0;i<5;i++)
	{
		EE_ReadVariable(VirtAddVarTab[PASSWORD+i],&temp);
		t=((u16)temp)&0x00ff;
		if((t>='0'&&t<='9')||t==0)
		{
			PassWord[i*2+1]=t;
		}
		else
		{
			return 0;
		}
		t=((u16)temp)>>8;
		if((t>='0'&&t<='9')||t==0)
		{
			PassWord[i*2]=t;
		}
		else
		{
			return 0;
		}		
	}	
	return 1;
}
void EE_Read_LightTime(void)
{
	short temp;
	temp=EE_Read_Byte(ROADLIGHT0);
	if(temp>=0&&temp<=99)
	{
	RoadLinght_Count[0]=temp;
	}
	temp=EE_Read_Byte(ROADLIGHT1);
	if(temp>=0&&temp<=99)
	{
	RoadLinght_Count[1]=temp;
	}
	Road_Count=RoadLinght_Count[1];	
}
