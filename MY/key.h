/***********************************************************/
/*  ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���; */
/*  miniSTMF103ZX-EX������                                 */
/*  ������Ц �ѣѣ�����������������                        */
/*  �޸�����: 2014/7/30                                    */
/***********************************************************/
#ifndef   _KEY_H
#define   _KEY_H
#include"stm32f10x.h"
#include"adc.h"
#include"delay.h"
char Key_Read(void);
u8 Key_Scan(void);
void Key_Init(void);
u8 Key_In(uint16_t);
void Key_Out(u8,uint16_t);
#define P1 GPIO_Pin_11
#define P2 GPIO_Pin_13
#define P3 GPIO_Pin_15
#endif  
