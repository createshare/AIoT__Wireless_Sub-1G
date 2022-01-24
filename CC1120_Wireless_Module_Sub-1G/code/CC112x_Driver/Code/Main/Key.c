/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 Key.c
* �����ļ�-Dependencies:  	 Key.h; System.h;
* �ļ�����-File Description:	 ( Դ����-Source File) 
	��  "IO ����" -��������(�ⲿ��Դ)
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


#include "System.h"	 //"ϵͳ" ���ù��ܺ�����-ͷ�ļ�

#include "Key.h"   //"IO ����" -��������(�ⲿ��Դ)-ͷ�ļ�



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
union FLAGBIT16 KeyFlagBits;  //�����õ��ı�־λ����



////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned char KeyValue = 0;  //�水�������İ���ֵ (����һ�㳣�õİ���)


unsigned char pKeyResult = 0;
unsigned char pKeyBuffer = 0;
unsigned char pKeyBuffer1 = 0;
unsigned char pKeyCnt = 0;     //����ʱ�������õļ�����
unsigned char pKeyNullCnt = 0; //����ʱ�������õļ�����

unsigned int  pLongKeyCnt = 0;  //����������.//ʱ��Ϊ10ms ("ѭ��"ִ��һ�γ���)




/****************************************************************************
*������-Function:	void Scan_Key(void)
*����- Description:	"IO�ڼ���"ɨ�裬1msɨ��һ�ΰ���(�ж���)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) ���ж���ɨ��
	��02)    ��03)    ��04)  
*****************************************************************************/
void Scan_Key(void)
{          

	mSetIn_Key_1_IO;  //����Key_1 ��IO��Ϊ"����"����
	mSetIn_Key_2_IO;  //����Key_2 ��IO��Ϊ"����"����

	pKeyResult = Key_IN;//����ֵIOֵ����

	pKeyResult = pKeyResult & M_KeyUsed;		
	
	if(pKeyResult != M_KeyUsed)         //�м�����
	{
		pKeyNullCnt = 0;  //����ʱ�������õļ�����
	
		F_KeyHave = 1; 
	} 
	else
	{
		F_KeyHave = 0;
		
		pKeyNullCnt ++;
		if(pKeyNullCnt >= M_KeyDelayTime)
		{
			pKeyNullCnt = 0;  //����ʱ�������õļ�����
			F_KeyNull = 1;

			pKeyBuffer = M_NullKey;  //��������������Ϊ��Ч����
			KeyValue = M_NullKey;  //��������������Ϊ��Ч����
		}
		
		pKeyCnt = 0;          //Լ20ms�����õ�
	}

	if(pKeyResult == 0x80) pKeyBuffer = 1;       //����1
	else if(pKeyResult == 0x40) pKeyBuffer = 2;  //����2

		 //��������İ�������Ϊ��Ч����//good,���õ���������ͬʱ���²���Ч�����,һ��Ҫ��������ĳ���else rKeyBuffer = M_NullKey; 
	else pKeyBuffer = M_NullKey; 


	if(F_KeyHave)
    {
		if(pKeyBuffer != pKeyBuffer1)
		{
			pKeyBuffer1 = pKeyBuffer;
			pKeyCnt = 0;
		}
		else
		{
			pKeyCnt++;
			if(pKeyCnt >= M_KeyDelayTime)   //(4+1)*5ms= 25ms  
			{
				pKeyCnt = 0;
				if(F_KeyNull)    //���ݱ�־λF_KeyNull��ʹ����ֻ���ٵ������ٰ�����Ч
				{
					KeyValue = pKeyBuffer;

					if(KeyValue != M_NullKey)
					{
						F_KeyRead = 1;
						
						F_KeyNull = 0;
						pKeyNullCnt = 0;  //����ʱ�������õļ�����
					}
				}
			}
		}

    }	

}




/****************************************************************************
*������-Function:	unsigned char Detect_Key_1(void)
*����- Description:	�����û�а���IO����"Key1"
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_Key_1(void)  
{	  
	unsigned char i;
	if(KeyValue == Key_1) 
	{
		KeyValue = M_NullKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*������-Function:	unsigned char Detect_Key_2(void)
*����- Description:	�����û�а���IO����"Key2"
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_Key_2(void)  
{	  
	unsigned char i;
	if(KeyValue == Key_2) 
	{
		KeyValue = M_NullKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return (i);
}



