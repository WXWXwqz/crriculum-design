/***********************************************************/
/*  本程序只供学习使用，未经作者许可，不得用于其它任何用途 */
/*  miniSTMF103ZX-EX开发板                                 */
/*  我想我笑 ＱＱ５２３８８５０１９                        */
/*  修改日期: 2014/7/7                                     */
/***********************************************************/
#include"zai.h"
#include"delay.h"
#include"led.h"
//调用函数进入待机状态
void Go_Sleep()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
    PWR_WakeUpPinCmd(ENABLE);
    PWR_EnterSTANDBYMode();     
}

void Weak_UpInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;  		  
	NVIC_InitTypeDef  NVIC_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;

    //GPIO初始化
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA 
                          | RCC_APB2Periph_AFIO, ENABLE); //使能端口A时钟和复用功能
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;	          //PA.0
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD;          //上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);	              //初始化IO


    //中断初始化
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);	//中断线0连接GPIOA.0

    EXTI_InitStructure.EXTI_Line = EXTI_Line0;	                //设置按键所有的外部线路
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//设外外部中断模式:EXTI线路为中断请求
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;      //上升沿触发
   	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	                            // 初始化外部中断

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;            //使能按键所在的外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;          //从优先级2级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); 
}

void EXTI0_IRQHandler(void)
{
    LED_Init(); 
	EXTI_ClearITPendingBit(EXTI_Line0);                         // 清除LINE10上的中断标志位	
    if(Check_WKUP()) Go_Sleep();
} 

u8 Check_WKUP()
{
    u8 i=0,j=0;
    LED_Init();	  
    LED_On(DS3);
    while(1)
    {
        
        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
        {
            i++;
            j=0;
        }
        else
        {
        j++;
        if(j>=5)
            return 0;    
        }
        delay_ms(30);
        if(i>=100)
            return 1;
        
    }
}







