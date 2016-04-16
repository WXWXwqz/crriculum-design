/***********************************************************/
/*  ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���; */
/*  miniSTMF103ZX-EX������                                 */
/*  ������Ц �ѣѣ�����������������                        */
/*  �޸�����: 2014/7/7                                     */
/***********************************************************/
#include"zai.h"
#include"delay.h"
#include"led.h"
//���ú����������״̬
void Go_Sleep()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
    PWR_WakeUpPinCmd(ENABLE);
    PWR_EnterSTANDBYMode();     
}

void Weak_UpInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;  		  
	NVIC_InitTypeDef  NVIC_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;

    //GPIO��ʼ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA 
                          | RCC_APB2Periph_AFIO, ENABLE); //ʹ�ܶ˿�Aʱ�Ӻ͸��ù���
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;	          //PA.0
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD;          //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	              //��ʼ��IO


    //�жϳ�ʼ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);	//�ж���0����GPIOA.0

    EXTI_InitStructure.EXTI_Line = EXTI_Line0;	                //���ð������е��ⲿ��·
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//�����ⲿ�ж�ģʽ:EXTI��·Ϊ�ж�����
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;      //�����ش���
   	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	                            // ��ʼ���ⲿ�ж�

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;            //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;          //�����ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); 
}

void EXTI0_IRQHandler(void)
{
    LED_Init(); 
	EXTI_ClearITPendingBit(EXTI_Line0);                         // ���LINE10�ϵ��жϱ�־λ	
    if(Check_WKUP()) Go_Sleep();
} 

u8 Check_WKUP()
{
    u8 i=0,j=0;
    LED_Init();	  
    LED_On(DS3);
    while(1)
    {
        
        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
        {
            i++;
            j=0;
        }
        else
        {
        j++;
        if(j>=5)
            return 0;    
        }
        delay_ms(30);
        if(i>=100)
            return 1;
        
    }
}







