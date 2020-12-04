/*

---------- file information -----------------------------------------------
file name: 
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/

//ȫ�ֱ�������
#define  KAKA_Run_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_Motor.h"
#include "LB_Run.h"
#include "LB_AD.h"
#include "LB_Led.h"
#include "LB_IR.h"
#endif
 
void  CheckRun()
{
    
	switch(RunMode)
	{

	case 2:
	{
	  switch(RunStep)
	  {
		  	case 0:
			{

			}
			break;

		case 1:
		{

			//SetXMotor(1,20,40,1,1,20,40,1);
			
			//SetXMotor(1,20,40,1,1,20,40,1);//1--??????SetXMotor(1,20,25,1,1,20,40,1);
			SetXMotor(1,20,160,1,1,20,160,1);//2--??????
			SetMotorcm(1,5000);
			RunStep=2;
			RunMs=0;
		}
		break;
		case 2:
        {
			
         if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin)||(GroundDp[2]>GroundMin))
			{
				 AllStop();
				 //SetXMotor(1,20,1,1,1,20,1,1);
				  RunStep=3;
				RunMs=0;			
			}
			if((RightMoveMotorData.Flag==1)||(LeftMoveMotorData.Flag==1))
			{
				//SetXMotor(1,20,40,1,1,20,40,1);  //???
				//SetXMotor(1,20,40,1,1,20,40,1);//1--??????SetXMotor(1,20,35,1,1,20,40,1);
				SetXMotor(1,20,160,1,1,20,160,1);//2--??????
				SetMotorcm(1,5000);			
			}
			
			if(RunMs>2000)//if(RunMs>3000)
			{
				 AllStop();
				 //SetXMotor(1,20,1,1,1,20,1,1);
				RunStep=3;
				RunMs=0;	
			}
			
		}
			break;
		case 3:
		{
		   if(RunMs>20)
		   {
			SetXMotor(2,20,160,1,2,20,160,1); //??
			SetMotorcm(2,1000);
			RunStep=4;		   
		   }
		    
		}
		break;
		case 4:
		{
			if(RunMs>120)
			{
				AllStop();
				//SetXMotor(2,20,1,1,2,20,1,1);
				RunMs=0;
				RunStep=5;
			}
			
		}
			break;
	    case 5:
		  {
			if(RunMs>20)
			{
				SetXMotor(2,20,160,1,1,20,160,1); //???
			    SetMotorcm(3,9000);
				RunMs=0;
				RunStep=6;
			}	
			
		  }
		break;
		case 6:
			if(RunMs > 100)//if(RunMs>100)
			{
				AllStop();
				//SetXMotor(2,20,1,1,1,20,1,1);
				RunMs=0;
				RunStep=7;
			}
			
			break;
		case 7:
			
			if(RunMs>20) //20 * 10ms =200ms
			{

				if(PumpTime >19 ){ //WT.EDIT

					
				   RunMs=0;
				   RunStep=8;//??? //RunStep=12;
				   WaterPump(); 
					SetXMotor(1,20,160,1,2,20,160,1);
				    SetMotorcm(4,9000); //???
					SetXMotor(2,20,160,2,1,20,160,2);//2--??????
					SetMotorcm(4,1000); //???
		    	}
				else{
					RunMs=0;
					RunStep=2;//??? //RunStep=12;
				  // SetXMotor(1,20,40,1,1,20,40,1);//SetXMotor(1,20,25,1,1,20,40,1); //???
                  // SetXMotor(1,20,35,1,1,20,40,1);//1--??????
                   SetXMotor(1,20,160,1,1,20,160,1);//2--??????
				   SetMotorcm(1,5000);				
				}

				
			}
		
	
			break;
		 case 8: // water pump

			        if(RunMs > 9){
						WaterPumpStop();
				        RunMs=0;
					    RunStep=9;//??? //RunStep=12;
			        }
		 break;
		 case 9:
		 {
		   if(RunMs > 240)
		   {
			    PumpTime=0;
			    RunMs=0;
			    RunStep=2; 
				//SetXMotor(1,20,40,1,1,20,60,1);//SetXMotor(1,20,25,1,1,20,40,1);//SetXMotor(1,20,25,1,1,20,40,1); //???
				// SetXMotor(1,20,35,1,1,20,40,1);//1--??????
				SetXMotor(1,20,160,1,1,20,160,1);//2--??????
				SetMotorcm(1,5000);		   
		   }
		 }
		 break;
		}
	}
  }
	
}
/***************************************************************
	*
	*Function Name:void CheckMode(INT8U Key)
	*Function :
	*Input Ref: Key
	*Return Ref: No
	*
***************************************************************/
void CheckMode(INT8U Key)
{

 if(Key ==2){

       
	Mode = 40;
	Delay_ms(100);
	LedBlueOff();
	LedRedON();
	Delay_ms(100);
	LedBlueON();
	LedRedON();
	Delay_ms(100);
	LedBlueOff();
	LedRedON();
	Delay_ms(100);
	LedBlueON();
	LedRedON();
  }
 else if(Key==1)
  {
    
    if(Mode==0) 
	{
	  //唤醒
	  Mode=1;
	  Step=1;
	 
	}
	else 
	 {
	  if(Step==0)
	  {
	    //20
	  	Step=1;
	    ADCtl=1;
        RunSecond=0;
	  }
	  else	if(Step<20)
	  {
	  //LedBlueON();
	  Mode=1;
	  Step=0;
	  RunSecond=0;
	  AllStop();

			  SetEdge(0);
			  RunStep=0;
			  //SetBuzzerTime(2);
		  }
	}
  }
 
  switch(Mode)
  {
  	case 0:
	{
	  switch(Step)
	  {
	     //上电检测电压,是否需要充电
	     case 0:
		 {

			AllStop();

		 }
		 break;
		 //工作完成,提示音响1次2秒加灯光闪动4次
		 case 1:
		 {
		    //if(RunSecond==20)
			{
			  RunSecond=0;
		 
			  //Step=2;
			}
		 }

		 case 10:
		 {
		   if(RunSecond>0)
		   {
		   	   Step=0;
			   RunSecond=0;
			   
		   }
		 }
		 break;
	  
	  }
	}
	break;
	
	case 1:  //开机工作 Mode =1
	{
	   switch(Step) //step =1
	   {
	     //开机提示音1秒响2次
	   	 case 0:
		 {
		   //ADCtl=1;
		 //5秒没有按键输入,进入休眠
		   if(RunSecond>15) //16 * 1s = 16s
		   {
		     //Step=0;
			 //Mode=0;
			 RunSecond=0;
			 LedBlueOff();
             ADCtl=0;
		   }
		 // ADCtl=1;

	   if(ReadPowerDCIn())
		  {
			 Step=5;

		  }
		 } 
		 break;
		 case 1:
		 {
		   if(RunSecond>0)
		   {
		   	  Step=2; //Next run 2
			   LedBlueON();
			  ADCtl=1;

			  
			  RunMode=2;
			  RunStep=1;
			  ADCtl=1;

				RunMs=0;
			  NoImpSecond=0;

		   }
		 }
		 break;
		 
		 case 2:
		 {

		  
		  if(Voltage<960)
			{

			     ADCtl=0;
			     RunStep=0;
			  	 AllStop();

				 SetEdge(0);

				 Step=8;
			 
				} 
			else  if(ReadPowerDCIn())
			  {
			     ADCtl=0;
			     RunStep=0;
			  	 AllStop();

				 SetEdge(0);

				 Step=5;


			  }
			  if(NoImpSecond==40)
			  {
			    SetEdge(50);
				NoImpSecond=41;
			  }
			 if(NoImpSecond==45)
			 {
			    SetEdge(0);
				NoImpSecond=0;		 
			 }
			  
			 }
		 break;
		 //电量不足时，灯光闪频率2Hz

		 case 3:
		 {

		   if(RunSecond>0)
		   {
			 LedBlueON();
			 	   	 
			 Step=4;
			 RunSecond=0;
		   }

		   
          if(ReadPowerDCIn())
		  {
		     ADCtl=0;
		     RunStep=0;
		  	 AllStop();
			 SetEdge(0);

			 Step=5;


		  }
		  
		 }
		 break;
		 
		 case 4:
		 {

		   if(RunSecond>0)
		   {
			  LedBlueOff();
  	 
			 Step=3;
			 RunSecond=0;
		   }
		   
          if(ReadPowerDCIn()) //电池检测GPIO ==1 ,电池电量不够
		  {
		     ADCtl=0;
		     RunStep=5;
		  	 AllStop();
			 SetEdge(0);


		  }	

		 }
		 break;
		// 充电中灯光频率 0.5Hz
		 case 5:
		 {
		   if(RunSecond>1) //2 * 1s =2s
		   {
			 LedBlueON();  
			 Step=6;
			 RunSecond=0;
		   }

		 }
		 break;
		 
		 case 6:
		 {
		   if(PowerCountErr>29)
		   {
		   	  //LedBlueON();
			  Step=10; 
		   }

		   if(RunSecond>1)
		   {
		   	 LedBlueOff();
			 Step=5;
			 RunSecond=0;
		   }
		   else if(PowerCountOK>20)
		   {
		   	  Step=7;
		   }		   
		   else if(0==ReadPowerDCIn())
		   {
		   	 Step=0;
			 Mode=1;
			 //SetBuzzerTime(1);
		   }
		 }
		 break;
		 //满电不闪
		 case 7:
		 if(0==ReadPowerDCIn())
		   {
		   	 Step=0;
			 Mode=0;
		   }
		
		   else if(Voltage<970)
		   {
		   	  Step=5;
			  
			  //SetBuzzerTime(3);
		   }
		 break;

		 case 8:
		 {
		   if(RunSecond>0)
		   {
			  LedBlueON();
		   	 
			 Step=9;
			 RunSecond=0;
		   }
        if(ReadPowerDCIn())
		  {
		     RunStep=5;

		  }
		 }
		 break;
		 
		 case 9:
		 {
		   if(RunSecond>0)
		   {

             LedBlueOff();	   	 
			 Step=8;
			 RunSecond=0;
		   }
        if(ReadPowerDCIn())
		  {
		     RunStep=5;

		  }
		 }
		 break;

		 case 10:
		 {
		   if(NoImpSecond>0)//100ms
		   {
			  LedBlueON();
		   	 
			 Step=11;
			 NoImpSecond=0;
		   }

		 }
		 break;
		 
		 case 11:
		 {
		   if(NoImpSecond>0)
		   {

             LedBlueOff();	   	 
			 Step=10;
			 NoImpSecond=0;
		   }

		 }
		 break;
		 case 20:
		 {
		 	if((GroundDp[0]>GroundMin)&&(GroundDp[1]>GroundMin)&&(GroundDp[2]>GroundMin))
			  LedBlueON();
			else
			  LedBlueOff();
		 }
		 break;

	   }
	}
	break;

	case 40 :
         
		  if(RunMs >10){
			ADFlag=1;
			RunMs =0;
			AllStop();
			RunStep=0;
			LedBlueON();
			LedRedON();
			CheckGround();
			SelfChecking();
		  }
		
		


	break;

  }
}

