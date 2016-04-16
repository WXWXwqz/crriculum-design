/***********************************************************/
/*  本程序只供学习使用，未经作者许可，不得用于其它任何用途 */
/*  miniSTMF103ZX-EX开发板                                 */
/*  我想我笑 ＱＱ５２３８８５０１９                        */
/*  修改日期: 2014/8/1                                     */
/***********************************************************/  
#include"dac.h"
void DAC_Open(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitStructure;
                    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    //GPIOA端口时钟使能
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);      //GPIOA端口时钟使能
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;             //模拟输入（防干扰）
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);      

    DAC_InitStructure.DAC_Trigger=DAC_Trigger_None;     //不使用触发
    DAC_InitStructure.DAC_WaveGeneration=\
                           DAC_WaveGeneration_None;     //不使用波形发生
    DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=
                           DAC_LFSRUnmask_Bit0; 
    DAC_InitStructure.DAC_OutputBuffer=
                           DAC_OutputBuffer_Disable;    //不设置输出缓存
    DAC_Init(DAC_Channel_1,&DAC_InitStructure);

    DAC_Cmd(DAC_Channel_1,ENABLE);                      //使能通道


}
void DAC_OutPut(float Vol)
{
    DAC_SetChannel1Data(DAC_Align_12b_R,Vol/3.3*4096);
}
