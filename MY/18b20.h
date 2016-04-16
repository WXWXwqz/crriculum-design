/***********************************************************/
/*  miniSTMF103ZX-EX开发板                                 */
/*  我想我笑 ＱＱ５２３８８５０１９                        */
/*  修改日期: 2014/8/3                                     */
/***********************************************************/
#ifndef _18B20_H
#define _18B20_H
#include"stm32f10x.h"
#include"delay.h"
#define DQ_H  GPIOC->BSRR=GPIO_Pin_6
#define DQ_L  GPIOC->BRR=GPIO_Pin_6
void GPIO_In(void);
void GPIO_Out(void);
void Reset(void);
void Write(u8 );
u8 Read(void );
void Convent(void);
u16 Get_Temputer(void);
#endif
