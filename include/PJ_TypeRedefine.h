/*
Copyright 2010  BUT
---------- file information -----------------------------------------------
file name: PJ_TypeRedefine.h
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/
#ifndef  PJ_TypeRedefine_h
#define  PJ_TypeRedefine_h
#define  codec51


//for c51--------------------------------------------------------------
#ifdef  codec51
typedef    unsigned  char     INT8U;         // 无符号8位整型变量
//  0~255
typedef    signed    char     INT8S;         // 有符号8位整型变量
//  -128~+127
typedef    unsigned  int      INT16U;        // 无符号16位整型变量
//  0~65535
typedef    signed    int      INT16S;        // 有符号16位整型变量
//  -32768~+32767
typedef    unsigned  long     INT32U;        // 无符号32位整型变量
//  0~4294967295
typedef    signed    long     INT32S;        // 有符号32位整型变量
//  -2147483648~+2147483647
typedef    float              FP32;          // 单精度浮点数（32位长度）
//  +/-1.175494E-38~+/-3.402823E+38
#define    INT1U              bit

//for c51 spec memory type used

#define    indata             data
#define    inindata           idata
#define    outdata            xdata
#endif
//for c51--------------------------------------------------------------



//for HT --------------------------------------------------------------
#ifdef  codeHT
typedef              char     INT8S;         // 有符号8位整型变量
//  -128~+127
typedef    unsigned  char     INT8U;         // 无符号8位整型变量
//  0~255
/*
 typedef              int      INT8S;         // 有符号8位整型变量
                                              //  -128~+127
 typedef    unsigned           INT8U;         // 无符号8位整型变量
                                              //  0~255
 typedef    short     int      INT8S;         // 有符号8位整型变量
                                              //  -128~+127
 typedef    unsigned short int INT8U;         // 无符号8位整型变量
                                              //  0~255
*/
typedef              long     INT16S;        // 有符号16位整型变量
//  -32768~+32767
typedef    unsigned  long     INT16U;        // 无符号16位整型变量
//  0~65535
#define    INT1U              bit;

#endif
//for HT --------------------------------------------------------------


//for gcc
//for ads
//STM8










#endif //PJ_TypeRedefine_h
/*
---------- modify information ---------------------------------------------
version  : v0
modify   : 0000
begin    : 20080403
finish   : 20080403
define   :
---------------------------------------------------------------------------
*/