/**
*   ************************************************************************************
*								�Ϻ�оʥ���ӹɷ����޹�˾
*								    www.holychip.cn
*	************************************************************************************
*	@Examle Version		V1.0.0.0
*	@Demo Version		V1.0.1.0
*	@Date				2017.09.18
*	************************************************************************************
*									 ģ�����ܽ���
*	1�����루��SMT��ģʽ��VDD=5Vʱ���͵�ƽ������͵�ѹ��VIL1����ΧΪ0~1.5V���ߵ�ƽ������
*	   �ߵ�ѹ��VIH1����ΧΪ3.5~5V��
*	2�����루SMT��ģʽ��VDD=5Vʱ���͵�ƽ������͵�ѹ��VIL1����ΧΪ0~1V���ߵ�ƽ������ߵ�
*	   ѹ��VIH1����ΧΪ4~5V��
*	3��P0xDBCT [5:0]���õ�����ʱ����һ����Χ����Ƶϵ��*Tosc*P0xDBCT[5:0]-Tosc<����ʱ��<
*	   ��Ƶϵ��*Tosc*(P0xDBCT[5:0]+1)-Tosc��
	4��HC89F003�ϵ縴λ�Լ�������λ���ܵĸ�λ�����е�IO��ؼĴ�������ָ�ΪĬ��ֵ��
*	************************************************************************************
*									 Ӧ��ע������
*	1����ʹ�÷�����ʱ����JTAG���õ�IO�ڻ��ж�ȡ��д�������쳣����˽���ʹ�÷�����ʱ��Ҫ
*	   �����⼸��IO�ڡ��Ͽ�������ʹ�õ�Դ���缴��������������
*	2�����䵽P0.0/P0.1/P0.2�������ܽ��ϵĹ��ܽš��ⲿ�ж����롢���ϼ�����Ŷ����������ơ�
*   3��HC89F003��B�漰���Ժ�汾��IO��P23��P24��P25��P27������������������ͬʱʹ�ܵĹ��ܣ�
       ���ǲ�����ʹ�ô����������Լ����������룬���ǿ���ʹ�ô�ʩ�������������Լ���ʩ����
       �������룬�������DateSheet��������оƬ�汾�������ѯ�ʴ������Լ�ԭ��ҵ��
*	************************************************************************************
*  								       �ͻ�����
*	��л��ʹ�����ǵĵ�Ƭ���������ִ����Ժ�����ʹ�ô������ʡ��������Ϻ�оʥ���ӹٷ�QQȺ
*	****************************����֧��Ⱥ��201030494***********************************
*   ************************************************************************************
**/
#define	ALLOCATE_EXTERN
#define	ver 5

#include "HC89F0541.h"

#include "..\lib\LB_Led.h"
#include "..\lib\LB_AD.h"
#include "..\lib\LB_Usart.h"
#include "..\lib\LB_eeprom.h"
#include "..\lib\LB_Motor.h"
#include "..\lib\LB_IR.h"
#include "..\lib\LB_Run.h"

INT16U Self_CheckingTime;
INT8U  Self_Checking=0;

void InitSysclk(INT8U SYS)
{

	/************************************ϵͳ��ʼ��****************************************/
	WDTCCR = 0x00;						//�رտ��Ź�
	FREQ_CLK = 0x10;

	while((CLKCON&0x20)!=0x20);			//�ȴ��ڲ���Ƶ��������
	CLKSWR = 0x51;						//ѡ���ڲ���Ƶʱ��Ϊ��ʱ�ӣ��ڲ���ƵRC2��Ƶ��Fosc=16MHz
	while((CLKSWR&0xC0)!=0x40);			//�ȴ��ڲ���Ƶ�л����
	CLKDIV = SYS;						//Fosc1��Ƶ�õ�Fcpu��Fcpu=16MHz
}



/***************************************************************************************
  * @ʵ��Ч��	��P02�˿ڵ�������������Ϊ100K

����3004����ң��ɨ�ػ����ܶ���??????? 2020.09.09
?
����������
1.???? �����������书�� 
?
2.???? ����һ���е��ײ����
?
3.��ɨģʽ:
3.1. ��������ɨģʽ������Ĭ�����ģʽ����
3.2. �ӱ���ɨģʽ�����ڹ�������ɨģʽ�£� 30������ײǽ5���Զ������ӱ���ɨģʽ��
3.3 ������ɨģʽ�� 
3.4. �˹���ɨģʽ����ͨ��ң�����ٿط����������ҷ���
?
4.������ң��: ǰ�������ҿ��ƣ�������3��������ͷ�����ӿڣ�����ϸ�뿴˿ӡͼ��
?
5.��е��ײ��⣺���飬�м�һ����⿪�أ����������һ���ᴥ����
?
6.������������ֹͣ�������ܲ�����ԭ����ģʽ�����»ص�������ɨʱ���ٴΰ�������/��ͣ����,���ٴ��������ǰ��ģʽ���빤��״̬.
?
7.���أ�����������ܵ�Դ���أ������������ϵ�����Դ����ʱ������Ĭ�Ϲ�������ɨģʽ.
�����������أ����Ϊ������ɨ��ݰ������ұ�Ϊ��ͣ/���������뿴˿ӡͼ��
?
8.???? ��Դ����﮵��7.4V������3.7V����2000MAH��
?
8.1 USB5V��磬����Ϊ MICRO? USB
?
8.2 ������Ϊ0.65A,������緽ʽ����������������������̵ơ������庸һ�����5MM˫ɫ�ƣ�
?
8.3 ���ŵ�ѹΪ6V,�����͵�ѹ�����������������죬�����ֹ��ѹΪ8.4V��
?
9.???? ��������: �ο��ͺ�̼ˢ��� RC-365SH-1992-52K ������ѹ6.8V����������ر�����
?
��������Ҫ������·�壬������˾�ṩPCB���ϣ������������������������ϣ�
?
10.? ��ɨ����: �ο��ͺŵ�ˢ���320CH-11480 ��������ѹ6.8V, ��������ر�����
?
11.��������: �ο��ͺ�̼ˢ���YRK-370SH-24110 D/V6.8������ѹ6.8V, ��������ر�����
?
������ʾ��
?
1.???? ������ס���������ÿ��5����һ��������
2.???? �������գ��������ÿ��5��������������
3.???? ��ɨ�����ת���������ÿ��5��������������
4.???? ���������ת���������ÿ��5��������������1�����һ��������
5.???? ���ȶ�ת���ߵ����󣬺������ÿ��5��������������1���������������
6.???? �͵�ʱ�����������������������ʾ������������


***************************************************************************************/

  

void main(void)
{
//    INT8U Self_Checking=0;
	INT8U  KK;
	INT8U  First_step=0;
	InitSysclk(1);

	InitT1();
	InitADIO();
	Init_MotorSpeed();
    InitMotorIO();
	Init_Usart1();
	InitFanEdgeIO();
	InitLed();
	InitKey();
	InitPowerIn();
	Init_IR();



	Init_MotorSpeedIR();

	ADCtl=1;
	EdgeCollectDelayTime=0;
    Self_CheckingTime=0;
	Self_Checking=0;


	RunStep=0;
	RCurrentMax=350;
	LCurrentMax=350;
	LCurrent=0;
	RCurrent=0;

	
	EdgeCurrent=0;
	FanCurrent=0;
	EdgeCurrentCount=0;

	

	Mode=1;
	Step=0;

	Voltage=840;

	while(1)
	{
	     KK= CheckHandsetIR();
	     
		
		#if 0
		KK=ReadKey();
	         if(KK==0)
	         KK= CheckHandsetIR();
	         CheckMode(KK);
	         CheckGround();
	         CheckRun();
		
		#endif 
		
	}

}
#if 0
void INT0_Rpt() interrupt INT0_VECTOR 
{
    if(PINTF0&0x01)						//�ж�INT15�жϱ�־λ
	{
	  PINTF0 &=0xfe;				//���INT15�жϱ�־λ		
	}
	 if(After_Lowpowermode==1)						//�ж�INT15�жϱ�־λ
	{
	  Mode=0;
	  After_Lowpowermode=0;
	  InitT1();
	  Init_Usart1();
	  InitADIO();
	  Init_MotorSpeed();
	  InitMotorIO();
	  InitFanEdgeIO();
	  InitLed();
	  InitKey();
	  InitPowerIn();
	  InitBuzzer();
	  InitIMP();
	  Init_MotorSpeedIR();
	  Init_IR();	
	}						  				
}
#endif 
void INT8_17_Rpt() interrupt INT8_17_VECTOR 
{

	if(PINTF1&0x20)						//�ж�INT13�жϱ�־λ
	{
		PINTF1 &=~ 0x20;				//���INT13�жϱ�־λ	
		Read_Remote1IR();
	}
	
}



void TIMER1_Rpt(void) interrupt TIMER1_VECTOR
{
  static INT8U t_10ms;
  static INT8U t_100ms;
  static INT8U t_1s;
  //IRTime++;
  t_10ms++;
  ReadAD5ms();
  Remote1_Count();
  
  if(t_10ms>99)
  {
  	t_10ms=0;
	t_100ms++;
	t_1s++;
	RunMs++;
 	  CheckLeftMotorSpeed();
	  CheckRightMotorSpeed();
	  AdjustSpeed();

	CheckVoltage();
	if(t_100ms>9)
	{
	  
	  t_100ms=0;
	 // Run100MSecond++;
	  // KeydelayTime++;
	  // KeyRunTime++;
	  CheckLCurrent();
	  CheckRCurrent();
	  CheckFanCurrent();
	  CheckEdgeCurrent();



//	      Usart1Send[0]=9;
//	      Usart1Send[1]=Self_Checking;
//		  Usart1Send[2]=Self_CheckingTime;
//		  Usart1Send[3]=ImpStatus;
//		  Usart1Send[4]=GroundDp[0];
//		  Usart1Send[5]=GroundDp[1];
//		  Usart1Send[6]=GroundDp[2];
//		  Usart1Send[7]=P3_2;
//		  Usart1Send[8]=P0_0;
//		  Usart1Send[9]=P0_1;
//	      SendCount=1;
//	      SBUF=Usart1Send[SendCount];
	  #if 0
	  Usart1Send[0]=19;
	  Usart1Send[1]=Voltage/100;
	  Usart1Send[2]=Voltage%100;
	  Usart1Send[3]=Mode;
	  Usart1Send[4]=Step;

	  Usart1Send[5]=RunStep;
	  Usart1Send[6]=ImpStatus;
	  Usart1Send[7]=LCurrent>>8;
	  Usart1Send[8]=LCurrent;
	  Usart1Send[9]=GroundDp[0];
	  Usart1Send[10]=GroundDp[1];
	  Usart1Send[11]=GroundDp[2];
	  Usart1Send[12]=LeftMoveMotorData.AvgSpeed;
	  Usart1Send[13]=RightMoveMotorData.AvgSpeed;
	  Usart1Send[14]=LeftMoveMotorData.NowPulsed/100;
	  Usart1Send[15]=LeftMoveMotorData.NowPulsed%100;
	  Usart1Send[16]=RightMoveMotorData.NowPulsed/100;
	  Usart1Send[17]=RightMoveMotorData.NowPulsed%100;
	  Usart1Send[18]=FanCurrent>>8;
	  Usart1Send[19]=FanCurrent;
//	  Usart1Send[18]=RCurrent>>8;
//	  Usart1Send[19]=RCurrent;
//	  Usart1Send[20]=EdgeCurrent>>8;
//	  Usart1Send[21]=EdgeCurrent;

	  SendCount=1;
	  SBUF=Usart1Send[SendCount];

    #endif 
	  
	}
	
	if(t_1s>99)
	{
	  t_1s=0;
	  Self_CheckingTime++;
//	  KeyclearTime++;
	//  EdgeErrordelayTime++;
	  EdgeCollectDelayTime++;
	  RunSecond++;	 
	//  GroundSecond++;
	//  ImpSecond++;
	  
      /*
	  Usart1Send[0]=8;
	  Usart1Send[1]=Voltage/100;
	  Usart1Send[2]=Voltage%100;
	  Usart1Send[3]=GroundDp[0];
	  Usart1Send[4]=GroundDp[1];
	  Usart1Send[5]=GroundDp[2];
	  Usart1Send[6]=LCurrent;
	  Usart1Send[7]=RCurrent;
	  Usart1Send[8]=RunStep;
	  SendCount=1;
	  SBUF=Usart1Send[SendCount];
	  */
	  /*
	  Usart1Send[0]=13;
	  Usart1Send[1]=LeftIR.Left;
	  Usart1Send[2]=LeftIR.Right;
	  Usart1Send[3]=LeftIR.Mid;
	  Usart1Send[4]=LeftIR.Top;

	  Usart1Send[5]=MidIR.Left;
	  Usart1Send[6]=MidIR.Right;
	  Usart1Send[7]=MidIR.Mid;
	  Usart1Send[8]=MidIR.Top;

	  Usart1Send[9]=RightIR.Left;
	  Usart1Send[10]=RightIR.Right;
	  Usart1Send[11]=RightIR.Mid;
	  Usart1Send[12]=RightIR.Top;

	  Usart1Send[13]=RunStep;
	  SendCount=1;
	  SBUF=Usart1Send[SendCount];
  	  */
	  //SBUF=Usart1Send[SendCount];	
	}
  }
}
void WDT_Rpt() interrupt WDT_VECTOR
{
	WDTC &=~ 0x20;						//���WDT�жϱ�־λ
}