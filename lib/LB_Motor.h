/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/
#ifndef  LB_Motor_h
#define  LB_Motor_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"


#endif


//全局变量声明
#ifdef  KAKA_Motor_GB
#define KAKA_Motor_EXT
#else
#define  KAKA_Motor_EXT extern
#endif


typedef struct
{
	INT8U   RMode;	
	INT8U   AvgSpeed;
	INT8U   AvgSpeedLast;
	INT8U   MotorMode;                 //?í′??￡ê?,í￡?1,?°??,oóí?
	INT8U   NowSpeed[5];                  //?í′?μ±?°?ù?è
	INT8U   RunSpeed;                  //?í′???DD?ù?è	
	INT8U   EndSpeed;                  //?í′???DD?ù?è	
	INT8U   Slope;	
	INT8U   SlopeTime;		
	INT8U   OutPWMFlag;	
	INT32S  NowPulsed;	               //μ±?°??3?êy
	INT32S  LastPulsed;
	INT32S  MovePulsed;	               //é?′???3?êy

	INT8U   Flag;
	INT16S  RunCm;	
	INT16S  SetCm;		

	INT16U  OutPWM;                    //?í′??y?ˉPWM

} MoveMotorData;

KAKA_Motor_EXT MoveMotorData idata LeftMoveMotorData;
KAKA_Motor_EXT MoveMotorData idata RightMoveMotorData;
KAKA_Motor_EXT void Init_MotorSpeed();
KAKA_Motor_EXT void Init_MotorSpeedIR();

KAKA_Motor_EXT void MotorSpeedIRON();
KAKA_Motor_EXT void MotorSpeedIROff();
KAKA_Motor_EXT void InitMotorIO(void);
KAKA_Motor_EXT void InitMotorForward(void);
KAKA_Motor_EXT void InitFanEdgeIO(void);
KAKA_Motor_EXT void SetFan(INT8U status);
KAKA_Motor_EXT void SetEdge(INT8U status);

KAKA_Motor_EXT  void InitMotorLeftForward(void);
KAKA_Motor_EXT  void InitMotorRightForward(void);
KAKA_Motor_EXT  void InitMotorLeftRetreat(void);
KAKA_Motor_EXT  void InitMotorRightRetreat(void);
KAKA_Motor_EXT  void AllStop();
KAKA_Motor_EXT  void LeftStop();
KAKA_Motor_EXT  void RightStop();
KAKA_Motor_EXT  void ReadLeftPulsed(void);
KAKA_Motor_EXT  void ReadRightPulsed(void);
KAKA_Motor_EXT  void CheckLeftMotorSpeed(void);
KAKA_Motor_EXT  void CheckRightMotorSpeed(void);
KAKA_Motor_EXT  void SetXMotor(
    INT8U Leftmotor,
    INT8U LeftStartSpeed,
    INT8U LeftEndSpeed,
	INT8U LeftSlope,
    INT8U Rightmotor,
    INT8U RightStartSpeed,
    INT8U RightEndSpeed,
	INT8U RightSlope
);
KAKA_Motor_EXT  void AdjustSpeed();
KAKA_Motor_EXT  void SetMotorcm(INT8U mode,INT16U Setcm);
#endif