/***********************************************************/
/*  本程序只供学习使用，未经作者许可，不得用于其它任何用途 */
/*  miniSTMF103ZX-EX开发板                                 */
/*  我想我笑 ＱＱ５２３８８５０１９                        */
/*  修改日期: 2014/7/28                                    */
/***********************************************************/
#include"adc.h"
void ADC_Open(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    //GPIOA端口时钟使能
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;             //推挽输出
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);    

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);    //ADC1时钟使能
    ADC_DeInit(ADC1);                                      //ADC1复位
    ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;        //独立模式
    ADC_InitStructure.ADC_ScanConvMode=ENABLE;            //单通道模式
    ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;      //单次模式
    ADC_InitStructure.ADC_ExternalTrigConv=\
                            ADC_ExternalTrigConv_None;     //软件触发
    ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;    //数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel=3;                  //通道数为1
    ADC_Init(ADC1,&ADC_InitStructure);
    ADC_DMACmd(ADC1,ENABLE);
    ADC_Cmd(ADC1,ENABLE);                                  //使能ADC
    ADC_ResetCalibration(ADC1);                            //复位校准
    while(ADC_GetResetCalibrationStatus(ADC1));            //等待复位校准
    ADC_StartCalibration(ADC1);                            //开始校准
    while(ADC_GetCalibrationStatus(ADC1));                 //等待开始校准
    
}
/******************************************************************
名称：double ADC_Get(float Vref)
功能：采集电压值返回
入口参数说明：
            Vref为基准电压

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
