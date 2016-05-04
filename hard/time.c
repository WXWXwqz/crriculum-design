/***********************************************************/
/*                                                         */
/*  miniSTMF103ZX-EX������                                 */
/*  ������Ц �ѣѣ�����������������                        */
/*  �޸�����: 2014/8/1                                     */
/***********************************************************/
#include "time.h"
#include "delay.h"
#include "stdio.h"
#include "netserve.h"
void TIM2_Init()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 


    /*��ʱ����������*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    TIM_TimeBaseStructure.TIM_Prescaler=72-1;                      //36��Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;      //���ϼ��� 
    TIM_TimeBaseStructure.TIM_Period= 10000-1;                      //���������õ���װ�ؼĴ���
  
    /*����������CR1�Ĵ����� 9 10 λ��
    �����ڶ�ʱ��ʱ��(CK_INT)Ƶ���������˲���(ETR��TIx)
    ʹ�õĲ���Ƶ��֮��ķ�Ƶ������*/
    TIM_TimeBaseStructure.TIM_ClockDivision=
                                            TIM_CKD_DIV1;          //   
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);

}

void TIM3_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
    NVIC_InitTypeDef NVIC_InitStructure;

    /*��ʱ����������*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    TIM_TimeBaseStructure.TIM_Prescaler=72-1;                      //36��Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;      //���ϼ��� 
    TIM_TimeBaseStructure.TIM_Period= 1000-1;                      //���������õ���װ�ؼĴ���
  
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

