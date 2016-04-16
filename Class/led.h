#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
class Led
{
	private:
		GPIO_TypeDef *Port;
		uint32_t Pin;
	public:		
		Led(GPIO_TypeDef *,int);
		void on(void);
		void off(void);
};
#ifdef __cplusplus
}
#endif

#endif
