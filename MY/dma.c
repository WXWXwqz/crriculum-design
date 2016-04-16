/***********************************************************/
/*                                                         */
/*  miniSTMF103ZX-EX开发板                                 */
/*  我想我笑 ＱＱ５２３８８５０１９                        */
/*  修改日期: 2014/8/1                                     */
/***********************************************************/
#include"dma.h"
u32 AA[100]={0};
void DMA_Open(u32 AddrIn)
{
    DMA_InitTypeDef DMA_InitStructure; 

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
    DMA_DeInit(DMA1_Channel1);
    
    DMA_InitStructure.DMA_PeripheralBaseAddr =
                                         (u32)(&ADC1->DR);             //AddrIn+10;      //DMA发送的外设地址
    DMA_InitStructure.DMA_MemoryBaseAddr =(u32)AA;                 //DMA内存地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;             //数据传输方向由外到内
    DMA_InitStructure.DMA_BufferSize = 20;                          //一次传输数据量大小
    DMA_InitStructure.DMA_PeripheralInc = 
                                    DMA_PeripheralInc_Disable;      //外设地址不变
    DMA_InitStructure.DMA_MemoryInc =    DMA_MemoryInc_Enable;      //内存地址递增
    DMA_InitStructure.DMA_PeripheralDataSize =
                                   DMA_PeripheralDataSize_Word;     //数据长度一个字节
    DMA_InitStructure.DMA_MemoryDataSize =
                                       DMA_MemoryDataSize_Word;     //设置内存数据长度
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                   //不循环采集
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;            //中等优先级
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                    //非内存到内存传输
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);    
    DMA_ClearFlag(DMA1_FLAG_TC1);

    

                                                        
 
}
