/*

---------- file information -----------------------------------------------
file name: 
define   : <????>
version  : ?????
---------------------------------------------------------------------------
*/
#ifndef  LB_Run_h
#define  LB_Run_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"
#include "..\include\HC89F0541.h"

#endif


//??????
#ifdef  KAKA_Run_GB
#define KAKA_Run_EXT
#else
#define  KAKA_Run_EXT extern
#endif
#define  GroundMin  0 //WT.EDIT  8
KAKA_Run_EXT outdata INT8U Mode;
KAKA_Run_EXT outdata INT8U Step;
KAKA_Run_EXT outdata INT8U RunMode;
KAKA_Run_EXT outdata INT8U RunStep;
KAKA_Run_EXT outdata INT8U PumpTime; //WT.EDIT
KAKA_Run_EXT outdata INT8U PowerSavingTime; //WT.EDIT,2020.11.30

KAKA_Run_EXT outdata INT16U RunSecond;
KAKA_Run_EXT outdata INT16U NoImpSecond;


KAKA_Run_EXT idata INT16U RunMs;

KAKA_Run_EXT  INT8U PowerCountErr;
KAKA_Run_EXT  INT8U PowerCountOK;

KAKA_Run_EXT  INT16U LmotorSpeedNum ; //WT.EDIT 2020.11.11
KAKA_Run_EXT  INT16U RmotorSpeedNum;   //WT.EDIT 2020.11.11

KAKA_Run_EXT  void  CheckRun();
KAKA_Run_EXT  INT8U  LowVoltageFlag;
KAKA_Run_EXT  void CheckMode(INT8U Key);
KAKA_Run_EXT  void InitSysclk(INT8U SYS);
#endif