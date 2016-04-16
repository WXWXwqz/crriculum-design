#ifndef __SERIAL_H
#define __SERIAL_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "stm32f10x.h"
#include "usart.h"
class SerialPort
{
	public:
   	SerialPort(int);	
    void sprintf(void);
};

#ifdef __cplusplus
}
#endif

#endif


