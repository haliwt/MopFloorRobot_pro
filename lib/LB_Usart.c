/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/

//全局变量声明
#define  KAKA_Usart_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\HC89F0541.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_Usart.h"

#endif
 void Init_Usart1()
  {
	P2M6 = 0xC2;				        //P26设置为推挽输出
	P2M7 = 0x62;				        //P27设置为上拉输出
	TXD_MAP = 0x26;						//TXD映射P26
	RXD_MAP = 0x27;						//RXD映射P27		
	T4CON = 0x06;						//T4工作模式：UART1波特率发生器
	//波特率计算
	//波特率 = 1/16 * (T4时钟源频率 / 定时器4预分频比) / (65536 - 0xFF98)
	//       = 1/16 * ((16000000 / 1) / 104)
	//		 = 9615.38(误差0.16%)

	//波特率9600
	//反推初值 = (65536 - ((T4时钟源频率 / 定时器4预分频比) * (1 / 16)) / 波特率)
	//		   = (65536 - (16000000 * (1 / 16) / 9600))
	//		   = (65536 - 104.167)
	//         = FF98
    
    TH4 = 0xFf;
	TL4 = 0x98;							//波特率9600
	SCON2 = 0x02;						//8位UART，波特率可变
	SCON = 0x00;						//允许串行接收
	IE |= 0x10;							//使能串口中断
	EA = 1;								//使能总中断
  }  
/***************************************************************************************
  * @说明  	UART1中断服务函数
  *	@参数	无
  * @返回值 无
  * @注		无
***************************************************************************************/
void UART1_Rpt(void) interrupt UART1_VECTOR
{
	if(SCON & 0x02)						//判断接收中断标志位
	{
		SCON &=~ 0x02;					//清除接收中断标志位
		if(Usart1Send[0]>SendCount)
		{
		  SendCount++;
		  SBUF= Usart1Send[SendCount];

		}
	}									
}