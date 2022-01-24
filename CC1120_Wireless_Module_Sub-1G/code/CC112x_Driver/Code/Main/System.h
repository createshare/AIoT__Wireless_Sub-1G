/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 System.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■"系统" 常用功能函数集-头文件
	01)     02)     03)    04)    05)    06)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 注意事项-Attention : 	
	▲01)     ▲02)     ▲03)    ▲04)    ▲05)    ▲06)   
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
* 修改记录-Change History:   
	作者   时间        版本  内容描述
	Author 	 Date		   Rev      Comment
	-------------------------------------------------------------------------------
	BlueS	2012-12-12	  1.0	   
			xxxx-xx-xx	  x.x	   
			xxxx-xx-xx	  x.x				
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#ifndef __System_H
#define __System_H

#include "msp430f6638.h"   // "处理器"头文件: 内部寄存相关定义等(处理器内部资源) 
#include "HAL_PMM.h"  //F5xx_F6xx_Core_Lib//系统电源管理模块-头文件 
#include "HAL_UCS.h"  //F5xx_F6xx_Core_Lib//系统时钟配置-头文件 

#include "Hardware_Profile.h"  //处理器"硬件配置文件" -Hardware specific definitions for Processor

#include "Key.h"   //"IO 按键" -驱动程序(外部资源)-头文件




union FLAGBIT16
{ 
	unsigned int FLAG16;
	unsigned char FLAG8[2];
	struct
	{   
		unsigned f0:1;		unsigned f1:1;
		unsigned f2:1;		unsigned f3:1;
		unsigned f4:1;		unsigned f5:1;
		unsigned f6:1;		unsigned f7:1;
		unsigned f8:1;		unsigned f9:1;
		unsigned f10:1;		unsigned f11:1;
		unsigned f12:1;		unsigned f13:1;
		unsigned f14:1;		unsigned f15:1;     
	}b;
}; 

#define YES   	(1)	
#define NO  	(0)	



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern union FLAGBIT16 SystemFlagBits;	//系统标志位定义
#define  G_SystemFlagBits    SystemFlagBits.FLAG16  
#define	 F_10ms_TaskClock    SystemFlagBits.b.f0  //系统10ms标志位//用于程序主循环周期10ms    
#define	 F_250ms_Working_Led SystemFlagBits.b.f1 //用于单片机正常工作时，工作指示灯一直闪烁(250ms闪烁一次) 
//#define  F_            SystemFlagBits.b.f2    //为1时，	  
//#define  F_	      SystemFlagBits.b.f3    //为1时，
//#define  F_		SystemFlagBits.b.f4   
//#define  F_		SystemFlagBits.b.f5  
//#define  F_		SystemFlagBits.b.f6   
//#define  F_		SystemFlagBits.b.f7  
//#define  F_	   	SystemFlagBits.b.f8  
//#define  F_	   	SystemFlagBits.b.f9  
//#define  F_	   	SystemFlagBits.b.f10	 
//#define  F_	   	SystemFlagBits.b.f11	 
//#define  F_	   	SystemFlagBits.b.f12	 
//#define  F_	   	SystemFlagBits.b.f13	 
//#define  F_	   	SystemFlagBits.b.f14 
//#define  F_	   	SystemFlagBits.b.f15	



extern unsigned char G_TempChar;    //测试临时用的"字节"变量


////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

extern void System_Initial(void);  //   系统初使化 :单片机内部资源+外部基本资源的初使化 

extern void Osccon_Initial(void);  //晶振初始化函数:配置相关晶振参数

extern void  Timer2_Initial(void); //定时器A2初始化设置(用于系统每1ms自动中断一次)

extern void System_10ms_Task(void);  //处理系统定时"10ms" 下的相关事务 

extern void System_250ms_Task(void);  //处理系统定时"250ms" 下的相关事务

extern void System_GetLoopClockTick(void);  //每次"死等"延时10ms后，系统"循环"执行一次程序

extern void System_Working_Led(void);  //单片机正常工作指示灯: 250ms闪烁一次




extern void WaitingDelayMs(unsigned int TimeData);  //死等待延时x毫秒

//将Cnt个相同的Data数据复制到数组Array[x]之后的Cnt个元素
extern void Sent_DataToArray(unsigned char *ArrayPoint,unsigned char DataValue,unsigned int Cnt);



#endif  /* __System_H */




