/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/

//全局变量声明
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
