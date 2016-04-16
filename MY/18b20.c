/***********************************************************/
/*  miniSTMF103ZX-EX������                                 */
/*  ������Ц �ѣѣ�����������������                        */
/*  �޸�����: 2014/8/3                                     */
/***********************************************************/
#include"18b20.h"
/**��C6��Ϊ18B20�����ݿ�**/
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
/*��λ����*/
void Reset(void)
{
    
    GPIO_Out();                     //���õ�Ƭ��Ϊ���ģʽ
    DQ_H;                           //���������ߣ��ͷ����ߡ�
       
    DQ_L;                           //���������͡�
    delay_us(480);                  // ��ʱԼ480us���������ߵ�ƽΪ�ͣ������ϵ�����������λ��
    DQ_H;;                          // ���͸�λ����󣬽��������ߡ��ͷ�����,�����ߴ��ڿ���״̬
    delay_us(30);
    GPIO_In();                      //���õ�Ƭ��Ϊ���롣
    /*ֻҪ�ǵ͵�ƽ���ͽ���ѭ�������Ǵ������壬��ԼΪ60-240us��*/
    while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6));  
    GPIO_Out();                     //�������������֮�����õ�Ƭ��Ϊ���ģʽ��
    DQ_H;                           //��⵽�������壬���������ߡ��ͷ����� ����240us��
    delay_us(300);                  // �ͷ�����    
                                    //��ʱ����Ƭ����18b20�ʹ����Э�顣���Խ���ͨѶ�ˡ�
}    

/*д����*/
void Write(u8 Cmd)
{
    u8 i,temp; 
    for(i = 0; i < 8; i ++) 
    {
    temp = Cmd & 0x01;             //ȡ����Ҫ���͵����ݵ����λ   
    GPIO_Out();                     //��Ƭ������Ϊ���ģʽ
    DQ_L;                           //�������ߡ�
    delay_us(15);                   //��ʱ15us���ң�����д����ʱ���϶��
    if(temp) 
    {                               //���д1�Ļ���                       
        DQ_H;                           // дʱ��϶��ʼ���15��s���Ƚ������������ߵ�ƽ
        delay_us(60);                   // ����дʱ��϶�������ٳ���60us
    }
    else
    {                               //д 0
        delay_us(60);                   //�������߱���60us
        DQ_H;                           //����60us������Ϊд0
    }
    delay_us(20);                   // ����һ������ʱ���Ա�֤����λ�ķ���ʱ����60-120us�䡣
    Cmd = Cmd >> 1;                 //���ƣ�����һ��Ҫ���͵����ݷŵ����λ
    }
    
}
/*������*/
u8 Read(void)
{
    u8 temp, i;
    GPIO_Out();                   
    DQ_H;
    temp=0;                         // �趨��ֵΪ0
    for(i = 0; i < 8; i ++)         //ѭ��8�εõ�һ���ֽڡ�
    {
    temp>>=1;                       //�Լ�����	
    GPIO_Out();                     
    DQ_L;                           // ����������
    delay_us(2);                    //����������������ʱ1us�������ʱ�䡣
    GPIO_In();                      // �������ߺ����ͷ����ߣ���DS18B20�ܹ��������ߣ��Ա������Ч����
    //��1.
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6))
    temp|=0x80;                     // �������ӻ�18b20��������ݣ�����temp���λ�������и����ƵĲ�������Ƶ����λ
    else
    temp&=0x7f;                     //  ���Ǵӵ�λ��ʼ�ġ�(����㷨���Ƿǳ��ؼ��ġ�)
    delay_us(65);                   // ����һ����ʱ����֤����λ�Ķ�ȡʱ�����60-120us��Ҳ��֤��������֮����һ����ʱ������
    }
    return temp;       
}
/*ת����ʼ*/
void Convent(void)	 
{
        Reset();
        Write(0xCC);                //  ����ROMָ��
        Write(0x44);                //  ִ���¶�ת���洢������ָ��
}
/*����¶�*/
u16 Get_Temputer(void)
//������ִ�еڶ�������Ϊ��λ������ROMָ�0xCC����ִ�ж�RAM�Ĵ洢������ָ�0xBE��
               //�������ݣ����Ϊ9���ֽڣ���;��ֹͣ��ֻ�����¶�ֵ���ǰ2���ֽڼ��ɣ���
{
    u16 a, b;
    u16 temp;
    Reset();
    Write(0xCC);                   //����ROMָ�0xCC��
    Write(0xBE);                   //ִ�ж�RAM�Ĵ洢������ָ�0xBE��
    a = Read();	                   //�ȶ����λ��
    b = Read();	                   //�ٶ�ǰ��λ��
    temp = (b << 8 )| a;           //�����ζ�����8λ���������һ��
    return temp;                   //���ش����¶ȵĴ��롣
}




//    while(1)
//    {
//        Convent();                   //����һ��ת��
//        delay_us(500);               //�ȴ�ת�����
//        temp=Get_Temputer();         //�õ�һ��ת������ 
//        if(temp>0xf000)  
//        printf("��ǰ�¶�%.2f \n",((~temp)+1)*0.0625);
//        else
//        printf("��ǰ�¶�%.2f ���϶�\n",temp*0.0625);
//        delay_ms(100);
//        LED_On(2);
//    }
