/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/

//全局变量声明
#define  KAKA_AD_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\PJ_TypeRedefine.h"
#include "..\lib\LB_Led.h"
#include "LB_AD.h"

#endif
/**
  * @说明  	延时函数
  * @参数  	fui_i : 延时时间
  * @返回值 无
  * @注 	Fcpu = 16MHz,fui_i = 1时,延时时间约为2us
  */
void Delay_2us(unsigned int fui_i)
{
	while(fui_i--);	
}
void InitADIO(void)
{
	P0M2 = 0x02;				        //P02设置为模拟输入
	P0M3 = 0x02;				        //P03设置为模拟输入
	P0M4 = 0x02;				        //P04设置为模拟输入
	P0M5 = 0x02;				        //P05设置为模拟输入
	P0M6 = 0x02;				        //P06设置为模拟输入
	P0M7 = 0x02;				        //P07设置为模拟输入
	P2M4 = 0x02;				        //P24设置为模拟输入
	P2M5 = 0x02;				        //P25设置为模拟输入

	P0M1 = 0X80;

	LCurrentAD[0]=0;
	LCurrentAD[2]=0;
	LCurrentAD[4]=0;
	LCurrentAD[6]=0;
	RCurrentAD[0]=0;
	RCurrentAD[2]=0;
	RCurrentAD[4]=0;
	RCurrentAD[6]=0;
}

void SeleADChanel(INT8U ADChanel)
{
	ADCC0 = 0x80;						//打开ADC转换电源
	ADCC1 = (ADChanel&0X0F);			//选择外部通道0
	ADCC2 = 0x4f;						//转换结果12位数据，数据右对齐，ADC时钟16分频

}

void StartAD()
{
	ADCC0&=0XDF;
	ADCC0 |= 0x40;					//启动ADC转换
}
void SetADINT(void)
{
    EADC = 1;                                   //使能ADC中断
    EA = 1;
}


void  SetAD(INT8U ADChanel)
{
  code INT8U ADCC[8]={2,3,4,5,6,7,12,13};
  SeleADChanel(ADCC[ADChanel]);
  SetADINT();
  StartAD();
}
void ReadAD5ms()
{
  static INT8U i=0;
  static INT8U chanel=0;
  static INT16U ADtemp[4];  
  ADtemp[i]=ADCR;
  i++;
  if(i>3)
  {
     i=0;
	 AD5ms[chanel]= (ADtemp[3]+ADtemp[2])/2;
	 chanel++;
	 if(chanel>7)
	 {
	   if(ADCtl)
	   {
	   if(ADFlag)
	   {
		 P0_1 = 1;
		 ADFlag=0;
		 ADFlashFlag=1;
	   }
	  else
	  {
		 P0_1 = 0;
		 ADFlag=1;
		 ADFlashFlag=1;
	  }
	  }
	  else
	  {
	  	 P0_1 = 0;
	  }
	 chanel=0;
	 }
  }
  else
  {
  	 SetAD(chanel);
  }
}
INT8U ReadGroundDp(INT8U *p)
{
  INT8U i;
  INT16U temp,tempMin,tempMax;
  temp=0;


  tempMin=*p;
  tempMax=*p;
  for(i=1;i<10;i++)
  {
    
	if(tempMin>*(p+i))
	{
	   tempMin=*(p+i);
	}
	else if(tempMax<*(p+i))
	{
	   tempMax=*(p+i);
	}
	else
	 temp+=*(p+i);
  }
  
  return(temp/8);
}

void CheckGround()
{
 if(ADFlashFlag)
 {
   if(ADFlag)
   {
   	   GroundAD[0][0]=(AD5ms[3]>>4);
	   GroundAD[1][0]=(AD5ms[2]>>4);
	   GroundAD[2][0]=(AD5ms[1]>>4);
	   ADFlashFlag=0;
	 //SBUF=GroundAD[0][0];
    if(GroundAD[0][1]>GroundAD[0][0])
	{
       GroundAD100Ms[0][ADTime]=GroundAD[0][1]-GroundAD[0][0];
	}
	else
       GroundAD100Ms[0][ADTime]=GroundAD[0][0]-GroundAD[0][1];

    if(GroundAD[1][1]>GroundAD[1][0])
	{
       GroundAD100Ms[1][ADTime]=GroundAD[1][1]-GroundAD[1][0];
	}
	else
	  GroundAD100Ms[1][ADTime]=GroundAD[1][0]-GroundAD[1][1];

    if(GroundAD[2][1]>GroundAD[2][0])
	{

       GroundAD100Ms[2][ADTime]=GroundAD[2][1]-GroundAD[2][0];
	}
	else
	  GroundAD100Ms[2][ADTime]=GroundAD[2][0]-GroundAD[2][1];

	 ADTime++;
   if(ADTime>7)
   {
   	  ADTime=0;
	  GroundDp[0]=(GroundAD100Ms[0][0]+GroundAD100Ms[0][2]+GroundAD100Ms[0][4]+GroundAD100Ms[0][6])/4;
	  GroundDp[1]=(GroundAD100Ms[1][0]+GroundAD100Ms[1][2]+GroundAD100Ms[1][4]+GroundAD100Ms[1][6])/4;
	  GroundDp[2]=(GroundAD100Ms[2][0]+GroundAD100Ms[2][2]+GroundAD100Ms[2][4]+GroundAD100Ms[2][6])/4;

   }
   //SBUF=AD5ms[5]/16;
   	LCurrentAD[ADTime]=AD5ms[4];
	RCurrentAD[ADTime]=AD5ms[5];
	 
   }
   else
   {
   	   GroundAD[0][1]=(AD5ms[3]>>4);
	   GroundAD[1][1]=(AD5ms[2]>>4);
	   GroundAD[2][1]=(AD5ms[1]>>4);
	   ADFlashFlag=0;
   }

 }
}

void CheckFanCurrent()
{
  if(EdgeCollectDelayTime>5)
  {
    FanCurrent=(FanCurrent*9+((AD5ms[6]*11)/2))/10;
    // 5000/4096/0.22
  	EdgeCollectDelayTime=6;
  }
}

void CheckEdgeCurrent()
{
  
  if(EdgeCollectDelayTime>5)
  {
     
  	 static INT8U i=0;  
     i++;
     if(i>7)
     i=0;
     //EdgeCurrent+=(INT8U)AD5ms[7];
     // 5000/4096/0.47
     //EdgeCurrent-=	EdgeCurrent/10;
     EdgeCurrent=(EdgeCurrent*9+((AD5ms[7]*2)/5))/10;
     if(EdgeCurrent>0x0F)
     EdgeCurrentCount++;
     else 
     {
       if(EdgeCurrentCount>1)
       EdgeCurrentCount--;
     }
	 EdgeCollectDelayTime=6;
  }    
}


void CheckLCurrent()
{
 INT16U	LCurrentADAvg;
 LCurrentADAvg=(LCurrentAD[0]+LCurrentAD[2]+LCurrentAD[4]+LCurrentAD[6])/4;
 //SBUF= (INT8U)LCurrentADAvg;
 //LCurrent=(LCurrent*9+(LCurrentADAvg*11)/2)/10;
 LCurrent=(LCurrent+(LCurrentADAvg*11)/2)/2;
 //SBUF= LCurrent;
}
void CheckRCurrent()
{
 INT16U	RCurrentADAvg;
 RCurrentADAvg=(RCurrentAD[0]+RCurrentAD[2]+RCurrentAD[4]+RCurrentAD[6])/4;

 //RCurrent=(RCurrent*9+(RCurrentADAvg*11)/2)/10;
 RCurrent=(RCurrent+(RCurrentADAvg*11)/2)/2;
 
}

void CheckVoltage()
{
   Voltage=(Voltage*9+((AD5ms[0])/25)*6)/10;
//   Voltage=840;
}

/***************************************************************************************
  * @说明  	ADC中断服务函数
  *	@参数	无
  * @返回值 无
  * @注		无
***************************************************************************************/
void ADC_Rpt() interrupt ADC_VECTOR
{

    IE1 &=~ 0x40;                       //关闭ADC中断
    ADCC0 &=~ 0x20;						//清除ADC中断标志位

} 