/***********************************************************/
/*  ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���; */
/*  miniSTMF103ZX-EX������                                 */
/*  ������Ц �ѣѣ�����������������                        */
/*  �޸�����: 2014/8/1                                     */
/***********************************************************/  
#include"dac.h"
void DAC_Open(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitStructure;
                    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    //GPIOA�˿�ʱ��ʹ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);      //GPIOA�˿�ʱ��ʹ��
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;             //ģ�����루�����ţ�
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);      

    DAC_InitStructure.DAC_Trigger=DAC_Trigger_None;     //��ʹ�ô���
    DAC_InitStructure.DAC_WaveGeneration=\
                           DAC_WaveGeneration_None;     //��ʹ�ò��η���
    DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=
                           DAC_LFSRUnmask_Bit0; 
    DAC_InitStructure.DAC_OutputBuffer=
                           DAC_OutputBuffer_Disable;    //�������������
    DAC_Init(DAC_Channel_1,&DAC_InitStructure);

    DAC_Cmd(DAC_Channel_1,ENABLE);                      //ʹ��ͨ��


}
void DAC_OutPut(float Vol)
{
    DAC_SetChannel1Data(DAC_Align_12b_R,Vol/3.3*4096);
}
