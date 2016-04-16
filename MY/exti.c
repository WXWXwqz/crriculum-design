/***********************************************************/
/*                                                         */
/*  miniSTMF103ZX-EX开发板                                 */
/*  我想我笑 ＱＱ５２３８８５０１９                        */
/*  修改日期: 2014/8/3                                     */
/***********************************************************/
#include"exti.h"
#include"led.h"
/*外部中断*/
void EXTI0_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure; 
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|
                           RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);   

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);   //GPIOB作外部中断线路0
		
    EXTI_InitStructure.EXTI_Line=EXTI_Line0;                      //0线中断
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;             //中断模式
    EXTI_InitStructure.EXTI_Trigger=
                            EXTI_Trigger_Falling;          //下降沿触发
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;               //使能中断线 
    EXTI_Init(&EXTI_InitStructure);

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;          //上拉输入
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn  ;              //TIM2中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;      //先占优先级2级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;             //从优先级0级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //IRQ通道被使能
		
		NVIC_Init(&NVIC_InitStructure);   
		
		EXTI_ClearITPendingBit(EXTI_Line0);

    
}


