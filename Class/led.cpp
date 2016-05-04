#include "led.h"
#include "stm32f10x.h"


Led::Led(GPIO_TypeDef *port,int pin)
{
	GPIO_InitTypeDef GPIO_InitStruct;
  switch((uint32_t)(port))
	{
		case (GPIOF_BASE):
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);	break;		
		case (GPIOE_BASE):
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	break;
		case (GPIOD_BASE):
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	break;
		case (GPIOC_BASE):
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	break;
		case (GPIOB_BASE):
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	break;
		case (GPIOA_BASE):
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	break;
	}
	Port=port;
	Pin=pin;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=pin;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(port,&GPIO_InitStruct);
	off();
}
void Led::on(void)
{
	Port->BSRR=Pin;
}

void Led::off(void)
{
	Port->BRR=Pin;
}
void Led::overturn(void)
{
	if(sta)
	{
		off();
		sta=0;
	}
	else
	{
		on();
		sta=1;
	}
}

