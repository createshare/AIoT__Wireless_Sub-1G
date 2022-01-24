/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 Hardware_Profile.h
* �����ļ�-Dependencies:  	 msp430f6638.h	
* �ļ�����-File Description:	 ( ͷ�ļ�-Header File )
	�� ������"Ӳ�������ļ�" -ͷ�ļ�-Hardware specific definitions for Processor
	01) ������IO��ʹ�ú궨�壬ͳһ��Hardware_Profile.h ����     
	02)      03)    04)    05)    06)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ע������-Attention : 	
	��01)     ��02)     ��03)    ��04)    ��05)    ��06)     
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
* �޸ļ�¼-Change History:   
	����   ʱ��        �汾  ��������
	Author 	 Date		   Rev      Comment
	-------------------------------------------------------------------------------
	BlueS	2012-12-12	  1.0	   
			xxxx-xx-xx	  x.x	   
			xxxx-xx-xx	  x.x				
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
* ��˾-Company: 			CS-EMLAB  Co. , Ltd.
* ������Э��-Software License Agreement:
	Copyright (C) 2012-2020 	CS-EMLAB  Co. , Ltd.	All rights reserved.	

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/


#ifndef __Hardware_Profile_H
#define __Hardware_Profile_H


#include "msp430f6638.h"   // "������"ͷ�ļ�: �ڲ��Ĵ���ض����



////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"�궨��**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//==**��Ƭ���ڲ�����**================================//

#define mClose_WDT      (WDTCTL = WDTPW + WDTHOLD)  // �رտ��Ź�
#define mClr_WDTCNT     (WDTCTL = WDTPW + WDTCNTCL) // �忴�Ź�(����MSP430��Ƭ��)
#define	mNop	        (__no_operation())    //�ղ���ָ��(����"����ʱ"��"����")

//#define	mEnable_GIE     (__bis_SR_register(GIE))  // �������ж�
#define	mEnable_GIE     (_EINT())  // �������ж�GIE
#define	mDisable_GIE    (_DINT())  // �ر����ж�GIE

#define	mReset_Soft    (PMMCTL0 |= PMMSWPOR) //"�����λ" (MSP430��Ƭ��)



#define	Fosc_System	    (12)		//ϵͳ����Ƶ�� unit:MHz (��Ƶ�󣬼����յ�)
////////////////////////////////////////////////////////////////////////////
//==** ϵͳƵ��MCLK =12M  (DCO  FLL��Ƶ��12MHz)   **==============//
	//ms����������ʱ������WaitingDelayMs(n); //���ȴ���ʱn��ms(�����忴�Ź�����)
	//us����������ʱ������mDelay_Cycles(n);	//���ȴ���ʱn��ʱ������
#define mDelay_Cycles(n) (__delay_cycles(n)) // ���ȴ���ʱ"n"��ʱ������.
	//��: __delay_cycles(12000000); //(1/12M)*12000000=1s

#define M_Delay_1us   (12)   //������ʱ"1us" //ϵͳƵ��Ϊ12 Mʱ
#define M_Delay_2us   (24)   //������ʱ"2us" //ϵͳƵ��Ϊ12 Mʱ
#define M_Delay_5us   (60)  //������ʱ"5us" //ϵͳƵ��Ϊ12 Mʱ

#define M_Delay_10us  (120)      //������ʱ"10us"//ϵͳƵ��Ϊ12 Mʱ
#define M_Delay_100us (1200)     //������ʱ"100us"//ϵͳƵ��Ϊ12 Mʱ
#define M_Delay_1ms   (12000)    //������ʱ"1ms"//ϵͳƵ��Ϊ12 Mʱ(ʾ����ʵ��1.02ms)
#define M_Delay_1s    (12000000) //������ʱ"1s"//ϵͳƵ��Ϊ12 Mʱ(ʾ����ʵ��1.02s)


#define CPU_F ((double)12000000)
#define _delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define _delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))


////////////////////////////////////////////////////////////////////////////
//==** ϵͳƵ��MCLK =20M  (DCO  FLL��Ƶ��20MHz)   **==============//

/********************************************
	//ms����������ʱ������WaitingDelayMs(n); //���ȴ���ʱn��ms(�����忴�Ź�����)
	//us����������ʱ������mDelay_Cycles(n);	//���ȴ���ʱn��ʱ������
#define mDelay_Cycles(n) (__delay_cycles(n)) // ���ȴ���ʱ"n"��ʱ������.
	//��: __delay_cycles(20000000); //Լ980ms �� (1/20M)*20000000=1s(ϵͳƵ��>20M(ͨ����Ƶ))

#define M_Delay_1us   (20)   //������ʱ"1us" //ϵͳƵ��Ϊ20 Mʱ
#define M_Delay_2us   (40)   //������ʱ"2us" //ϵͳƵ��Ϊ20 Mʱ
#define M_Delay_5us   (100)  //������ʱ"5us" //ϵͳƵ��Ϊ20 Mʱ

#define M_Delay_10us  (200)   //������ʱ"10us"
#define M_Delay_100us  (2000)   //������ʱ"100us"

//#define M_Delay_1s    (20000000)  //������ʱ"1s"	      //care ϵͳƵ��(����)ԼΪ20M
//#define M_Delay_500ms (10000000) //������ʱ"500ms"	//care ϵͳƵ��(����)ԼΪ20M
//#define M_Delay_5ms   (100000)  //������ʱ"5ms"	    //care ϵͳƵ��(����)ԼΪ20M
//#define M_Delay_1ms   (20000)  //������ʱ"1ms"	    //care ϵͳƵ��(����)ԼΪ20M
//#define M_Delay_250us (5000)  //������ʱ"250us"	    //care ϵͳƵ��(����)ԼΪ20M
//#define M_Delay_50us (1000)  //������ʱ"50us"	    //care ϵͳƵ��(����)ԼΪ20M

#define CPU_F ((double)20000000)
#define _delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define _delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
********************************************/




////////////////////////////////////////////////////////////////////////////
//==**��Ƭ��IO��ʹ�ú궨��,ͳһ��HardwareProfile.h����**===//
//==**������**MSP430F5xx_6xx �ĵ�Ƭ��**====================//
/*****************************

//==**����"����ѡ��Ĵ���"��IOΪ��Χģ�鹦�����Ż�IO����**IO bits Function Pin/IO Pin**====//
#define mSelect_Xxx_FunctionPin  (P1SEL |= BIT) //��������Ϊ"��Χģ�鹦��"����
#define mSelect_Xxx_IoPin (P1SEL &= (~BIT))     //��������Ϊ"IO"����

//==**����"����Ĵ���"��IOΪ��������**IO bits Input/Output**===================//
#define mSetOut_Xxx   (P1DIR |= BIT)         //��������Ϊ"���"
#define mSetIn_Xxx     (P1DIR &= (~BIT))    //��������Ϊ"����"

//==**����"����Ĵ���"������ߵ�ƽ��͵�ƽ**IO bits Set/Clr**===============//
#define mHigh_Xxx   (P1OUT |= BIT)           //�������"�ߵ�ƽ(1)"
#define mLow_Xxx    (P1OUT &= (~BIT))      //�������"�͵�ƽ(0)"

#define mTurn_Xxx    (P1OUT ^= BIT)        //"��ת"�������״̬

#define mOpen_Xxx   (P1OUT |= BIT)         //���������Ӧ"��"����
#define mClose_Xxx   (P1OUT &= (~BIT))    //���������Ӧ"�ر�"����

//==**���� "��������������ʹ�ܼĴ���"��ʹ�ܻ��ֹ�˹���**IO bits PULL Enabled/Disabled**===//
#define mPullEnabled_Xxx(n)   (P1REN |= BIT)        //ʹ��--����/��������
#define mPullDisabled_Xxx(n)  (P1REN &= (~BIT))   //��ֹ--����/��������

//==**���� "����Ĵ���(����)"��ѡ����������������**IO bits PullUp/PullDown**======//
#define mPullUp_Xxx(n)        (P1OUT |= BIT)      //��������"����"����
#define mPullDown_Xxx(n)    (P1OUT &= (BIT) )   //��������"����"����


//==**��ȡ"����Ĵ���"���������ŵĵ�ƽֵ**IO bits Input**================//
#define mRead_Xxx(n)   (P1IN&n?1:0 )      //��ȡ���ŵ�ƽֵ


//#define _MIN(a,b)			( (a) < (b) ? (a) : (b) )
//#define _MAX(a,b)			( (a) > (b) ? (a) : (b) )
*****************************/


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//==**�ڲ�"��ԴIO��ʹ�ú궨��**=======================//

////////////////////////////////////////////////////////////////////////////
//==**SPI_B *IO��ʹ�ú궨��**=============================//

//--**P8.4 ����: SPI_B_CLK (P8.4/UCB1CLK/UCA1STE/S11)** -------------------//
#define SPI_B_CLK_SEL  (P8SEL)
#define SPI_B_CLK_DIR  (P8DIR)  
#define SPI_B_CLK_PORT (P8OUT)

#define SPI_B_CLK_IO   (BIT4)	

	//��������Ϊ"��Χģ�鹦��"����
#define mSelect_SPI_B_CLK_FunctionPin  (SPI_B_CLK_SEL |= SPI_B_CLK_IO) 

	//����"SPI_B_CLK" ����Ϊ"���"
#define mSetOut_SPI_B_CLK (SPI_B_CLK_DIR |= SPI_B_CLK_IO)  

	//��������Ϊ"���",�����"�ߵ�ƽ"
#define mHigh_SPI_B_CLK  {SPI_B_CLK_DIR |= SPI_B_CLK_IO; SPI_B_CLK_PORT |= SPI_B_CLK_IO;}      //�������"�ߵ�ƽ(1)"
	//��������Ϊ"���",�����"�͵�ƽ"
#define mLow_SPI_B_CLK   {SPI_B_CLK_DIR |= SPI_B_CLK_IO; SPI_B_CLK_PORT &= ~SPI_B_CLK_IO;}    //�������"�͵�ƽ(0)"




//--**P8.5 ����: SPI_B_MOSI (P8.5/UCB1SIMO/UCB1SDA/S10)** ----------------//
#define SPI_B_MOSI_SEL  (P8SEL)
#define SPI_B_MOSI_DIR  (P8DIR)  
#define SPI_B_MOSI_IO   (BIT5)

	//��������Ϊ"��Χģ�鹦��"����
#define mSelect_SPI_B_MOSI_FunctionPin  (SPI_B_MOSI_SEL |= SPI_B_MOSI_IO) 

	 //����"SPI_B_MOSI" ����Ϊ"���"
#define mSetOut_SPI_B_MOSI (SPI_B_MOSI_DIR |= SPI_B_MOSI_IO)  


//--**P8.6����: SPI_B_MISO (P8.6/UCB1SOMI/UCB1SCL/S9)** ----------------//
#define SPI_B_MISO_SEL  (P8SEL)
#define SPI_B_MISO_DIR  (P8DIR)  
#define SPI_B_MISO_IO   (BIT6)

	//��������Ϊ"��Χģ�鹦��"����
#define mSelect_SPI_B_MISO_FunctionPin  (SPI_B_MISO_SEL |= SPI_B_MISO_IO) 

	 //����"SPI_B_MISO" ����Ϊ"����"
#define mSetIn_SPI_B_MISO (SPI_B_MISO_DIR &= (~SPI_B_MISO_IO))  

//--**P3.6 ����: �ӻ�SPI ʹ������SPI_CS ("��"��Ч)** -------------------//
#define Slave_SPI_CS_DIR  (P3DIR)  
#define Slave_SPI_CS_PORT (P3OUT)
#define Slave_SPI_CS_IO   (BIT6)

		//��������Ϊ"���",��"����ߵ�ƽ"
//#define mHigh_Slave_SPI_CS {Slave_SPI_CS_DIR |= Slave_SPI_CS_IO; Slave_SPI_CS_PORT |= Slave_SPI_CS_IO;}   
			//��������Ϊ"���",��"����͵�ƽ"
//#define mLow_Slave_SPI_CS {Slave_SPI_CS_DIR |= Slave_SPI_CS_IO; Slave_SPI_CS_PORT &= ~Slave_SPI_CS_IO;}   

	//��������Ϊ"���",��"ʹ��"�ӻ�SPI_CS("��"��ƽ��Ч)
#define mOpen_Slave_SPI_CS {Slave_SPI_CS_DIR |= Slave_SPI_CS_IO; Slave_SPI_CS_PORT &= ~Slave_SPI_CS_IO;}   

	//��������Ϊ"���",��"�ر�"�ӻ�SPI_CS("��"��ƽ��Ч)
#define mClose_Slave_SPI_CS {Slave_SPI_CS_DIR |= Slave_SPI_CS_IO; Slave_SPI_CS_PORT |= Slave_SPI_CS_IO;}   




 
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//==**�ⲿ"��ԴIO��ʹ�ú궨��**=======================//

////////////////////////////////////////////////////////////////////////////
//==**��·������TS3A5017 *IO��ʹ�ú궨��**================//

//--**P3.4 ����: ���ӵ���·������:����IN1** -------------------//
#define TS3A5017_01_IN1_DIR  (P3DIR)  
#define TS3A5017_01_IN1_PORT (P3OUT)
#define TS3A5017_01_IN1_IO   (BIT4)

#define mSetOut_TS3A5017_01_IN1 (TS3A5017_01_IN1_DIR |= TS3A5017_01_IN1_IO)   //����IN1���Ŷ�Ϊ"���"
#define mHigh_TS3A5017_01_IN1   (TS3A5017_01_IN1_PORT |= TS3A5017_01_IN1_IO)    //�������"�ߵ�ƽ(1)"
#define mLow_TS3A5017_01_IN1    (TS3A5017_01_IN1_PORT &= (~TS3A5017_01_IN1_IO)) //�������"�͵�ƽ(0)"

#define mConfig_TS3A5017_01_IN1(IN1) {mSetOut_TS3A5017_01_IN1; IN1 ? mHigh_TS3A5017_01_IN1 : mLow_TS3A5017_01_IN1;} 

//--**P3.5 ����: ���ӵ���·������:����IN2** -------------------//
#define TS3A5017_01_IN2_DIR  (P3DIR)  
#define TS3A5017_01_IN2_PORT (P3OUT)
#define TS3A5017_01_IN2_IO   (BIT5)	

#define mSetOut_TS3A5017_01_IN2 (TS3A5017_01_IN2_DIR |= TS3A5017_01_IN2_IO)   //����IN2���Ŷ�Ϊ"���"
#define mHigh_TS3A5017_01_IN2   (TS3A5017_01_IN2_PORT |= TS3A5017_01_IN2_IO)    //�������"�ߵ�ƽ(1)"
#define mLow_TS3A5017_01_IN2    (TS3A5017_01_IN2_PORT &= (~TS3A5017_01_IN2_IO)) //�������"�͵�ƽ(0)"

#define mConfig_TS3A5017_01_IN2(IN2) {mSetOut_TS3A5017_01_IN2; IN2 ? mHigh_TS3A5017_01_IN2 : mLow_TS3A5017_01_IN2;} 


////////////////////////////////////////////////////////////////////////////
//==**LCD_TFT Һ����ʾ��*IO��ʹ�ú궨��**===============//

//--**P3.6 ����: LCD_TFTʹ������CS ("��"��Ч)** -------------------//
#define LCD_TFT_CS_DIR  (P3DIR)  
#define LCD_TFT_CS_PORT (P3OUT)
#define LCD_TFT_CS_IO   (BIT6)

		//��������Ϊ"���",��"����ߵ�ƽ"
#define mHigh_LCD_TFT_CS {LCD_TFT_CS_DIR |= LCD_TFT_CS_IO; LCD_TFT_CS_PORT |= LCD_TFT_CS_IO;}   
			//��������Ϊ"���",��"����͵�ƽ"
#define mLow_LCD_TFT_CS {LCD_TFT_CS_DIR |= LCD_TFT_CS_IO; LCD_TFT_CS_PORT &= ~LCD_TFT_CS_IO;}   

	//��������Ϊ"���" ,��"����"CS�����ź�(�����½���)
#define mTrigger_LCD_TFT_CS {LCD_TFT_CS_DIR |= LCD_TFT_CS_IO; LCD_TFT_CS_PORT |= LCD_TFT_CS_IO; LCD_TFT_CS_PORT &= ~LCD_TFT_CS_IO;} 

	//����"LCD_TFT_CS" ����Ϊ"����"
//#define mSetIn_LCD_TFT_CS (LCD_TFT_CS_DIR &= (~LCD_TFT_CS_IO))  



//--**PJ.0 ����: ����LCD_TFT��λ** ----------------------------------//
#define LCD_TFT_Reset_DIR  (PJDIR)  
#define LCD_TFT_Reset_PORT (PJOUT)
#define LCD_TFT_Reset_IO   (BIT0)

	//��������Ϊ"���",��"ʹ��"��λ����(��λ"��"��ƽ��Ч)
#define mOpen_LCD_TFT_Reset {LCD_TFT_Reset_DIR |= LCD_TFT_Reset_IO; LCD_TFT_Reset_PORT &= ~LCD_TFT_Reset_IO;}   

	//��������Ϊ"���",��"�ر�"��λ����
#define mClose_LCD_TFT_Reset {LCD_TFT_Reset_DIR |= LCD_TFT_Reset_IO; LCD_TFT_Reset_PORT |= LCD_TFT_Reset_IO;}   


//--**P3.7 ����: ����LCD_TFT����** ----------------------------------//
	//�������������ռ�ձȣ����Ա�������
#define LCD_TFT_BackLight_DIR  (P3DIR)  
#define LCD_TFT_BackLight_PORT (P3OUT)
#define LCD_TFT_BackLight_IO   (BIT7)

	//����: ����ߵ�ƽ(ռ�ձ�Ϊ100%)(��ʱ��������)
	//��������Ϊ"���",��"��"LCD_TFT����
#define mOpen_LCD_TFT_BackLight {LCD_TFT_BackLight_DIR |= LCD_TFT_BackLight_IO; LCD_TFT_BackLight_PORT |= LCD_TFT_BackLight_IO;}   

	//����: ����͵�ƽ(ռ�ձ�Ϊ  0%)(��ʱ����ر�)
	//��������Ϊ"���",��"�ر�"LCD_TFT����
#define mClose_LCD_TFT_BackLight {LCD_TFT_BackLight_DIR |= LCD_TFT_BackLight_IO; LCD_TFT_BackLight_PORT &= (~LCD_TFT_BackLight_IO);} 



////////////////////////////////////////////////////////////////////////////
//==**��Ƭ����������ָʾ��*IO��ʹ�ú궨��**=========//
//==**ϵͳ��������ʱ��ָʾ��ÿ250ms��һ��)**=========//

//--**P4.2  ����: ��Ƭ����������ָʾ��** ---------------------//
#define WORKING_LED_DIR  (P4DIR)  
#define WORKING_LED_PORT (P4OUT)
#define WORKING_LED_IO   (BIT2)
   
	 //��������Ϊ"���",��"��ת"�������״̬
#define mTurn_Working_Led  {WORKING_LED_DIR |= WORKING_LED_IO; WORKING_LED_PORT ^= WORKING_LED_IO;}              

	//��������Ϊ"���",��"����"����ָʾ��
#define mOpen_Working_Led  {WORKING_LED_DIR |= WORKING_LED_IO; WORKING_LED_PORT |= WORKING_LED_IO;}   

	//��������Ϊ"���",��"Ϩ��"����ָʾ��
#define mClose_Working_Led {WORKING_LED_DIR |= WORKING_LED_IO; WORKING_LED_PORT &= (~WORKING_LED_IO);} 


////////////////////////////////////////////////////////////////////////////
//==***LED���������**IO��ʹ�ú궨��**=================//

//--**P4.1  ����: LED_YELLOW** -------------------------------------------//
#define LED_YELLOW_DIR  (P4DIR)  
#define LED_YELLOW_PORT (P4OUT)
#define LED_YELLOW_IO   (BIT1)
	//��������Ϊ"���",��"����"LED_YELLOW
#define mOpen_LED_YELLOW  {LED_YELLOW_DIR |= LED_YELLOW_IO; LED_YELLOW_PORT |= LED_YELLOW_IO;}   
	//��������Ϊ"���",��"Ϩ��"LED_YELLOW
#define mClose_LED_YELLOW {LED_YELLOW_DIR |= LED_YELLOW_IO; LED_YELLOW_PORT &= (~LED_YELLOW_IO);} 
	 //��������Ϊ"���",��"��ת"�������״̬
#define mTurn_LED_YELLOW  {LED_YELLOW_DIR |= LED_YELLOW_IO; LED_YELLOW_PORT ^= LED_YELLOW_IO;}              


//--**P4.2  ����: LED_GREEN** -------------------------------------------//
#define LED_GREEN_DIR   (P4DIR)  
#define LED_GREEN_PORT  (P4OUT)
#define LED_GREEN_IO    (BIT2)
	//��������Ϊ"���",��"����"LED_GREEN
#define mOpen_LED_GREEN  {LED_GREEN_DIR |= LED_GREEN_IO; LED_GREEN_PORT |= LED_GREEN_IO;}   
	//��������Ϊ"���",��"Ϩ��"LED_GREEN
#define mClose_LED_GREEN {LED_GREEN_DIR |= LED_GREEN_IO; LED_GREEN_PORT &= (~LED_GREEN_IO);} 
	 //��������Ϊ"���",��"��ת"�������״̬
#define mTurn_LED_GREEN  {LED_GREEN_DIR |= LED_GREEN_IO; LED_GREEN_PORT ^= LED_GREEN_IO;}              


//--**P4.3  ����: LED_RED** -------------------------------------------//
#define LED_RED_DIR     (P4DIR)    
#define LED_RED_PORT    (P4OUT)
#define LED_RED_IO      (BIT3)
	//��������Ϊ"���",��"����"LED_RED
#define mOpen_LED_RED  {LED_RED_DIR |= LED_RED_IO; LED_RED_PORT |= LED_RED_IO;}   
	//��������Ϊ"���",��"Ϩ��"LED_RED
#define mClose_LED_RED {LED_RED_DIR |= LED_RED_IO; LED_RED_PORT &= (~LED_RED_IO);} 
	 //��������Ϊ"���",��"��ת"�������״̬
#define mTurn_LED_RED  {LED_RED_DIR |= LED_RED_IO; LED_RED_PORT ^= LED_RED_IO;}              





////////////////////////////////////////////////////////////////////////////
//==**��Ŀ"ר��"�궨��**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"��������**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"�ⲿ" API ��������**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////




#endif  /* __Hardware_Profile_H */






