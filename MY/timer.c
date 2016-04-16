/***********************************************************/
/*                                                         */
/*  miniSTMF103ZX-EX开发板                                 */
/*  我想我笑 ＱＱ５２３８８５０１９                        */
/*  修改日期: 2014/8/1                                     */
/***********************************************************/
#include "timer.h"
#include "led.h"
#include "delay.h"
extern u8 Code;
void TIM2_Init()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 


    /*定时器基本设置*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    TIM_TimeBaseStructure.TIM_Prescaler=72-1;                      //36分频
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;      //向上计数 
    TIM_TimeBaseStructure.TIM_Period= 50000-1;                      //这里是配置的重装载寄存器
  
    /*这里配置了CR1寄存器的 9 10 位。
    定义在定时器时钟(CK_INT)频率与数字滤波器(ETR，TIx)
    使用的采样频率之间的分频比例。*/
    TIM_TimeBaseStructure.TIM_ClockDivision=
                                            TIM_CKD_DIV1;          //   
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);

}

void TIM3_Init()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
    NVIC_InitTypeDef NVIC_InitStructure;

    /*定时器基本设置*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    TIM_TimeBaseStructure.TIM_Prescaler=720-1;                      //36分频
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;      //向上计数 
    TIM_TimeBaseStructure.TIM_Period= 50000-1;                      //这里是配置的重装载寄存器
  
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
	//	while(Code==32)
   // LED_On(2);
		
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);

}

void TIM4_Init(void)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM4
	TIM_TimeBaseStructure.TIM_Period = 5000; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =72-1; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
  
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OCInitStructure.TIM_Pulse = 0;//初始占空比为0
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);


 //使能TIM3在CCR2上的预装载寄存器;
	TIM_Cmd(TIM4, ENABLE);  //使能TIM3
	TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_ARRPreloadConfig(TIM4, ENABLE);

}
