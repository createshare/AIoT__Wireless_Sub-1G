/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 System.c
* �����ļ�-Dependencies:  	 System.h; msp430f6638.h; LCD_TFT.h;
* �ļ�����-File Description:	 ( Դ����-Source File) 
	�� "ϵͳ" ���ù��ܺ�����
	01)    ϵͳ��Ƭ���ڲ���Դ�ĳ�ʹ������
		A. �������ó�ʹ��		      B. IO�ڳ�ʹ������  
		C. AD�ڳ�ʹ��				      D. ��ʱ����ʹ��	  
		E. �жϳ�ʹ��			  	      F. �ϵ�󣬲��ݱ�����ʹ��
		G. ���Ź���ʹ��(����)	      H. ���ָ�λ��ʹ��
		I.  ��������ģ���ʹ��
	02)   ϵͳ������ʹ��(����״̬����ʹ��)����Ϊ"��λ"��"�ϵ�"�������
		A. ϵͳ��״̬��ʼֵ��ֵ   B. ϵͳ��״̬��ʼֵ��ֵ
		C.				 D.
	03)  ϵͳ�Լ�
		A. �Լ������		 B. �Լ���ʾ����:Led������ܣ�Һ��
		C.
	04)  ͨ��"ϵͳʱ��"����  
		�ֱ����ж��в�����ʱΪ1ms,10ms, 20ms, 100ms, 200ms, 250ms, 500ms ,1s, 2s
	05) ϵͳ״̬��
	06) 

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ע������-Attention : 	
	��01) ������IO��ʹ�ú궨�壬ͳһ��Hardware_Profile.h ����        
	��02)     ��03)    ��04)    ��05)    ��06)     
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
* �޸ļ�¼-Change History:   
	����   ʱ��        �汾  ��������
	Author 	 Date		   Rev      Comment
	-------------------------------------------------------------------------------
	BlueS	2012-12-12	  1.0	   
			xxxx-xx-xx	  x.x	   
			xxxx-xx-xx	  x.x				
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/



#include "System.h"	 //"ϵͳ" ���ù��ܺ�����-ͷ�ļ�



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
union FLAGBIT16 SystemFlagBits;	//ϵͳ��־λ����


unsigned char G_TempChar = 0 ;    //������ʱ�õ�"�ֽ�"����

////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned int G_10msCnt = 0;   //ϵͳ��ʱ10ms������
unsigned int G_250msCnt = 0;  //ϵͳ��ʱ250ms������


////////////////////////////////////////////////////////////////////////////
//==**ϵͳ��Ƭ��ʹ������**============================//
////////////////////////////////////////////////////////////////////////////


/****************************************************************************
*������-Function:	void System_Initial(void)
*����- Description:	ϵͳ��ʹ�� :��Ƭ���ڲ���Դ+�ⲿ������Դ�ĳ�ʹ��
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) �Ѳ�ʹ�õ��ڲ���Դ���ⲿ��Դ��"//"���ε�����������   
	��02) ��ʹ��˳��Ҫ��:
	���ڲ���Դ:	�ȹ������жϡ������AD�����á�IO�ڡ�Timer0
		��UART����ͨ�� ����������ģ�����λ�Ĵ��������Ź�
	���ڲ���Դ: ��LCD Һ��ģ�� ��  �� �ܢݢ�	
	���жϳ�ʹ��:ʹ��Ҫʹ�õ��ж�
	��03)    ��04)  
*****************************************************************************/
void System_Initial(void)
{	 
	Osccon_Initial(); //�����ʼ������:������ؾ������
	
	Timer2_Initial(); //��ʱ��A2��ʼ������(����ϵͳÿ1ms�Զ��ж�һ��)
}      


/****************************************************************************
*������-Function:	void Osccon_Initial(void)
*����- Description:	�����ʼ������:������ؾ������
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Osccon_Initial(void)
{

	//IO��ʼ�����ڷ���"����"���õ�ǰ��
//P1DIR |= BIT0;		 // ACLK set out to pins
//P1SEL |= BIT0;	   		

//==care=����֮����һ��Ҫ�У���֪��Ϊʲô?//////////////////
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
//==care=��Ƶ��20M, ����һ��Ҫ��������,��Ȼ��Ӱ�쵽RTC//////
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
	
	//UCSCTL4 |= SELS_4;   //SMCLKѡ��DCOCLKDIV (��Ƶ���Ƶ��)
	
	UCSCTL4 |= SELA_0; // ACLK = LFTX1 (by default)=32.768KHz

}




/****************************************************************************
*������-Function:	void  Timer2_Initial(void)
*����- Description:	��ʱ��A2��ʼ������(����ϵͳÿ1ms�Զ��ж�һ��)
*�������-Input:	None
*�������-output:	None
*ע������-Note��
	��01) ��Ϊϵͳ����ʱ��   
	��02)    ��03)    ��04)  
*****************************************************************************/
void  Timer2_Initial(void)
{
		// ʹ��Timer2�ж�, ������ģʽ����ʱ���������� TAxCCR0,�ٴ�0���¼���
    TA2CTL = TASSEL_2 + MC_1 + TACLR + TAIE;  // ѡSMCLK��ΪTimer2��ʱ��Դ, ���� TAR

		//care	Ϊ"SMCLK=XT2=4 MHz"�������:  ��ʱʱ��Ϊ1ms = 4000/4M(ʾ����ʵ��1ms)			   
	TA2CCR0 = 4000; 
}



/****************************************************************************
*������-Function:	void System_10ms_Task(void)
*����- Description:	����ϵͳ��ʱ"10ms" �µ�������� 
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) ��1ms�Ļ������ۼӼ��� 
	��02) ÿ10ms�ж���λ���Ƿ��յ���Ч����
	��03) ����Ƿ�����������(��10msΪʱ��)
	��04)  
*****************************************************************************/
void System_10ms_Task(void)  //����ϵͳ��ʱ"10ms" �µ�������� 
{
	G_10msCnt++;			  //ϵͳ��ʱ10ms
	
	if(G_10msCnt >= 10)	
	{
		G_10msCnt = 0; 
		F_10ms_TaskClock = 1;			 //ϵͳ��ʱ10ms��־λ 
	}
}


/****************************************************************************
*������-Function:	void System_250ms_Task(void) 
*����- Description:	����ϵͳ��ʱ"250ms" �µ��������
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) ��1ms�Ļ������ۼӼ��� 
	��02) ����ռ�ձ�Ϊ50%,����Ϊ0.5s�ľ��в�
	��03) ����ָʾ��һֱ��˸(250ms��˸һ��) 
	��04)  
*****************************************************************************/
void System_250ms_Task(void)  //����ϵͳ��ʱ"250ms" �µ��������
{
	G_250msCnt++;		   //ϵͳ��ʱ250ms
	if(G_250msCnt >= 250)  
	{
		G_250msCnt = 0; 
		
		F_250ms_Working_Led = 1; //���ڵ�Ƭ����������ʱ������ָʾ��һֱ��˸(250ms��˸һ��)  
	}
}




/****************************************************************************
*������-Function:	void System_GetLoopClockTick(void)
*����- Description:	ÿ��"����"��ʱ10ms��ϵͳ"ѭ��"ִ��һ�γ���
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void System_GetLoopClockTick(void) //ÿ��"����"��ʱ10ms��ϵͳ"ѭ��"ִ��һ�γ���
{
    while (F_10ms_TaskClock == 0)
    {
		mClr_WDTCNT;  // �忴�Ź�
    }
	
    F_10ms_TaskClock = 0;
}


/****************************************************************************
*������-Function:	void System_Working_Led(void)
*����- Description:	��Ƭ����������ָʾ��: 250ms��˸һ��
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01)  ϵͳ"����": ָʾ��ÿ250ms ��˸һ��
	            ϵͳ"�쳣": �ٲ���250ms ��һ�¢���˸�������  �� �ܢ�
	��02)    ��03)    ��04)  
*****************************************************************************/
void System_Working_Led(void)  //��Ƭ����������ָʾ��: 250ms��˸һ��
{
	if(F_250ms_Working_Led)
	{
		F_250ms_Working_Led = 0;
		
			//MCU������������250ms��˸
		mTurn_Working_Led;	//��������Ϊ"���",��"��ת"�������״̬		   
	}
}



/****************************************************************************
*������-Function:	void WaitingDelayMs(unsigned int TimeData)  
*����- Description:		���ȴ���ʱx����
*�������-Input:	TimeData: Ҫ��ʱmsֵ����WaitingDelayMs(1);  //��ʾ���ȴ���ʱ1ms
*�������-output:	None
*ע������-Note��	
	��01) ��ϵͳƵ���й�,DCO��ƵΪ12MHzʱȡt1 = 60 (��ǰϵͳƵ��12M)
	            ��ϵͳƵ���й�,DCO��ƵΪ20MHzʱȡt1 = 107 
	��02) TimeData  = TimeData *10 = 100ʱ����ʱΪ10ms   
	��03) ����"�忴�Ź�"����   
	��04) ms����������ʱ������WaitingDelayMs(n); //���ȴ���ʱn��ms(�����忴�Ź�����)
	            us����������ʱ������mDelay_Cycles(n);	//���ȴ���ʱn��ʱ������ 
*****************************************************************************/
void WaitingDelayMs(unsigned int TimeData)  
{
	unsigned char t1;
	unsigned int t2;

	TimeData = TimeData *10;   //����Ϊ20MHzʱ,TimeData = 100ʱ����ʱΪ10ms
	
	for(t2 = TimeData; t2 != 0; t2--)
	{
		for(t1 = 60; t1 != 0; t1--)
		{      
			mClr_WDTCNT;  // �忴�Ź�
			
			mNop; mNop; mNop; mNop;   //�ղ���ָ��(����"����ʱ"��"����")
			mNop; mNop; mNop; mNop; 
			mNop; mNop; mNop; mNop;   
		}
	}
}


/****************************************************************************
*������-Function:	void Sent_DataToArray(unsigned char *ArrayPoint,unsigned char DataValue,unsigned int Cnt)
*����- Description:		��Cnt����ͬ��Data���ݸ��Ƶ�����Array[x]֮���Cnt��Ԫ��
*�������-Input:	ArrayPoint: Ŀ������;  DataValue: �ֽ�����;   Cnt: �����ֽڸ���  
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
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
*������-Function:	__interrupt void TIMER2_A1_ISR(void)  // Timer2_A1 �жϴ������
*����- Description:	ϵͳÿ "500us = 0.5ms"�ж�һ����Ϊ�����ж�ʱ��
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) TIMERAʹ�������ж�����,CCR0���ȼ����ռ��A0_VECTOR;  
	��02) TIMERA������жϺ�CCRI CCR2ռ��A1_VECTOR 
	��03) ����A1_VECTOR�������ж���ͨ��TAIV�ж������Ĵ�����
		     �����ĸ������жϣ��������ȼ���     
	��04) 
*****************************************************************************/
#pragma vector=TIMER2_A1_VECTOR
__interrupt void TIMER2_A1_ISR(void)  // Timer2_A1 �жϴ������
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
		
		case 14:   //14��Ӧ��ʱ�����ʱ�����ж������Ĵ���TA2IV��ֵ	
			////////////////////////////////////////////////////////////////////////////
			//==**ϵͳ��1msΪʱ��**================================//	
		
			Scan_Key();  //"IO�ڼ���"ɨ�裬1msɨ��һ�ΰ���(�ж���)

			System_10ms_Task();	//����ϵͳ��ʱ"10ms" �µ�������� 
			
			System_250ms_Task();  //����ϵͳ��ʱ"250ms" �µ��������
			break;
			
		default: break;
	}
}





