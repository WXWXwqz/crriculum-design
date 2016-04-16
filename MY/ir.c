/***********************************************************/
/*                                                         */
/*  miniSTMF103ZX-EX开发板                                 */
/*  我想我笑 ＱＱ５２３８８５０１９                        */
/*  修改日期: 2014/8/3                                     */
/***********************************************************/
#include "ir.h"
#include "timer.h"
#include "exti.h"
#include "usart.h"
#include "led.h"
#include "delay.h"
#include "Car.h"
u8 Data[4]={0,0,0,0};
u8 Code,Code_Last;
u16 L_time,H_time;
u8 Flag_Time=0;
u8 Flag_Off=1;
u8 Flag_Auto=1;
//extern s8 CarSTARTFLAG;
void IR_init(void)
{
    TIM2_Init();
    EXTI0_Init();
}

u8 Decode(void)
{
    u8 i,j,temp=0;
    
    for(j=0;j<4;j++)
    {    
        for(i=0;i<8;i++)
        {
            TIM_Cmd(TIM2,ENABLE);
            while(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)&&(TIM2->CNT)<20000); 
            TIM_Cmd(TIM2,DISABLE);
            L_time=TIM2->CNT;               
            TIM2->CNT=0;  
            TIM_Cmd(TIM2,ENABLE); 
            while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)&&(TIM2->CNT)<20000);
            TIM_Cmd(TIM2,DISABLE);
            H_time=TIM2->CNT; 
            TIM2->CNT=0;  
            temp<<=1;					
            if(L_time>400&&L_time<700)
            {		
                if(H_time>500&&H_time<650)
                temp&=0xfe;
                else if(H_time>1500&&H_time<1900)
                temp|=0x01;							
                 else return 0;                   
            }
             else return 0;
        } 
        Data[j]=temp;	
    }
 
        Code=Code_Last=Data[2];    
		
        return 1; 
}

void EXTI0_IRQHandler(void)
{

    TIM2->CNT=0;
    TIM_Cmd(TIM2,ENABLE);   
    while(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)&&(TIM2->CNT)<20000); 
    TIM_Cmd(TIM2,DISABLE);    
    L_time=TIM2->CNT; 
	  TIM2->CNT=0;
    TIM_Cmd(TIM2,ENABLE);
    while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)&&(TIM2->CNT)<20000 );
    TIM_Cmd(TIM2,DISABLE);    
    H_time=TIM2->CNT; 
    TIM2->CNT=0;

    if((L_time>8000)&&(L_time<10000)&&H_time>4000&&H_time<5000)
    {
			while(!Decode());  
    }
		if((L_time>8000)&&(L_time<10000)&&H_time>2000&&H_time<3000)
		{
			Code=Code_Last;		
		}			
			if(Code==144)
			{
				Flag_Off=~Flag_Off;
//				CarSTARTFLAG=1;
				delay_ms(20);
			}			
			if(Code==80&&(Flag_Off!=1))		//右转
			{
				LED_On(2);
				Car_Right();
				Flag_Time=1;
				printf("右转");
			}
			if(Code==160&&(Flag_Off!=1))	//前进
			{
				LED_On(2);
				Car_Front();
				Flag_Time=1;
				printf("前进");
			}
			if(Code==176&&(Flag_Off!=1))		//后退
			{
				LED_On(2);
				Car_Back();
				Flag_Time=1;
				printf("后退");
			}
			if(Code==16&&(Flag_Off!=1))		//左转
			{
				LED_On(2);
				Car_Left();
				Flag_Time=1;	
				printf("左转");
			}		
			if(Code==32&&(Flag_Off!=1))		//左转
			{
				LED_On(2);
				delay_ms(20);
				Flag_Auto=~Flag_Auto;	
				printf("自航");
			}		
		
			
			
		EXTI_ClearITPendingBit(EXTI_Line0);
    
}

