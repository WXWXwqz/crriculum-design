
#ifndef	__12864_h__
#define	__12864_h__

#define	OFF			0							//�߼���
#define	ON			1							//�߼���

#define LCD12864_CS_1  	GPIOA->BSRR=GPIO_Pin_12   //Ƭѡ�ź����� 1 
#define LCD12864_CS_0  	GPIOA->BRR=GPIO_Pin_12   //Ƭѡ�ź����� 1 

#define LCD12864_STD_1  	GPIOA->BSRR=GPIO_Pin_10   //������������
#define LCD12864_STD_0  	GPIOA->BRR=GPIO_Pin_10   //������������

#define LCD12864_SCLK_1 	GPIOA->BSRR=GPIO_Pin_8  //������λ��������
#define LCD12864_SCLK_0 	GPIOA->BRR=GPIO_Pin_8  //������λ��������

#define LCD12864_COM 0	//����ָ��
#define LCD12864_DAT 1	//��������
#define uchar unsigned char
#define uint  unsigned int
#define LCD12864_CLEAR			0x01	//�����ʾ
#define LCD12864_CURSOR			0x02	//λַ��λ���α��ԭ��
#define LCD12864_CURSOR_RLF		0x04	//������ƣ�������ʾ���ƶ�
#define LCD12864_CURSOR_RRF		0x06	//������ƣ�������ʾ���ƶ�
#define LCD12864_CURSOR_RLN		0x05	//������ƣ�������ʾ�ƶ�
#define LCD12864_CURSOR_RRN		0x07	//������ƣ�������ʾ�ƶ�
#define LCD12864_DIS_OFF		0x08	//��ʾ״̬ȫ��
#define LCD12864_DIS_ON			0x0E	//��ʾ״̬��
#define LCD12864_DIS_CUR_ON		0x0E	//�α���ʾ��
#define LCD12864_DIS_CURS_ON	0x0F	//�α�λ����ʾ��
#define LCD12864_CURSOR_RL		0x10	//�α�����
#define LCD12864_CURSOR_RR		0x14	//�α�����
#define LCD12864_CURDIS_RL		0x18	//������ʾ���ƣ�������
#define LCD12864_CURDIS_RR		0x1C	//������ʾ���ƣ�������
#define LCD12864_COM_BASIC		0x30	//����ָ�����
#define LCD12864_COM_PLOT_ON	0x36	//��չָ���������ͼ��ʾON
#define LCD12864_COM_PLOT_OFF	0x34	//��չָ���������ͼ��ʾOFF
#define LCD12864_STAND_TO		0x31	//�������ģʽ
#define LCD12864_PLACE_ROLL		0x03	//���������λַ
#define LCD12864_PLACE_IRAM		0x02	//��������IRAMλַ
#define LCD12864_REVERES_13		0x04	//ѡ��һ������ͬʱ��������ʾ
#define LCD12864_REVERES_24		0x05	//ѡ���������ͬʱ��������ʾ
#define LCD12864_REST_ON		0x08	//����˯��ģʽ
#define LCD12864_REST_OFF		0x0C	//����˯��ģʽ

#define LCD12864_W_COM			0xF8	//дָ��
#define LCD12864_R_COM			0xFC	//��ָ��
#define LCD12864_W_DAT			0xFA	//д����
#define LCD12864_R_DAT			0xFE	//������
 
void LCD12864_IOinit(void);
void LCD12864_Init(void);			//LCD12864��ʼ��
void LCD12864_Clear(void);			//LCD12864����

void LCD12864_Waddr(int x,int y);////1 2 3 4
void LCD12864_WPoss(int m,u8 *buff);	//	m=0д���ַ���,m=1,д���ַ�
void LCD12864_Wnum(double m,unsigned int n);

void Interse(u8 y,u8 x,u8 width);
void convertChar (u8 CX,u8 CY,u8 width);

void delete1(void);
void LCD12864_W(u16 dat_com,u8 byte);//dat_com=0дָ�dat_com=1д����
void LCD12864_Wbyte(u8 byte);	//��12864д��8λ����
void LCD12864_TXT_Clear(void);		//LCD12864���ı�
void LCD12864_BMP_Clear(void);		//LCD12864��ͼ��
void LCD12864_Wbmp(u8 *puts);	//LCD12864��ͼ

void Delay_1ms(u16 x) ;



#endif
