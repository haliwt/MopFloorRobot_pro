/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/

//全局变量声明
#define  KAKA_IR_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\HC89F0541.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_IR.h"
#include "..\lib\LB_Usart.h"
#include "LB_Motor.h"
#include "LB_Run.h"

#endif

void Init_IR()
{

	P1M5 = 0x68;	//P1M6 = 0x68;			        	//P16设置为带SMT上拉输入

 	PITS3 |=0x04;//PITS3 |= 0x10;						//14 
    PINTE1 |= 0x20;//PINTE1 |= 0x40;						//使能INT14

	IE2 |= 0x01;						//打开INT8-17中断
	EA=1;
	Remote1_ReadIR.ReadIRFlag=0;


}
void Remote1_Count(void)
{
	if(Remote1_ReadIR.ReadIRFlag==1)
	{
		Remote1_ReadIR.Nowcount++;
		if(Remote1_ReadIR.Nowcount>200)
		{
			Remote1_ReadIR.ReadIRFlag=2;
		}
	}
}



 
void Read_Remote1IR(void)
{
    TCON |= 0x40;						//使能T1
	Remote1_ReadIR.NowVoltage=P1_5;

	if(
	    (Remote1_ReadIR.NowVoltage==0)&&(Remote1_ReadIR.ReadIRFlag==0)
	)
	{
		Remote1_ReadIR.ReadIRFlag=1;
		Remote1_ReadIR.Nowcount=0;
		Remote1_ReadIR.ReadIRBit=0;
	}
//	else if(
//	    (Remote1_ReadIR.NowVoltage==1)&&(Remote1_ReadIR.ReadIRFlag==1)
//	)
//	{
//		Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit]=Remote1_ReadIR.Nowcount;
//		Remote1_ReadIR.Nowcount=0;
//
//	  Usart1Send[0]=1;
//	  Usart1Send[1]=Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit];
//	  SendCount=1;
//	  SBUF=Usart1Send[SendCount];
//
//		Remote1_ReadIR.ReadIRBit++;
//		if(Remote1_ReadIR.ReadIRBit>80)
//			Remote1_ReadIR.ReadIRFlag=2;
//	}
	else if(
	    (Remote1_ReadIR.NowVoltage==0)&&(Remote1_ReadIR.ReadIRFlag==1)
	)
	{
		Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit]=Remote1_ReadIR.Nowcount;
		Remote1_ReadIR.Runcontrol=Remote1_ReadIR.Nowcount;
		Remote1_ReadIR.Nowcount=0;

//	  Usart1Send[0]=1;
//	  Usart1Send[1]=Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit];
//	  SendCount=1;
//	  SBUF=Usart1Send[SendCount];

		Remote1_ReadIR.ReadIRBit++;
		if(Remote1_ReadIR.ReadIRBit>80)
			Remote1_ReadIR.ReadIRFlag=2;
	}
}


void CheckXReadIR(ReadIRByte *P)
{
	INT8U k,ReadIR_cnt,FristCodeflag;
	FristCodeflag=0;
	ReadIR_cnt=0;
	P->AABit=0;

	if(P->ReadIRFlag==2)
	{		
		P->ReadIRByte=0;
		k=0;
		if(P->ReadIRData[P->AABit]>120)
		{
			for(P->AABit=1; P->AABit<P->ReadIRBit;P->AABit++)
			{				     
					 if((P->ReadIRData[P->AABit]>0)&&(P->ReadIRData[P->AABit]<=14))
					 {
					 	P->ReadIRByte<<=1;
					    k++;
						if(k>7)
					    {
						    P->ReadIR[ReadIR_cnt++]=P->ReadIRByte;
						    k=0;
						    P->ReadIRByte=0;
//							P->ReadIRFlag=3;

					    }
					 }
					 if((P->ReadIRData[P->AABit]>14)&&(P->ReadIRData[P->AABit]<28))
					 {
					 	P->ReadIRByte<<=1;
						P->ReadIRByte|=1;
					    k++;
						if(k>7)
					    {
						    P->ReadIR[ReadIR_cnt++]=P->ReadIRByte;
						    k=0;
						    P->ReadIRByte=0;
							P->ReadIRFlag=3;
					    }
					 }
					 if(ReadIR_cnt==4)
					 {
			    	    Usart1Send[0]=4;
	                    Usart1Send[1]=P->ReadIR[0];
						Usart1Send[2]=P->ReadIR[1];
						Usart1Send[3]=P->ReadIR[2];
						Usart1Send[4]=P->ReadIR[3];
	                    SendCount=1;
	                    SBUF=Usart1Send[SendCount];
						ReadIR_cnt=0;
						FristCodeflag=0;
						P->ReadIRFlag=3;


					 }
			}
			for(P->AABit=0; P->AABit<80; P->AABit++)
			{
			    P->ReadIRData[P->AABit]=0;
			}
		}
		else if((P->ReadIRData[P->AABit]>105)&&(P->ReadIRData[P->AABit]<115))
		{
			P->ReadIRFlag=3;
		}
		else
		{
			Remote1_ReadIR.ReadIRFlag=0;
			for(P->AABit=0; P->AABit<80; P->AABit++)
			{
			     P->ReadIRData[P->AABit]=0;
			}
		}		
	}
}



INT8U CheckHandsetIR()
{
	INT8U KK=0;
	INT8U N=0;
	INT8U M=0;

   CheckXReadIR(&Remote1_ReadIR);

   if(Remote1_ReadIR.ReadIRFlag==3)
   {
    
      Remote1_ReadIR.ReadIRFlag=0;
	   Usart1Send[0]=4;
	                    Usart1Send[1]=Remote1_ReadIR.ReadIR[0];
						Usart1Send[2]=Remote1_ReadIR.ReadIR[1];
						Usart1Send[3]=Remote1_ReadIR.ReadIR[2];
						Usart1Send[4]=Remote1_ReadIR.ReadIR[3];
	                    SendCount=1;
	                    SBUF=Usart1Send[SendCount];

	  }
   

  
  return(KK);
}


