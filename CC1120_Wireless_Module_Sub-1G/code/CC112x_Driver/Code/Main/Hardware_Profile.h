/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 Hardware_Profile.h
* 附属文件-Dependencies:  	 msp430f6638.h	
* 文件描述-File Description:	 ( 头文件-Header File )
	■ 处理器"硬件配置文件" -头文件-Hardware specific definitions for Processor
	01) 处理器IO口使用宏定义，统一在Hardware_Profile.h 定义     
	02)      03)    04)    05)    06)	
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
* 公司-Company: 			CS-EMLAB  Co. , Ltd.
* 软件许可协议-Software License Agreement:
	Copyright (C) 2012-2020 	CS-EMLAB  Co. , Ltd.	All rights reserved.	

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/


#ifndef __Hardware_Profile_H
#define __Hardware_Profile_H


#include "msp430f6638.h"   // "处理器"头文件: 内部寄存相关定义等



////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//==**单片机内部定义**================================//

#define mClose_WDT      (WDTCTL = WDTPW + WDTHOLD)  // 关闭看门狗
#define mClr_WDTCNT     (WDTCTL = WDTPW + WDTCNTCL) // 清看门狗(对于MSP430单片机)
#define	mNop	        (__no_operation())    //空操作指令(用于"短延时"或"调试")

//#define	mEnable_GIE     (__bis_SR_register(GIE))  // 开启总中断
#define	mEnable_GIE     (_EINT())  // 开启总中断GIE
#define	mDisable_GIE    (_DINT())  // 关闭总中断GIE

#define	mReset_Soft    (PMMCTL0 |= PMMSWPOR) //"软件复位" (MSP430单片机)



#define	Fosc_System	    (12)		//系统运行频率 unit:MHz (倍频后，即最终的)
////////////////////////////////////////////////////////////////////////////
//==** 系统频率MCLK =12M  (DCO  FLL倍频到12MHz)   **==============//
	//ms级的死等延时，调用WaitingDelayMs(n); //死等待延时n个ms(包含清看门狗操作)
	//us级的死等延时，调用mDelay_Cycles(n);	//死等待延时n个时钟周期
#define mDelay_Cycles(n) (__delay_cycles(n)) // 死等待延时"n"个时钟周期.
	//例: __delay_cycles(12000000); //(1/12M)*12000000=1s

#define M_Delay_1us   (12)   //死等延时"1us" //系统频率为12 M时
#define M_Delay_2us   (24)   //死等延时"2us" //系统频率为12 M时
#define M_Delay_5us   (60)  //死等延时"5us" //系统频率为12 M时

#define M_Delay_10us  (120)      //死等延时"10us"//系统频率为12 M时
#define M_Delay_100us (1200)     //死等延时"100us"//系统频率为12 M时
#define M_Delay_1ms   (12000)    //死等延时"1ms"//系统频率为12 M时(示波器实测1.02ms)
#define M_Delay_1s    (12000000) //死等延时"1s"//系统频率为12 M时(示波器实测1.02s)


#define CPU_F ((double)12000000)
#define _delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define _delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))


////////////////////////////////////////////////////////////////////////////
//==** 系统频率MCLK =20M  (DCO  FLL倍频到20MHz)   **==============//

/********************************************
	//ms级的死等延时，调用WaitingDelayMs(n); //死等待延时n个ms(包含清看门狗操作)
	//us级的死等延时，调用mDelay_Cycles(n);	//死等待延时n个时钟周期
#define mDelay_Cycles(n) (__delay_cycles(n)) // 死等待延时"n"个时钟周期.
	//例: __delay_cycles(20000000); //约980ms ≈ (1/20M)*20000000=1s(系统频率>20M(通过倍频))

#define M_Delay_1us   (20)   //死等延时"1us" //系统频率为20 M时
#define M_Delay_2us   (40)   //死等延时"2us" //系统频率为20 M时
#define M_Delay_5us   (100)  //死等延时"5us" //系统频率为20 M时

#define M_Delay_10us  (200)   //死等延时"10us"
#define M_Delay_100us  (2000)   //死等延时"100us"

//#define M_Delay_1s    (20000000)  //死等延时"1s"	      //care 系统频率(大于)约为20M
//#define M_Delay_500ms (10000000) //死等延时"500ms"	//care 系统频率(大于)约为20M
//#define M_Delay_5ms   (100000)  //死等延时"5ms"	    //care 系统频率(大于)约为20M
//#define M_Delay_1ms   (20000)  //死等延时"1ms"	    //care 系统频率(大于)约为20M
//#define M_Delay_250us (5000)  //死等延时"250us"	    //care 系统频率(大于)约为20M
//#define M_Delay_50us (1000)  //死等延时"50us"	    //care 系统频率(大于)约为20M

#define CPU_F ((double)20000000)
#define _delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define _delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
********************************************/




////////////////////////////////////////////////////////////////////////////
//==**单片机IO口使用宏定义,统一在HardwareProfile.h定义**===//
//==**适用于**MSP430F5xx_6xx 的单片机**====================//
/*****************************

//==**配置"功能选择寄存器"：IO为外围模块功能引脚或IO引脚**IO bits Function Pin/IO Pin**====//
#define mSelect_Xxx_FunctionPin  (P1SEL |= BIT) //配置引脚为"外围模块功能"引脚
#define mSelect_Xxx_IoPin (P1SEL &= (~BIT))     //配置引脚为"IO"引脚

//==**配置"方向寄存器"：IO为输入或输出**IO bits Input/Output**===================//
#define mSetOut_Xxx   (P1DIR |= BIT)         //配置引脚为"输出"
#define mSetIn_Xxx     (P1DIR &= (~BIT))    //配置引脚为"输入"

//==**配置"输出寄存器"：输出高电平或低电平**IO bits Set/Clr**===============//
#define mHigh_Xxx   (P1OUT |= BIT)           //引脚输出"高电平(1)"
#define mLow_Xxx    (P1OUT &= (~BIT))      //引脚输出"低电平(0)"

#define mTurn_Xxx    (P1OUT ^= BIT)        //"翻转"引脚输出状态

#define mOpen_Xxx   (P1OUT |= BIT)         //引脚输出对应"打开"功能
#define mClose_Xxx   (P1OUT &= (~BIT))    //引脚输出对应"关闭"功能

//==**配置 "上拉或下拉电阻使能寄存器"：使能或禁止此功能**IO bits PULL Enabled/Disabled**===//
#define mPullEnabled_Xxx(n)   (P1REN |= BIT)        //使能--上拉/下拉功能
#define mPullDisabled_Xxx(n)  (P1REN &= (~BIT))   //禁止--上拉/下拉功能

//==**配置 "输出寄存器(复用)"：选择引脚上拉或下拉**IO bits PullUp/PullDown**======//
#define mPullUp_Xxx(n)        (P1OUT |= BIT)      //配置引脚"上拉"功能
#define mPullDown_Xxx(n)    (P1OUT &= (BIT) )   //配置引脚"下拉"功能


//==**读取"输入寄存器"：返回引脚的电平值**IO bits Input**================//
#define mRead_Xxx(n)   (P1IN&n?1:0 )      //读取引脚电平值


//#define _MIN(a,b)			( (a) < (b) ? (a) : (b) )
//#define _MAX(a,b)			( (a) > (b) ? (a) : (b) )
*****************************/


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//==**内部"资源IO口使用宏定义**=======================//

////////////////////////////////////////////////////////////////////////////
//==**SPI_B *IO口使用宏定义**=============================//

//--**P8.4 引脚: SPI_B_CLK (P8.4/UCB1CLK/UCA1STE/S11)** -------------------//
#define SPI_B_CLK_SEL  (P8SEL)
#define SPI_B_CLK_DIR  (P8DIR)  
#define SPI_B_CLK_PORT (P8OUT)

#define SPI_B_CLK_IO   (BIT4)	

	//配置引脚为"外围模块功能"引脚
#define mSelect_SPI_B_CLK_FunctionPin  (SPI_B_CLK_SEL |= SPI_B_CLK_IO) 

	//配置"SPI_B_CLK" 引脚为"输出"
#define mSetOut_SPI_B_CLK (SPI_B_CLK_DIR |= SPI_B_CLK_IO)  

	//配置引脚为"输出",并输出"高电平"
#define mHigh_SPI_B_CLK  {SPI_B_CLK_DIR |= SPI_B_CLK_IO; SPI_B_CLK_PORT |= SPI_B_CLK_IO;}      //引脚输出"高电平(1)"
	//配置引脚为"输出",并输出"低电平"
#define mLow_SPI_B_CLK   {SPI_B_CLK_DIR |= SPI_B_CLK_IO; SPI_B_CLK_PORT &= ~SPI_B_CLK_IO;}    //引脚输出"低电平(0)"




//--**P8.5 引脚: SPI_B_MOSI (P8.5/UCB1SIMO/UCB1SDA/S10)** ----------------//
#define SPI_B_MOSI_SEL  (P8SEL)
#define SPI_B_MOSI_DIR  (P8DIR)  
#define SPI_B_MOSI_IO   (BIT5)

	//配置引脚为"外围模块功能"引脚
#define mSelect_SPI_B_MOSI_FunctionPin  (SPI_B_MOSI_SEL |= SPI_B_MOSI_IO) 

	 //配置"SPI_B_MOSI" 引脚为"输出"
#define mSetOut_SPI_B_MOSI (SPI_B_MOSI_DIR |= SPI_B_MOSI_IO)  


//--**P8.6引脚: SPI_B_MISO (P8.6/UCB1SOMI/UCB1SCL/S9)** ----------------//
#define SPI_B_MISO_SEL  (P8SEL)
#define SPI_B_MISO_DIR  (P8DIR)  
#define SPI_B_MISO_IO   (BIT6)

	//配置引脚为"外围模块功能"引脚
#define mSelect_SPI_B_MISO_FunctionPin  (SPI_B_MISO_SEL |= SPI_B_MISO_IO) 

	 //配置"SPI_B_MISO" 引脚为"输入"
#define mSetIn_SPI_B_MISO (SPI_B_MISO_DIR &= (~SPI_B_MISO_IO))  

//--**P3.6 引脚: 从机SPI 使能引脚SPI_CS ("低"有效)** -------------------//
#define Slave_SPI_CS_DIR  (P3DIR)  
#define Slave_SPI_CS_PORT (P3OUT)
#define Slave_SPI_CS_IO   (BIT6)

		//配置引脚为"输出",并"输出高电平"
//#define mHigh_Slave_SPI_CS {Slave_SPI_CS_DIR |= Slave_SPI_CS_IO; Slave_SPI_CS_PORT |= Slave_SPI_CS_IO;}   
			//配置引脚为"输出",并"输出低电平"
//#define mLow_Slave_SPI_CS {Slave_SPI_CS_DIR |= Slave_SPI_CS_IO; Slave_SPI_CS_PORT &= ~Slave_SPI_CS_IO;}   

	//配置引脚为"输出",并"使能"从机SPI_CS("低"电平有效)
#define mOpen_Slave_SPI_CS {Slave_SPI_CS_DIR |= Slave_SPI_CS_IO; Slave_SPI_CS_PORT &= ~Slave_SPI_CS_IO;}   

	//配置引脚为"输出",并"关闭"从机SPI_CS("高"电平有效)
#define mClose_Slave_SPI_CS {Slave_SPI_CS_DIR |= Slave_SPI_CS_IO; Slave_SPI_CS_PORT |= Slave_SPI_CS_IO;}   




 
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//==**外部"资源IO口使用宏定义**=======================//

////////////////////////////////////////////////////////////////////////////
//==**多路复用器TS3A5017 *IO口使用宏定义**================//

//--**P3.4 引脚: 连接到多路复用器:引脚IN1** -------------------//
#define TS3A5017_01_IN1_DIR  (P3DIR)  
#define TS3A5017_01_IN1_PORT (P3OUT)
#define TS3A5017_01_IN1_IO   (BIT4)

#define mSetOut_TS3A5017_01_IN1 (TS3A5017_01_IN1_DIR |= TS3A5017_01_IN1_IO)   //设置IN1引脚都为"输出"
#define mHigh_TS3A5017_01_IN1   (TS3A5017_01_IN1_PORT |= TS3A5017_01_IN1_IO)    //引脚输出"高电平(1)"
#define mLow_TS3A5017_01_IN1    (TS3A5017_01_IN1_PORT &= (~TS3A5017_01_IN1_IO)) //引脚输出"低电平(0)"

#define mConfig_TS3A5017_01_IN1(IN1) {mSetOut_TS3A5017_01_IN1; IN1 ? mHigh_TS3A5017_01_IN1 : mLow_TS3A5017_01_IN1;} 

//--**P3.5 引脚: 连接到多路复用器:引脚IN2** -------------------//
#define TS3A5017_01_IN2_DIR  (P3DIR)  
#define TS3A5017_01_IN2_PORT (P3OUT)
#define TS3A5017_01_IN2_IO   (BIT5)	

#define mSetOut_TS3A5017_01_IN2 (TS3A5017_01_IN2_DIR |= TS3A5017_01_IN2_IO)   //设置IN2引脚都为"输出"
#define mHigh_TS3A5017_01_IN2   (TS3A5017_01_IN2_PORT |= TS3A5017_01_IN2_IO)    //引脚输出"高电平(1)"
#define mLow_TS3A5017_01_IN2    (TS3A5017_01_IN2_PORT &= (~TS3A5017_01_IN2_IO)) //引脚输出"低电平(0)"

#define mConfig_TS3A5017_01_IN2(IN2) {mSetOut_TS3A5017_01_IN2; IN2 ? mHigh_TS3A5017_01_IN2 : mLow_TS3A5017_01_IN2;} 


////////////////////////////////////////////////////////////////////////////
//==**LCD_TFT 液晶显示器*IO口使用宏定义**===============//

//--**P3.6 引脚: LCD_TFT使能引脚CS ("低"有效)** -------------------//
#define LCD_TFT_CS_DIR  (P3DIR)  
#define LCD_TFT_CS_PORT (P3OUT)
#define LCD_TFT_CS_IO   (BIT6)

		//配置引脚为"输出",并"输出高电平"
#define mHigh_LCD_TFT_CS {LCD_TFT_CS_DIR |= LCD_TFT_CS_IO; LCD_TFT_CS_PORT |= LCD_TFT_CS_IO;}   
			//配置引脚为"输出",并"输出低电平"
#define mLow_LCD_TFT_CS {LCD_TFT_CS_DIR |= LCD_TFT_CS_IO; LCD_TFT_CS_PORT &= ~LCD_TFT_CS_IO;}   

	//配置引脚为"输出" ,并"触发"CS引脚信号(产生下降沿)
#define mTrigger_LCD_TFT_CS {LCD_TFT_CS_DIR |= LCD_TFT_CS_IO; LCD_TFT_CS_PORT |= LCD_TFT_CS_IO; LCD_TFT_CS_PORT &= ~LCD_TFT_CS_IO;} 

	//配置"LCD_TFT_CS" 引脚为"输入"
//#define mSetIn_LCD_TFT_CS (LCD_TFT_CS_DIR &= (~LCD_TFT_CS_IO))  



//--**PJ.0 引脚: 控制LCD_TFT复位** ----------------------------------//
#define LCD_TFT_Reset_DIR  (PJDIR)  
#define LCD_TFT_Reset_PORT (PJOUT)
#define LCD_TFT_Reset_IO   (BIT0)

	//配置引脚为"输出",并"使能"复位功能(复位"低"电平有效)
#define mOpen_LCD_TFT_Reset {LCD_TFT_Reset_DIR |= LCD_TFT_Reset_IO; LCD_TFT_Reset_PORT &= ~LCD_TFT_Reset_IO;}   

	//配置引脚为"输出",并"关闭"复位功能
#define mClose_LCD_TFT_Reset {LCD_TFT_Reset_DIR |= LCD_TFT_Reset_IO; LCD_TFT_Reset_PORT |= LCD_TFT_Reset_IO;}   


//--**P3.7 引脚: 控制LCD_TFT背光** ----------------------------------//
	//根据引脚输出的占空比，调试背光亮度
#define LCD_TFT_BackLight_DIR  (P3DIR)  
#define LCD_TFT_BackLight_PORT (P3OUT)
#define LCD_TFT_BackLight_IO   (BIT7)

	//引脚: 输出高电平(占空比为100%)(此时背光最亮)
	//配置引脚为"输出",并"打开"LCD_TFT背光
#define mOpen_LCD_TFT_BackLight {LCD_TFT_BackLight_DIR |= LCD_TFT_BackLight_IO; LCD_TFT_BackLight_PORT |= LCD_TFT_BackLight_IO;}   

	//引脚: 输出低电平(占空比为  0%)(此时背光关闭)
	//配置引脚为"输出",并"关闭"LCD_TFT背光
#define mClose_LCD_TFT_BackLight {LCD_TFT_BackLight_DIR |= LCD_TFT_BackLight_IO; LCD_TFT_BackLight_PORT &= (~LCD_TFT_BackLight_IO);} 



////////////////////////////////////////////////////////////////////////////
//==**单片机正常工作指示灯*IO口使用宏定义**=========//
//==**系统正常工作时，指示灯每250ms闪一次)**=========//

//--**P4.2  引脚: 单片机正常工作指示灯** ---------------------//
#define WORKING_LED_DIR  (P4DIR)  
#define WORKING_LED_PORT (P4OUT)
#define WORKING_LED_IO   (BIT2)
   
	 //配置引脚为"输出",并"翻转"引脚输出状态
#define mTurn_Working_Led  {WORKING_LED_DIR |= WORKING_LED_IO; WORKING_LED_PORT ^= WORKING_LED_IO;}              

	//配置引脚为"输出",并"点亮"工作指示灯
#define mOpen_Working_Led  {WORKING_LED_DIR |= WORKING_LED_IO; WORKING_LED_PORT |= WORKING_LED_IO;}   

	//配置引脚为"输出",并"熄灭"工作指示灯
#define mClose_Working_Led {WORKING_LED_DIR |= WORKING_LED_IO; WORKING_LED_PORT &= (~WORKING_LED_IO);} 


////////////////////////////////////////////////////////////////////////////
//==***LED发光二极管**IO口使用宏定义**=================//

//--**P4.1  引脚: LED_YELLOW** -------------------------------------------//
#define LED_YELLOW_DIR  (P4DIR)  
#define LED_YELLOW_PORT (P4OUT)
#define LED_YELLOW_IO   (BIT1)
	//配置引脚为"输出",并"点亮"LED_YELLOW
#define mOpen_LED_YELLOW  {LED_YELLOW_DIR |= LED_YELLOW_IO; LED_YELLOW_PORT |= LED_YELLOW_IO;}   
	//配置引脚为"输出",并"熄灭"LED_YELLOW
#define mClose_LED_YELLOW {LED_YELLOW_DIR |= LED_YELLOW_IO; LED_YELLOW_PORT &= (~LED_YELLOW_IO);} 
	 //配置引脚为"输出",并"翻转"引脚输出状态
#define mTurn_LED_YELLOW  {LED_YELLOW_DIR |= LED_YELLOW_IO; LED_YELLOW_PORT ^= LED_YELLOW_IO;}              


//--**P4.2  引脚: LED_GREEN** -------------------------------------------//
#define LED_GREEN_DIR   (P4DIR)  
#define LED_GREEN_PORT  (P4OUT)
#define LED_GREEN_IO    (BIT2)
	//配置引脚为"输出",并"点亮"LED_GREEN
#define mOpen_LED_GREEN  {LED_GREEN_DIR |= LED_GREEN_IO; LED_GREEN_PORT |= LED_GREEN_IO;}   
	//配置引脚为"输出",并"熄灭"LED_GREEN
#define mClose_LED_GREEN {LED_GREEN_DIR |= LED_GREEN_IO; LED_GREEN_PORT &= (~LED_GREEN_IO);} 
	 //配置引脚为"输出",并"翻转"引脚输出状态
#define mTurn_LED_GREEN  {LED_GREEN_DIR |= LED_GREEN_IO; LED_GREEN_PORT ^= LED_GREEN_IO;}              


//--**P4.3  引脚: LED_RED** -------------------------------------------//
#define LED_RED_DIR     (P4DIR)    
#define LED_RED_PORT    (P4OUT)
#define LED_RED_IO      (BIT3)
	//配置引脚为"输出",并"点亮"LED_RED
#define mOpen_LED_RED  {LED_RED_DIR |= LED_RED_IO; LED_RED_PORT |= LED_RED_IO;}   
	//配置引脚为"输出",并"熄灭"LED_RED
#define mClose_LED_RED {LED_RED_DIR |= LED_RED_IO; LED_RED_PORT &= (~LED_RED_IO);} 
	 //配置引脚为"输出",并"翻转"引脚输出状态
#define mTurn_LED_RED  {LED_RED_DIR |= LED_RED_IO; LED_RED_PORT ^= LED_RED_IO;}              





////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////




#endif  /* __Hardware_Profile_H */






