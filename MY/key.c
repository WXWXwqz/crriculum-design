/***********************************************************/
/*  ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���; */
/*  miniSTMF103ZX-EX������                                 */
/*  ������Ц �ѣѣ�����������������                        */
/*  �޸�����: 2014/7/30                                    */
/***********************************************************/
#include"key.h"
void Key_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);    //GPIOF�˿�ʱ��ʹ��
}
void Key_Out(u8 flag,uint16_t Pin)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin=Pin;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;          //�������
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOF,&GPIO_InitStructure);

    if(flag==0)
    GPIO_ResetBits(GPIOF,Pin);
    if(flag==1)
    GPIO_SetBits(GPIOF,Pin);
}
u8 Key_In(uint16_t Pin)
{
    u8 temp=0;
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin=Pin;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;          //��������
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOF,&GPIO_InitStructure);

    temp=GPIO_ReadInputDataBit(GPIOF, Pin);
    return temp;
}
/******************************************************************
���ƣ�char Key_Read(void)
���ܣ���ȡ������̵İ���������
˵��: ������������µĶ����ܾ�����̽ӷ�
******************************************************************/
u8 Key_Scan(void)
{
    
    static u8 temp=0;
    Key_Out(0,P1);
    Key_Out(1,P2|P3);            //�Ե�1�и�0��2��3�и�1

    if(Key_In(P2)==0)
        temp= 1;
    if(Key_In(P3)==0)
        temp=  2;

    Key_Out(0,P2);
    Key_Out(1,P1|P3);            //�Ե�2�и�0��1��3�и�1

    if(Key_In(P3)==0)
        temp=  4;
    if(Key_In(P1)==0)
        temp=  3;

    Key_Out(0,P3);
    Key_Out(1,P1|P2);            //�Ե�3�и�0��2��1�и�1

    if(Key_In(P2)==0)
        temp=  6;
    if(Key_In(P1)==0)
        temp=  5;


    return temp;
}












/******************************************************************
���ƣ�char Key_Read(void)
���ܣ���ȡ������̵İ���������
˵��: ��������ã��ģòɾ�����̵�ѹ����ȡ����ֵ
******************************************************************/
char Key_Read(void)
{
    int i,j;
    static char flag,temp='0';
    double AA;     
    for(i=0;i<15&&j<10;i++)
    {
        AA=ADC_Get(3.3);
        if(AA>=0.1&&AA<=0.139)
        flag='1';
        if(AA>=0.141&&AA<=0.145)
        flag='2';
        if(AA>=0.146&&AA<=0.153)
        flag='3';
        if(AA>=0.224&&AA<=0.230)
        flag='4';
        if(AA>=0.240&&AA<=0.249)
        flag='5';
        if(AA>=0.257&&AA<=0.269)
        flag='6';
        if(AA>=0.363&&AA<=0.370)
        flag='7';
        if(AA>=0.4&&AA<=0.420)
        flag='8';
        if(AA>=0.475&&AA<=0.484)
        flag='9';
        if(AA>=0.808&&AA<=0.816)
        flag='0';
        if(AA>=0.646&&AA<=0.655)
        flag='*';
        if(AA>=1.08&&AA<=1.09)
        flag='#';
        if(AA>=0.153&&AA<=0.165)
        flag='A';
        if(AA>=0.280&&AA<=0.294)
        flag='B';
        if(AA>=0.550&&AA<=0.561)
        flag='C';
        if(AA>=1.6&&AA<=1.62)
        flag='D';
        switch(flag)
        {
                case '1':
                        j++;
                        if(j>=10) flag='1';break;
                case '2': 
                        j++;
                        if(j>=10) flag='2';break;                         
                case '3':                        
                        j++;
                        if(j>=10) flag='3';break; 
                case '4': 
                        j++;
                        if(j>=10) flag='4';break;                        
                case '5': 
                        j++;
                        if(j>=10) flag='5';break;
                case '6':
                        j++;
                        if(j>=10) flag='6';break;
                case '7':                         
                        j++;
                        if(j>=10) flag='7';break;
                case '8':                       
                        j++;
                        if(j>=10) flag='8';break;
                case '9':                         
                        j++;
                        if(j>=10) flag='9';break;
                case '0':                        
                        j++;
                        if(j>=10) flag='0';break;  
                case '*':
                        j++;
                        if(j>=10) flag='*';break;
                case '#':
                        j++;
                        if(j>=10) flag='#';break;
                case 'A':
                        j++;
                        if(j>=10) flag='A';break;
                case 'B':
                        j++;
                        if(j>=10) flag='B';break;
                case 'C':
                        j++;
                        if(j>=10) flag='C';break;
                case 'D':
                        j++;
                        if(j>=10) flag='D';break;
                                                                       
                default: ;
                

        }
            delay_ms(20);

    }
    if(j>=10) temp=flag,j=0;
    return temp; 
}
