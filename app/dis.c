#include "dis.h"
#include "stdio.h"
#include "key.h"
#include "bsp.h"
#include "delay.h"
T_Dis_Flag DisFlag;
extern const u8 QTU_Pinture[240*9];
char PassWord[10]="123321123";
char Time[23]={0};
short   Road_Count;
short   RoadLinght_Count[2]={80,25};   //�ֱ�ΪAC���̵�(BD�ĺ��)��BD�ĺ��(AC�ĺ��)

void LCD_Show_Main_Page(void)       
{
	static u8 flag=1;
	if(flag)
	{
		POINT_COLOR=BLUE;//��������Ϊ��ɫ 
		LCD_Clear(WHITE);//����
		LCD_ShowPicture(1,1,240,70,QTU_Pinture);
		LCD_ShowChinese((lcddev.width-24*4-1)/2,80,1,"��ҵ���");	
		LCD_ShowChinese((lcddev.width-24*9)/2,110,0,"������̫�������ܽ�");
		LCD_ShowChinese((lcddev.width-24*9)/2,110+24,0,"ͨϵͳ�����������");
		POINT_COLOR=RED;
		LCD_ShowChinese((lcddev.width-24*4)/2,200,3,"�������");
		POINT_COLOR=BLACK;
		LCD_ShowChinese(lcddev.width-24*4,250,3,"���䳯");	
		
		flag=0;
	}
	tp_dev.scan(0);
	if(KEY_Scan(0)==KEY_RIGHT)	//KEY_RIGHT����,��ִ��У׼����
	{
		DisFlag.dis_adjust=1;		
    DisFlag.dis_main=0;		
		flag=1;
	}
	if(tp_dev.sta&TP_PRES_DOWN)			//������������
	{	
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{	
			if((tp_dev.x[0]>(lcddev.width-24*4)/2)&&(tp_dev.x[0]<((lcddev.width-24*4)/2+24*4))&&tp_dev.y[0]>200&tp_dev.y[0]<224)
			{
				DisFlag.dis_main=0;
				DisFlag.dis_login=1;
				flag=1;
			}
		}
	}
}
void LCD_Show_Adjust_Page(void)
{
	  POINT_COLOR=BLUE;//��������Ϊ��ɫ 
		LCD_Clear(WHITE);//����
		TP_Adjust();  //��ĻУ׼ 
		TP_Save_Adjdata();	
	  TP_Get_Adjdata();
		DisFlag.dis_adjust=0;		
	  DisFlag.dis_main=1;	
}
u8 LCD_Get_Input(char *data,u8 num)
{
	u8 sw = 0xff;
	static u8 dataflag=0;
	static	char dataword[11]={0};
	static u8 datacnt=0;
	tp_dev.scan(0);
	if(tp_dev.sta&TP_PRES_DOWN)			//������������
	{	
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{	
			tp_dev.scan(0);
		  delay_ms(100);
			if(tp_dev.sta&TP_PRES_DOWN)			//������������
			{	
				if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
				{	
					if(tp_dev.x[0]>=15&&tp_dev.x[0]<85)
					{
						sw=0x01;
					}
					else if(tp_dev.x[0]>=85&&tp_dev.x[0]<155)
					{
						sw=0x02;
					}
					else if(tp_dev.x[0]>=155&&tp_dev.x[0]<=225)
					{
						sw=0x03;
					}
					if(tp_dev.y[0]>=100&&tp_dev.y[0]<150)
					{
						sw|=0x10;
					}
					else if(tp_dev.y[0]>=150&&tp_dev.y[0]<200)
					{
						sw|=0x20;
					}			
					else if(tp_dev.y[0]>=200&&tp_dev.y[0]<250)
					{
						sw|=0x30;
					}
					else if(tp_dev.y[0]>=250&&tp_dev.y[0]<=300)
					{
						sw|=0x40;
					}
					dataflag=1;	
					switch(sw)
					{
						case 0x11: dataword[datacnt]='1';break;
						case 0x12: dataword[datacnt]='2';break;
						case 0x13: dataword[datacnt]='3';break;
						case 0x21: dataword[datacnt]='4';break;
						case 0x22: dataword[datacnt]='5';break;
						case 0x23: dataword[datacnt]='6';break;
						case 0x31: dataword[datacnt]='7';break;
						case 0x32: dataword[datacnt]='8';break;
						case 0x33: dataword[datacnt]='9';break;
						case 0x41: dataword[datacnt]=' ';break;
						case 0x42: dataword[datacnt]='0';break;
						case 0x43: dataword[datacnt]='O';break;
						default  : dataword[datacnt]=0;
					}
					if(datacnt==num&&dataword[datacnt]!=' '&&dataword[datacnt]!='O')
					{
						dataword[datacnt]=0;
						datacnt=num-1;
					}
					sw=0xff;
				}
			}
		}
	}	
	if(dataflag)      //�����ְ���
	{
		dataflag=0;		
		if(dataword[datacnt]!=' '&&dataword[datacnt])   //����ɾ�����ߴ����λ
		{
			
			if(dataword[datacnt]=='O')  //��ȷ��  
			{					
				datacnt=0;                
				for(int i=0;i<num;i++)
				{
					data[i]=dataword[i];
					dataword[i]=0;					
				}
	      dataflag=0;
				datacnt=0;				
				return 1;
			}
			else                     //���������ְ���
			{
				LCD_ShowChar(85+10+datacnt*8,50+17,dataword[datacnt],16,0);
				datacnt++;
			}
		}
		else if(dataword[datacnt])        //ɾ����
		{
			if(datacnt>0)
			{
				dataword[datacnt]=0;
				dataword[--datacnt]=0;
				LCD_Fill(85+10+datacnt*8,50+17,85+10+datacnt*8+8,50+17+16,WHITE);
			}
		}
//		printf("dataword=%s\n",dataword);
//		printf("cnt=%d\n",datacnt);	
	}
	return 0;
}
void LCD_Show_Login_Page(void)
{
	static u8 flag=1;
  static	char password[11]={0};
	if(flag)         //��ʾ����
	{
		delay_ms(100);
		LCD_Show_InPut_Page("����");
		POINT_COLOR=RED;//��������Ϊ��ɫ 
    LCD_ShowChinese((240-24*3-3*2)/2,20,3,"���¼");
		flag=0;
	}
	if(LCD_Get_Input(password,10))    //�õ����룬����У��
	{
			int i=0;				
			while(PassWord[i]!=0)
			{
				if(PassWord[i]!=password[i])
				{
					LCD_ShowChinese(85+10,50+13,0,"�������");
					delay_ms(1000);
					LCD_Fill(85+10,50+13,85+10+24*4+8,50+17+24,WHITE);			
					break;
				}
				i++;
			}
			if(PassWord[i]==0&&password[i]=='O')  //������ȷ
			{
				DisFlag.dis_login=0;
				DisFlag.dis_work_sta=1;
				flag=1;
			}		
	}
}
void LCD_Show_Test_Page (void)
{	
	static u8 flag=1;
	if(flag)         //��ʾ����
	{
		LCD_Clear(WHITE);
	  LCD_ShowString(60,60,200,16,16,"Something need to add");
	  LCD_ShowString(60,80,200,16,16,"Please wait");
		flag=0;
	}
}

void LCD_Show_InPut_Page(char *title)
{
	  LCD_Clear(WHITE);
		POINT_COLOR=BLUE;//��������Ϊ��ɫ 
		for(int i=0;i<6;i++)  //����
		{
			LCD_DrawLine(15,50+i*50,225,50+i*50);
		}
		LCD_DrawLine(15,50,15,100);
		LCD_DrawLine(225,50,225,100);
		for(int i=0;i<4;i++)  //����
		{
			LCD_DrawLine(15+i*70,100,15+i*70,300);
		}
		for(int i=0;i<3;i++)      //��
		{
			for(int j=0;j<3;j++)      //��
			{
				LCD_ShowChar(15+j*70+(70-8)/2,100+50*i+17,'0'+i*3+j+1,16,0);
			}
		}
		LCD_ShowChar(15+1*70+(70-8)/2,100+50*3+17,'0',16,0);       //0
		LCD_ShowChinese(15+11,250+13,0,"ɾ��");
		LCD_ShowChinese(155+11,250+13,0,"ȷ��");
		POINT_COLOR=BLUE;//��������Ϊ��ɫ 
		LCD_ShowChinese(15+11,50+13,0,title);
	//	LCD_ShowChar(15+11+48+1,50+17,':',16,0);	
}
extern const unsigned char DisNum[10][24*48/8];
void LCD_Show_WorkingSta_Input_Page(void)
{
	
}
void LCD_Show_WorkingSta_Page(void)
{
	static u8 flag=1;
	char time[3];
	if(flag)         //��ʾ����
	{
		LCD_Clear(WHITE);
		POINT_COLOR=RED;
		LCD_ShowChinese(5,5,0,"��ǰ״̬");
		LCD_ShowChar(10+24*4,5+4,':',16,0);
		POINT_COLOR=BLACK;
		LCD_DrawLine(15,160,225,160);
		LCD_DrawLine(15,160+100,225,160+100);
		LCD_DrawLine(15,160,15,260);
		LCD_DrawLine(135,160,135,260);
		LCD_DrawLine(45,160,45,260);
		LCD_DrawLine(225,160,225,260);
		LCD_DrawLine(45,190,225,190);
		LCD_DrawLine(90,190,90,260);
		LCD_DrawLine(180,190,180,260);
		LCD_ShowChinese(15+4,160+20,0,"��");
		LCD_ShowChinese(15+4,260-24-20,0,"��");
		LCD_ShowChinese(60,160+3,7,"���");
		LCD_ShowChinese(150,160+3,7,"�̵�");
		LCD_ShowChar(45+19,190+10,'A',16,0);
		LCD_ShowChar(45+19,190+35+10,'C',16,0);
		LCD_ShowChar(135+19,190+10,'A',16,0);
		LCD_ShowChar(135+19,190+35+10,'C',16,0);
		LCD_ShowChar(90+19,190+10,'B',16,0);
		LCD_ShowChar(90+19,190+35+10,'D',16,0);
		LCD_ShowChar(180+19,190+10,'B',16,0);
		LCD_ShowChar(180+19,190+35+10,'D',16,0);
		POINT_COLOR=BLUE;
		LCD_ShowChinese(5,260+18,0,"����ʱ��");
	//	LCD_ShowChar(5+100,260+20,'2',16,0);
		for(int i=0;i<2;i++)
		{
			POINT_COLOR=BLUE;
			LCD_ShowChinese(10,70*i+30,0,"·��");
			LCD_ShowChar(10+48+2,70*i+30+4,'A'+i,16,0);
			LCD_ShowChar(10+48+2+8,70*i+30+4,'C'+i,16,0);
			LCD_ShowChar(10+48+2+16,70*i+30+4,':',16,0);	   		
		}
		flag=0;
	}
	if(DisFlag.monitor_dis)
	{
		DisFlag.monitor_dis=0;
		if(DisFlag.monitor)
		{
			POINT_COLOR=BLUE;
			LCD_ShowChinese(5+24*4+8+24*2+10,5,0,"���");
			LCD_Fill(5+24*4+8+24*2+10+24+24,5,5+24*4+8+24*2+10+24+24+24,5+24,WHITE);
		}
		else
		{
			POINT_COLOR=RED;
			LCD_ShowChinese(5+24*4+8+24*2+10,5,0,"δ���");
		}
	}
	if(DisFlag.mode_dis)
	{
		DisFlag.mode_dis=0;
		if(DisFlag.mode)
		{
			POINT_COLOR=BLUE;
			LCD_ShowChinese(10+24*4+8,5,0,"�Զ�");
		}
		else
		{
			POINT_COLOR=BLUE;
			LCD_ShowChinese(10+24*4+8,5,0,"�ֶ�");
		}
	}
	if(DisFlag.t1000ms && !DisFlag.dis_work_sta_input)
	{
		DisFlag.t1000ms=0;
		WorkingSta_Page_Ref(Road_Count,0);
		WorkingSta_Page_Ref(-Road_Count,1);
		POINT_COLOR=RED;
		if(DisFlag.monitor)
		{
			LCD_DisString(5+120,270+4,0,16,Time);
			LCD_DisString(5+120,270+20+4,0,16,Time+10);
		}
	}
	if(!DisFlag.dis_work_sta_input)
	{
		tp_dev.scan(0);
		if(tp_dev.sta&TP_PRES_DOWN)			//������������
		{	
			if(tp_dev.x[0]<=225&&tp_dev.x[0]>=45&&tp_dev.y[0]<=260&&tp_dev.y[0]>=190)
			{
					if(tp_dev.x[0]<=180&&tp_dev.x[0]>=90)
					{						
						delay_ms(300);
						DisFlag.dis_work_sta_input=1;
						LCD_Show_InPut_Page("ʱ��");
						LCD_ShowChinese((240-24*5-4*2)/2,20,3,"������ʱ��");
						DisFlag.dis_work_sta_input_redac=0;
					}
					else
					{
						DisFlag.dis_work_sta_input=1;
						
						delay_ms(300);
						LCD_Show_InPut_Page("ʱ��");
						LCD_ShowChinese((240-24*5-4*2)/2,20,3,"������ʱ��");
						DisFlag.dis_work_sta_input_redac=1;
					}
			}
		}
	}
	else
	{
		if(LCD_Get_Input(time,2))
		{
			if(DisFlag.dis_work_sta_input_redac)
			{
				if(time[1]>='0'&&time[1]<='9')
				{
					RoadLinght_Count[1]=(time[0]-'0')*10+time[1]-'0';
					EE_Write_Byte(ROADLIGHT1,RoadLinght_Count[1]);
				}
				else
				{
			  	RoadLinght_Count[1]=(time[0]-'0');
					EE_Write_Byte(ROADLIGHT1,RoadLinght_Count[1]);
				}
			}
			else
			{
				if(time[1]>='0'&&time[1]<='9')
				{
					RoadLinght_Count[0]=(time[0]-'0')*10+time[1]-'0';
					EE_Write_Byte(ROADLIGHT0,RoadLinght_Count[0]);
				}
				else
				{
			  	RoadLinght_Count[0]=(time[0]-'0');
					EE_Write_Byte(ROADLIGHT0,RoadLinght_Count[0]);
				}
			}
			DisFlag.dis_work_sta_input=0;
			flag=1;
			DisFlag.mode_dis=1;
			DisFlag.monitor_dis=1;
		}
//		printf("%c ",time[0]);printf("%c ",time[1]);
	}
	

	
}
void WorkingSta_Page_Ref(short num,u8 n)
{

	  if(num>=0)
		{
			POINT_COLOR=BLUE;
			LCD_ShowPicture(10+48+2+16+30,70*n+40,24,42, DisNum[num/10]);
			LCD_ShowPicture(10+48+2+16+30+24+10,70*n+40,24,42,DisNum[num%10]);	
		}
		else
		{
			POINT_COLOR=RED;
			num=-num;
			LCD_ShowPicture(10+48+2+16+30,70*n+40,24,42, DisNum[num/10]);
			LCD_ShowPicture(10+48+2+16+30+24+10,70*n+40,24,42,DisNum[num%10]);	
		}
}
void Dis(void)
{
	if(DisFlag.dis_adjust)
	{
		LCD_Show_Adjust_Page();
	}
	else if(DisFlag.dis_main)
	{
		LCD_Show_Main_Page();			
	}
	else if(DisFlag.dis_login)
	{
		LCD_Show_Login_Page();
	}
	else if(DisFlag.dis_work_sta)
	{		
		LCD_Show_WorkingSta_Page();
	}

	
}
