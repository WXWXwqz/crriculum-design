/***********************************************************/
/*  本程序只供学习使用，未经作者许可，不得用于其它任何用途 */
/*  miniSTMF103ZX-EX开发板                                 */
/*  我想我笑 ＱＱ５２３８８５０１９                        */
/*  修改日期: 2014/7/2                                     */
/*  说明：部分代码摘自原子战舰开发板例程                   */
/***********************************************************/
#include"usart.h"
void USART1_Init()
{
    USART_InitTypeDef  USART_InitStructure; 
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1
                           |RCC_APB2Periph_GPIOA
                           |RCC_APB2Periph_AFIO,ENABLE);//串口时钟使能    
    USART_DeInit(USART1);                                //串口复位  
    USART_InitStructure.USART_BaudRate=9600;             //波特率9600
    USART_InitStructure.USART_WordLength=
                                    USART_WordLength_8b; //有效数据8位
    USART_InitStructure.USART_Parity=USART_Parity_No;    //奇偶校验位无
    USART_InitStructure.USART_StopBits=USART_StopBits_1; //停止位1位
    USART_InitStructure.USART_HardwareFlowControl=
                         USART_HardwareFlowControl_None; //硬件流控制失能 
    USART_InitStructure.USART_Mode=
                            USART_Mode_Rx|USART_Mode_Tx; //收发使能
    USART_Init(USART1,&USART_InitStructure);
	//	USART_ITConfig(USART1,USART_IT_TC,ENABLE); 
    USART_Cmd(USART1,ENABLE);                            //串口使能

    /*串口引脚设置*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);    

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
}
//////////////////////////////////////////////////////////////////
//以下代码摘自原子战舰开发板例程
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); 
    USART_SendData(USART1,(uint8_t)ch);   
	return ch;
}

#endif 
