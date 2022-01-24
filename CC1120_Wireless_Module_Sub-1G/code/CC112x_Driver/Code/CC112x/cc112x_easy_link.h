/******************************************************************************
    Filename: cc112x_easy_link.h  
    
    Description: Template for CC112x register export from SmartRF Studio 
                 
*******************************************************************************/
#ifndef CC112X_EASY_LINK_H
#define CC112X_EASY_LINK_H

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
 * INCLUDES
 */
#include "hal_spi_rf_trxeb.h"
#include "cc112x_spi.h"
  
/******************************************************************************
 * FUNCTIONS
 */  



/*************************************************************
01. Æµ¶ÎÑ¡ÔñBand Select = 410.0 - 480.0 MHzÆµ¶Î
02. ÔØ²¨ÆµÂÊCarrier frequency = 434.000000  MHz
03. ·ûºÅËÙÂÊSymbol rate = 1.2  ksps
04. Êý¾ÝËÙÂÊBit rate = 1.2  kbps
05. ·¢Éä¹¦ÂÊTX power = 15 dBm
06. ½ÓÊÕÂË²¨Æ÷ÅäÖÃRX filter BW = 25.000000 KHz
07. ÆµÂÊÆ«²îDeviation = 3.997803  KHz
08. µ÷ÖÆ¸ñÊ½Modulation format = 2-FSK 
09. Âü³¹Ë¹ÌØÊ¹ÄÜManchester enable = ½ûÓÃ 
10. Êý¾Ý°×»¯Whitening =  ½ûÓÃ 
11. Êý¾Ý°ü³¤¶ÈÄ£Ê½Packet length mode = ¿É±äÊý¾Ý°ü³¤¶ÈÄ£Ê½(Í¬²½×ÖºóÊÕµ½µÄµÚÒ»¸ö×Ö½ÚÎªÊý¾Ý°ü³¤¶ÈÅäÖÃ)
12. Êý¾Ý°ü³¤¶ÈPacket length = 255 ¸ö×Ö½Ú
13. ¹¦ÂÊ·Å´óPA ramping = Ê¹ÄÜ 
14. µØÖ·¼ì²éÊ¹ÄÜAddress Check = ½ûÓÃ
15. Éè±¸µØÖ·Device address = 0 
16. GPIO3Òý½Å=ÅäÖÃÎªÊý¾Ý°ü·¢ËÍ/½ÓÊÕ³É¹¦µÄÖ¸Ê¾Òý½Å
*************************************************************/



static const registerSetting_t preferredSettings[]= 
{  
//IOCFG3 -GPIO3Òý½ÅÅäÖÃ//¸´Î»Öµ=0x06 (¸´Î»Ê±Ñ¡"PKT_SYNC_RXTX" )
	//GPIO3_ATRAN Ä£Äâ´«ÊäÊ¹ÄÜ= 0=Ñ¡Ôñ±ê×¼Êý×ÖGPIO
	//GPIO3_INV ·´×ªÊä³öÊ¹ÄÜ= 0=½ûÖ¹Êä³ö·´×ª
	//GPIO3_CFG Êä³öÑ¡Ôñ= 000110=Ñ¡"PKT_SYNC_RXTX" =CC1120·¢ËÍ/½ÓÊÕµ½Í¬²½×ÖÊ±ÖÃÎ»£¬²¢ÔÚÊý¾Ý°üµÄÄ©Î²È¡ÏûÖÃÎ»¡£
	{CC112X_IOCFG3,            0x06}, 

//IOCFG2 -GPIO2Òý½ÅÅäÖÃ//¸´Î»Öµ=0x07(¸´Î»Ê±Ñ¡"PKT_CRC_OK" )
	//GPIO2_ATRAN Ä£Äâ´«ÊäÊ¹ÄÜ= 1=½ûÓÃÊý×ÖGPIO
	//GPIO2_INV ·´×ªÊä³öÊ¹ÄÜ= 0=½ûÖ¹Êä³ö·´×ª
	//GPIO2_CFG Êä³öÑ¡Ôñ= 110000=Ñ¡"HIGHZ" =  ¸ß×è¿¹£¨ÈýÌ¬£©
	{CC112X_IOCFG2,            0xB0},
	
//IOCFG1 -GPIO1Òý½ÅÅäÖÃ//¸´Î»Öµ=0x30(¸´Î»Ê±Ñ¡"HIGHZ"=  ¸ß×è¿¹ )
//×¢Òâ£ºGPIO1ÓëSPIµÄMISOÒý½Å¸´ÓÃ¡£µ±CSnÓÐÐ§£¨µÍµçÆ½£©£¬GPIO1×÷ÎªMISOÊä³öÒý½Å¡£
//×¢Òâ£ºÏµÍ³±ØÐëÍ¨¹ýÈí¼þ»òÓ²¼þÈ·±£ MISOÒý½ÅÉÏÀ­¡£
	//GPIO1_ATRAN Ä£Äâ´«ÊäÊ¹ÄÜ= 1=½ûÓÃÊý×ÖGPIO
	//GPIO1_INV ·´×ªÊä³öÊ¹ÄÜ= 0=½ûÖ¹Êä³ö·´×ª
	//GPIO1_CFG Êä³öÑ¡Ôñ= 110000=Ñ¡"HIGHZ" =  ¸ß×è¿¹£¨ÈýÌ¬£©
	{CC112X_IOCFG1,            0xB0},

//IOCFG0 -GPIO0Òý½ÅÅäÖÃ//¸´Î»Öµ=0x3C(¸´Î»Ê±Ñ¡"EXT_OSC_EN"=  Ê¹ÄÜÍâ²¿Õñµ´Æ÷ )
	//GPIO0_ATRAN Ä£Äâ´«ÊäÊ¹ÄÜ= 1=½ûÓÃÊý×ÖGPIO
	//GPIO0_INV ·´×ªÊä³öÊ¹ÄÜ= 0=½ûÖ¹Êä³ö·´×ª
	//GPIO0_CFG Êä³öÑ¡Ôñ= 110000=Ñ¡"HIGHZ" =  ¸ß×è¿¹£¨ÈýÌ¬£©
	{CC112X_IOCFG0,            0xB0},

//SYNC0 ~ SYNC3-32Î»Í¬²½×Ö
	{CC112X_SYNC3,             0xD3},//SYNC3 //¸´Î»Öµ=0x93
	{CC112X_SYNC2,             0x91},//SYNC2 //¸´Î»Öµ=0x0B
	{CC112X_SYNC1,             0xD3},//SYNC1 //¸´Î»Öµ=0x51
	{CC112X_SYNC0,             0x91},//SYNC0 //¸´Î»Öµ=0xDE
	
//SYNC_CFG1-Í¬²½×Ö¼ì²âÅäÖÃ//¸´Î»Öµ=0x0A
	//DEM_CFG Ç°µ¼ÖÊÁ¿ãÐÖµÊ¹ÄÜÎ» =000=½ûÓÃÇ°µ¼ÖÊÁ¿ãÐÖµ (PQT),
	//SYNC_THR Èí¼þÉèÖÃµÄÍ¬²½×ÖãÐÖµ=0x0B¡£
	{CC112X_SYNC_CFG1,         0x0B},
	
//care--Î´³õÊ¼»¯//SYNC_CFG0 - Í¬²½×Ö³¤¶ÈÅäÖÃ//¸´Î»Öµ=0x17H
	//SYNC_MODE Í¬²½×Ö³¤¶ÈÅäÖÃ=101=Ñ¡Ôñ32Í¬²½×Ö//32 bits
	//SYNC_NUM_ERROR Î»Í¬²½×Ö¼ì²é=11=½ûÓÃÎóÂëÏÞ¶¨·û¡£ÎÞÐ£ÑéÎ»´íÎó  //Bit Error Qualifier disabled. No check on bit errors

//care--Î´³õÊ¼»¯//DEVIATION_M -ÆµÂÊÆ«²îÅäÖÃ//¸´Î»Öµ=0x06
	//ÆµÂÊÆ«²î£¨Î²ÊýµÄÒ»²¿·Ö£©DEV_M  = 0x06

//care--Î´³õÊ¼»¯//MODCFG_DEV_E-µ÷ÖÆ¸ñÊ½ºÍÆµÂÊÆ«²îÅäÖÃ//¸´Î»Öµ=0x03
	//MODEM_MODE µ÷ÖÆ½âµ÷Æ÷Ä£Ê½ÅäÖÃ= 00 =ÆÕÍ¨Ä£Ê½
	//MOD_FORMAT µ÷ÖÆ¸ñÊ½=000= "2-FSK"    //001=2-GFSK //010=Reserved //011=ASK/OOK //100=4-FSK //101=4-GFSK //110=SC-MSK unshaped (CC1125, TX only). For CC1120, CC1121, and CC1175this setting is reserved  //111=SC-MSK shaped (CC1125, TX only). For CC1120, CC1121, and CC1175 thissetting is reserved
	//DEV_E  ÆµÂÊÆ«²î£¨Ö¸Êý²¿·Ö£©= 011
		//¨ˆ¡ïµ÷ÖÆ¸ñÊ½ = "2-FSK"
		//¨ˆ¡ïÆµÂÊÆ«²î Deviation = 3.997803

//DCFILT_CFG-Êý×ÖÖ±Á÷È¥³ýÅäÖÃ//¸´Î»Öµ=0x4C
	//DCFILT_FREEZE_COEFF Ö±Á÷ÂË²¨Æ÷¸²¸Ç=0 =Ö±Á÷ÂË²¨Ëã·¨¹À¼ÆºÍ²¹³¥Ö±Á÷Îó²î
	//DCFILT_BW_SETTLE AGCµ÷ÕûºóµÄÎÈ¶¨ÆÚ=011=256 samples
	//DCFILT_BW Ö±Á÷ÂË²¨Æ÷´ø¿í= 100;
	{CC112X_DCFILT_CFG,        0x1C},
									
//PREAMBLE_CFG1-Ç°µ¼Âë³¤¶ÈÅäÖÃ//¸´Î»Öµ=00010100
	//NUM_PREAMBLE ÉèÖÃÒª±»·¢ËÍµÄÇ°µ¼Î»µÄ×îÐ¡ÊýÄ¿= 0110 = 4×Ö½Ú
	//PREAMBLE_WORD Ç°µ¼Âë×Ö½ÚÅäÖÃ= 00 = Ñ¡Ôñ10101010 (0xAA)
	{CC112X_PREAMBLE_CFG1,     0x18},

//care--Î´³õÊ¼»¯//PREAMBLE_CFG0-Ç°µ¼Âë³¤¶ÈÅäÖÃ//¸´Î»Öµ=00101010
	//PQT_EN Ç°µ¼Âë¼ì²âÊ¹ÄÜÎ» = 1=Ê¹ÄÜÇ°µ¼Âë¼ì²â
	//PQT_VALID_TIMEOUT PQTÆô¶¯¶¨Ê±Æ÷  = 0=16¸öÂëÔª
	//PQT  Èí¼þÉèÖÃPQT   (Ç°µ¼ÖÊÁ¿ãÐÖµ)= 0x0A  

//care--Î´³õÊ¼»¯//FREQ_IF_CFG-RX»ìÆµÆ÷ÆµÂÊÅäÖÃ//¸´Î»Öµ=0x40
	//FREQ_IF Êý×Ö½ÓÊÕ»ú»ìÆµÆ÷ÆµÂÊ=0x40

//IQIC-Êý×ÖÍ¼ÏñÐÅµÀ²¹³¥ÅäÖÃ//¸´Î»Öµ=11000100
	//IQIC_EN  IQÍ¼Ïñ²¹³¥Ê¹ÄÜÎ»=1=ÆôÓÃÍ¼Ïñ²¹³¥
	//IQIC_UPDATE_COEFF_EN  IQIC¸üÐÂÏµÊýÊ¹ÄÜ = 1=Ê¹ÄÜIQICÏµÊý¸üÐÂ£¨¸üÐÂIQIE_I1 IQIE_I0£¬IQIE_Q1£¬IQIE_Q0¼Ä´æÆ÷£©
	//IQIC_BLEN_SETTLE  ÎÈ¶¨Ê±£¬IQIC¿é³¤¶ÈÖµ=00=8¸öÑù±¾
	//IQIC_BLEN  IQIC¿é³¤¶ÈÖµ=01=32¸öÑù±¾
	//IQIC_IMGCH_LEVEL_THR   IQICÍ¼ÏñÐÅµÀµçÆ½ãÐÖµ=10=Ñ¡Ôñ¡°>1024¡±
	{CC112X_IQIC,              0xC6},

//CHAN_BW-ÐÅµÀÂË²¨Æ÷ÅäÖÃ//¸´Î»Öµ=0x14
	//CHFILT_BYPASS  ÐÅµÀÂË²¨Æ÷ÅÔÂ· =0=Ê¹ÄÜÐÅµÀÂË²¨Æ÷£¨²»ÅÔÂ·£©
	//ADC_CIC_DECFACT  µÚÒ»¸ö³éÈ¡Òò×ÓÑ¡ÔñÎ»=0=³éÈ¡Òò×ÓÎª20
	//BB_CIC_DECFACT  µÚ¶þ¸ö³éÈ¡Òò×ÓÑ¡ÔñÎ»= 001000=×îÐ¡RXÂË²¨Æ÷´ø¿íBWÎª8KHz
		//¨ˆ¡ï"RX filter BW = 25KHz"
	{CC112X_CHAN_BW,           0x08},  

//care--Î´³õÊ¼»¯//MDMCFG1-Í¨ÓÃµ÷ÖÆ½âµ÷Æ÷²ÎÊýÅäÖÃ//¸´Î»Öµ=01000110
	//CARRIER_SENSE_GATE  Í¬²½×ÖËÑË÷ÅäÖÃ= 0=Í¬²½×ÖËÑË÷£¬ÎÞÂÛCSÎªÊ²Ã´×´Ì¬
	//FIFO_EN  FIFOÊ¹ÄÜ =1=Êý¾ÝÊäÈë/Êä³öÍ¨¹ýFIFO
	//MANCHESTER_EN  Âü³¹Ë¹ÌØÊ¹ÄÜ= 0=NRZ£¨²»Ê¹ÄÜ£©
	//INVERT_DATA_EN  Êý¾Ý·´×ªÊ¹ÄÜ=0=½ûÖ¹Êý¾Ý·´×ª
	//COLLISION_DETECT_EN  ³åÍ»¼ì²âÊ¹ÄÜ=0=½ûÓÃ³åÍ»¼ì²â
	//DVGA_GAIN  ¹Ì¶¨DVGAÔöÒæÅäÖÃ=11=9 dB DVGA
	//SINGLE_ADC_EN  ÅäÖÃ»î¶¯µÄ½ÓÊÕÐÅµÀµÄÊýÁ¿=0=IQ-ÐÅµÀ
		//¨ˆ¡ï½ûÓÃÂü³¹Ë¹ÌØ
	
//MDMCFG0-Í¨ÓÃµ÷ÖÆ½âµ÷Æ÷²ÎÊýÅäÖÃ//¸´Î»Öµ=00001101
	//TRANSPARENT_MODE_EN  Í¸Ã÷Ä£Ê½Ê¹ÄÜ=0=½ûÓÃÍ¸Ã÷Ä£Ê½Ê¹ÄÜ
	//TRANSPARENT_INTFACT  Í¸Ã÷ÐÅºÅ²åÖµÒò×Ó=00=1*Í¸Ã÷ÐÅºÅ²åÖµÊä³öÇ°Ò»´Î£¨¸´Î»£©//00    1x transparent signal interpolated one time before output (reset)
	//DATA_FILTER_EN  Í¸Ã÷µÄÊý¾Ý¹ýÂËºÍÀ©Õ¹Êý¾Ý¹ýÂËÊ¹ÄÜ=0=½ûÖ¹Í¸Ã÷Êý¾Ý¹ýÂËºÍ½ûÓÃÀ©Õ¹µÄÊý¾Ý¹ýÂËÆ÷
	//VITERBI_EN Î¬ÌØ±È¼ì²âÊ¹ÄÜ=1=Ê¹ÄÜÊ¹ÄÜ=1=Ê¹ÄÜ
	//MDMCFG0_RESERVED1_0  =01=½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµ´Ó"SmartRF"Ì×¼þ
	{CC112X_MDMCFG0,           0x05},

//care--Î´³õÊ¼»¯//DRATE2-Êý¾ÝËÙÂÊÅäÖÃÖ¸ÊýºÍÎ²Êý//¸´Î»Öµ=0x43
	//DATARATE_E  Êý¾ÝËÙÂÊ£¨Ö¸Êý²¿·Ö£©=0100=0x04
	//DATARATE_M_19_16  Êý¾ÝÂÊ£¨Î²Êý²¿·Ö[19-16Î»]£©=0011

//care--Î´³õÊ¼»¯//DRATE1-Êý¾ÝËÙÂÊÅäÖÃÎ²Êý[15:8]//¸´Î»Öµ=0xA9
	//DATARATE_M_15_8  Êý¾ÝËÙÂÊÅäÖÃÎ²Êý[15:8] = 0xA9

//care--Î´³õÊ¼»¯//DRATE0-Êý¾ÝËÙÂÊÅäÖÃÎ²Êý[7:0]//¸´Î»Öµ=0x2A
	//DATARATE_M_7_0   Êý¾ÝËÙÂÊÅäÖÃÎ²Êý[7:0]  =0x2A
		//¨ˆ¡ïÊý¾ÝËÙÂÊ=1.2 kbps

//AGC_REF-AGC²Î¿¼µçÆ½ÅäÖÃ//¸´Î»Öµ=0x36
	//AGC_REFERENCE  AGC²Î¿¼µçÆ½= 0x20      //AGC: ×Ô¶¯ÔöÒæ¿ØÖÆ
	{CC112X_AGC_REF,           0x20},

//AGC_CS_THR-ÔØ²¨¼ì²âãÐÖµÅäÖÃ//¸´Î»Öµ=0x00
	//AGC_CS_THRESHOLD   AGCÔØ²¨¼ì²âãÐÖµ= 0x19    //AGC: ×Ô¶¯ÔöÒæ¿ØÖÆ
	{CC112X_AGC_CS_THR,        0x19},

//care--Î´³õÊ¼»¯//AGC_GAIN_ADJUST-RSSIÆ«ÒÆÅäÖÃ//¸´Î»Öµ=0x00
	//GAIN_ADJUSTMENT  AGCÔöÒæµ÷Õû= 0x00     //AGC: ×Ô¶¯ÔöÒæ¿ØÖÆ

//care--Î´³õÊ¼»¯//AGC_CFG3-AGCÅäÖÃ//¸´Î»Öµ=10010001
	//RSSI_STEP_THR = 1=RSSIãÐÖµÊÇ6 dB (RSSI :½ÓÊÕÐÅºÅÇ¿¶ÈÖ¸Ê¾)
	//AGC_ASK_BW  =00=ÎÞÊý¾Ý¹ýÂËÆ÷
	//AGC_MIN_GAIN  AGC×îÐ¡ÔöÒæ=0x11
	
//care--Î´³õÊ¼»¯//AGC_CFG2-AGCÅäÖÃ//¸´Î»Öµ=00100000
	//START_PREVIOUS_GAIN_EN  = 0 =ÒÔ×î´óÔöÒæÖµ¿ªÊ¼½ÓÊÕ
	//FE_PERFORMANCE_MODE  Ñ¡ÔñÓ¦ÓÃµÄÔöÒæ±í=01=Õý³£²Ù×÷Ä£Ê½
	//AGC_MAX_GAIN   AGC  ×î´óÔöÒæ = 00000

//AGC_CFG1-AGCÅäÖÃ//¸´Î»Öµ=10101010=0xAA
	//AGC_SYNC_BEHAVIOR  AGCÍ¬²½×Ö¼ì²âºóµÄ²Ù×÷ = 101=Í¬Ê±¶³½áAGCÔöÒæºÍRSSI
	//AGC_WIN_SIZE  AGC»ý·Ö´°¿ÚÖÐµÄÃ¿Ò»¸öÖµµÄ´óÐ¡ = 010=32¸öÑù±¾
	//AGC_SETTLE_WAIT  ÉèÖÃAGCÔöÒæµ÷ÕûÖ®¼äµÄµÈ´ýÊ±¼ä = 01=32¸öÑù±¾
	{CC112X_AGC_CFG1,          0xA9},

//AGC_CFG0-AGCÅäÖÃ//¸´Î»Öµ=11000011=0xC3
	//AGC_HYST_LEVEL  AGC³ÙÖÍµÈ¼¶ = 11=10 dB
	//AGC_SLEWRATE_LIMIT  AGCÐ±ÂÊÏÞÖÆ= 00= 60 dB
	//RSSI_VALID_CNT  ÊäÈëµ½Æ½¾ùÂË²¨Æ÷µÄÑù±¾Êý= 11=9
	//AGC_ASK_DECAY  ÔÚASK/ OOKÄ£Ê½,¿ØÖÆË¥¼õ²½Öè = 11=1/128 IIRË¥¼õ
	{CC112X_AGC_CFG0,          0xCF},

//FIFO_CFG-FIFOÅäÖÃ//¸´Î»Öµ=0x80
	//CRC_AUTOFLUSH  = 0= Èç¹ûÒ»¸öCRC´íÎó·¢Éú£¬×Ô¶¯Ë¢ÐÂRX FIFOÖÐ×îºóÊÕµ½µÄÊý¾Ý°ü¡£Èç¹û¸ÃÎ»±»¹Ø±Õ£¬Ó¦ÔÙ´Î´ò¿ª£¬±ØÐëÏÈ·¢Ò»¸öSFRXÑ¡Í¨ÐÅºÅ
	//FIFO_THR  RXºÍTX FIFOµÄãÐÖµ = 0x00=´ïµ½ãÐÖµÊ±£¬FIFO_THR= 0±íÊ¾TX FIFOÖÐÓÐ127×Ö½Ú£¬RX FIFOÖÐÓÐ1¸ö×Ö½Ú£»¶øFIFO_THR= 127 ±íÊ¾TX FIFOÖÐÓÐ0×Ö½Ú£¬RX FIFOÓÐ128×Ö½Ú¡£
	{CC112X_FIFO_CFG,          0x00},

//care--Î´³õÊ¼»¯//DEV_ADDR-Éè±¸µØÖ·ÅäÖÃ//¸´Î»Öµ=0x00
	//DEVICE_ADDR  Éè±¸µØÖ·=0x00=ÔÚ½ÓÊÕÊý¾Ý°ü¹ýÂËÊ±Ê¹ÓÃµÄµØÖ·
		//¨ˆ¡ïÉè±¸µØÖ·=0x00

//SETTLING_CFG-//¸´Î»Öµ=00001011
	//FS_AUTOCAL   ×Ô¶¯½øÐÐÐ£×¼=00= ´Ó²»£¨ÊÖ¶¯Ð£×¼Ê¹ÓÃSCALÑ¡Í¨ÐÅºÅ£©
	//LOCK_TIME  ÉèÖÃµÄÆµÂÊºÏ³ÉÆ÷£¬ÒÔ½â¾öËø¶¨×´Ì¬µÄÊ±¼ä= 01=  75/30 ¦Ìs
	//FSREG_TIME ÆµÂÊºÏ³ÉÆ÷µÄÎÈ¶¨Ê±¼ä£¨Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ£©= 1 = 60 ¦Ìs
	{CC112X_SETTLING_CFG,      0x03},

//FS_CFG-ÆµÂÊºÏ³ÉÆ÷µÄÅäÖÃ//¸´Î»Öµ=0x02
	//FS_LOCK_EN  Êä³öËø¶¨¼ì²âÊ¹ÄÜ= 0 = ½ûÓÃÊä³öËø¶¨¼ì²â
	//FSD_BANDSELECT  Æµ¶ÎÑ¡ÔñÉèÖÃLO·ÖÆµÆ÷ = 0100 = 410.0 - 480.0 MHzÆµ¶Î£¨LO·ÖÆµÆ÷= 8£©//0010=820.0 - 960.0 MHz band //100=410.0 - 480.0 MHz band //0110=273.3 - 320.0 MHz band //1000=205.0 - 240.0 MHz band //1010=164.0 - 192.0 MHz band //1011=136.7 - 160.0 MHz band 
		//¨ˆ¡ïÆµ¶ÎÑ¡Ôñ= 410.0 - 480.0 MHzÆµ¶Î£¨LO·ÖÆµÆ÷= 8£© //Frequency Synthesizer Configuration
	{CC112X_FS_CFG,            0x04},
		

//care--Î´³õÊ¼»¯//WOR_CFG1-eWORÅäÖÃ//¸´Î»Öµ=00001000
	//WOR_RES    eWOR¶¨Ê±Æ÷·Ö±æÂÊ= 00 =¸ß·Ö±æÂÊ
	//WOR_MODE   eWOR Ä£Ê½= 001 = Õý³£Ä£Ê½
	//EVENT1   ÊÂ¼þ1³¬Ê± = 000 =4

//care--Î´³õÊ¼»¯//WOR_CFG0-eWORÅäÖÃ//¸´Î»Öµ=00100001
	//DIV_256HZ_EN   Ê±ÖÓ·ÖÆµÊ¹ÄÜ(ÔÚË¯ÃßÄ£Ê½ÏÂÆôÓÃÊ±ÖÓ·ÖÆµ) = 1 = ÆôÓÃÊ±ÖÓ·ÖÆµ
	//EVENT2_CFG      ÊÂ¼þ2³¬Ê± = 00 =½ûÓÃ
	//RC_MODE  RCOSCÐ£×¼Ä£Ê½ = 00 = ½ûÓÃRCOSCÐ£×¼
	//RC_PD   RCOSCµôµçÐÅºÅÎ» = 1 =RCOSCÊÇÔÚµôµç×´Ì¬

//care--Î´³õÊ¼»¯//WOR_EVENT0_MSB-ÊÂ¼þ0ÅäÖÃ//¸´Î»Öµ=0x00
	//EVENT0_15_8   ÊÂ¼þ0³¬Ê±£¨MSB£©= 0x00

//care--Î´³õÊ¼»¯//WOR_EVENT0_LSB-ÊÂ¼þ0ÅäÖÃ//¸´Î»Öµ=0x00
	//EVENT0_7_0    ÊÂ¼þ0³¬Ê±£¨LSB£©= 0x00

//PKT_CFG2-°üÅäÖÃ//¸´Î»Öµ=00000100
	//PKT_CFG2_RESERVED5  = 0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	//CCA_MODE   CCAÄ£Ê½= 000 = ×ÜÊÇ¸øÒ»¸öÃ÷È·µÄÐÅµÀÖ¸Ê¾
	//PKT_FORMAT  Êý¾Ý°ü¸ñÊ½ÅäÖÃ = 00=Õý³£Ä£Ê½/ FIFOÄ£Ê½£¨MDMCFG1.FIFO_EN±ØÐëÉèÖÃÎª1ºÍMDMCFG0.TRANSPARENT_MODE_EN±ØÐëÉèÖÃÎª0£©
	{CC112X_PKT_CFG2,          0x00},

//care--Î´³õÊ¼»¯//PKT_CFG1-°üÅäÖÃ//¸´Î»Öµ=00000101
	//WHITE_DATA   °×»¯Ê¹ÄÜ = 0 =½ûÓÃÊý¾Ý°×»¯
	//ADDR_CHECK_CFG    µØÖ·¼ì²éÅäÖÃ = 00=ÎÞµØÖ·¼ì²é
	//CRC_CFG   CRCÅäÖÃ = 01 = TXÄ£Ê½Ê±£¬¼ÆËãCRC£»ÔÚRXÄ£Ê½£¬¼ì²éCRC
	//BYTE_SWAP_EN   TX/ RXÊý¾Ý×Ö½Ú½»»»Ê¹ÄÜ= 0 = ½ûÓÃ£º×Ö½ÚµÄÊý¾Ý½»»»
	//APPEND_STATUS   ¸½¼Ó×´Ì¬×Ö½Úµ½RX FIFOÊ¹ÄÜ= 1 =¸½¼Ó×´Ì¬×Ö½Ú
		//¨ˆ¡ï½ûÓÃÊý¾Ý°×»¯     
		//¨ˆ¡ïÎÞµØÖ·¼ì²é     
		//¨ˆ¡ïCRCÅäÖÃ = 01 = TXÄ£Ê½Ê±£¬¼ÆËãCRC£»ÔÚRXÄ£Ê½£¬¼ì²éCRC

//PKT_CFG0-°üÅäÖÃ//¸´Î»Öµ=0x00
	//PKT_CFG0_RESERVED7  = 0 //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	//LENGTH_CONFIG  Êý¾Ý°ü³¤¶ÈÅäÖÃ= 01=¿É±äÊý¾Ý°ü³¤¶ÈÄ£Ê½¡£Í¬²½×ÖºóÊÕµ½µÄµÚÒ»¸ö×Ö½ÚÎªÊý¾Ý°ü³¤¶ÈÅäÖÃ //00¹Ì¶¨Êý¾Ý°ü³¤¶ÈÄ£Ê½¡£Êý¾Ý°ü³¤¶ÈÍ¨¹ýPKT_LEN¼Ä´æÆ÷ÅäÖÃ
	//PKT_BIT_LEN = 000  //ÓÃÔÚ¹Ì¶¨Êý¾Ý°ü³¤¶ÈÄ£Ê½£ºPKT_BIT_LEN£¨²»ÎªÁã£©±íÊ¾ÊýÎ»·¢ËÍ/½ÓÊÕµÄPKT_LENµÄ×Ö½ÚÊý¡£
	//UART_MODE_EN  UARTÄ£Ê½Ê¹ÄÜ= 0=½ûÓÃUARTÄ£Ê½  //1=Ê¹ÄÜUARTÄ£Ê½¡£µ±ÆôÓÃÊ±£¬Êý¾Ý°üÒýÇæ½«²åÈë/É¾³ý¿ªÊ¼ºÍÍ£Ö¹Î»/·¢ËÍ/½ÓÊÕµÄ×Ö½Ú
	//UART_SWAP_EN   Æô¶¯ºÍÍ£Ö¹Î»Öµ»¥»»Ê¹ÄÜ = 0=½ûÓÃ½»»»¡£Æô¶¯/Í£Ö¹Î»ÖµÊÇ'1'/'0'
		//¨ˆ¡ï¿É±äÊý¾Ý°ü³¤¶ÈÄ£Ê½¡£Í¬²½×ÖºóÊÕµ½µÄµÚÒ»¸ö×Ö½ÚÎªÊý¾Ý°ü³¤¶ÈÅäÖÃ 
	{CC112X_PKT_CFG0,          0x20}, 

//care--Î´³õÊ¼»¯//RFEND_CFG1 -RFENDÅäÖÃ//¸´Î»Öµ=00001111
	//RXOFF_MODE  RXOFFÄ£Ê½= 00=¿ÕÏÐ  //01= FSTXON //10=TX //11=RX  //ÔÚÐ¾Æ¬½ÓÊÕµ½Á¼ºÃµÄÊý¾Ý°üºó£¬¾ö¶¨CC1120½«½øÈëÊ²Ã´×´Ì¬¡£
	//RX_TIME  RXÔÚRXÍ¬²½×ÖËÑË÷³¬Ê±ÅäÖÃ= 111
	//RX_TIME_QUAL  RX³¬Ê±ÏÞ¶¨·û= 1= Èç¹ûÃ»ËÑË÷µ½Í¬²½×Ö£¬»ò´ïµ½PQT£¬»òCSÓÐÐ§Ê±£¬ÔÚRX³¬Ê±£¬¼ÌÐø¹¤×÷ÔÚRXÄ£Ê½

//care--Î´³õÊ¼»¯//RFEND_CFG0 -RFENDÅäÖÃ//¸´Î»Öµ=0x00
	//CAL_END_WAKE_UP_EN  Ð£×¼½áÊø¸½¼ÓµÄ»½ÐÑÂö³åÊ¹ÄÜ = 0 =½ûÖ¹¸½¼ÓµÄ»½ÐÑÂö³å
	//TXOFF_MODE   TXOFFÄ£Ê½ =00=¿ÕÏÐ  //01=FSTXON //10=TX //11=RX
	//TERM_ON_BAD_PACKET_EN	ÖÕÖ¹´íÎóµÄÊý¾Ý°üÊ¹ÄÜ =0=½ûÓÃÖÕÖ¹»µ°ü¡£µ±Ò»¸ö´íÎóµÄÊý¾Ý°ü±»½ÓÊÕ£¨µØÖ·£¬³¤¶È»òCRCÓÐ´íÎó£©Ê±£¬ÎÞÏßÐ¾Æ¬½øÈë×´Ì¬ÓÉRFEND_CFG1.RXOFF_MODEÈ·¶¨
	//ANT_DIV_RX_TERM_CFG   Ö±½ÓRXÖÕÖ¹ºÍÌìÏß·Ö¼¯ÅäÖÃ= 000=½ûÓÃ£ºÓÉCS/ PQT¾ö¶¨µÄÌìÏß·Ö¼¯ºÍÖÕÖ¹¹¦ÄÜ

//care--Î´³õÊ¼»¯//PA_CFG2 -¹¦ÂÊ·Å´óÆ÷ÅäÖÃ//¸´Î»Öµ=01111111
	//PA_CFG2_RESERVED6  = 1  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	//PA_POWER_RAMP   PA¹¦ÂÊÐ±ÆÂÄ¿±êË®Æ½=111111  //´ËÊ±Êä³ö¹¦ÂÊ=£¨PA_POWER_RAMP+1£©/2  -18 = 14   //0x7F=·¢Éä¹¦ÂÊ15dBm //0x7D=14dBm //0x7B=13dBm //0x79=12dBm  //0x77=11dBm //0x74=10dBm  //0x72=9dBm //0x6F=8dBm   //0x6D=7dBm //0x6B=6dBm   //0x69=5dBm //0x66=4dBm   //0x64=3dBm //0x62=2dBm   //0x5F=1dBm //0x5D=0dBm   //0x56=-3dBm //0x4F=-6dBm //0x43=-11dBm
		//¨ˆ¡ïµ±PA_CFG2=0x7F£¬¶ÔÓ¦µÄ·¢Éä¹¦ÂÊ TX power=15dB 
		
//care--Î´³õÊ¼»¯//PA_CFG1 -¹¦ÂÊ·Å´óÆ÷ÅäÖÃ//¸´Î»Öµ=01010110
	//FIRST_IPL = 010=µÚÒ»ÖÐ¼ä¹¦ÂÊµÈ¼¶¡£µÚÒ»ÖÐ¼ä¹¦ÂÊµÈ¼¶£¬¿ÉÒÔ±à³Ì·¶Î§Îª0 - 7/16 (ÒÔ1/16¼Ó¼õ£©
	//SECOND_IPL = 101=µÚ¶þÖÐ¼ä¹¦ÂÊµÈ¼¶¡£µÚ¶þÖÐ¼ä¹¦ÂÊµÈ¼¶£¬¿ÉÒÔ±à³Ì·¶Î§Îª8/16 - 15/16 (ÒÔ1/16¼Ó¼õ£©
	//RAMP_SHAPE   PAÐ±ÆÂÊ±¼äºÍASK / OOKÐÎ×´µÄ³¤¶È=10=3·ûºÅÐ±ÆÂÊ±¼äºÍ1/8·ûºÅASK / OOKÐÎ×´µÄ³¤¶È£¨ºÏ·¨µÄUPSAMPLER_PÖµ£º4£¬8£¬16£¬32£¬64£©
	
//care--Î´³õÊ¼»¯//PA_CFG0 -¹¦ÂÊ·Å´óÆ÷ÅäÖÃ//¸´Î»Öµ=01111100
	//ASK_DEPTH  ASK / OOKÉî¶ÈµÄ£¨2 dB²½³¤£©=1111
	//UPSAMPLER_P   ÅäÖÃTXÉÏ²ÉÑùµÄ¿É±äÉýÆµ²ÉÑùÒò×ÓP=100= TXÉýÆµ²ÉÑùÒò×ÓP =16

//PKT_LEN-Êý¾Ý°ü³¤¶ÈÅäÖÃ//¸´Î»Öµ=0x03
	//PACKET_LENGTH  =0xFF  //ÔÚ¹Ì¶¨³¤¶ÈÄ£Ê½ÏÂ£¬±íÊ¾¸ÃÊý¾Ý°üµÄ³¤¶È£¬ÖµÎª0±íÊ¾µÄ³¤¶ÈÎª256×Ö½Ú¡£ÔÚ¿É±ä³¤¶ÈµÄÊý¾Ý°üÄ£Ê½ÏÂ£¬¸ÃÖµÖ¸Ê¾ËùÔÊÐíµÄ×î´ó³¤¶ÈµÄÊý¾Ý°ü¡£
		//¨ˆ¡ïÔÊÐíµÄ×î´ó³¤¶ÈµÄÊý¾Ý°üÎª255×Ö½Ú(³õÊ¼»¯Îª¡°¿É±ä³¤¶ÈµÄÊý¾Ý°üÄ£Ê½¡±)
	{CC112X_PKT_LEN,           0xFF},
	
//IF_MIX_CFG-IF»ìºÏÅäÖÃ//¸´Î»Öµ=0x04
	//IF_MIX_CFG_RESERVED3_0 =0x00   //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	{CC112X_IF_MIX_CFG,        0x00},
	
//FREQOFF_CFG-ÆµÂÊÆ«ÒÆ¾ÀÕýÅäÖÃ//¸´Î»Öµ=0x20=00100000
	//FOC_EN   ÆµÂÊÆ«ÒÆÐ£ÕýÊ¹ÄÜ = 1=Ê¹ÄÜÆµÂÊÆ«ÒÆÐ£Õý
	//FOC_CFG  ÆµÂÊÆ«ÒÆÐ£ÕýÅäÖÃ =00=ÐÅµÀÂË²¨Æ÷ºó£¬½øÐÐFOC£¨ÎÈ¶¨µäÐÍÖµ0 - 1Ç°µ¼×Ö½Ú£©
	//FOC_LIMIT  FOCÏÞÖÆ = 0=RXÂË²¨Æ÷´ø¿í/4   //1=RXÂË²¨Æ÷´ø¿í/8   //ÕâÊÇ×î´óµÄÆµÂÊºÏ³ÉÆ÷ÖÐµÄÆµÂÊÆ«ÒÆÐ£Õý¡£Ö»ÓÐFOC_CFG£¡= 00BÓÐÐ§Ê±.
	//FOC_KI_FACTOR  ÆµÂÊÆ«ÒÆ¾ÀÕý =10=ÆµÂÊÆ«ÒÆ²¹³¥ÔÚÊý¾Ý°ü½ÓÊÕ»ØÂ·ÔöÒæÏµÊý=1/64
	{CC112X_FREQOFF_CFG,       0x22},

//care--Î´³õÊ¼»¯//TOC_CFG -¶¨Ê±Æ«ÒÆÐ£ÕýÅäÖÃ//¸´Î»Öµ=00001011
	//TOC_LIMIT   ¶¨Ê±Æ«ÒÆÐ£ÕýÏÞÖÆ =00=Ñ¡ < 2000 ppm
	//TOC_PRE_SYNC_BLOCKLEN   =001=(Ç°ÌáTOC_LIMIT = 0) 16·ûºÅÕûºÏ´°¿Ú//(Ç°ÌáTOC_LIMIT != 0)x11=Õý±ÈµÄ±ÈÀýÏµÊý= 1/16
	//TOC_POST_SYNC_BLOCKLEN  = 011=(Ç°ÌáTOC_LIMIT = 0) 64·ûºÅÕûºÏ´°¿Ú//(Ç°ÌáTOC_LIMIT != 0)x11=»ý·Ö±ÈÀýÒò×Ó= 1/32

//care--Î´³õÊ¼»¯//MARC_SPARE -MARC±¸ÓÃ//¸´Î»Öµ=0x00
	//MARC_SPARE_RESERVED3_0 =0x00  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	
//care--Î´³õÊ¼»¯//ECG_CFG -Íâ²¿Ê±ÖÓÆµÂÊÅäÖÃ//¸´Î»Öµ=0x00
	//EXT_CLOCK_FREQ   Íâ²¿Ê±ÖÓÆµÂÊ¡£¿ØÖÆ·ÖÆµÒò×Ó¡£ =0x00=64

//care--Î´³õÊ¼»¯//SOFT_TX_DATA_CFG -Èí¼þÅäÖÃTXÊý¾Ý//¸´Î»Öµ=0x00
	//SYMBOL_MAP_CFG   ·ûºÅÓ³ÉäÅäÖÃ = 00  //¸ù¾Ý²»Í¬µÄµ÷ÊÔ·½Ê½£¬ÓÐ²»Í¬µÄº¬Òå¡££¨¾ßÌåÇë²Î¿¼User Guider£©
	//SOFT_TX_DATA_CFG_RESERVED4_1  =0000    //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	//SOFT_TX_DATA_EN  ÈíTXÊý¾ÝÄ£Ê½Ê¹ÄÜ=0=½ûÓÃ ÈíTXÊý¾ÝÄ£Ê½
	
//care--Î´³õÊ¼»¯//EXT_CTRL -Íâ²¿¿ØÖÆÅäÖÃ//¸´Î»Öµ=0x01
	//PIN_CTRL_EN  Òý½Å¿ØÖÆÊ¹ÄÜ=0=½ûÓÃÒý½Å¿ØÖÆ  //Òý½Å¿ØÖÆÖØ¸´Ê¹ÓÃSPI½Ó¿ÚÒý½ÅÖ´ÐÐSRX£¬STX£¬SPWDºÍ¿ÕÏÐÉÁ¹âµÆ
	//EXT_32K_CLOCK_EN  Íâ²¿32KÊ±ÖÓÊ¹ÄÜ=0=½ûÓÃ Íâ²¿32KÊ±ÖÓ
	//BURST_ADDR_INCR_EN  Í»·¢µØÖ·µÝÔöÊ¹ÄÜ =1=Í»·¢µØÖ·ÔöÁ¿ÆôÓÃ£¨¼´ÔÚÍ»·¢·ÃÎÊ£¬µØÖ·µÝÔö£©

//care--Î´³õÊ¼»¯//RCCAL_FINE-RCÕñµ´Æ÷Ð£×¼£¨¾«£©//¸´Î»Öµ=0x00
	//RCC_FINE   =0x00=32kHzµÄRCOSCÐ£×¼¾«ºâ

//care--Î´³õÊ¼»¯//RCCAL_COARSE-RCÕñµ´Æ÷Ð£×¼£¨´Ö£©//¸´Î»Öµ=0x00
	//RCC_COARSE  =0x00=32kHzµÄRCOSCÐ£×¼´ÖÖµ

//care--Î´³õÊ¼»¯//RCCAL_OFFSET-RCÕñµ´Æ÷Ð£×¼Ê±ÖÓÆ«ÒÆ//¸´Î»Öµ=0x00
	//RCC_CLOCK_OFFSET_RESERVED4_0  = 0x00  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ

//care--Î´³õÊ¼»¯//FREQOFF1 - ÆµÂÊÆ«ÒÆ£¨MSB£©//¸´Î»Öµ=0x00
	//FREQ_OFF_15_8  = 0x00   //ÆµÂÊÆ«ÒÆ[15:8]¡£ÓÉÓÃ»§»òSAFC´¥·¢¸üÐÂ¡£¸ÃÖµÊÇ2µÄ²¹Âë¸ñÊ½.//SAFCÖ¸Automatic Frequency Compensation

//care--Î´³õÊ¼»¯//FREQOFF0 - ÆµÂÊÆ«ÒÆ£¨LSB£©//¸´Î»Öµ=0x00
	//FREQ_OFF_7_0 = 0x00   //ÆµÂÊÆ«ÒÆ[7:0]¡£ÓÉÓÃ»§»òSAFC´¥·¢¸üÐÂ¡£¸ÃÖµÊÇ2µÄ²¹Âë¸ñÊ½.//SAFCÖ¸Automatic Frequency Compensation

//FREQ2-ÆµÂÊÅäÖÃ[23:16]//¸´Î»Öµ=0x00
	//FREQ_23_16  ÆµÂÊ[23:16]  =0x6C
	{CC112X_FREQ2,             0x6C},
	
//FREQ1-ÆµÂÊÅäÖÃ[23:16]//¸´Î»Öµ=0x00
	//FREQ_15_8  ÆµÂÊ[15:8]  =0x80
	{CC112X_FREQ1,             0x80}, 
	
//care--Î´³õÊ¼»¯//FREQ0 - ÆµÂÊÅäÖÃ[7:0]//¸´Î»Öµ=0x00
	//FREQ_7_0 ÆµÂÊ[7:0] = 0x00	
		//¨ˆ¡ïÔØ²¨ÆµÂÊ = 434MHz 

//care--Î´³õÊ¼»¯//IF_ADC2-Ä£Äâµ½Êý×Ö×ª»»Æ÷ÅäÖÃ//¸´Î»Öµ=0x02
	//IF_ADC2_RESERVED1_0 = 0x02   //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ

//care--Î´³õÊ¼»¯//IF_ADC1-Ä£Äâµ½Êý×Ö×ª»»Æ÷ÅäÖÃ//¸´Î»Öµ=0xA6
	//IF_ADC1_RESERVED7_0  = 0xA6   //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ

//care--Î´³õÊ¼»¯//IF_ADC0-Ä£Äâµ½Êý×Ö×ª»»Æ÷ÅäÖÃ//¸´Î»Öµ=0x04
	//IF_ADC0_RESERVED2_0   = 0x04  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ

//FS_DIG1-//¸´Î»Öµ=0x08
	//FS_DIG1_RESERVED3_0  = 0x00    //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	{CC112X_FS_DIG1,           0x00},
	
//FS_DIG0-//¸´Î»Öµ=01011010
	//FS_DIG0_RESERVED7_4  = 0x05 //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	//RX_LPF_BW    ÔÚRXµÄFS»·Â·´ø¿í =11=170.8 kHz
	//TX_LPF_BW    ÔÚTXµÄFS»·Â·´ø¿í =11=170.8 kHz
	{CC112X_FS_DIG0,           0x5F},

//care--Î´³õÊ¼»¯//FS_CAL3 -//¸´Î»Öµ=0x00
	//KVCO_HIGH_RES_CFG  KVCO¸ß·Ö±æÂÊÊ¹ÄÜ=0=½ûÓÃ¸ß·Ö±æÂÊ£¨Õý³£·Ö±æÂÊÄ£Ê½£©
	//FS_CAL3_RESERVED3_0   =0000    //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ

//care--Î´³õÊ¼»¯//FS_CAL2 -//¸´Î»Öµ=0x20
	//VCDAC_START    =0x20    //VCDACÆðÊ¼Öµ¡£Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ

//FS_CAL1-//¸´Î»Öµ=0x00
	//FS_CAL1_RESERVED7_0  =0x40     //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	{CC112X_FS_CAL1,           0x40},

//FS_CAL0-//¸´Î»Öµ=0x00
	//LOCK_CFG   ÔÚËø¶¨¼ì²âµÄÆ½¾ùÊ±¼ä=11=ÎÞÏÞÆ½¾ù   //00=Æ½¾ù³¬¹ý512´ÎµÄ²âÁ¿
	//FS_CAL0_RESERVED1_0  =10   //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	{CC112X_FS_CAL0,           0x0E},

//care--Î´³õÊ¼»¯//FS_CHP - µçºÉ±ÃÅäÖÃ//¸´Î»Öµ=0x28
	//CHP_CAL_CURR  =0x28   //µçºÉ±ÃµçÁ÷ºÍÐ£×¼¡£Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ

//FS_DIVTWO-³ýÒÔ2//¸´Î»Öµ=0x01
	//FS_DIVTWO_RESERVED1_0  = 11   //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	{CC112X_FS_DIVTWO,         0x03},

//care--Î´³õÊ¼»¯//FS_DSM1- Êý×ÖÆµÂÊºÏ³ÉÆ÷Ä£¿éÅäÖÃ//¸´Î»Öµ=0x00
	//FS_DSM1_RESERVED2_0 =000  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ

//FS_DSM0-Êý×ÖÆµÂÊºÏ³ÉÆ÷Ä£¿éÅäÖÃ//¸´Î»Öµ=0x03
	//FS_DSM0_RESERVED7_0  = 0x33    //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	{CC112X_FS_DSM0,           0x33},

//care--Î´³õÊ¼»¯//FS_DVC1 - ·ÖÆµÆ÷Á´ÅäÖÃ//¸´Î»Öµ=0xFF
	//FS_DVC1_RESERVED7_0  = 0xFF   //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ

//FS_DVC0 - ·ÖÆµÆ÷Á´ÅäÖÃ//¸´Î»Öµ=0x1F
	//FS_DVC0_RESERVED4_0  =0x17   //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	{CC112X_FS_DVC0,           0x17},

//care--Î´³õÊ¼»¯//FS_LBI - ±¾µØÆ«ÖÃÅäÖÃ//¸´Î»Öµ=0x00
	//Î´Ê¹ÓÃ

//FS_PFD - ÏàÎ»ÆµÂÊ¼ì²âÆ÷ÅäÖÃ//¸´Î»Öµ=0x51
	//FS_PFD_RESERVED6_0   = 0x50   //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	{CC112X_FS_PFD,            0x50},

//FS_PRE - Ô¤·ÖÆµÆ÷ÅäÖÃ//¸´Î»Öµ=0x2C
	//FS_PRE_RESERVED6_0  =0x6E  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	{CC112X_FS_PRE,            0x6E},

//FS_REG_DIV_CML- //¸´Î»Öµ=0x11
	//FS_REG_DIV_CML_RESERVED4_0   =0x14  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	{CC112X_FS_REG_DIV_CML,    0x14},

//FS_SPARE- //¸´Î»Öµ=0x00
	//FS_SPARE_RESERVED7_0 =0xAC   //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	{CC112X_FS_SPARE,          0xAC},

//care--Î´³õÊ¼»¯//FS_VCO4-//¸´Î»Öµ=0x14
	//FSD_VCO_CAL_CURR  =0x14   //VCOµçÁ÷Ð£×¼¹ý³ÌÖÐÉèÖÃ
	
//care--Î´³õÊ¼»¯//FS_VCO3-//¸´Î»Öµ=0x00
	//FS_VCO3_RESERVED0  =0x00  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	
//care--Î´³õÊ¼»¯//FS_VCO2-//¸´Î»Öµ=0x00
	//FSD_VCO_CAL_CAPARR  =0x00  //ÔÚÐ£×¼¹ý³ÌÖÐµÄµÄVCOÃ±ÕóÁÐÅäÖÃ¼¯
	
//care--Î´³õÊ¼»¯//FS_VCO1-//¸´Î»Öµ=0x00
	//FSD_VCDAC  VCDACµÄÅäÖÃ =000000=×îÐ¡160ºÁ·ü  //ÓÃÓÚ¿ª»·CALÄ£Ê½¡£ÐèÒª×¢ÒâµÄÊÇAVDDÄÚ²¿VCOµÄµ÷½ÚµçÑ¹
	//FS_VCO1_RESERVED1_0 =00  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ

//FS_VCO0- //¸´Î»Öµ=10000001
	//FS_VCO0_RESERVED7 =1    //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	//FS_VCO0_RESERVED6_0  =0110100 //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	{CC112X_FS_VCO0,           0xB4},

//care--Î´³õÊ¼»¯//GBIAS6¡«GBIAS0- Í¨ÓÃÆ«ÖÃÅäÖÃ
	//GBIAS6 //¸´Î»Öµ=0x00
	//GBIAS5 //¸´Î»Öµ=0x02
	//GBIAS4 //¸´Î»Öµ=0x00
	//GBIAS3 //¸´Î»Öµ=0x00
	//GBIAS2 //¸´Î»Öµ=0x10
	//GBIAS1 //¸´Î»Öµ=0x00
	//GBIAS0 //¸´Î»Öµ=0x00

//care--Î´³õÊ¼»¯//IFAMP-ÖÐÆµ·Å´óÆ÷ÅäÖÃ//¸´Î»Öµ=0x01
	//IFAMP_RESERVED1_0 = 01  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ

//care--Î´³õÊ¼»¯//LNA -µÍÔëÉù·Å´óÆ÷ÅäÖÃ//¸´Î»Öµ=0x01
	//LNA_RESERVED1_0  = 01  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ

//care--Î´³õÊ¼»¯//RXMIX - RX»ìÆµÆ÷ÅäÖÃ//¸´Î»Öµ=0x01
	//RXMIX_RESERVED1_0  = 01  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ

//XOSC5-¾§ÌåÕñµ´Æ÷ÅäÖÃ //¸´Î»Öµ=0x0C
	//XOSC5_RESERVED3_0  = 0x0E   //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	{CC112X_XOSC5,             0x0E},   

//care--Î´³õÊ¼»¯//XOSC4-¾§ÌåÕñµ´Æ÷ÅäÖÃ//¸´Î»Öµ=0xA0
	//XOSC4_RESERVED7_0  =0xA0 //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ

//care--Î´³õÊ¼»¯//XOSC3-¾§ÌåÕñµ´Æ÷ÅäÖÃ//¸´Î»Öµ=0x03
	//XOSC3_RESERVED7_0  =0x03   //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ

//care--Î´³õÊ¼»¯//XOSC2-¾§ÌåÕñµ´Æ÷ÅäÖÃ//¸´Î»Öµ=00000100
	//XOSC2_RESERVED3_1 = 010 //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	//XOSC_CORE_PD_OVERRIDE  = 0=Èç¹û SXOFF£¬SPWD»òSWORÃüÁî±»´¥·¢£¬ÔòXOSC½«±»¹Ø±Õ
	
//XOSC1-¾§ÌåÕñµ´Æ÷ÅäÖÃ//¸´Î»Öµ=0x00
	//XOSC1_RESERVED2 = 0   //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	//XOSC_BUF_SEL XOSC»º³åÇøÑ¡Ôñ¡£Ñ¡ÔñÄÚ²¿XOSC»º³åµÄÉäÆµËøÏà»·= 1=µÍÏàÎ»ÔëÉù£¬²î·Ö»º³åÆ÷£¨µÍ¹¦ÂÊÊý×ÖÊ±ÖÓ»º³åÆ÷ÈÔÊ¹ÓÃ£© //0=µÍ¹¦ºÄ£¬µ¥¶Ë»º³åÇø£¨²î·Ö»º³åÆ÷±»¹Ø±Õ£©
	//XOSC_STABLE =1=XOSCÊÇÎÈ¶¨µÄ£¨ÒÑÍê³ÉÎÈ¶¨£©
	{CC112X_XOSC1,             0x03},   //{CC112X_XOSC1,         0x07},
	
//care--Î´³õÊ¼»¯//XOSC0-¾§ÌåÕñµ´Æ÷ÅäÖÃ//¸´Î»Öµ=0x00
	//XOSC0_RESERVED1_0 =00  //½öÓÃÓÚ²âÊÔÄ¿µÄ

///////////////////////////////////////////////////
//care--Î´³õÊ¼»¯//ANALOG_SPARE- //¸´Î»Öµ=0x00
//care--Î´³õÊ¼»¯//PA_CFG3- ¹¦ÂÊ·Å´óÆ÷ÅäÖÃ//¸´Î»Öµ=0x00
//care--Î´³õÊ¼»¯//WOR_TIME1-eWOR¶¨Ê±Æ÷×´Ì¬£¨MSB£© //¸´Î»Öµ=0x00
//care--Î´³õÊ¼»¯//WOR_TIME0-eWOR¶¨Ê±Æ÷×´Ì¬£¨LSB£© //¸´Î»Öµ=0x00
//care--Î´³õÊ¼»¯//WOR_CAPTURE1 - eWOR¶¨Ê±Æ÷²¶×½£¨MSB£©//¸´Î»Öµ=0x00
//care--Î´³õÊ¼»¯//WOR_CAPTURE0 - eWOR¶¨Ê±Æ÷²¶×½£¨LSB£©//¸´Î»Öµ=0x00
//care--Î´³õÊ¼»¯//BIST - MARC BIST- //¸´Î»Öµ=0x00
//care--Î´³õÊ¼»¯//DCFILTOFFSET_I1 - Ö±Á÷ÂË²¨Æ÷Æ«ÒÆI£¨MSB£©//¸´Î»Öµ=0x00
//care--Î´³õÊ¼»¯//DCFILTOFFSET_I0 - Ö±Á÷ÂË²¨Æ÷Æ«ÒÆI£¨LSB£©//¸´Î»Öµ=0x00
//care--Î´³õÊ¼»¯//DCFILTOFFSET_Q1 -Ö±Á÷ÂË²¨Æ÷Æ«ÒÆ Q£¨MSB£©//¸´Î»Öµ=0x00
//care--Î´³õÊ¼»¯//DCFILTOFFSET_Q0 -Ö±Á÷ÂË²¨Æ÷Æ«ÒÆ Q£¨LSB£©//¸´Î»Öµ=0x00
//care--Î´³õÊ¼»¯//IQIE_I1 - IQ²»Æ½ºâÖµI£¨MSB£©//¸´Î»Öµ=0x00
//care--Î´³õÊ¼»¯//IQIE_I0 - IQ²»Æ½ºâÖµI£¨LSB£©//¸´Î»Öµ=0x00
//care--Î´³õÊ¼»¯//IQIE_Q1 - IQ²»Æ½ºâÖµQ£¨MSB£©//¸´Î»Öµ=0x00
//care--Î´³õÊ¼»¯//IQIE_Q0 - IQ²»Æ½ºâÖµQ£¨LSB£©//¸´Î»Öµ=0x00
///////////////////////////////////////////////////

//care--Î´³õÊ¼»¯//RSSI1 - ½ÓÊÕÐÅºÅÇ¿¶ÈÖ¸Ê¾Æ÷£¨MSB£©(Ö»¶Á) //¸´Î»Öµ=0x80
	//RSSI_11_4   ½ÓÊÕÐÅºÅÇ¿¶ÈÖ¸Ê¾Æ÷[11:4]=0x80

//care--Î´³õÊ¼»¯//RSSI0 - ½ÓÊÕÐÅºÅÇ¿¶ÈÖ¸Ê¾Æ÷£¨LSB£©(Ö»¶Á) //¸´Î»Öµ=0x00
	//RSSI_3_0  ½ÓÊÕÐÅºÅÇ¿¶ÈÖ¸Ê¾Æ÷[3:0]=0x00
	//CARRIER_SENSE  ÔØ²¨ÕìÌý=0=ÎÞÔØ²¨¼ì²â
	//CARRIER_SENSE_VALID  ÔØ²¨ÕìÌýÓÐÐ§Ê¹ÄÜ=0= ÔØ²¨ÕìÌýÎÞÐ§
	//RSSI_VALID   RSSIÓÐÐ§Ê¹ÄÜ=0=RSSIÎÞÐ§
		//¨ˆ¡ïÎÞÔØ²¨¼ì²â,ÔØ²¨ÕìÌýÎÞÐ§,RSSIÎÞÐ§ 

//care--Î´³õÊ¼»¯//MARCSTATE - MARC ×´Ì¬(Ö»¶Á) //¸´Î»Öµ=01000001       //MARC (Main Radio Control)
	//MARC_2PIN_STATE   MARC2Òý½Å×´Ì¬Öµ=10=¿ÕÏÐIDLE   //00=SETTLING //01=TX //11=RX
	//MARC_STATE    MARC ×´Ì¬=00001=¿ÕÏÐIDLE   //00000=SLEEP //00001=IDLE //00010=XOFF //00011=BIAS_SETTLE_MC //00100=REG_SETTLE_MC //00101=MANCAL //00110=BIAS_SETTLE //00111=REG_SETTLE //01000=STARTCAL //01001=BWBOOST //01010=FS_LOCK //01011=IFADCON //01100=ENDCAL //01101=RX //01110=RX_END //01111=Reserved //10000=TXRX_SWITCH //10001=RX_FIFO_ERR //10010=FSTXON //10011=TX //10100=TX_END //10101=RXTX_SWITCH //10110=TX_FIFO_ERR //10111=IFADCON_TXRX

//care--Î´³õÊ¼»¯//LQI_VAL - Á´Â·ÖÊÁ¿Ö¸±êÖµ(Ö»¶Á) //¸´Î»Öµ=0x00
	//CRC_OK  = 0=CRCÐ£Ñé²»Õý³££¨ÎóÂë£©
	//LQI  Á´½ÓÖÊÁ¿Ö¸±ê=0x00  //½ÏµÍÖµµÄÁ´½Ó±È½Ï¸ßÖµµÄÁ´½ÓÒªºÃ

//care--Î´³õÊ¼»¯//PQT_SYNC_ERROR-Ç°µ¼ÂëºÍÍ¬²½×Ö´íÎó(Ö»¶Á) //¸´Î»Öµ=0xFF
	//PQT_ERROR  Ç°µ¼ÂëÏÞ¶¨·ûÖµ= 1111   //
	//SYNC_ERROR Í¬²½×ÖÏÞ¶¨·ûÖµ= 1111  //

//care--Î´³õÊ¼»¯//DEM_STATUS - ½âµ÷Æ÷×´Ì¬(Ö»¶Á)//¸´Î»Öµ=0x00
	//RSSI_STEP_FOUND  (Ö»¶Á)  //ÔÚÊý¾Ý°ü½ÓÊÕÊ±£¬Èç¹û·¢ÏÖRSSI£¬ÔòÖÃÎ»
	//COLLISION_FOUND  (Ö»¶Á)  //ÔÚÊý¾Ý°ü½ÓÊÕÊ±£¬Èç¹û¼ì²âµ½Í¬²½×Ö£¬ÔòÖÃÎ»
	//SYNC_LOW0_HIGH1  ¼ì²âDualSync = 0=Í¬²½×Ö·¢ÏÖ=[SYNC15_8 SYNC7_0]   //1=Í¬²½×Ö·¢ÏÖ=[SYNC31_24 SYNC23_16]
	//DEM_STATUS_RESERVED4_1  =0000  //½öÓÃÓÚ²âÊÔÄ¿µÄ
	//IMAGE_FOUND    Í¼ÏñÌ½²âÆ÷=0=Î´·¢ÏÖÓ°Ïñ

//care--Î´³õÊ¼»¯//FREQOFF_EST1 - ÆµÆ«¹À¼Æ£¨MSB£©(Ö»¶Á) //¸´Î»Öµ=0x00
//care--Î´³õÊ¼»¯//FREQOFF_EST0 - ÆµÆ«¹À¼Æ£¨LSB£©(Ö»¶Á) //¸´Î»Öµ=0x00
//care--Î´³õÊ¼»¯//AGC_GAIN3-AGCÔöÒæ//¸´Î»Öµ=0x00   //AGC_FRONT_END_GAIN =00  //AGCÇ°¶ËÔöÒæ¡£Êµ¼ÊÓ¦ÓÃµÄ·Ö±æÂÊÎª1 dBÔöÒæ
//care--Î´³õÊ¼»¯//AGC_GAIN2-AGCÔöÒæ//¸´Î»Öµ=11101001  //AGC_DRIVES_FE_GAIN  ¸²¸ÇAGCÔöÒæ¿ØÖÆ=1=AGC¿ØÖÆÇ°¶ËÔöÒæ  //AGC_LNA_CURRENT  //AGC_LNA_R_DEGEN
//care--Î´³õÊ¼»¯//AGC_GAIN1-AGCÔöÒæ//¸´Î»Öµ=0x00   //AGC_LNA_R_LOAD //AGC_LNA_R_RATIO
//care--Î´³õÊ¼»¯//AGC_GAIN0-AGCÔöÒæ//¸´Î»Öµ=00111111  //AGC_IF_MODE  //AGC_IFAMP_GAIN
//care--Î´³õÊ¼»¯//SOFT_RX_DATA_OUT-Èí¼þÉèÖÃRXÊý¾ÝÊä³ö//¸´Î»Öµ=0x00   //SOFT_RX_DATA
//care--Î´³õÊ¼»¯//SOFT_TX_DATA_OUT-Èí¼þÉèÖÃTXÊý¾ÝÊäÈë//¸´Î»Öµ=0x00   //SOFT_TX_DATA
//care--Î´³õÊ¼»¯//ASK_SOFT_RX_DATA - AGC ASK Èí¼þÅäÖÃÊä³ö//¸´Î»Öµ=0x30  //ASK_SOFT_RX_DATA_RESERVED5_0 

//care--Î´³õÊ¼»¯//RNDGEN - Ëæ»úÊýÖµ//¸´Î»Öµ=0x7F
	//RNDGEN_EN  Ëæ»úÊý·¢ÉúÆ÷Ê¹ÄÜ =0=½ûÓÃËæ»úÊý·¢ÉúÆ÷
	//RNDGEN_VALUE Ëæ»úÊýÖµ=0x7F

//care--Î´³õÊ¼»¯//MAGN2 - CORDICºóµÄÐÅºÅ·ù¶È[16](Ö»¶Á)//¸´Î»Öµ=0x00  //DEM_MAGN_16=0  //CORDICºóµÄË²Ê±ÐÅºÅ·ù¶È£¬17Î»[16]
//care--Î´³õÊ¼»¯//MAGN1 - CORDICºóµÄÐÅºÅ·ù¶È[15:8](Ö»¶Á)//¸´Î»Öµ=0x00  //DEM_MAGN_15_8=0  //CORDICºóµÄË²Ê±ÐÅºÅ·ù¶È[15:8]
//care--Î´³õÊ¼»¯//MAGN0 - CORDICºóµÄÐÅºÅ·ù¶È[7:0](Ö»¶Á)//¸´Î»Öµ=0x00  //DEM_MAGN_7_0=0  //CORDICºóµÄË²Ê±ÐÅºÅ·ù¶È[7:0]
//care--Î´³õÊ¼»¯//ANG1 - CORDICºóµÄÐÅºÅ½Ç¶È[9:8](Ö»¶Á)//¸´Î»Öµ=0x00  //CORDICºóµÄË²Ê±ÐÅºÅµÄ½Ç¶È
//care--Î´³õÊ¼»¯//ANG0 - CORDICºóµÄÐÅºÅ½Ç¶È[7:0](Ö»¶Á)//¸´Î»Öµ=0x00  //CORDICºóµÄË²Ê±ÐÅºÅµÄ½Ç¶È
//care--Î´³õÊ¼»¯//CHFILT_I2 - Í¨µÀÉ¸Ñ¡Êý¾ÝµÄÊµ²¿[18:16](Ö»¶Á)//¸´Î»Öµ=0x80  //DEM_CHFILT_STARTUP_VALID=1=ÐÅµÀÂË²¨Æ÷Êý¾ÝÓÐÐ§£¨ºóÖÃ16ÐÅµÀÂË²¨Æ÷ÑùÆ·£©  //DEM_CHFILT_I_18_16
//care--Î´³õÊ¼»¯//CHFILT_I1 - Í¨µÀÉ¸Ñ¡Êý¾ÝµÄÊµ²¿[15:8](Ö»¶Á)//¸´Î»Öµ=0x00   //DEM_CHFILT_I_15_8
//care--Î´³õÊ¼»¯//CHFILT_I0 - Í¨µÀÉ¸Ñ¡Êý¾ÝµÄÊµ²¿[7:0](Ö»¶Á)//¸´Î»Öµ=0x00    //DEM_CHFILT_I_7_0
//care--Î´³õÊ¼»¯//CHFILT_Q2 - Í¨µÀÉ¸Ñ¡Êý¾ÝµÄÐé²¿[18:16](Ö»¶Á)//¸´Î»Öµ=0x00  //DEM_CHFILT_Q_18_16
//care--Î´³õÊ¼»¯//CHFILT_Q1 - Í¨µÀÉ¸Ñ¡Êý¾ÝµÄÊµ²¿[15:8](Ö»¶Á)//¸´Î»Öµ=0x00   //DEM_CHFILT_Q_15_8
//care--Î´³õÊ¼»¯//CHFILT_Q0 - Í¨µÀÉ¸Ñ¡Êý¾ÝµÄÊµ²¿[7:0](Ö»¶Á)//¸´Î»Öµ=0x00    //DEM_CHFILT_Q_7_0

//care--Î´³õÊ¼»¯//GPIO_STATUS - GPIO ×´Ì¬//¸´Î»Öµ=0x00
	//GPIO_STATUS_RESERVED7_4  =0000  //½öÓÃÓÚ²âÊÔÄ¿µÄ
	//GPIO_STATE  GPIOÒý½ÅµÄµÄ×´Ì¬=0000

//care--Î´³õÊ¼»¯//FSCAL_CTRL-//¸´Î»Öµ=0x01
	//FSCAL_CTRL_RESERVED6_1  =0x00 //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
	//LOCK  ³öËøÖ¸Ê¾µÆ£¨FS_CFG.FS_LOCK_EN±ØÐëÊÇ1£©=1=FSËøÎ´¼ì²âµ½   //ÐÅºÅ×´Ì¬Ö»ÊÊÓÃÓÚRX£¬TXºÍFSTXON×´Ì¬

//care--Î´³õÊ¼»¯//PHASE_ADJUST-//¸´Î»Öµ=0x00  //½öÓÃÓÚ²âÊÔÄ¿µÄ

//PARTNUMBER -Ð¾Æ¬ÐÍºÅ//¸´Î»Öµ=0x00
	//PARTNUM   Ð¾Æ¬ID=0x48=CC1120  //0x40=CC1121 //0x48=CC1120 //0x58=CC1125 //0x5A=CC1175
	{CC112X_PARTNUMBER,        0x48},
	
//PARTVERSION- ²¿·Öµ÷Õû//¸´Î»Öµ=0x00
	//PARTVER  Ð¾Æ¬ÐÞ¶©=0x21
	{CC112X_PARTVERSION,       0x21},

//care--Î´³õÊ¼»¯//SERIAL_STATUS - ´®ÐÐ×´Ì¬//¸´Î»Öµ=0x00
	//CLK32K (Ö»¶Á) =0=ÄÚ²¿32 kHz RCÕñµ´Æ÷Ê±ÖÓ
	//IOC_SYNC_PINS_EN  Í¬²½IOÒý½ÅÊ¹ÄÜ =0
	//SOFT_TX_DATA_CLK(Ö»¶Á) =0   //µ÷ÖÆÆ÷ÈíÊý¾ÝÊ±ÖÓ£¨±à³ÌµÄÊý¾ÝËÙÂÊµÄ16±¶ÒÔÉÏ£©
	//SERIAL_RX(Ö»¶Á) =0   //´®ÐÐ½ÓÊÕÊý¾Ý
	//SERIAL_RX_CLK(Ö»¶Á) =0   //´®ÐÐ½ÓÊÕÊý¾ÝÊ±ÖÓ

//RX_STATUS- RX  ×´Ì¬(Ö»¶Á) //¸´Î»Öµ=0x01
	//SYNC_FOUND =0  //·¢ÉúSYNC_EVENTÊ±ÖÃÎ»¡£´¥·¢SRXÊ±£¬¸´Î»
	//RXFIFO_FULL =0 //µ±×Ö½ÚÊý´óÓÚRX FIFOãÐÖµÊ±£¬ÖÃÎ»£» µ±RX FIFOÎª¿ÕÊ±£¬¸´Î»
	//RXFIFO_OVER_THR =0  //µ±×Ö½ÚÊý´óÓÚRX FIFOãÐÖµÊ±£¬ÖÃÎ»£» µ±RX FIFOÐ¡ÓÚ»òµÈÓÚãÐÖµÊ±£¬¸´Î»¡£
	//RXFIFO_EMPTY =0  //RX FIFO Îª¿ÕÊ±£¬ÖÃÎ»
	//RXFIFO_OVERFLOW =0 //µ±RX FIFOÒç³öÊ±£¬ÖÃÎ»; µ± RX FIFO±»Çå¿ÕÊ±£¬¸´Î»¡£
	//RXFIFO_UNDERFLOW =0 //Èç¹ûÓÃ»§´Ó¿ÕµÄRX FIFO ¶ÁÈ¡Êý¾ÝÊ±£¬ÖÃÎ»£»  µ± RX FIFO±»Çå¿ÕÊ±£¬¸´Î»¡£
	//PQT_REACHED =0 //¼ì²âµ½Ç°Í¬²½Âë£¨Ç°µ¼ÏÞ¶¨·ûÖµÐ¡ÓÚÉè¶¨µÄPQTãÐÖµ£©Ê±£¬ÖÃÎ»£»¸´Î»£¬Çë²ÎÔÄUserGuider
	//PQT_VALID =1 //½ÓÊÕµ½16Î»»ò43Î»£¨È¡¾öÓÚPREAMBLE_CFG0.PQT_VALID_TIMEOUTÉèÖÃ£©Ê±£¬»ò¼ì²âµ½Ç°µ¼ÂëÊ±£¬ÖÃÎ»£»
	{CC112X_RX_STATUS,         0x10},

//care--Î´³õÊ¼»¯//TX_STATUS-TX ×´Ì¬(Ö»¶Á)//¸´Î»Öµ=0x00
	//TX_STATUS_RESERVED5   =0  //½öÓÃÓÚ²âÊÔÄ¿µÄ
	//SYNC_SENT =0  //·¢ËÍÍêÍ¬²½×Ö×îºóÒ»Î»
	//TXFIFO_FUL =0  //µ±TX FIFO ÂúÊ±£¬ÖÃÎ»£» µ±×ÖÊý½ÚÐ¡ÓÚTX FIFO·§ÖµÊ±£¬¸´Î»
	//TXFIFO_OVER_THR =0  //µ±×ÖÊý½Ú´óÓÚ»òµÈÓÚTX FIFO·§ÖµÊ±£¬ÖÃÎ»
	//TXFIFO_OVERFLOW =0  //µ±TX FIFOÒç³öÊ±£¨ÓÃ»§ÏòÒÑÂúµÄTXFIFOÐ´Êý¾Ý£©Ê±£¬ÖÃÎ»£» TX FIFO±»Çå¿ÕÊ±£¬¸´Î»
	//TXFIFO_UNDERFLOW =0  //µ±TX FIFO ÏÂÒç£¨ÔÚÊý¾Ý°ü·¢ËÍÇ°£¬TX FIFOÎª¿Õ£©Ê±£¬ÖÃÎ»£» µ±TX FIFO±»Çå¿ÕÊ±£¬¸´Î»
	
//care--Î´³õÊ¼»¯//MARC_STATUS1 -MARC ×´Ì¬(Ö»¶Á)//¸´Î»Öµ=0x00  //ÓÃÓÚ¼ÇÂ¼ÊÇÊ²Ã´ÐÅºÅ²úÉúMARC_MCU_WAKEUPÐÅºÅ
	//MARC_STATUS_OUT =00000000=Ã»ÓÐ´íÎó£¨¾ßÌåÇë²ÎÔÄ User Guide£©

//care--Î´³õÊ¼»¯//MARC_STATUS0 -MARC ×´Ì¬(Ö»¶Á)//¸´Î»Öµ=0x00  
	//MARC_STATUS0_RESERVED3 =0  //½öÓÃÓÚ²âÊÔÄ¿µÄ
	//TXONCCA_FAILED =0=ÐÅµÀºÜÇå³þ¡£ÎÞÏßµçÔò½øÈëTX×´Ì¬  //1=ÐÅµÀºÜÃ¦¡£ÎÞÏßµç½«±£³ÖÔÚRX×´Ì¬  //ÔÚTXONCCA_DONEÐÅºÅÓÐÐ§Ö®ºó£¬²ÅÄÜ¶ÁÈ¡´ËÎ»¡£
	//MCU_WAKE_UP MCU»½ÐÑÐÅºÅ=0  //´ÓMARC_STATUS1.MARC_STATUS_OUT²éÕÒ»½ÐÑÊÂ¼þµÄÔ­Òò
	//RCC_CAL_VALID =0   //RCOSCÒÑ¾­ÖÁÉÙÐ£×¼Ò»´Î


//care--Î´³õÊ¼»¯//PA_IFAMP_TEST-//¸´Î»Öµ=0x00 //PA_IFAMP_TEST_RESERVED4_0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
//care--Î´³õÊ¼»¯//FSRF_TEST-//¸´Î»Öµ=0x00     //FSRF_TEST_RESERVED6_0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
//care--Î´³õÊ¼»¯//PRE_TEST-//¸´Î»Öµ=0x00     //PRE_TEST_RESERVED4_0   //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
//care--Î´³õÊ¼»¯//PRE_OVR-//¸´Î»Öµ=0x00   //PRE_TEST_RESERVED4_0   //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
//care--Î´³õÊ¼»¯//ADC_TEST - ADC Test //¸´Î»Öµ=0x00  //ADC_TEST_RESERVED5_0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
//care--Î´³õÊ¼»¯//DVC_TEST - DVC Test //¸´Î»Öµ=0x0B  //DVC_TEST_RESERVED4_0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
//care--Î´³õÊ¼»¯//ATEST-//¸´Î»Öµ=0x40    //ATEST_RESERVED6_0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
//care--Î´³õÊ¼»¯//ATEST_LVDS-//¸´Î»Öµ=0x00   //ATEST_LVDS_RESERVED3_0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
//care--Î´³õÊ¼»¯//ATEST_MODE-//¸´Î»Öµ=0x00   //ATEST_MODE_RESERVED7_0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
//care--Î´³õÊ¼»¯//XOSC_TEST1-//¸´Î»Öµ=0x3C   //XOSC_TEST1_RESERVED7_0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
//care--Î´³õÊ¼»¯//XOSC_TEST0-//¸´Î»Öµ=0x00   //XOSC_TEST0_RESERVED7_0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
//care--Î´³õÊ¼»¯//RXFIRST - RX FIFO Pointer (first entry)//¸´Î»Öµ=0x00  //Ö¸ÏòµÚÒ»¸öÐ´½øRX FIFOµÄ×Ö½Ú
//care--Î´³õÊ¼»¯//TXFIRST - TX FIFO Pointer (first entry)//¸´Î»Öµ=0x00  //Ö¸ÏòµÚÒ»¸öÐ´½øTX FIFOµÄ×Ö½Ú  
//care--Î´³õÊ¼»¯//RXLAST - RX FIFO Pointer (last entry)//¸´Î»Öµ=0x00    //Ö¸Ïò×îºóÒ»¸öÐ´½øRX FIFOµÄ×Ö½Ú
//care--Î´³õÊ¼»¯//TXLAST - TX FIFO Pointer (last entry)//¸´Î»Öµ=0x00    //Ö¸Ïò×îºóÒ»¸öÐ´½øTX FIFOµÄ×Ö½Ú  
//care--Î´³õÊ¼»¯//NUM_TXBYTES - TX FIFO×´Ì¬(Õ¼ÓÃ¿Õ¼ä)//¸´Î»Öµ=0x00  //TXBYTES  TX FIFOÖÐµÄ×Ö½ÚÊý
//care--Î´³õÊ¼»¯//NUM_RXBYTES - RX FIFO×´Ì¬(Õ¼ÓÃ¿Õ¼ä)//¸´Î»Öµ=0x00  //RXBYTES  RX FIFOÖÐµÄ×Ö½ÚÊý
//care--Î´³õÊ¼»¯//FIFO_NUM_TXBYTES - TX FIFO×´Ì¬(¿Õ°×¿Õ¼ä)//¸´Î»Öµ=0x0F  //FIFO_TXBYTES  TX FIFOÖÐ¿Õ°×¿Õ¼äµÄ×Ö½ÚÊý¡£1111£º±íÊ¾»¹ÓÐ>=15¸ö×Ö½ÚµÄ¿Õ¼ä£¬¿ÉÒÔ±»Ð´Èë¡£
//care--Î´³õÊ¼»¯//FIFO_NUM_RXBYTES - RX FIFO×´Ì¬(¿É»ñµÃµÄ×Ö½ÚÊý)//¸´Î»Öµ=0x00  //FIFO_RXBYTES  RX FIFOÖÐ¿ÉÒÔ±»¶Á³öµÄ×Ö½ÚÊý£¬1111£º±íÊ¾»¹ÓÐ>=15¸ö×Ö½Ú£¬¿ÉÒÔ¶Á³ö
};


////////////////////////////////////////////////////////////////////////////
//==blues==ÐÂÔöAPIÏà¹Ø==////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//--**Æµ¶ÎÑ¡Ôñ**----------------------------------------------//
#define CC112X_820_band    (1)  //820.0 - 960.0 MHz band
#define CC112X_410_band    (2)  //410.0 - 480.0 MHz band
#define CC112X_273_3_band  (3)  //273.3 - 320.0 MHz band
#define CC112X_205_band    (4)  //205.0 - 240.0 MHz band
#define CC112X_164_band    (5)  //164.0 - 192.0 MHz band
#define CC112X_136_7_band  (6)  //136.7 - 160.0 MHz band

////////////////////////////////////////////////////////////////////////////
//--**µ÷ÖÆ¸ñÊ½**--------------------------------------------------//
#define CC112X_2_FSK_mode    (1)  //bit5:3=000="2-FSK"
#define CC112X_2_GFSK_mode   (2)  //bit5:3=001=2-GFSK
#define CC112X_ASK_OOK_mode  (3)  //bit5:3=011=ASK/OOK
#define CC112X_4_FSK_mode    (4)  //bit5:3=100=4-FSK
#define CC112X_4_GFSK_mode   (5)  //bit5:3=101=4-GFSK 

////////////////////////////////////////////////////////////////////////////
//--**·¢Éä¹¦ÂÊ**--------------------------------------------------//
#define CC112X_15dBm_TxPower    ( 1)  //0x7F=·¢Éä¹¦ÂÊ= 15dBm
#define CC112X_14dBm_TxPower    ( 2)  //0x7D=·¢Éä¹¦ÂÊ= 14dBm
#define CC112X_13dBm_TxPower    ( 3)  //0x7B=·¢Éä¹¦ÂÊ= 13dBm
#define CC112X_12dBm_TxPower    ( 4)  //0x79=·¢Éä¹¦ÂÊ= 12dBm
#define CC112X_11dBm_TxPower    ( 5)  //0x77=·¢Éä¹¦ÂÊ= 11dBm
#define CC112X_10dBm_TxPower    ( 6)  //0x74=·¢Éä¹¦ÂÊ= 10dBm
#define CC112X_09dBm_TxPower    ( 7)  //0x72=·¢Éä¹¦ÂÊ= 09dBm
#define CC112X_08dBm_TxPower    ( 8)  //0x6F=·¢Éä¹¦ÂÊ= 08dBm
#define CC112X_07dBm_TxPower    ( 9)  //0x6D=·¢Éä¹¦ÂÊ= 07dBm
#define CC112X_06dBm_TxPower    (10)  //0x6B=·¢Éä¹¦ÂÊ= 06dBm
#define CC112X_05dBm_TxPower    (11)  //0x69=·¢Éä¹¦ÂÊ= 05dBm
#define CC112X_04dBm_TxPower    (12)  //0x66=·¢Éä¹¦ÂÊ= 04dBm
#define CC112X_03dBm_TxPower    (13)  //0x64=·¢Éä¹¦ÂÊ= 03dBm
#define CC112X_02dBm_TxPower    (14)  //0x62=·¢Éä¹¦ÂÊ= 02dBm
#define CC112X_01dBm_TxPower    (15)  //0x5F=·¢Éä¹¦ÂÊ= 01dBm
#define CC112X_00dBm_TxPower    (16)  //0x5D=·¢Éä¹¦ÂÊ= 00dBm
#define CC112X__3dBm_TxPower    (17)  //0x56=·¢Éä¹¦ÂÊ= -3dBm
#define CC112X__6dBm_TxPower    (18)  //0x4F=·¢Éä¹¦ÂÊ= -6dBm
#define CC112X__11dBm_TxPower   (19)  //0x43=·¢Éä¹¦ÂÊ= -11dBm


////////////////////////////////////////////////////////////////////////////
//--** **--------------------------------------------------//



////////////////////////////////////////////////////////////////////////////
//--** **--------------------------------------------------//



////////////////////////////////////////////////////////////////////////////
//--** **--------------------------------------------------//



////////////////////////////////////////////////////////////////////////////
//==**È«¾Ö±äÁ¿¶¨Òå**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern unsigned int CC112x_RX_PacketCnt;
extern unsigned int CC112x_TX_PacketCnt;
extern unsigned char CC112x_TxBuf[128]; // ·¢ËÍ»º³åÇø×Ü×Ö½ÚÊý<128


////////////////////////////////////////////////////////////////////////////
//==**"º¯Êý"ºê¶¨Òå**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"´ËÄ£¿é×¨ÓÃ"º¯ÊýÉùÃ÷**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////
static void Initial_GPIO_Int_CC112x(void);  //³õÊ¼»¯:  GPIOµçÆ½ÖÐ¶Ï
static void Initial_SPI_CC112x(void);  //³õÊ¼»¯: SPI´®ÐÐ½Ó¿Ú(CC112x)

static void registerConfig(void);
static void manualCalibration(void);
//static void createPacket(uint8 randBuffer[]);



////////////////////////////////////////////////////////////////////////////
//==**"Íâ²¿" API º¯ÊýÉùÃ÷**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

	//³õÊ¼»¯ÉèÖÃ:  "CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
extern void Initial_CC112x(void);  

	//´¦Àí½ÓÊÕ²¿·Ö"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
extern void Deal_RX_CC112x(void);  

	//CC112x·¢ËÍÊý¾Ý(×Ö·û´®)-- "CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
extern void TX_String_CC112x(unsigned char *pData, unsigned char len); 

////////////////////////////////////////////////////////////////////////////

	//ÅäÖÃ:Æµ¶Î--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
extern void Config_FrequencyBand(unsigned char bandKind);  

	//ÅäÖÃ:ÔØ²¨ÆµÂÊ--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
extern void Config_CarrierFrequency(unsigned char frenquency_2,unsigned char frenquency_1,unsigned char frenquency_0);  

	//ÅäÖÃ:½ÓÊÕÂË²¨Æ÷´ø¿í--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
extern void Config_RxFilterBW(unsigned char rxFilterBW);  

	//ÅäÖÃ:Êý¾ÝËÙÂÊ--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
extern void Config_DataRate(unsigned char dataRate_2,unsigned char dataRate_1,unsigned char dataRate_0);  

	//ÅäÖÃ:µ÷ÖÆ¸ñÊ½ºÍÆµÂÊÆ«²î--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
extern void Config_ModulationFormat_Deviation(unsigned char modulation,unsigned char deviation);  

	//ÅäÖÃ:·¢Éä¹¦ÂÊ(¹¦ÂÊ·Å´óÆ÷)--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
extern void Config_PA_TxPower(unsigned char txPower);  

	//ÅäÖÃ:Éè±¸µØÖ·--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
extern void Config_DeviceAddress(unsigned char deviceAddress);  




/******************************************
// Carrier frequency = 868.000000 
// Symbol rate = 1.2 
// Bit rate = 1.2 
// Deviation = 3.997803 
// Manchester enable = false 
// Bit rate = 1.2 
// Modulation format = 2-FSK 
// Bit rate = 1.2 
// RX filter BW = 25.000000 
// TX power = -6 
// PA ramping = true 
// Packet length mode = Variable 
// Whitening = false 
// Address config = No address check. 
// Packet length = 255 
// Device address = 0 


static const registerSetting_t preferredSettings[] = {
  {CC112X_IOCFG3,        0xB0},
  {CC112X_IOCFG2,        0x06},
  {CC112X_IOCFG1,        0xB0},
  {CC112X_IOCFG0,        0xB0},
  {CC112X_SYNC_CFG1,     0x0B},
  {CC112X_DCFILT_CFG,    0x1C},
  {CC112X_IQIC,          0xC6},
  {CC112X_CHAN_BW,       0x08},
  {CC112X_MDMCFG0,       0x05},
  {CC112X_AGC_REF,       0x20},
  {CC112X_AGC_CS_THR,    0x19},
  {CC112X_AGC_CFG1,      0xA9},
  {CC112X_AGC_CFG0,      0xCF},
  {CC112X_FIFO_CFG,      0x00},
  {CC112X_SETTLING_CFG,  0x03},
  {CC112X_FS_CFG,        0x12}, //820.0 - 960.0 MHz band (LO divider = 4) //Frequency Synthesizer Configuration
  {CC112X_PKT_CFG1,      0x05},  
  {CC112X_PKT_CFG0,      0x20},
  {CC112X_PA_CFG2,       0x4F},
  {CC112X_PA_CFG1,       0x56},
  {CC112X_PA_CFG0,       0x1C},
  {CC112X_PKT_LEN,       0xFF},
  {CC112X_IF_MIX_CFG,    0x00},
  {CC112X_FREQOFF_CFG,   0x22},
  {CC112X_FREQ2,         0x6C},
  {CC112X_FREQ1,         0x80},
  {CC112X_FREQ0,         0x00},
  {CC112X_FS_DIG1,       0x00},
  {CC112X_FS_DIG0,       0x5F},
  {CC112X_FS_CAL0,       0x0E},
  {CC112X_FS_DIVTWO,     0x03},
  {CC112X_FS_DSM0,       0x33},
  {CC112X_FS_DVC0,       0x17},
  {CC112X_FS_PFD,        0x50},
  {CC112X_FS_PRE,        0x6E},
  {CC112X_FS_REG_DIV_CML,0x14},
  {CC112X_FS_SPARE,      0xAC},
  {CC112X_XOSC5,         0x0E},
  {CC112X_XOSC3,         0xC7},
  {CC112X_XOSC1,         0x07},
};
**/
#ifdef  __cplusplus
}
#endif
/******************************************************************************
  Copyright 2012 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
*******************************************************************************/
#endif

