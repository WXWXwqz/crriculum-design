/***********************************************************/
/*  本程序只供学习使用，未经作者许可，不得用于其它任何用途 */
/*  miniSTMF103ZX-EX开发板                                 */
/*  我想我笑 ＱＱ５２３８８５０１９                        */
/*  修改日期: 2014/7/2                                     */
/***************************残品****************************/
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

    //设置中断
    NVIC_InitStructure.NVIC_IRQChannel=RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);                           
    if(BKP_ReadBackupRegister(BKP_DR1)!=0x5050)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|\
                                     RCC_APB1Periph_BKP,ENABLE); //使能电源及备份区域时钟
        PWR_BackupAccessCmd(ENABLE);                             //取消备份区域写保护
        BKP_DeInit();                                            //备份区域复位
        RCC_LSEConfig(RCC_LSE_ON);                               //开启外部低速振荡器
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);                  //选择ＬＳＥ为RTC时钟
        RCC_RTCCLKCmd(ENABLE);                                   //使能RTC时钟
       	RTC_WaitForLastTask();	                                 //等待最近一次对RTC寄存器的写操作完成
    	RTC_WaitForSynchro();		                             //等待RTC寄存器同步  
    	RTC_ITConfig(RTC_IT_SEC, ENABLE);		                 //使能RTC秒中断
    	RTC_WaitForLastTask();	                                 //等待最近一次对RTC寄存器的写操作完成
        RTC_EnterConfigMode();                                   //进入配置模式
        RTC_SetPrescaler(32767);                                 //时钟分频，得1s计数频率
        RTC_ITConfig(RTC_IT_SEC,ENABLE);                         //使能秒中断
        RTC_SetCounter(3600);                                    //设置计数值
        RTC_ExitConfigMode();                                    //退出配置模式
        BKP_WriteBackupRegister(BKP_DR1, 0X5050);                //写入用户数据                
        
    }
    else
    {
		RTC_WaitForSynchro();	                                //等待最近一次对RTC寄存器的写操作完成
		RTC_ITConfig(RTC_IT_SEC, ENABLE);                   	//使能RTC秒中断
		RTC_WaitForLastTask();	                                //等待最近一次对RTC寄存器的写操作完成    }
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





