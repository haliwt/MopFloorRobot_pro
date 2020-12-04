/**
*   ************************************************************************************
*								上海芯圣电子股份有限公司
*								    www.holychip.cn
*	************************************************************************************
*	@Examle Version		V1.0.0.0
*	@Demo Version		V1.0.1.0
*	@Date				2017.09.18
*	************************************************************************************
*									 模块性能介绍
*	1、输入（无SMT）模式下VDD=5V时，低电平即输入低电压（VIL1）范围为0~1.5V、高电平即输入
*	   高电压（VIH1）范围为3.5~5V。
*	2、输入（SMT）模式下VDD=5V时，低电平即输入低电压（VIL1）范围为0~1V、高电平即输入高电
*	   压（VIH1）范围为4~5V。
*	3、P0xDBCT [5:0]配置的消抖时间是一个范围，分频系数*Tosc*P0xDBCT[5:0]-Tosc<消抖时间<
*	   分频系数*Tosc*(P0xDBCT[5:0]+1)-Tosc。
	4、HC89F003上电复位以及其它复位功能的复位，所有的IO相关寄存器都会恢复为默认值。
*	************************************************************************************
*									 应用注意事项
*	1、在使用仿真器时，与JTAG复用的IO口会有读取或写入数据异常，因此建议使用仿真器时不要
*	   操作这几个IO口。断开仿真器使用电源供电即可以正常操作。
*	2、分配到P0.0/P0.1/P0.2这三个管脚上的功能脚、外部中断输入、故障检测引脚都受消抖控制。
*   3、HC89F003自B版及其以后版本，IO口P23、P24、P25、P27口增加了上下拉输入同时使能的功能，
       但是不可以使用带上拉输入以及带下拉输入，但是可以使用带施密特上拉输入以及带施密特
       下拉输入，具体详见DateSheet。（关于芯片版本问题可以询问代理商以及原厂业务）
*	************************************************************************************
*  								       客户服务
*	感谢您使用我们的单片机，若发现错误或对函数的使用存在疑问。请添加上海芯圣电子官方QQ群
*	****************************技术支持群：201030494***********************************
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

	/************************************系统初始化****************************************/
	WDTCCR = 0x00;						//关闭看门狗
	FREQ_CLK = 0x10;

	while((CLKCON&0x20)!=0x20);			//等待内部高频晶振起振
	CLKSWR = 0x51;						//选择内部高频时钟为主时钟，内部高频RC2分频，Fosc=16MHz
	while((CLKSWR&0xC0)!=0x40);			//等待内部高频切换完成
	CLKDIV = SYS;						//Fosc1分频得到Fcpu，Fcpu=16MHz
}



/***************************************************************************************
  * @实现效果	将P02端口的上拉电阻设置为100K

数博3004红外遥控扫地机功能定义??????? 2020.09.09
?
功能描述：
1.???? 三组红外防跌落功能 
?
2.???? 正面一组机械防撞功能
?
3.清扫模式:
3.1. 弓字形清扫模式（开机默认这个模式）；
3.2. 延边清扫模式；（在弓字形清扫模式下， 30秒连续撞墙5次自动进入延边清扫模式）
3.3 定点清扫模式； 
3.4. 人工清扫模式；（通过遥控器操控方向：上下左右方向）
?
4.红外线遥控: 前、后、左、右控制（主板做3组红外接收头插座接口），详细请看丝印图；
?
5.机械防撞检测：三组，中间一组红外开关，左右两侧各一组轻触开关
?
6.机器拿起来后停止工作功能并保存原工作模式，重新回到地面清扫时，再次按下启动/暂停键后，,可再次运行离地前的模式进入工作状态.
?
7.开关：主机面板有总电源开关，当按下主板上的主电源开关时，开机默认弓字形清扫模式.
两个触摸开关：左边为定点清扫快捷按键，右边为暂停/启动键，请看丝印图。
?
8.???? 电源：用锂电池7.4V，两节3.7V容量2000MAH。
?
8.1 USB5V充电，充电口为 MICRO? USB
?
8.2 充电电流为0.65A,恒流充电方式。充电红灯闪亮，充满长亮绿灯。（主板焊一个插件5MM双色灯）
?
8.3 过放电压为6V,机器低电压报警，蜂鸣器连续响，过充截止电压为8.4V。
?
9.???? 后轮马达: 参考型号碳刷马达， RC-365SH-1992-52K 工作电压6.8V，主板带过载保护。
?
后轮马达要带检测电路板，方案公司提供PCB资料，由数博负责制作焊到马达上；
?
10.? 边扫马达: 参考型号电刷马达，320CH-11480 ，工作电压6.8V, 主板带过载保护。
?
11.吸尘马达: 参考型号碳刷马达，YRK-370SH-24110 D/V6.8工作电压6.8V, 主板带过载保护。
?
故障提示：
?
1.???? 机器卡住，红灯亮，每隔5秒响一声哔声；
2.???? 机器悬空，红灯亮，每隔5秒响两声哔声；
3.???? 边扫马达堵转，红灯亮，每隔5秒响三声哔声；
4.???? 后轮马达堵转，红灯亮，每隔5秒响两声哔声，1秒后响一声哔声；
5.???? 风扇堵转或者电流大，红灯亮，每隔5秒响三声哔声，1秒后响两声哔声；
6.???? 低电时，红灯闪，蜂鸣器连续响提示音响哔声音；


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



	//Init_MotorSpeedIR();

	ADCtl=1;

    Self_CheckingTime=0;
	Self_Checking=0;


	RunStep=0;

	
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
	     LedBlueON();
		
	
		//KK=ReadKey();
	         if(KK==0xC0){
				 KK= CheckHandsetIR();
				 CheckMode(KK);
				 CheckGround();
				 CheckRun();
		     }
			 else{
			    KK=ReadKey();
			 
			 }
		
		
	}

}
#if 0
void INT0_Rpt() interrupt INT0_VECTOR 
{
    if(PINTF0&0x01)						//判断INT15中断标志位
	{
	  PINTF0 &=0xfe;				//清除INT15中断标志位		
	}
	 if(After_Lowpowermode==1)						//判断INT15中断标志位
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

	if(PINTF1&0x20)						//判断INT13中断标志位
	{
		PINTF1 &=~ 0x20;				//清除INT13中断标志位	
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
	WDTC &=~ 0x20;						//清除WDT中断标志位
}
