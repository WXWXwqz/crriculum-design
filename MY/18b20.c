/***********************************************************/
/*  miniSTMF103ZX-EX开发板                                 */
/*  我想我笑 ＱＱ５２３８８５０１９                        */
/*  修改日期: 2014/8/3                                     */
/***********************************************************/
#include"18b20.h"
/**用C6作为18B20的数据口**/
void GPIO_In(void)
{
    GPIO_InitTypeDef ds18b20_out ; 
    ds18b20_out.GPIO_Pin = GPIO_Pin_6; 
    ds18b20_out.GPIO_Speed = GPIO_Speed_50MHz; 
    ds18b20_out.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
    GPIO_Init(GPIOC, &ds18b20_out);     
}
void GPIO_Out(void)
{
    GPIO_InitTypeDef ds18b20_in ; 
    ds18b20_in.GPIO_Pin = GPIO_Pin_6; 
    ds18b20_in.GPIO_Speed = GPIO_Speed_50MHz; 
    ds18b20_in.GPIO_Mode = GPIO_Mode_Out_PP; 
    GPIO_Init(GPIOC, &ds18b20_in); 
}
/*复位函数*/
void Reset(void)
{
    
    GPIO_Out();                     //设置单片机为输出模式
    DQ_H;                           //将总线拉高，释放总线。
       
    DQ_L;                           //将总线拉低。
    delay_us(480);                  // 延时约480us，保持总线电平为低，总线上的器件将被复位。
    DQ_H;;                          // 发送复位脉冲后，将总线拉高。释放总线,让总线处于空闲状态
    delay_us(30);
    GPIO_In();                      //设置单片机为输入。
    /*只要是低电平，就进行循环。这是存在脉冲，大约为60-240us。*/
    while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6));  
    GPIO_Out();                     //当存在脉冲结束之后，设置单片机为输出模式。
    DQ_H;                           //检测到存在脉冲，把总线拉高。释放总线 至少240us。
    delay_us(300);                  // 释放总线    
                                    //此时，单片机和18b20就达成了协议。可以进行通讯了。
}    

/*写函数*/
void Write(u8 Cmd)
{
    u8 i,temp; 
    for(i = 0; i < 8; i ++) 
    {
    temp = Cmd & 0x01;             //取出需要发送的数据的最低位   
    GPIO_Out();                     //单片机设置为输出模式
    DQ_L;                           //拉低总线。
    delay_us(15);                   //延时15us左右，进入写数据时间间隙。
    if(temp) 
    {                               //如果写1的话。                       
        DQ_H;                           // 写时间隙开始后的15μs内先将数据线拉到高电平
        delay_us(60);                   // 所有写时间隙必须最少持续60us
    }
    else
    {                               //写 0
        delay_us(60);                   //让数据线保持60us
        DQ_H;                           //保持60us后拉高为写0
    }
    delay_us(20);                   // 给予一定的延时，以保证整个位的发送时间在60-120us间。
    Cmd = Cmd >> 1;                 //右移，将下一次要发送的数据放到最低位
    }
    
}
/*读函数*/
u8 Read(void)
{
    u8 temp, i;
    GPIO_Out();                   
    DQ_H;
    temp=0;                         // 设定初值为0
    for(i = 0; i < 8; i ++)         //循环8次得到一个字节。
    {
    temp>>=1;                       //自己理解吧	
    GPIO_Out();                     
    DQ_L;                           // 将总线拉低
    delay_us(2);                    //将总线拉低至少延时1us，进入读时间。
    GPIO_In();                      // 拉低总线后再释放总线，让DS18B20能够控制总线，以便输出有效数据
    //读1.
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6))
    temp|=0x80;                     // 主机读从机18b20输出的数据，放在temp最高位，上面有个右移的操作最后移到最低位
    else
    temp&=0x7f;                     //  读是从低位开始的。(这个算法还是非常关键的。)
    delay_us(65);                   // 给予一定延时，保证整个位的读取时间大于60-120us。也保证连续读数之间有一定的时间间隔。
    }
    return temp;       
}
/*转换开始*/
void Convent(void)	 
{
        Reset();
        Write(0xCC);                //  跳过ROM指令
        Write(0x44);                //  执行温度转换存储器操作指令
}
/*获得温度*/
u16 Get_Temputer(void)
//紧接着执行第二个周期为复位、跳过ROM指令（0xCC）、执行读RAM的存储器操作指令（0xBE）
               //、读数据（最多为9个字节，中途可停止，只读简单温度值则读前2个字节即可）。
{
    u16 a, b;
    u16 temp;
    Reset();
    Write(0xCC);                   //跳过ROM指令（0xCC）
    Write(0xBE);                   //执行读RAM的存储器操作指令（0xBE）
    a = Read();	                   //先读后八位，
    b = Read();	                   //再读前八位。
    temp = (b << 8 )| a;           //把两次读到的8位数据组合在一起
    return temp;                   //返回代表温度的代码。
}




//    while(1)
//    {
//        Convent();                   //开启一次转换
//        delay_us(500);               //等待转换完成
//        temp=Get_Temputer();         //得到一次转换数据 
//        if(temp>0xf000)  
//        printf("当前温度%.2f \n",((~temp)+1)*0.0625);
//        else
//        printf("当前温度%.2f 摄氏度\n",temp*0.0625);
//        delay_ms(100);
//        LED_On(2);
//    }
