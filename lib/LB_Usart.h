/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/
#ifndef  LB_Usart_h
#define  LB_Usart_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"


#endif


//全局变量声明
#ifdef  KAKA_Usart_GB
#define KAKA_Usart_EXT
#else
#define  KAKA_Usart_EXT extern
#endif
KAKA_Usart_EXT INT8U SendCount;
KAKA_Usart_EXT INT8U idata Usart1Send[20];
KAKA_Usart_EXT  void Init_Usart1();

#endif