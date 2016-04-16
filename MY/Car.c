#include "stm32f10x.h"
void Car_Stop(void)
{
	TIM4->CCR1=0;
	TIM4->CCR2=0;
	TIM4->CCR3=0;
	TIM4->CCR4=0;
}
void Car_Front(void)
{
	TIM4->CCR1=5000;
	TIM4->CCR2=5000;
	GPIO_SetBits(GPIOE,GPIO_Pin_4|GPIO_Pin_7);
	GPIO_ResetBits(GPIOE,GPIO_Pin_5|GPIO_Pin_8);
//	TIM4->CCR3=3000;
//	TIM4->CCR4=0;	
}
void Car_Back(void)
{
	TIM4->CCR1=5000;
	TIM4->CCR2=5000;
	GPIO_ResetBits(GPIOE,GPIO_Pin_4|GPIO_Pin_7);
	GPIO_SetBits(GPIOE,GPIO_Pin_5|GPIO_Pin_8);
}
void Car_Left(void)
{
//	TIM4->CCR1=5000;
	TIM4->CCR2=5000;
	GPIO_SetBits(GPIOE,GPIO_Pin_4|GPIO_Pin_7);
	GPIO_ResetBits(GPIOE,GPIO_Pin_5|GPIO_Pin_8);
}
void Car_Right(void)
{
	TIM4->CCR1=5000;
//	TIM4->CCR2=5000;
	GPIO_SetBits(GPIOE,GPIO_Pin_4|GPIO_Pin_7);
	GPIO_ResetBits(GPIOE,GPIO_Pin_5|GPIO_Pin_8);
}
