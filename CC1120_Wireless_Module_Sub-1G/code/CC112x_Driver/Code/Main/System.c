/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 System.c
* 附属文件-Dependencies:  	 System.h; msp430f6638.h; LCD_TFT.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■ "系统" 常用功能函数集
	01)    系统单片机内部资源的初使化程序
		A. 晶振设置初使化		      B. IO口初使化定义  
		C. AD口初使化				      D. 定时器初使化	  
		E. 中断初使化			  	      F. 上电后，部份变量初使化
		G. 看门狗初使化(周期)	      H. 各种复位初使化
		I.  其他功能模块初使化
	02)   系统变量初使化(包括状态机初使化)，分为"复位"和"上电"两种情况
		A. 系统主状态初始值赋值   B. 系统次状态初始值赋值
		C.				 D.
	03)  系统自检
		A. 自检蜂鸣器		 B. 自检显示部份:Led，数码管，液晶
		C.
	04)  通用"系统时钟"处理  
		分别在中断中产生定时为1ms,10ms, 20ms, 100ms, 200ms, 250ms, 500ms ,1s, 2s
	05) 系统状态机
	06) 

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 注意事项-Attention : 	
	▲01) 处理器IO口使用宏定义，统一在Hardware_Profile.h 定义        
	▲02)     ▲03)    ▲04)    ▲05)    ▲06)     
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



#include "System.h"	 //"系统" 常用功能函数集-头文件



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
union FLAGBIT16 SystemFlagBits;	//系统标志位定义


unsigned char G_TempChar = 0 ;    //测试临时用的"字节"变量

////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned int G_10msCnt = 0;   //系统定时10ms计数器
unsigned int G_250msCnt = 0;  //系统定时250ms计数器


////////////////////////////////////////////////////////////////////////////
//==**系统单片初使化程序**============================//
////////////////////////////////////////////////////////////////////////////


/****************************************************************************
*函数名-Function:	void System_Initial(void)
*描述- Description:	系统初使化 :单片机内部资源+外部基本资源的初使化
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) 把不使用的内部资源和外部资源用"//"屏蔽掉，以免误动作   
	▲02) 初使化顺序要求:
	⑴内部资源:	先关所有中断→晶振→AD口设置→IO口→Timer0
		→UART串口通信 →其他功能模块→复位寄存器→看门狗
	⑵内部资源: ①LCD 液晶模块 ②  ③ ④⑤⑥	
	⑶中断初使化:使能要使用的中断
	▲03)    ▲04)  
*****************************************************************************/
void System_Initial(void)
{	 
	Osccon_Initial(); //晶振初始化函数:定义相关晶振参数
	
	Timer2_Initial(); //定时器A2初始化设置(用于系统每1ms自动中断一次)
}      


/****************************************************************************
*函数名-Function:	void Osccon_Initial(void)
*描述- Description:	晶振初始化函数:配置相关晶振参数
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Osccon_Initial(void)
{

	//IO初始化，在放在"晶振"配置的前面
//P1DIR |= BIT0;		 // ACLK set out to pins
//P1SEL |= BIT0;	   		

//==care=下面之两句一定要有，不知道为什么?//////////////////
//P3DIR |= BIT4;							  // SMCLK set out to pins
//P3SEL |= BIT4;							  

	
/************************************/

	SetVCore(PMMCOREV_3);			 // Set Vcore to accomodate for max. allowed system speed

	UCSCTL3 |= SELREF_2;					  // Set DCO FLL reference = REFO

	__bis_SR_register(SCG0);				  // Disable the FLL control loop
	UCSCTL0 = 0x0000;						  // Set lowest possible DCOx, MODx
	UCSCTL1 = DCORSEL_5;					  // Select DCO range 24MHz operation
	UCSCTL2 = FLLD_1 + 374; 				  // Set DCO Multiplier for 12MHz
									  // (N + 1) * FLLRef = Fdco
									  // (374 + 1) * 32768 = 12MHz
									  // Set FLL Div = fDCOCLK/2
	__bic_SR_register(SCG0);				  // Enable the FLL control loop
	

/******************
//==care=倍频到20M, 程序一定要放在这里,不然会影响到RTC//////
	 SetVCore(PMMCOREV_3);			 // Set Vcore to accomodate for max. allowed system speed
	 UCSCTL3 |= SELREF_2;				 // Set DCO FLL reference = REFO
	// UCSCTL4 |= SELA_2;				 // Set ACLK = REFO
	 Init_FLL_Settle(20000, 630);	// MCLK=DCO = 20MHz // Set system clock to max (20MHz)
*******/


									 
////////////////////////////////////////////////////////////////////////////								 
	 while(BAKCTL & LOCKIO) 				   // Unlock XT1 pins for operation
		BAKCTL &= ~(LOCKIO);   
	 

	 P7SEL |= BIT2+BIT3;					   // Port select XT2

	 UCSCTL6 &= ~XT2OFF;					   // Enable XT2 
//	 UCSCTL3 |= SELREF_2;					   // Set DCO FLL reference = REFO
											   // Since LFXT1 is not used,
											   // sourcing FLL with LFXT1 can cause
											   // XT1OFFG flag to set
	//  UCSCTL4 |= SELA_2; 					   // ACLK=REFO=32.768KHz,SMCLK=DCO,MCLK=DCO


	 UCSCTL6 &= ~(XT1OFF);					   // XT1 On
	 UCSCTL6 |= XCAP_3; 					   // Internal load cap 


	// Loop until XT1,XT2 & DCO stabilizes - in this case loop until XT2 settles
	do
	{
		UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
									  // Clear XT2,XT1,DCO fault flags
		SFRIFG1 &= ~OFIFG;					  // Clear fault flags
	}while (SFRIFG1&OFIFG); 				  // Test oscillator fault flag

	UCSCTL6 &= ~XT2DRIVE0;					  // Decrease XT2 Drive according to  expected frequency
							
	//UCSCTL4 |= SELS_5 + SELM_5; 			  // SMCLK=MCLK=XT2
	UCSCTL4 |= SELS_5;	   // SMCLK=XT2 = 4MHz
	
	//UCSCTL4 |= SELS_4;   //SMCLK选择DCOCLKDIV (倍频后的频率)
	
	UCSCTL4 |= SELA_0; // ACLK = LFTX1 (by default)=32.768KHz

}




/****************************************************************************
*函数名-Function:	void  Timer2_Initial(void)
*描述- Description:	定时器A2初始化设置(用于系统每1ms自动中断一次)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：
	▲01) 作为系统基本时钟   
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void  Timer2_Initial(void)
{
		// 使能Timer2中断, 增计数模式：定时器增计数到 TAxCCR0,再从0重新计数
    TA2CTL = TASSEL_2 + MC_1 + TACLR + TAIE;  // 选SMCLK作为Timer2的时钟源, 清零 TAR

		//care	为"SMCLK=XT2=4 MHz"的情况下:  定时时间为1ms = 4000/4M(示波器实测1ms)			   
	TA2CCR0 = 4000; 
}



/****************************************************************************
*函数名-Function:	void System_10ms_Task(void)
*描述- Description:	处理系统定时"10ms" 下的相关事务 
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) 在1ms的基础上累加计数 
	▲02) 每10ms判断下位机是否收到有效数据
	▲03) 检查是否启动蜂鸣器(以10ms为时基)
	▲04)  
*****************************************************************************/
void System_10ms_Task(void)  //处理系统定时"10ms" 下的相关事务 
{
	G_10msCnt++;			  //系统定时10ms
	
	if(G_10msCnt >= 10)	
	{
		G_10msCnt = 0; 
		F_10ms_TaskClock = 1;			 //系统定时10ms标志位 
	}
}


/****************************************************************************
*函数名-Function:	void System_250ms_Task(void) 
*描述- Description:	处理系统定时"250ms" 下的相关事务
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) 在1ms的基础上累加计数 
	▲02) 产生占空比为50%,周期为0.5s的矩行波
	▲03) 工作指示灯一直闪烁(250ms闪烁一次) 
	▲04)  
*****************************************************************************/
void System_250ms_Task(void)  //处理系统定时"250ms" 下的相关事务
{
	G_250msCnt++;		   //系统定时250ms
	if(G_250msCnt >= 250)  
	{
		G_250msCnt = 0; 
		
		F_250ms_Working_Led = 1; //用于单片机正常工作时，工作指示灯一直闪烁(250ms闪烁一次)  
	}
}




/****************************************************************************
*函数名-Function:	void System_GetLoopClockTick(void)
*描述- Description:	每次"死等"延时10ms后，系统"循环"执行一次程序
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void System_GetLoopClockTick(void) //每次"死等"延时10ms后，系统"循环"执行一次程序
{
    while (F_10ms_TaskClock == 0)
    {
		mClr_WDTCNT;  // 清看门狗
    }
	
    F_10ms_TaskClock = 0;
}


/****************************************************************************
*函数名-Function:	void System_Working_Led(void)
*描述- Description:	单片机正常工作指示灯: 250ms闪烁一次
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01)  系统"正常": 指示灯每250ms 闪烁一次
	            系统"异常": ①不是250ms 闪一下②闪烁忽快忽慢  ③ ④⑤
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void System_Working_Led(void)  //单片机正常工作指示灯: 250ms闪烁一次
{
	if(F_250ms_Working_Led)
	{
		F_250ms_Working_Led = 0;
		
			//MCU正常工作，灯250ms闪烁
		mTurn_Working_Led;	//设置引脚为"输出",并"翻转"引脚输出状态		   
	}
}



/****************************************************************************
*函数名-Function:	void WaitingDelayMs(unsigned int TimeData)  
*描述- Description:		死等待延时x毫秒
*输入参数-Input:	TimeData: 要延时ms值，例WaitingDelayMs(1);  //表示死等待延时1ms
*输出参数-output:	None
*注意事项-Note：	
	▲01) 与系统频率有关,DCO倍频为12MHz时取t1 = 60 (当前系统频率12M)
	            与系统频率有关,DCO倍频为20MHz时取t1 = 107 
	▲02) TimeData  = TimeData *10 = 100时，延时为10ms   
	▲03) 里面"清看门狗"操作   
	▲04) ms级的死等延时，调用WaitingDelayMs(n); //死等待延时n个ms(包含清看门狗操作)
	            us级的死等延时，调用mDelay_Cycles(n);	//死等待延时n个时钟周期 
*****************************************************************************/
void WaitingDelayMs(unsigned int TimeData)  
{
	unsigned char t1;
	unsigned int t2;

	TimeData = TimeData *10;   //晶振为20MHz时,TimeData = 100时，延时为10ms
	
	for(t2 = TimeData; t2 != 0; t2--)
	{
		for(t1 = 60; t1 != 0; t1--)
		{      
			mClr_WDTCNT;  // 清看门狗
			
			mNop; mNop; mNop; mNop;   //空操作指令(用于"短延时"或"调试")
			mNop; mNop; mNop; mNop; 
			mNop; mNop; mNop; mNop;   
		}
	}
}


/****************************************************************************
*函数名-Function:	void Sent_DataToArray(unsigned char *ArrayPoint,unsigned char DataValue,unsigned int Cnt)
*描述- Description:		将Cnt个相同的Data数据复制到数组Array[x]之后的Cnt个元素
*输入参数-Input:	ArrayPoint: 目的数组;  DataValue: 字节数据;   Cnt: 复制字节个数  
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
	void Sent_DataToArray(unsigned char *ArrayPoint,unsigned char DataValue,unsigned int Cnt)

{
	for( ; Cnt > 0; Cnt--)
    {
    	*ArrayPoint = DataValue;
		ArrayPoint++;
    }
}




/****************************************************************************
*函数名-Function:	__interrupt void TIMER2_A1_ISR(void)  // Timer2_A1 中断处理程序
*描述- Description:	系统每 "500us = 0.5ms"中断一次作为基本中断时基
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) TIMERA使用两个中断向量,CCR0优先级最高占用A0_VECTOR;  
	▲02) TIMERA的溢出中断和CCRI CCR2占用A1_VECTOR 
	▲03) 其中A1_VECTOR这三个中断又通过TAIV中断向量寄存器，
		     区分哪个产生中断，并有优先级。     
	▲04) 
*****************************************************************************/
#pragma vector=TIMER2_A1_VECTOR
__interrupt void TIMER2_A1_ISR(void)  // Timer2_A1 中断处理程序
{
	switch(__even_in_range(TA2IV,14))
	{
		case  0: break; 						 // No interrupt
		case  2: break; 						 // CCR1 not used
		case  4: break; 						 // CCR2 not used
		case  6: break; 						 // reserved
		case  8: break; 						 // reserved
		case 10: break; 						 // reserved
		case 12: break; 						 // reserved
		
		case 14:   //14对应定时器溢出时，在中断向量寄存器TA2IV的值	
			////////////////////////////////////////////////////////////////////////////
			//==**系统以1ms为时基**================================//	
		
			Scan_Key();  //"IO口键盘"扫描，1ms扫描一次按键(中断里)

			System_10ms_Task();	//处理系统定时"10ms" 下的相关事务 
			
			System_250ms_Task();  //处理系统定时"250ms" 下的相关事务
			break;
			
		default: break;
	}
}





