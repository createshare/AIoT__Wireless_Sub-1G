/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 Key.c
* 附属文件-Dependencies:  	 Key.h; System.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■  "IO 按键" -驱动程序(外部资源)
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


#include "System.h"	 //"系统" 常用功能函数集-头文件

#include "Key.h"   //"IO 按键" -驱动程序(外部资源)-头文件



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
union FLAGBIT16 KeyFlagBits;  //按键用到的标志位定义



////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned char KeyValue = 0;  //存按键解码后的按键值 (对于一般常用的按键)


unsigned char pKeyResult = 0;
unsigned char pKeyBuffer = 0;
unsigned char pKeyBuffer1 = 0;
unsigned char pKeyCnt = 0;     //按下时，消抖用的计数器
unsigned char pKeyNullCnt = 0; //弹起时，消抖用的计数器

unsigned int  pLongKeyCnt = 0;  //长按计数器.//时基为10ms ("循环"执行一次程序)




/****************************************************************************
*函数名-Function:	void Scan_Key(void)
*描述- Description:	"IO口键盘"扫描，1ms扫描一次按键(中断里)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) 在中断里扫描
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Scan_Key(void)
{          

	mSetIn_Key_1_IO;  //设置Key_1 的IO口为"输入"引脚
	mSetIn_Key_2_IO;  //设置Key_2 的IO口为"输入"引脚

	pKeyResult = Key_IN;//按键值IO值更新

	pKeyResult = pKeyResult & M_KeyUsed;		
	
	if(pKeyResult != M_KeyUsed)         //有键按下
	{
		pKeyNullCnt = 0;  //弹起时，消抖用的计数器
	
		F_KeyHave = 1; 
	} 
	else
	{
		F_KeyHave = 0;
		
		pKeyNullCnt ++;
		if(pKeyNullCnt >= M_KeyDelayTime)
		{
			pKeyNullCnt = 0;  //弹起时，消抖用的计数器
			F_KeyNull = 1;

			pKeyBuffer = M_NullKey;  //按键弹起消抖后，为无效按键
			KeyValue = M_NullKey;  //按键弹起消抖后，为无效按键
		}
		
		pKeyCnt = 0;          //约20ms消抖用的
	}

	if(pKeyResult == 0x80) pKeyBuffer = 1;       //按键1
	else if(pKeyResult == 0x40) pKeyBuffer = 2;  //按键2

		 //其他情况的按键，作为无效按键//good,当用到两个按键同时按下才有效的情况,一定要加入下面的程序else rKeyBuffer = M_NullKey; 
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
				if(F_KeyNull)    //根据标志位F_KeyNull，使按键只有再弹开后，再按才有效
				{
					KeyValue = pKeyBuffer;

					if(KeyValue != M_NullKey)
					{
						F_KeyRead = 1;
						
						F_KeyNull = 0;
						pKeyNullCnt = 0;  //弹起时，消抖用的计数器
					}
				}
			}
		}

    }	

}




/****************************************************************************
*函数名-Function:	unsigned char Detect_Key_1(void)
*描述- Description:	检测有没有按下IO按键"Key1"
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_Key_1(void)  
{	  
	unsigned char i;
	if(KeyValue == Key_1) 
	{
		KeyValue = M_NullKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*函数名-Function:	unsigned char Detect_Key_2(void)
*描述- Description:	检测有没有按下IO按键"Key2"
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_Key_2(void)  
{	  
	unsigned char i;
	if(KeyValue == Key_2) 
	{
		KeyValue = M_NullKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return (i);
}



