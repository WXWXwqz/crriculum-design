/***********************************************************/
/*                                                         */
/*  miniSTMF103ZX-EX������                                 */
/*  ������Ц �ѣѣ�����������������                        */
/*  �޸�����: 2014/8/1                                     */
/***********************************************************/
#include"dma.h"
u32 AA[100]={0};
void DMA_Open(u32 AddrIn)
{
    DMA_InitTypeDef DMA_InitStructure; 

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
    DMA_DeInit(DMA1_Channel1);
    
    DMA_InitStructure.DMA_PeripheralBaseAddr =
                                         (u32)(&ADC1->DR);             //AddrIn+10;      //DMA���͵������ַ
    DMA_InitStructure.DMA_MemoryBaseAddr =(u32)AA;                 //DMA�ڴ��ַ
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;             //���ݴ��䷽�����⵽��
    DMA_InitStructure.DMA_BufferSize = 20;                          //һ�δ�����������С
    DMA_InitStructure.DMA_PeripheralInc = 
                                    DMA_PeripheralInc_Disable;      //�����ַ����
    DMA_InitStructure.DMA_MemoryInc =    DMA_MemoryInc_Enable;      //�ڴ��ַ����
    DMA_InitStructure.DMA_PeripheralDataSize =
                                   DMA_PeripheralDataSize_Word;     //���ݳ���һ���ֽ�
    DMA_InitStructure.DMA_MemoryDataSize =
                                       DMA_MemoryDataSize_Word;     //�����ڴ����ݳ���
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                   //��ѭ���ɼ�
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;            //�е����ȼ�
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                    //���ڴ浽�ڴ洫��
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);    
    DMA_ClearFlag(DMA1_FLAG_TC1);

    

                                                        
 
}
