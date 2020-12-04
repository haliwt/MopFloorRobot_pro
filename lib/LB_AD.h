/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/
#ifndef  LB_AD_h
#define  LB_AD_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"
#include "..\include\HC89F0541.h"

#endif


//全局变量声明
#ifdef  KAKA_AD_GB
#define KAKA_AD_EXT
#else
#define  KAKA_AD_EXT extern
#endif
KAKA_AD_EXT INT8U ADCtl;
KAKA_AD_EXT INT8U ADTime;
KAKA_AD_EXT INT8U ADFlag;

KAKA_AD_EXT INT8U ADFlashFlag;

KAKA_AD_EXT INT16U EdgeCollectDelayTime;
KAKA_AD_EXT INT16U AD5ms[10];

KAKA_AD_EXT  INT8U  GroundAD[3][2];
KAKA_AD_EXT  INT8U outdata  GroundAD100Ms[3][8];
KAKA_AD_EXT INT16U outdata LCurrentAD[8];
KAKA_AD_EXT INT16U outdata RCurrentAD[8];


KAKA_AD_EXT INT8U  outdata  GroundDp[3];
KAKA_AD_EXT INT16U  LCurrent;
KAKA_AD_EXT INT16U  RCurrent;
KAKA_AD_EXT INT16U  LCurrentMax;
KAKA_AD_EXT INT16U  RCurrentMax;
KAKA_AD_EXT INT16U  FanCurrent;
KAKA_AD_EXT INT16U  EdgeCurrent;
KAKA_AD_EXT INT16U  EdgeCurrentCount;
KAKA_AD_EXT INT16U  Voltage;

KAKA_AD_EXT	void InitADIO(void);

KAKA_AD_EXT	void ReadAD5ms();
KAKA_AD_EXT	void ReadADAvg();
KAKA_AD_EXT	void CheckLCurrent();
KAKA_AD_EXT	void CheckRCurrent();
KAKA_AD_EXT	void CheckFanCurrent();
KAKA_AD_EXT	void CheckEdgeCurrent();
KAKA_AD_EXT	void CheckVoltage();
KAKA_AD_EXT	void CheckGround();

#endif