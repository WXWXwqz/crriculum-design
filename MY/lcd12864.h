/***********************************************************/
/*  ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���; */
/*  miniSTMF103ZX-EX������                                 */
/*  ������Ц �ѣѣ�����������������                        */
/*  �޸�����: 2014/7/3-4                                   */
/***********************************************************/
#ifndef _LCD12864_H
#define _LCD12864_H
#include "stm32f10x.h"  
#define E GPIO_Pin_5        
#define SID GPIO_Pin_6      
#define SCLK GPIO_Pin_7
#define PSB  GPIO_Pin_12
//#define DB(x)     Data_Bit(x)
#define LCD_CLEAR			0x01	    //�����ʾ
#define LCD_CURSOR			0x02	    //λַ��λ���α��ԭ��
#define LCD_CURSOR_RLF		0x04    	//������ƣ�������ʾ���ƶ�
#define LCD_CURSOR_RRF		0x06    	//������ƣ�������ʾ���ƶ�
#define LCD_CURSOR_RLN		0x05       	//������ƣ�������ʾ�ƶ�
#define LCD_CURSOR_RRN		0x07    	//������ƣ�������ʾ�ƶ�
#define LCD_DIS_OFF		    0x08    	//��ʾ״̬ȫ��
#define LCD_DIS_ON			0x0E    	//��ʾ״̬��
#define LCD_DIS_CUR_ON		0x0E    	//�α���ʾ��
#define LCD_DIS_CURS_ON	    0x0F    	//�α�λ����ʾ��
#define LCD_CURSOR_RL		0x10    	//�α�����
#define LCD_CURSOR_RR		0x14      	//�α�����
#define LCD_CURDIS_RL		0x18    	//������ʾ���ƣ�������
#define LCD_CURDIS_RR		0x1C    	//������ʾ���ƣ�������
#define LCD_COM_BASIC		0x30    	//����ָ�����
#define LCD_COM_PLOT_ON	    0x36    	//��չָ���������ͼ��ʾON
#define LCD_COM_PLOT_OFF	0x34    	//��չָ���������ͼ��ʾOFF
#define LCD_STAND_TO		0x31    	//�������ģʽ
#define LCD_PLACE_ROLL		0x03      	//���������λַ
#define LCD_PLACE_IRAM		0x02    	//��������IRAMλַ
#define LCD_REVERES_13		0x04    	//ѡ��һ������ͬʱ��������ʾ
#define LCD_REVERES_24		0x05    	//ѡ���������ͬʱ��������ʾ
#define LCD_REST_ON		    0x08    	//����˯��ģʽ
#define LCD_REST_OFF		  0x0C    	//����˯��ģʽ
#define LCD_Line1           0x80
#define LCD_Line2           0x90
#define LCD_Line3           0x88
#define LCD_Line4           0x98
#define LCD_Flag_Cmd 0
#define LCD_Flag_Data 1  
#define LCD_SetBits(n) GPIOA->BSRR=(n)
#define LCD_ResetBits(n) GPIOA->BRR=(n) 
 
void LCD_GPIOInit(void);
void LCD_Init(void);
void LCD_GPIO_Init(void);
void LCD_Write(u8 LCD_Flag,u8 LCD_Data);
void LCD_Test(void);
void LCD_Cls(void);
void LCD_DisChar(u8,char *);
void LCD_DisNum(u8,u32);
void LCD_DisXiaoShu(u8 ,double Num);
void LCD_WriteAddr(u8 ,u8);
void LCD_WriteBmp(u8 *);
void LCD_DisPel(u8,u8,u8);
//u8   LCD_Read(void);

#endif
