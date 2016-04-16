#include "lcd.h"
#include "stm32f10x.h"
#include "delay.h"

lcd::lcd(TypeLCDIO t)
{
	switch((uint32_t)(t.DataPort))
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
  switch((uint32_t)(t.ControlPort))
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
	io=t;
}
void lcd::writecmd(u8 data)
{
  Reset(io.Rs);
	write(data);
}
void lcd::writedata(u8 data)
{
  Set(io.Rs);
	write(data);
}
void lcd::write(u8 data)
{
	uint16_t temp=0;
	temp=temp|data;
	Reset(io.Rw);	
	io.DataPort->ODR=((io.DataPort->ODR)&0xff00)|temp;
	Set(io.E);
	delay_us(10);
	Reset(io.E);
	
}
void lcd::Reset(uint16_t pin)
{
	io.ControlPort->BRR=pin;
}
void lcd::Set(uint16_t pin)
{
	io.ControlPort->BSRR=pin;
}
void lcd::Init(void)
{
	writecmd(0x30);                       //8 位介面，基本指令集
	delay_ms(10);
	writecmd(0x30);
  delay_ms(10);                       
  writecmd(0x0c);                       //显示打开，光标关，反白关
  delay_ms(10); 
  writecmd(0x01);                       //清屏，将DDRAM的地址计数器归零
  delay_ms(10); 	
}
