#ifndef __LCD_H
#define __LCD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f10x.h"
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
typedef struct TypeLCDIO
{
	GPIO_TypeDef *DataPort,*ControlPort;
	uint16_t E,Rw,Rs;
} TypeLCDIO;
	
	
class lcd
{
	private:		
		TypeLCDIO io;
	public:
		lcd(TypeLCDIO);
	  void writedata(u8);
		void writecmd(u8);
		void readdata(u8);
		void readcmd(u8);
	  void write(u8);
	  void Reset(uint16_t);
		void Set(uint16_t);
		void Init(void);
	  
};

	
	
	
#ifdef __cplusplus
}
#endif

#endif
