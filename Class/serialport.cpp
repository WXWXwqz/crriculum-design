#include "usart.h"
#include "stm32f10x.h"
#include "serialport.h"

SerialPort::SerialPort(int bound)
{
	uart_init(bound);
}

//void SerialPort::sprintf(void)
//{
//	//printf();
//}
