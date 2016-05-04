/***********************************************************/
/*                                                         */
/*  miniSTMF103ZX-EX开发板                                 */
/*  我想我笑 ＱＱ５２３８８５０１９                        */
/*  修改日期: 2014/8/1                                     */
/***********************************************************/
#include "time.h"
#include "delay.h"
#include "stdio.h"
#include "netserve.h"
void TIM2_Init()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 


    /*定时器基本设置*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    TIM_TimeBaseStructure.TIM_Prescaler=72-1;                      //36分频
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;      //向上计数 
    TIM_TimeBaseStructure.TIM_Period= 10000-1;                      //这里是配置的重装载寄存器
  
    /*这里配置了CR1寄存器的 9 10 位。
    定义在定时器时钟(CK_INT)频率与数字滤波器(ETR，TIx)
    使用的采样频率之间的分频比例。*/
    TIM_TimeBaseStructure.TIM_ClockDivision=
                                            TIM_CKD_DIV1;          //   
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);

}

void TIM3_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
    NVIC_InitTypeDef NVIC_InitStructure;

    /*定时器基本设置*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    TIM_TimeBaseStructure.TIM_Prescaler=72-1;                      //36分频
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;      //向上计数 
    TIM_TimeBaseStructure.TIM_Period= 1000-1;                      //这里是配置的重装载寄存器
  
    /*这里配置了CR1寄存器的 9 10 位。
    定义在定时器时钟(CK_INT)频率与数字滤波器(ETR，TIx)
    使用的采样频率之间的分频比例。*/
    TIM_TimeBaseStructure.TIM_ClockDivision=
                                            TIM_CKD_DIV1;          //   
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                      //开启更新中断

		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ;          //TIM2中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //先占优先级2级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;             //从优先级0级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //IRQ通道被使能
		NVIC_Init(&NVIC_InitStructure); 
		TIM_Cmd(TIM3,ENABLE);
}
void TIM3_IRQHandler(void)
{		
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		if(IPandARP_Serve())
		{
			goto BREAK;
		}
		if(Ping_Serve())
		{
			goto BREAK;
		}
		if(UDP_Serve())
		{
			goto BREAK;
		}
		BREAK: ;
}

