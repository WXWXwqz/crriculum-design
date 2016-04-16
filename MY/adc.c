/***********************************************************/
/*  ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���; */
/*  miniSTMF103ZX-EX������                                 */
/*  ������Ц �ѣѣ�����������������                        */
/*  �޸�����: 2014/7/28                                    */
/***********************************************************/
#include"adc.h"
void ADC_Open(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    //GPIOA�˿�ʱ��ʹ��
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;             //�������
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);    

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);    //ADC1ʱ��ʹ��
    ADC_DeInit(ADC1);                                      //ADC1��λ
    ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;        //����ģʽ
    ADC_InitStructure.ADC_ScanConvMode=ENABLE;            //��ͨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;      //����ģʽ
    ADC_InitStructure.ADC_ExternalTrigConv=\
                            ADC_ExternalTrigConv_None;     //�������
    ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;    //�����Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel=3;                  //ͨ����Ϊ1
    ADC_Init(ADC1,&ADC_InitStructure);
    ADC_DMACmd(ADC1,ENABLE);
    ADC_Cmd(ADC1,ENABLE);                                  //ʹ��ADC
    ADC_ResetCalibration(ADC1);                            //��λУ׼
    while(ADC_GetResetCalibrationStatus(ADC1));            //�ȴ���λУ׼
    ADC_StartCalibration(ADC1);                            //��ʼУ׼
    while(ADC_GetCalibrationStatus(ADC1));                 //�ȴ���ʼУ׼
    
}
/******************************************************************
���ƣ�double ADC_Get(float Vref)
���ܣ��ɼ���ѹֵ����
��ڲ���˵����
            VrefΪ��׼��ѹ

******************************************************************/
double ADC_Get(float Vref)
{
    u16 temp;
    double Vol;
    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_239Cycles5);
//    ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_239Cycles5);
//    ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_239Cycles5);
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
    temp=ADC_GetConversionValue(ADC1); 
    Vol=Vref*(temp/4096.0);
     
    return Vol;  
}
