  /**
  ***************2016青岛理工大学毕业设计 智能交通灯控制网络**************
  * @author  我想我笑
  * @version V1
	*	@chip		 stm32f103zet6
	* @lib		 V3.5.0
	* @history 		
	* @data    2016/4/16
  ************************************************************************
  */
#include "head.h"
void Sys_Init(void)
{	
	delay_init();	
}

int main(void)
{
	Sys_Init();
	Led DS0(GPIOE,GPIO_Pin_0);
	Led DS1(GPIOE,GPIO_Pin_2);
	DS1.on();
	return 0;
}

