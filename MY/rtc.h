/***********************************************************/
/*  本程序只供学习使用，未经作者许可，不得用于其它任何用途 */
/*  miniSTMF103ZX-EX开发板                                 */
/*  我想我笑 ＱＱ５２３８８５０１９                        */
/*  修改日期: 2014/7/2                                     */
/***********************************************************/
#ifndef _RTC_H
#define _RTC_H
#include"stm32f10x.h"
//#include <stm32f10x_lib.h>
void RTC_Init(void );
void RTC_TimeDis(void);
void RTC_TimeSet(u16,u8,u8,u8,u8,u8);
#endif
