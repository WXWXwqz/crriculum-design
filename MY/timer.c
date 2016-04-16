/***********************************************************/
/*                                                         */
/*  miniSTMF103ZX-EX������                                 */
/*  ������Ц �ѣѣ�����������������                        */
/*  �޸�����: 2014/8/1                                     */
/***********************************************************/
#include "timer.h"
#include "led.h"
#include "delay.h"
extern u8 Code;
void TIM2_Init()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 


    /*��ʱ����������*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    TIM_TimeBaseStructure.TIM_Prescaler=72-1;                      //36��Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;      //���ϼ��� 
    TIM_TimeBaseStructure.TIM_Period= 50000-1;                      //���������õ���װ�ؼĴ���
  
    /*����������CR1�Ĵ����� 9 10 λ��
    �����ڶ�ʱ��ʱ��(CK_INT)Ƶ���������˲���(ETR��TIx)
    ʹ�õĲ���Ƶ��֮��ķ�Ƶ������*/
    TIM_TimeBaseStructure.TIM_ClockDivision=
                                            TIM_CKD_DIV1;          //   
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);

}

void TIM3_Init()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
    NVIC_InitTypeDef NVIC_InitStructure;

    /*��ʱ����������*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    TIM_TimeBaseStructure.TIM_Prescaler=720-1;                      //36��Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;      //���ϼ��� 
    TIM_TimeBaseStructure.TIM_Period= 50000-1;                      //���������õ���װ�ؼĴ���
  
    /*����������CR1�Ĵ����� 9 10 λ��
    �����ڶ�ʱ��ʱ��(CK_INT)Ƶ���������˲���(ETR��TIx)
    ʹ�õĲ���Ƶ��֮��ķ�Ƶ������*/
    TIM_TimeBaseStructure.TIM_ClockDivision=
                                            TIM_CKD_DIV1;          //   
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                      //���������ж�

		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ;          //TIM2�ж�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //��ռ���ȼ�2��
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;             //�����ȼ�0��
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //IRQͨ����ʹ��
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

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
 
   //��ʼ��TIM4
	TIM_TimeBaseStructure.TIM_Period = 5000; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =72-1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
  
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_Pulse = 0;//��ʼռ�ձ�Ϊ0
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);


 //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���;
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM3
	TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_ARRPreloadConfig(TIM4, ENABLE);

}
