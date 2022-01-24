/******************************************************************************
  Filename:        cc112x_easy_link.c
  
  Description:    This program sets up an easy link between two trxEB's with
                  CC112x EM's connected. 
                  The program can take any recomended register settings exported
                  from SmartRF Studio 7 without any modification with exeption 
                  from the assumtions decribed below.
  
  Notes:          The following asumptions must be fulfilled for the program
                  to work:
                  
                  1. GPIO3 has to be set up with GPIOx_CFG = 0x06
                     PKT_SYNC_RXTX for correct interupt
                  2. Packet engine has to be set up with status bytes enabled 
                     PKT_CFG1.APPEND_STATUS = 1
  
******************************************************************************/


/*****************************************************************************
* INCLUDES
*/

#include "System.h"	 //"ÏµÍ³" ³£ÓÃ¹¦ÄÜº¯Êý¼¯-Í·ÎÄ¼þ

/////////////////////////////////
#include "msp430.h"

#include "hal_spi_rf_trxeb.h"

#include "cc112x_spi.h"
#include "stdlib.h"
#include "cc112x_easy_link.h"  //"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"-Çý¶¯³ÌÐò(Íâ²¿×ÊÔ´)-Í·ÎÄ¼þ



/******************************************************************************
 * CONSTANTS
 */ 

/******************************************************************************
* DEFINES
*/
#define ISR_ACTION_REQUIRED 1
#define ISR_IDLE            0

//#define PKTLEN              15 // Packet length has to be within fifo limits ( 1 - 127 bytes)

#define RX_FIFO_ERROR       0x11


////////////////////////////////////////////////////////////////////////////
//==**È«¾Ö±äÁ¿¶¨Òå**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned int CC112x_RX_PacketCnt = 0;
unsigned int CC112x_TX_PacketCnt = 0;
unsigned char CC112x_TxBuf[128] = {0}; //  ·¢ËÍ»º³åÇø×Ü×Ö½ÚÊý<128



/******************************************************************************
* LOCAL VARIABLES
*/
static uint8  packetSemaphore = 0;


/****************************************************************************
*º¯ÊýÃû-Function:	static void Initial_GPIO_Interrupt(void)
*ÃèÊö- Description:		³õÊ¼»¯: SPI´®ÐÐ½Ó¿Ú(CC112x)
*ÊäÈë²ÎÊý-Input:	None
*Êä³ö²ÎÊý-output:	None
*×¢ÒâÊÂÏî-Note£º	¡ø01)    	¡ø02)    	¡ø03)    ¡ø04)  
*****************************************************************************/
static void Initial_SPI_CC112x(void)  //³õÊ¼»¯: SPI´®ÐÐ½Ó¿Ú(CC112x)
{
	//³õÊ¼»¯SPI ´®ÐÐ½Ó¿Ú
		// Instantiate tranceiver RF spi interface to SCLK ~ 4 MHz */
		//input clockDivider - SMCLK/clockDivider gives SCLK frequency
				//trxRfSpiInterfaceInit(0x02);
	trxRfSpiInterfaceInit(0x01);

////////////////////////////////////////////////////////////////////////////
//care--ÏÂÃæ³ÌÐò£¬Ö»ÊÊÓÃÓÚMSP430F6638ÊµÑé°å----------------//
	//--care--Ò»¶¨Òª¼ÓÉÏÕâ¸öÓï¾ä//"LCD_B ¶Ë¿Ú¿ØÖÆ¼Ä´æÆ÷"Ïà¹ØÅäÖÃ
	LCDBPCTL0 = 0;

		//ÅäÖÃ¶àÂ·¸´ÓÃÆ÷TS3A5017: Ñ¡ÔñIN2 ¡¢IN1
		//IN2=0; IN1=1; ¶ÔÓ¦SPI_B Òý½Å(CLK_B; SPI_MOSI_B; SPI_MISO_B)
	mConfig_TS3A5017_01_IN2(0);  //IN2 = 0
	mConfig_TS3A5017_01_IN1(1);  //IN1 = 1
}



/****************************************************************************
*º¯ÊýÃû-Function:	static void Initial_GPIO_Int_CC112x(void)
*ÃèÊö- Description:		³õÊ¼»¯:  GPIOµçÆ½ÖÐ¶Ï(CC112x)
*ÊäÈë²ÎÊý-Input:	None
*Êä³ö²ÎÊý-output:	None
*×¢ÒâÊÂÏî-Note£º	¡ø01)    	¡ø02)    	¡ø03)    ¡ø04)  
*****************************************************************************/
static void Initial_GPIO_Int_CC112x(void)  //³õÊ¼»¯:  GPIOµçÆ½ÖÐ¶Ï
{
	TRXEM_GPIO3_SEL &= ~ TRXEM_GPIO3_IO;  //ÅäÖÃÒý½ÅÎª"IO"Òý½Å			
	TRXEM_GPIO3_DIR &= ~ TRXEM_GPIO3_IO;  //ÅäÖÃÒý½ÅÎª"ÊäÈë"
	TRXEM_GPIO3_IES |= TRXEM_GPIO3_IO;	  // ÏÂ½µÑØÊ±ÖÃÎ»¸÷×ÔµÄPxIFGx±êÖ¾
	TRXEM_GPIO3_IFG &= ~ TRXEM_GPIO3_IO;  // Çå³ýÖÐ¶Ï±êÖ¾Î»
	TRXEM_GPIO3_IE |= TRXEM_GPIO3_IO;	  // ´ò¿ª P1.0 ÖÐ¶Ï
}


/****************************************************************************
*º¯ÊýÃû-Function:	void Initial_CC112x(void)
*ÃèÊö- Description:		³õÊ¼»¯ÉèÖÃ:  "CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
*ÊäÈë²ÎÊý-Input:	None
*Êä³ö²ÎÊý-output:	None
*×¢ÒâÊÂÏî-Note£º	¡ø01)    	¡ø02)    	¡ø03)    ¡ø04)  
*****************************************************************************/
void Initial_CC112x(void)  //³õÊ¼»¯ÉèÖÃ:  "CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
{
////////////////////////////////////////////////////////////////////////////
//==**SPI_B Ä£¿é³õÊ¼»¯--½Óµ½CC112xµÄSPIÒý½Å**===//
	Initial_SPI_CC112x();  //³õÊ¼»¯: SPI´®ÐÐ½Ó¿Ú(CC112x)

////////////////////////////////////////////////////////////////////////////
//==**³õÊ¼»¯:  GPIOµçÆ½ÖÐ¶Ï--CC112xµÄGPIO3×÷ÎªÖÐ¶ÏÔ´**===//
	Initial_GPIO_Int_CC112x();  //³õÊ¼»¯:  GPIOµçÆ½ÖÐ¶Ï

////////////////////////////////////////////////////////////////////////////
//==**³õÊ¼»¯CC112xµÄÅäÖÃ¼Ä´æÆ÷--Write radio registers**=========//
	registerConfig(); 

////////////////////////////////////////////////////////////////////////////
//==**¸ù¾Ý¿±Îó±íÐ£×¼CC112x--Calibrate radio according to errata**=====//
	manualCalibration();

////////////////////////////////////////////////////////////////////////////
//==**³õÊ¼ÅäÖÃCC112x ´¦ÓÚ½ÓÊÕ×´Ì¬--Set radio in RX**==========//
	trxSpiCmdStrobe(CC112X_SRX);
}



/****************************************************************************
*º¯ÊýÃû-Function:	void Deal_RX_CC112x(void)
*ÃèÊö- Description:		´¦Àí½ÓÊÕ²¿·Ö"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
*ÊäÈë²ÎÊý-Input:	None
*Êä³ö²ÎÊý-output:	None
*×¢ÒâÊÂÏî-Note£º 
	¡ø01) 	¡ø02) 	¡ø03) 	¡ø04)  
*****************************************************************************/
void Deal_RX_CC112x(void)  //´¦Àí½ÓÊÕ²¿·Ö"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
{
	unsigned char rxBuffer[128] = {0};
	unsigned char rxBytes;
	unsigned char marcStatus;


	//ÅÐ¶ÏCC112xÊÇ·ñ½ÓÊÕµ½Êý¾Ý //Wait for packet received interrupt 
	//µ±½ÓÊÕ³É¹¦Ò»¸öÊý¾Ý°üÊ±£¬ÏàÓ¦µÄGPIOx²úÉú"ÏÂ½µÑØÖÐ¶Ï"(´ËÇý¶¯Ñ¡ÓÃGPIO3)
	if(packetSemaphore == ISR_ACTION_REQUIRED)
	{
		//¶Á³ö½ÓÊÕµ½µÄÊý¾Ý×Ö½ÚÊý// Read number of bytes in rx fifo
		cc112xSpiReadReg(CC112X_NUM_RXBYTES, &rxBytes, 1);

		//Èç¹û×Ö½ÚÊý²»Îª0£¬Ôò´ÓRX FIFO¶Á³ö½ÓÊÕµ½µÄÊý¾Ý// Check that we have bytes in fifo
		if(rxBytes != 0)
		{
			//¶ÁÈ¡MARCSTATE¼Ä´æÖµ£¬²é¿´ÊÇ·ñ·¢Éú"½ÓÊÕ´íÎó"// Read marcstate to check for RX FIFO error
			cc112xSpiReadReg(CC112X_MARCSTATE, &marcStatus, 1);

			//Èç¹û·¢Éú"½ÓÊÕ´íÎó"£¬ÔòÇå¿ÕRX FIFO»º³åÇø// Mask out marcstate bits and check if we have a RX FIFO error
			if((marcStatus & 0x1F) == RX_FIFO_ERROR)
			{
				//Çå¿ÕRX FIFO»º³åÇø// Flush RX Fifo
				trxSpiCmdStrobe(CC112X_SFRX);
			}
			else   //Ã»ÓÐ·¢Éú"½ÓÊÕ´íÎó"£¬Ôò´ÓRX FIFO»º³åÇø¶Á³ö½ÓÊÕµ½µÄn¸öÊý¾Ý
			{
				//´ÓRX FIFO¶Á³ö½ÓÊÕµ½µÄn¸öÊý¾Ý// Read n bytes from rx fifo
				cc112xSpiReadRxFifo(rxBuffer, rxBytes);  

				// RX FIFO ×îºóÁ½¸ö×Ö½ÚÎªCRCÐ£Ñé×Ö
				// Check CRC ok (CRC_OK: bit7 in second status byte)
				// This assumes status bytes are appended in RX_FIFO
				// (PKT_CFG1.APPEND_STATUS = 1.)
				// If CRC is disabled the CRC_OK field will read 1
				//Ð£Ñé×ÖµÄ×îºóÒ»¸ö×Ö½ÚµÄ×î¸ßÎ»ÎªCRC_OK
				//CRC_OK=1Ê±£¬±íÊ¾Êý¾Ý°üÕýÈ·½ÓÊÕ¡£
				if(rxBuffer[rxBytes-1] & 0x80)
				{
					// Update packet counter
					CC112x_RX_PacketCnt++;
				}
			}
		}


		//´¦ÀíÍê½ÓÊÕµ½µÄÊý¾Ý°ü£¬¸´Î»Êý¾Ý°ü×´Ì¬±äÁ¿// Reset packet semaphore
		packetSemaphore = ISR_IDLE;

		//ÅäÖÃCC112x ´¦ÓÚ½ÓÊÕ×´Ì¬// Set radio back in RX
		trxSpiCmdStrobe(CC112X_SRX);

	}


}


/****************************************************************************
*º¯ÊýÃû-Function:	void TX_String_CC112x(void)
*ÃèÊö- Description:		CC112x·¢ËÍÊý¾Ý(×Ö·û´®)-- "CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
*ÊäÈë²ÎÊý-Input:	pData: Òª·¢ËÍµÄ×Ö·û´®Êý×é;  len:·¢ËÍµÄ×Ü×Ö½ÚÊý
*Êä³ö²ÎÊý-output:	None
*×¢ÒâÊÂÏî-Note£º 
	¡ø01) len <= 128
	¡ø02) 	¡ø03) 	¡ø04)  
*****************************************************************************/
void TX_String_CC112x(unsigned char *pData, unsigned char len) //CC112x·¢ËÍÊý¾Ý(×Ö·û´®)-- "CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
{
	//½«Òª·¢ËÍµÄÊý¾Ý£¬Ð´ÈëTX FIFO »º³åÆ÷// Write packet to tx fifo
	cc112xSpiWriteTxFifo(pData,len);
	
	//ÅäÖÃCC112xÎª·¢ËÍ×´Ì¬£¬Æô¶¯·¢ËÍ// Strobe TX to send packet
	trxSpiCmdStrobe(CC112X_STX);
	
	// Wait for interrupt that packet has been sent. 
	// (Assumes the GPIO connected to the radioRxTxISR function is set 
	// to GPIOx_CFG = 0x06)
	while(!packetSemaphore);  //µÈ´ýÊý¾Ý°ü·¢ËÍÍê³É
	
	//·¢ËÍÍêÊý¾Ý°ü£¬¸´Î»Êý¾Ý°ü×´Ì¬±äÁ¿// Clear semaphore flag
	packetSemaphore = ISR_IDLE;
	
	//CC112x ·¢ËÍÍêÊý¾Ý°üºó£¬·µ»Ø½ÓÊÕ×´Ì¬// Set radio in RX
	trxSpiCmdStrobe(CC112X_SRX);


}



/****************************************************************************
*º¯ÊýÃû-Function:	void Config_FrequencyBand(unsigned char bandKind)
*ÃèÊö- Description:		ÅäÖÃ:Æµ¶Î--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
*ÊäÈë²ÎÊý-Input:	bandKind
*Êä³ö²ÎÊý-output:	None
*×¢ÒâÊÂÏî-Note£º 
	¡ø01) 	Ä¬ÈÏÅäÖÃÎª410.0 - 480.0 MHzÆµ¶Î
	¡ø02) 	1<= bandKind <=6
	¡ø03) 	¡ø04)  
*****************************************************************************/
void Config_FrequencyBand(unsigned char bandKind)  //ÅäÖÃ:Æµ¶Î--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
{
	unsigned char bandSelect = 0;


	switch(bandKind) 
	{
		case CC112X_820_band:  //0010=820.0 - 960.0 MHz band
			bandSelect = 0x02;
			break;	

		case CC112X_410_band: //0100=410.0 - 480.0 MHz band
			bandSelect = 0x04;
			break;	
			
		case CC112X_273_3_band: //0110=273.3 - 320.0 MHz band 
			bandSelect = 0x06;
			break;		

		case CC112X_205_band: //1000=205.0 - 240.0 MHz band 
			bandSelect = 0x08;
			break;
			
		case CC112X_164_band: //1010=164.0 - 192.0 MHz band 
			bandSelect = 0x0A;
			break;		
		
		case CC112X_136_7_band: //1011=136.7 - 160.0 MHz band
			bandSelect = 0x0B;
			break;

////////////////////////////////////////////////////////////////////////////
		default:    //Ä¬ÈÏÅäÖÃÎª410.0 - 480.0 MHzÆµ¶Î
			bandSelect = 0x04;  //0100=410.0 - 480.0 MHz band
			break;
	}

	//ÐÞ¸ÄÏàÓ¦µÄ¼Ä´æÆ÷Öµ
	cc112xSpiWriteReg(CC112X_FS_CFG, &bandSelect, 1);  //ÆµÂÊºÏ³ÉÆ÷µÄÅäÖÃ

}


/****************************************************************************
*º¯ÊýÃû-Function:	void Config_CarrierFrequency(unsigned char frenquency_2,unsigned char frenquency_1,unsigned char frenquency_0)
*ÃèÊö- Description:		ÅäÖÃ:ÔØ²¨ÆµÂÊ--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
*ÊäÈë²ÎÊý-Input:	frenquency_2,frenquency_1,frenquency_0
*Êä³ö²ÎÊý-output:	None
*×¢ÒâÊÂÏî-Note£º 
	¡ø01) 	Ö»ÊÊÓÃÓÚ410.0 - 480.0 MHzÆµ¶Î
	¡ø02) 	ÔØ²¨ÆµÂÊµÄ¼ÆËã¹«Ê½£¬Çë²ÎÔÄCC112x User's Guide
	¡ø03) 	434Mhz¶ÔÓ¦µÄ¼Ä´æÆ÷ÖµCC112X_FREQ2=0x6C£¬CC112X_FREQ1=0x80£¬CC112X_FREQ0=0x00
	¡ø04)  
*****************************************************************************/
void Config_CarrierFrequency(unsigned char frenquency_2,unsigned char frenquency_1,unsigned char frenquency_0)  //ÅäÖÃ:ÔØ²¨ÆµÂÊ--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
{
	//ÐÞ¸ÄÏàÓ¦µÄ¼Ä´æÆ÷Öµ
	cc112xSpiWriteReg(CC112X_FREQ2, &frenquency_2, 1);  //ÔØ²¨ÆµÂÊÅäÖÃ
	cc112xSpiWriteReg(CC112X_FREQ1, &frenquency_1, 1);
	cc112xSpiWriteReg(CC112X_FREQ0, &frenquency_0, 1);

}


/****************************************************************************
*º¯ÊýÃû-Function:	void Config_RxFilterBW(unsigned char rxFilterBW)
*ÃèÊö- Description:		ÅäÖÃ:½ÓÊÕÂË²¨Æ÷´ø¿í--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
*ÊäÈë²ÎÊý-Input:	rxFilterBW
*Êä³ö²ÎÊý-output:	None
*×¢ÒâÊÂÏî-Note£º 
	¡ø01) 	½ÓÊÕÂË²¨Æ÷´ø¿íµÄ¼ÆËã¹«Ê½£¬Çë²ÎÔÄCC112x User's Guide
	¡ø02) 	¶ÔÓÚCC1120£¬½ÓÊÕÂË²¨Æ÷´ø¿í25kbps ¶ÔÓ¦µÄ¼Ä´æÆ÷ÖµCC112X_CHAN_BW=0x08
	¡ø03) 	  Bite rate(DataRate) < 	RX filter BW /2
	¡ø04)  
*****************************************************************************/
void Config_RxFilterBW(unsigned char rxFilterBW)  //ÅäÖÃ:½ÓÊÕÂË²¨Æ÷´ø¿í--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
{
	//ÐÞ¸ÄÏàÓ¦µÄ¼Ä´æÆ÷Öµ
	cc112xSpiWriteReg(CC112X_CHAN_BW, &rxFilterBW, 1);  //ÐÅµÀÂË²¨Æ÷ÅäÖÃ
}


/****************************************************************************
*º¯ÊýÃû-Function:	void Config_DataRate(unsigned char dataRate_2,unsigned char dataRate_1,unsigned char dataRate_0)
*ÃèÊö- Description:		ÅäÖÃ:Êý¾ÝËÙÂÊ--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
*ÊäÈë²ÎÊý-Input:	dataRate_2,dataRate_1,dataRate_0
*Êä³ö²ÎÊý-output:	None
*×¢ÒâÊÂÏî-Note£º 
	¡ø01) 	Êý¾ÝËÙÂÊµÄ¼ÆËã¹«Ê½£¬Çë²ÎÔÄCC112x User's Guide
	¡ø02) 	1.2kbps ¶ÔÓ¦µÄ¼Ä´æÆ÷ÖµCC112X_DRATE2=0x43£¬CC112X_DRATE1=0xA9£¬CC112X_DRATE0=0x2A
	¡ø03) 	  Bite rate(DataRate) < 	RX filter BW /2
	¡ø04)  
*****************************************************************************/
void Config_DataRate(unsigned char dataRate_2,unsigned char dataRate_1,unsigned char dataRate_0)  //ÅäÖÃ:Êý¾ÝËÙÂÊ--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
{
	//ÐÞ¸ÄÏàÓ¦µÄ¼Ä´æÆ÷Öµ
	cc112xSpiWriteReg(CC112X_DRATE2, &dataRate_2, 1);  //Êý¾ÝËÙÂÊÅäÖÃ
	cc112xSpiWriteReg(CC112X_DRATE1, &dataRate_1, 1);
	cc112xSpiWriteReg(CC112X_DRATE0, &dataRate_0, 1);

}


/****************************************************************************
*º¯ÊýÃû-Function:	void Config_ModulationFormat_Deviation(unsigned char modulation,unsigned char deviation)
*ÃèÊö- Description:		ÅäÖÃ:µ÷ÖÆ¸ñÊ½ºÍÆµÂÊÆ«²î--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
*ÊäÈë²ÎÊý-Input:	modulation,deviation
*Êä³ö²ÎÊý-output:	None
*×¢ÒâÊÂÏî-Note£º 
	¡ø01) 	ÆµÂÊÆ«²îµÄ¼ÆËã¹«Ê½£¬Çë²ÎÔÄCC112x User's Guide
	¡ø02) 	MODCFG_DEV_E-µ÷ÖÆ¸ñÊ½ºÍÆµÂÊÆ«²îÅäÖÃ//¸´Î»Öµ=0x03
				//MODEM_MODE µ÷ÖÆ½âµ÷Æ÷Ä£Ê½ÅäÖÃ= 00 =ÆÕÍ¨Ä£Ê½
				//MOD_FORMAT µ÷ÖÆ¸ñÊ½=000= "2-FSK"    //001=2-GFSK //010=Reserved //011=ASK/OOK //100=4-FSK //101=4-GFSK //110=SC-MSK unshaped (CC1125, TX only). For CC1120, CC1121, and CC1175this setting is reserved  //111=SC-MSK shaped (CC1125, TX only). For CC1120, CC1121, and CC1175 thissetting is reserved
				//DEV_E  ÆµÂÊÆ«²î£¨Ö¸Êý²¿·Ö£©= 011
	¡ø03) 	Ä¬ÈÏMOD_FORMAT µ÷ÖÆ¸ñÊ½=000= "2-FSK", ÆµÂÊÆ«²î= 3.99780 kHz
	               ¶ÔÓ¦µÄmodulation=0x00£¬deviation=0x03
	¡ø04)  
*****************************************************************************/
void Config_ModulationFormat_Deviation(unsigned char modulation,unsigned char deviation)  //ÅäÖÃ:µ÷ÖÆ¸ñÊ½ºÍÆµÂÊÆ«²î--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
{
	unsigned char configData;

	switch(modulation) 
	{
		case CC112X_2_FSK_mode:	//bit5:3=000="2-FSK"
			configData = 0x00;
			break;	

		case CC112X_2_GFSK_mode: //bit5:3=001=2-GFSK 
			configData = 0x08;
			break;	

		case CC112X_ASK_OOK_mode: //bit5:3=011=ASK/OOK
			configData = 0x18;
			break;	
			
		case CC112X_4_FSK_mode: //bit5:3=100=4-FSK
			configData = 0x20;
			break;	
			
		case CC112X_4_GFSK_mode: //bit5:3=101=4-GFSK  
			configData = 0x28;
			break;	

////////////////////////////////////////////////////////////////////////////
		default:  //Ä¬ÈÏMOD_FORMAT µ÷ÖÆ¸ñÊ½=000= "2-FSK"
			configData = 0x00; //bit5:3=000="2-FSK"
			break;
	}

	configData += deviation;

	//ÐÞ¸ÄÏàÓ¦µÄ¼Ä´æÆ÷Öµ
	cc112xSpiWriteReg(CC112X_MODCFG_DEV_E, &configData, 1);  //Êý¾ÝËÙÂÊÅäÖÃ
}



/****************************************************************************
*º¯ÊýÃû-Function:	void Config_PA_TxPower(unsigned char txPower)
*ÃèÊö- Description:		ÅäÖÃ:·¢Éä¹¦ÂÊ(¹¦ÂÊ·Å´óÆ÷)--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
*ÊäÈë²ÎÊý-Input:	txPower
*Êä³ö²ÎÊý-output:	None
*×¢ÒâÊÂÏî-Note£º 
	¡ø01) 	Ä¬ÈÏ·¢Éä¹¦ÂÊ = 15 dBm  (×î´ó¹¦ÂÊ)
	¡ø02) 		¡ø03) 		¡ø04)  
*****************************************************************************/
void Config_PA_TxPower(unsigned char txPower)  //ÅäÖÃ:·¢Éä¹¦ÂÊ(¹¦ÂÊ·Å´óÆ÷)--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
{
	unsigned char configData;

	switch(txPower) 
	{
		case CC112X_15dBm_TxPower:	//0x7F=·¢Éä¹¦ÂÊ= 15dBm
			configData = 0x7F;
			break;	

		case CC112X_14dBm_TxPower: //0x7D=·¢Éä¹¦ÂÊ= 14dBm
			configData = 0x7D;
			break;	

		case CC112X_13dBm_TxPower: //0x7B=·¢Éä¹¦ÂÊ= 13dBm
			configData = 0x7B;
			break;	
			
		case CC112X_12dBm_TxPower: //0x79=·¢Éä¹¦ÂÊ= 12dBm
			configData = 0x79;
			break;	

		case CC112X_11dBm_TxPower: //0x77=·¢Éä¹¦ÂÊ= 11dBm
			configData = 0x77;
			break;	
			
		case CC112X_10dBm_TxPower: //0x74=·¢Éä¹¦ÂÊ= 10dBm
			configData = 0x74;
			break;	
		
		case CC112X_09dBm_TxPower: //0x72=·¢Éä¹¦ÂÊ= 09dBm
			configData = 0x72;
			break;	
			
		case CC112X_08dBm_TxPower: //0x6F=·¢Éä¹¦ÂÊ= 08dBm
			configData = 0x6F;
			break;	
				
		case CC112X_07dBm_TxPower: //0x6D=·¢Éä¹¦ÂÊ= 07dBm
			configData = 0x6D;
			break;	
		
		case CC112X_06dBm_TxPower: //0x6B=·¢Éä¹¦ÂÊ= 06dBm
			configData = 0x6B;
			break;	
			
		case CC112X_05dBm_TxPower: //0x69=·¢Éä¹¦ÂÊ= 05dBm
			configData = 0x69;
			break;	

		case CC112X_04dBm_TxPower: //0x66=·¢Éä¹¦ÂÊ= 04dBm
			configData = 0x66;
			break;	
			
		case CC112X_03dBm_TxPower: //0x64=·¢Éä¹¦ÂÊ= 03dBm
			configData = 0x64;
			break;	
		
		case CC112X_02dBm_TxPower: //0x62=·¢Éä¹¦ÂÊ= 02dBm 
			configData = 0x62;
			break;	
			
		case CC112X_01dBm_TxPower: //0x5F=·¢Éä¹¦ÂÊ= 01dBm
			configData = 0x5F;
			break;	
			
		case CC112X_00dBm_TxPower: //0x5D=·¢Éä¹¦ÂÊ= 00dBm 
			configData = 0x5D;
			break;	
	
		case CC112X__3dBm_TxPower: //0x56=·¢Éä¹¦ÂÊ= -3dBm
			configData = 0x56;
			break;	
			
		case CC112X__6dBm_TxPower: //0x4F=·¢Éä¹¦ÂÊ= -6dBm
			configData = 0x4F;
			break;	
			
		case CC112X__11dBm_TxPower: //0x43=·¢Éä¹¦ÂÊ= -11dBm
			configData = 0x43;
			break;	

////////////////////////////////////////////////////////////////////////////
		default:  //Ä¬ÈÏ·¢Éä¹¦ÂÊ = 15 dBm  (×î´ó¹¦ÂÊ)
			configData = 0x7F;  //0x7F=·¢Éä¹¦ÂÊ= 15dBm
			break;
	}

	//ÐÞ¸ÄÏàÓ¦µÄ¼Ä´æÆ÷Öµ
	cc112xSpiWriteReg(CC112X_PA_CFG2, &configData, 1);  //¹¦ÂÊ·Å´óÆ÷ÅäÖÃ
}



/****************************************************************************
*º¯ÊýÃû-Function:	void Config_DeviceAddress(unsigned char deviceAddress) 
*ÃèÊö- Description:		ÅäÖÃ:Éè±¸µØÖ·--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
*ÊäÈë²ÎÊý-Input:	deviceAddress
*Êä³ö²ÎÊý-output:	None
*×¢ÒâÊÂÏî-Note£º 
	¡ø01) 	Ä¬ÈÏÉè±¸µØÖ·Device Address = 0 
	¡ø02) 	Éè±¸µØÖ·Îª1¸ö×Ö½Ú
	¡ø03)  	ÔÚ½ÓÊÕÊý¾Ý°ü¹ýÂËÊ±Ê¹ÓÃµÄµØÖ·
	¡ø04)  ¸ù¾ÝCC112X_PKT_CFG1.ADDR_CHECK_CFGÎ»¶ÎµÄÖµ£¬¾ö¶¨ÊÇ·ñ¡°Ê¹ÄÜµØÖ·¼ì²é¡±
*****************************************************************************/
void Config_DeviceAddress(unsigned char deviceAddress)  //ÅäÖÃ:Éè±¸µØÖ·--"CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
{
	//ÐÞ¸ÄÏàÓ¦µÄ¼Ä´æÆ÷Öµ
	cc112xSpiWriteReg(CC112X_DEV_ADDR, &deviceAddress, 1);  //Éè±¸µØÖ·ÅäÖÃ
}






/****************************************************************************
*º¯ÊýÃû-Function:	void TX_String_CC112x(void)
*ÃèÊö- Description:		CC112x·¢ËÍÊý¾Ý(×Ö·û´®)-- "CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
*ÊäÈë²ÎÊý-Input:	pData: Òª·¢ËÍµÄ×Ö·û´®Êý×é;  len:·¢ËÍµÄ×Ü×Ö½ÚÊý
*Êä³ö²ÎÊý-output:	None
*×¢ÒâÊÂÏî-Note£º 
	¡ø01)   	¡ø02) 	¡ø03) 	¡ø04)  
******************************
void TX_String_CC112x(unsigned char *pData, unsigned char len) //CC112x·¢ËÍÊý¾Ý(×Ö·û´®)-- "CC112x µÍ¹¦ºÄÎÞÏßÉäÆµÊÕ·¢Æ÷"
{

	
	// Create a random packet with PKTLEN + 2 byte packet counter + n x random bytes
	createPacket(txBuffer);
	
	// Write packet to tx fifo
	cc112xSpiWriteTxFifo(txBuffer,sizeof(txBuffer));
	
	//ÅäÖÃCC112xÎª·¢ËÍ×´Ì¬// Strobe TX to send packet
	trxSpiCmdStrobe(CC112X_STX);
	
	// Wait for interrupt that packet has been sent. 
	// (Assumes the GPIO connected to the radioRxTxISR function is set 
	// to GPIOx_CFG = 0x06)
	while(!packetSemaphore);
	
	//·¢ËÍÍêÊý¾Ý°ü£¬¸´Î»Êý¾Ý°ü×´Ì¬±äÁ¿// Clear semaphore flag
	packetSemaphore = ISR_IDLE;
	
	//CC112x ·¢ËÍÍêÊý¾Ý°üºó£¬·µ»Ø½ÓÊÕ×´Ì¬// Set radio in RX
	trxSpiCmdStrobe(CC112X_SRX);


}
***********************************************/


/*******************************************************************************
* @fn          registerConfig
*
* @brief       Write register settings as given by SmartRF Studio found in
*              cc112x_easy_link_reg_config.h
*
* @param       none
*
* @return      none
*/
static void registerConfig(void){
  
  uint8 writeByte;
  
  // Reset radio
  trxSpiCmdStrobe(CC112X_SRES);
  
  // Write registers to radio
  for(uint16 i = 0; i < (sizeof  preferredSettings/sizeof(registerSetting_t)); i++) 
  {  
    writeByte =  preferredSettings[i].data; 
    cc112xSpiWriteReg( preferredSettings[i].addr, &writeByte, 1);
  }
}
/******************************************************************************
 * @fn          createPacket
 *
 * @brief       This function is called before a packet is transmitted. It fills
 *              the txBuffer with a packet consisting of a length byte, two
 *              bytes packet counter and n random bytes.
 *
 *              The packet format is as follows:
 *              |--------------------------------------------------------------|
 *              |           |           |           |         |       |        |
 *              | pktLength | pktCount1 | pktCount0 | rndData |.......| rndData|
 *              |           |           |           |         |       |        |
 *              |--------------------------------------------------------------|
 *               txBuffer[0] txBuffer[1] txBuffer[2]  ......... txBuffer[PKTLEN]
 *                
 * @param       pointer to start of txBuffer
 *
 * @return      none

static void createPacket(uint8 txBuffer[]){
  
  txBuffer[0] = PKTLEN;                     // Length byte
//  txBuffer[1] = (uint8) (packetCounter >> 8); // MSB of packetCounter
//  txBuffer[2] = (uint8) packetCounter;      // LSB of packetCounter
  
  // Fill rest of buffer with random bytes
  for(uint8 i =3; i< (PKTLEN+1); i++)
  {
    txBuffer[i] = (uint8)rand();
  }
}
*/


/******************************************************************************
 * @fn          manualCalibration
 *
 * @brief       calibrates radio according to CC112x errata
 *                
 * @param       none
 *
 * @return      none
 */
#define VCDAC_START_OFFSET 2
#define FS_VCO2_INDEX 0
#define FS_VCO4_INDEX 1
#define FS_CHP_INDEX 2
static void manualCalibration(void) {
  
    uint8 original_fs_cal2;
    uint8 calResults_for_vcdac_start_high[3];
    uint8 calResults_for_vcdac_start_mid[3];
    uint8 marcstate;
    uint8 writeByte;
    
    // 1) Set VCO cap-array to 0 (FS_VCO2 = 0x00)
    writeByte = 0x00;
    cc112xSpiWriteReg(CC112X_FS_VCO2, &writeByte, 1);
    
    // 2) Start with high VCDAC (original VCDAC_START + 2):
    cc112xSpiReadReg(CC112X_FS_CAL2, &original_fs_cal2, 1);
    writeByte = original_fs_cal2 + VCDAC_START_OFFSET;
    cc112xSpiWriteReg(CC112X_FS_CAL2, &writeByte, 1);
    
    // 3) Calibrate and wait for calibration to be done (radio back in IDLE state)
    trxSpiCmdStrobe(CC112X_SCAL);
    
    do 
    {
        cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);
    } while (marcstate != 0x41);
    
    // 4) Read FS_VCO2, FS_VCO4 and FS_CHP register obtained with high VCDAC_START value
    cc112xSpiReadReg(CC112X_FS_VCO2, &calResults_for_vcdac_start_high[FS_VCO2_INDEX], 1);
    cc112xSpiReadReg(CC112X_FS_VCO4, &calResults_for_vcdac_start_high[FS_VCO4_INDEX], 1);
    cc112xSpiReadReg(CC112X_FS_CHP, &calResults_for_vcdac_start_high[FS_CHP_INDEX], 1);
    
    // 5) Set VCO cap-array to 0 (FS_VCO2 = 0x00)
    writeByte = 0x00;
    cc112xSpiWriteReg(CC112X_FS_VCO2, &writeByte, 1);
    
    // 6) Continue with mid VCDAC (original VCDAC_START):
    writeByte = original_fs_cal2;
    cc112xSpiWriteReg(CC112X_FS_CAL2, &writeByte, 1);
    
    // 7) Calibrate and wait for calibration to be done (radio back in IDLE state)
    trxSpiCmdStrobe(CC112X_SCAL);
    
    do 
    {
        cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);
    } while (marcstate != 0x41);
    
    // 8) Read FS_VCO2, FS_VCO4 and FS_CHP register obtained with mid VCDAC_START value
    cc112xSpiReadReg(CC112X_FS_VCO2, &calResults_for_vcdac_start_mid[FS_VCO2_INDEX], 1);
    cc112xSpiReadReg(CC112X_FS_VCO4, &calResults_for_vcdac_start_mid[FS_VCO4_INDEX], 1);
    cc112xSpiReadReg(CC112X_FS_CHP, &calResults_for_vcdac_start_mid[FS_CHP_INDEX], 1);
    
    // 9) Write back highest FS_VCO2 and corresponding FS_VCO and FS_CHP result
    if (calResults_for_vcdac_start_high[FS_VCO2_INDEX] > calResults_for_vcdac_start_mid[FS_VCO2_INDEX]) 
    {
        writeByte = calResults_for_vcdac_start_high[FS_VCO2_INDEX];
        cc112xSpiWriteReg(CC112X_FS_VCO2, &writeByte, 1);
        writeByte = calResults_for_vcdac_start_high[FS_VCO4_INDEX];
        cc112xSpiWriteReg(CC112X_FS_VCO4, &writeByte, 1);
        writeByte = calResults_for_vcdac_start_high[FS_CHP_INDEX];
        cc112xSpiWriteReg(CC112X_FS_CHP, &writeByte, 1);
    }
    else 
    {
        writeByte = calResults_for_vcdac_start_mid[FS_VCO2_INDEX];
        cc112xSpiWriteReg(CC112X_FS_VCO2, &writeByte, 1);
        writeByte = calResults_for_vcdac_start_mid[FS_VCO4_INDEX];
        cc112xSpiWriteReg(CC112X_FS_VCO4, &writeByte, 1);
        writeByte = calResults_for_vcdac_start_mid[FS_CHP_INDEX];
        cc112xSpiWriteReg(CC112X_FS_CHP, &writeByte, 1);
    }
}


// PORT1 ÖÐ¶Ï·þÎñ³ÌÐò PORT1 interrupt service routine 
#pragma vector=PORT1_VECTOR
__interrupt void port_1(void)
{
	// Set packet semaphore
	packetSemaphore = ISR_ACTION_REQUIRED;	
	
	TRXEM_GPIO3_IFG &= ~ TRXEM_GPIO3_IO; //Çå³ýÖÐ¶Ï±êÖ¾Î»  Clear isr flag
	mNop;
}



/***********************************************************************************
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
***********************************************************************************/
