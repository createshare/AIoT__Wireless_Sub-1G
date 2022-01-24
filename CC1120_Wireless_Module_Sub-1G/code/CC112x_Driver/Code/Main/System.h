/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 System.h
* �����ļ�-Dependencies:  	 None	
* �ļ�����-File Description:	 ( ͷ�ļ�-Header File )
	��"ϵͳ" ���ù��ܺ�����-ͷ�ļ�
	01)     02)     03)    04)    05)    06)	
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

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#ifndef __System_H
#define __System_H

#include "msp430f6638.h"   // "������"ͷ�ļ�: �ڲ��Ĵ���ض����(�������ڲ���Դ) 
#include "HAL_PMM.h"  //F5xx_F6xx_Core_Lib//ϵͳ��Դ����ģ��-ͷ�ļ� 
#include "HAL_UCS.h"  //F5xx_F6xx_Core_Lib//ϵͳʱ������-ͷ�ļ� 

#include "Hardware_Profile.h"  //������"Ӳ�������ļ�" -Hardware specific definitions for Processor

#include "Key.h"   //"IO ����" -��������(�ⲿ��Դ)-ͷ�ļ�




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
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern union FLAGBIT16 SystemFlagBits;	//ϵͳ��־λ����
#define  G_SystemFlagBits    SystemFlagBits.FLAG16  
#define	 F_10ms_TaskClock    SystemFlagBits.b.f0  //ϵͳ10ms��־λ//���ڳ�����ѭ������10ms    
#define	 F_250ms_Working_Led SystemFlagBits.b.f1 //���ڵ�Ƭ����������ʱ������ָʾ��һֱ��˸(250ms��˸һ��) 
//#define  F_            SystemFlagBits.b.f2    //Ϊ1ʱ��	  
//#define  F_	      SystemFlagBits.b.f3    //Ϊ1ʱ��
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



extern unsigned char G_TempChar;    //������ʱ�õ�"�ֽ�"����


////////////////////////////////////////////////////////////////////////////
//==**"�ⲿ" API ��������**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

extern void System_Initial(void);  //   ϵͳ��ʹ�� :��Ƭ���ڲ���Դ+�ⲿ������Դ�ĳ�ʹ�� 

extern void Osccon_Initial(void);  //�����ʼ������:������ؾ������

extern void  Timer2_Initial(void); //��ʱ��A2��ʼ������(����ϵͳÿ1ms�Զ��ж�һ��)

extern void System_10ms_Task(void);  //����ϵͳ��ʱ"10ms" �µ�������� 

extern void System_250ms_Task(void);  //����ϵͳ��ʱ"250ms" �µ��������

extern void System_GetLoopClockTick(void);  //ÿ��"����"��ʱ10ms��ϵͳ"ѭ��"ִ��һ�γ���

extern void System_Working_Led(void);  //��Ƭ����������ָʾ��: 250ms��˸һ��




extern void WaitingDelayMs(unsigned int TimeData);  //���ȴ���ʱx����

//��Cnt����ͬ��Data���ݸ��Ƶ�����Array[x]֮���Cnt��Ԫ��
extern void Sent_DataToArray(unsigned char *ArrayPoint,unsigned char DataValue,unsigned int Cnt);



#endif  /* __System_H */




