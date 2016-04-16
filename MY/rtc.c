/***********************************************************/
/*  ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���; */
/*  miniSTMF103ZX-EX������                                 */
/*  ������Ц �ѣѣ�����������������                        */
/*  �޸�����: 2014/7/2                                     */
/***************************��Ʒ****************************/
/***********************************************************/
#include"rtc.h"
#include"led.h"
#include"delay.h"
#include"lcd12864.h"
extern u32 RTC_Counter;
u8 Mon_O,Day_O,Hour_O,Min_O,S_O;
u16 Year_O;
void RTC_Init(void)
{

    NVIC_InitTypeDef NVIC_InitStructure;

    //�����ж�
    NVIC_InitStructure.NVIC_IRQChannel=RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);                           
    if(BKP_ReadBackupRegister(BKP_DR1)!=0x5050)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|\
                                     RCC_APB1Periph_BKP,ENABLE); //ʹ�ܵ�Դ����������ʱ��
        PWR_BackupAccessCmd(ENABLE);                             //ȡ����������д����
        BKP_DeInit();                                            //��������λ
        RCC_LSEConfig(RCC_LSE_ON);                               //�����ⲿ��������
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);                  //ѡ��̣ӣ�ΪRTCʱ��
        RCC_RTCCLKCmd(ENABLE);                                   //ʹ��RTCʱ��
       	RTC_WaitForLastTask();	                                 //�ȴ����һ�ζ�RTC�Ĵ�����д�������
    	RTC_WaitForSynchro();		                             //�ȴ�RTC�Ĵ���ͬ��  
    	RTC_ITConfig(RTC_IT_SEC, ENABLE);		                 //ʹ��RTC���ж�
    	RTC_WaitForLastTask();	                                 //�ȴ����һ�ζ�RTC�Ĵ�����д�������
        RTC_EnterConfigMode();                                   //��������ģʽ
        RTC_SetPrescaler(32767);                                 //ʱ�ӷ�Ƶ����1s����Ƶ��
        RTC_ITConfig(RTC_IT_SEC,ENABLE);                         //ʹ�����ж�
        RTC_SetCounter(3600);                                    //���ü���ֵ
        RTC_ExitConfigMode();                                    //�˳�����ģʽ
        BKP_WriteBackupRegister(BKP_DR1, 0X5050);                //д���û�����                
        
    }
    else
    {
		RTC_WaitForSynchro();	                                //�ȴ����һ�ζ�RTC�Ĵ�����д�������
		RTC_ITConfig(RTC_IT_SEC, ENABLE);                   	//ʹ��RTC���ж�
		RTC_WaitForLastTask();	                                //�ȴ����һ�ζ�RTC�Ĵ�����д�������    }
    }
    RTC_Counter=RTC_GetCounter();
    RTC_TimeSet(2014,7,6,16,44,25);
}

void RTC_IRQHandler(void)
{
 
    if(RTC_GetITStatus(RTC_IT_SEC)!=RESET)
    {
        RTC_Counter=RTC_GetCounter();
    }
    RTC_ClearITPendingBit(RTC_IT_SEC);
    RTC_WaitForLastTask();

  
}

void RTC_TimeSet(u16 a,u8 b,u8 c,u8 d,u8 e,u8 f)
{
    Year_O=a;
    Mon_O=b;
    Day_O=c;
    Hour_O=d;
    Min_O=e;
    S_O=f;
}

void RTC_TimeDis(void)
{
    u32 temp;
    u8 Mon_N,Day_N,Hour_N,Min_N,S_N;
    u16 Year_N;
    temp=RTC_Counter;
    S_N=S_O+(temp%60);
    temp/=60;
    if(S_N>59)
    {
        Min_N+=1;
        S_N-=60;
    }    
    Min_N=Min_O+temp%60;
    if(Min_N>59)
    {
        Hour_N+=1;
        Min_N-=60;
    }
    temp/=60;
    Hour_N=Hour_O+temp%60;
    if(Hour_N>23)
    {
        Day_N+=1;
        Hour_N-=24;
    }
    Day_N=Day_O+temp%24;
    temp/=24;
    if(Day_N>30)
    {
        Mon_N+=1;
        Day_N-=30;
    }    
    Mon_N=Mon_O+temp%30;
    temp/=30;    
    if(Mon_N>12)
    {
        Year_N+=1;
        Mon_N-=12;
    }
    Year_N=Year_O+temp%12;
    
    LCD_DisNum(LCD_Line1+2,Year_N);
    LCD_Write(1,'/');
    LCD_DisNum(0,Mon_N);
    LCD_Write(1,'/');
    LCD_DisNum(0,Day_N); 
    if(Hour_N<10)
        LCD_DisNum(LCD_Line2+2,0);    
    LCD_DisNum(LCD_Line2+2,Hour_N);
    LCD_Write(1,':');
    if(Min_N<10)
        LCD_Write(1,'0');    
    LCD_DisNum(0,Min_N);
    LCD_Write(1,':');
    if(S_N<10)
        LCD_Write(1,'0');    
    LCD_DisNum(0,S_N);
      
}





