/***********************************************************/
/*  ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���; */
/*  miniSTMF103ZX-EX������                                 */
/*  ������Ц �ѣѣ�����������������                        */
/*  �޸�����: 2014/7/2                                     */
/*  ˵�������ִ���ժ��ԭ��ս������������                   */
/***********************************************************/
#include"usart.h"
void USART1_Init()
{
    USART_InitTypeDef  USART_InitStructure; 
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1
                           |RCC_APB2Periph_GPIOA
                           |RCC_APB2Periph_AFIO,ENABLE);//����ʱ��ʹ��    
    USART_DeInit(USART1);                                //���ڸ�λ  
    USART_InitStructure.USART_BaudRate=9600;             //������9600
    USART_InitStructure.USART_WordLength=
                                    USART_WordLength_8b; //��Ч����8λ
    USART_InitStructure.USART_Parity=USART_Parity_No;    //��żУ��λ��
    USART_InitStructure.USART_StopBits=USART_StopBits_1; //ֹͣλ1λ
    USART_InitStructure.USART_HardwareFlowControl=
                         USART_HardwareFlowControl_None; //Ӳ��������ʧ�� 
    USART_InitStructure.USART_Mode=
                            USART_Mode_Rx|USART_Mode_Tx; //�շ�ʹ��
    USART_Init(USART1,&USART_InitStructure);
	//	USART_ITConfig(USART1,USART_IT_TC,ENABLE); 
    USART_Cmd(USART1,ENABLE);                            //����ʹ��

    /*������������*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);    

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
}
//////////////////////////////////////////////////////////////////
//���´���ժ��ԭ��ս������������
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); 
    USART_SendData(USART1,(uint8_t)ch);   
	return ch;
}

#endif 
