/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 Key.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■ 具体项目: "IO 按键" -驱动程序-头文件(外部资源)
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


#ifndef  __Key_H 
#define  __Key_H 


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**键盘相关宏定义**================================//


#define M_KeyDelayTime  (20)      //用于调整按键灵敏度(即消抖时间)，以1ms为时基

	//用到P2.6 和P2.7，故为0xC0
#define M_KeyUsed       (0xC0)   //用于定义接8个按键，若定义为只使用第1,2个键时，则令 M_KeyUsed＝0x03 

#define M_NullKey       (0xFF)   //定义按键为无效键



////////////////////////////////////////////////////////////////////////////
//--**"矩阵按键值"宏定义**---------------------------------------//
////////////////////////////////////////////////////////////////////////////


#define Key_1      (1)    //定义"数字1键"
#define Key_2      (2)    //定义"数字2键"




////////////////////////////////////////////////////////////////////////////
//==***IO按键**IO口使用宏定义**=========================//

//--**P2.7 引脚:  Key_1 (IO 按键)** -------------------//
//--**P2.6 引脚:  Key_2 (IO 按键)**--------------------//

#define Key_DIR    (P2DIR)  
#define Key_IN     (P2IN)
#define Key_1_IO   (BIT7)
#define Key_2_IO   (BIT6)

#define mSetIn_Key_1_IO   (Key_DIR &= (~Key_1_IO)) //配置引脚为"输入"
#define mSetIn_Key_2_IO   (Key_DIR &= (~Key_2_IO)) //配置引脚为"输入"





////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////

extern union FLAGBIT16 KeyFlagBits; //按键用到的标志位定义
#define  G_KeyFlagBits	KeyFlagBits.FLAG16  
//#define	 F_ScanKey   KeyFlagBits.b.f0    
#define  F_KeyHave      KeyFlagBits.b.f1
#define  F_KeyRead	    KeyFlagBits.b.f2	
#define  F_KeyNull	    KeyFlagBits.b.f3	
#define  F_Ok_LongKey	KeyFlagBits.b.f4   //"确定键"长按标志位   
//#define   F_	KeyFlagBits.b.f5	
//#define  F_	KeyFlagBits.b.f6	
//#define  F_	KeyFlagBits.b.f7    
//#define   F_	KeyFlagBits.b.f8      
//#define   F_	KeyFlagBits.b.f9     
//#define   F_	KeyFlagBits.b.f10    
//#define   F_	KeyFlagBits.b.f11      
//#define   F_	KeyFlagBits.b.f12      
//#define   F_	KeyFlagBits.b.f13      
//#define   F_	KeyFlagBits.b.f14      
//#define   F_	KeyFlagBits.b.f15     




////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

extern void Scan_Key(void); // "IO口键盘"扫描，5ms扫描一次按键(中断里)


extern unsigned char Detect_Key_1(void);  //检测有没有按下IO按键"Key1"

extern unsigned char Detect_Key_2(void);  //检测有没有按下IO按键"Key2" 


#endif   /* __Key_H  */





