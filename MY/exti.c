/***********************************************************/
/*                                                         */
/*  miniSTMF103ZX-EX������                                 */
/*  ������Ц �ѣѣ�����������������                        */
/*  �޸�����: 2014/8/3                                     */
/***********************************************************/
#include"exti.h"
#include"led.h"
/*�ⲿ�ж�*/
void EXTI0_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure; 
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|
                           RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);   

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);   //GPIOB���ⲿ�ж���·0
		
    EXTI_InitStructure.EXTI_Line=EXTI_Line0;                      //0���ж�
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;             //�ж�ģʽ
    EXTI_InitStructure.EXTI_Trigger=
                            EXTI_Trigger_Falling;          //�½��ش���
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;               //ʹ���ж��� 
    EXTI_Init(&EXTI_InitStructure);

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;          //��������
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn  ;              //TIM2�ж�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;      //��ռ���ȼ�2��
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;             //�����ȼ�0��
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //IRQͨ����ʹ��
		
		NVIC_Init(&NVIC_InitStructure);   
		
		EXTI_ClearITPendingBit(EXTI_Line0);

    
}


