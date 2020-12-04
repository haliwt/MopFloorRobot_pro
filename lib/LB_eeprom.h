/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/
#ifndef  LB_eeprom_h
#define  LB_eeprom_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"


#endif


//全局变量声明
#ifdef  KAKA_eeprom_GB
#define KAKA_eeprom_EXT
#else
#define  KAKA_eeprom_EXT extern
#endif
KAKA_eeprom_EXT void Flash_EraseBlock(unsigned int fui_Address);
KAKA_eeprom_EXT void FLASH_WriteData(unsigned char fuc_SaveData, unsigned int fui_Address);
KAKA_eeprom_EXT void Flash_WriteArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr);
KAKA_eeprom_EXT void Flash_ReadArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr);
#endif