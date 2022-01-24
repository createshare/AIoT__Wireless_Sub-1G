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

#include "System.h"	 //"ϵͳ" ���ù��ܺ�����-ͷ�ļ�

/////////////////////////////////
#include "msp430.h"

#include "hal_spi_rf_trxeb.h"

#include "cc112x_spi.h"
#include "stdlib.h"
#include "cc112x_easy_link.h"  //"CC112x �͹���������Ƶ�շ���"-��������(�ⲿ��Դ)-ͷ�ļ�



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
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned int CC112x_RX_PacketCnt = 0;
unsigned int CC112x_TX_PacketCnt = 0;
unsigned char CC112x_TxBuf[128] = {0}; //  ���ͻ��������ֽ���<128



/******************************************************************************
* LOCAL VARIABLES
*/
static uint8  packetSemaphore = 0;


/****************************************************************************
*������-Function:	static void Initial_GPIO_Interrupt(void)
*����- Description:		��ʼ��: SPI���нӿ�(CC112x)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
static void Initial_SPI_CC112x(void)  //��ʼ��: SPI���нӿ�(CC112x)
{
	//��ʼ��SPI ���нӿ�
		// Instantiate tranceiver RF spi interface to SCLK ~ 4 MHz */
		//input clockDivider - SMCLK/clockDivider gives SCLK frequency
				//trxRfSpiInterfaceInit(0x02);
	trxRfSpiInterfaceInit(0x01);

////////////////////////////////////////////////////////////////////////////
//care--�������ֻ������MSP430F6638ʵ���----------------//
	//--care--һ��Ҫ����������//"LCD_B �˿ڿ��ƼĴ���"�������
	LCDBPCTL0 = 0;

		//���ö�·������TS3A5017: ѡ��IN2 ��IN1
		//IN2=0; IN1=1; ��ӦSPI_B ����(CLK_B; SPI_MOSI_B; SPI_MISO_B)
	mConfig_TS3A5017_01_IN2(0);  //IN2 = 0
	mConfig_TS3A5017_01_IN1(1);  //IN1 = 1
}



/****************************************************************************
*������-Function:	static void Initial_GPIO_Int_CC112x(void)
*����- Description:		��ʼ��:  GPIO��ƽ�ж�(CC112x)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
static void Initial_GPIO_Int_CC112x(void)  //��ʼ��:  GPIO��ƽ�ж�
{
	TRXEM_GPIO3_SEL &= ~ TRXEM_GPIO3_IO;  //��������Ϊ"IO"����			
	TRXEM_GPIO3_DIR &= ~ TRXEM_GPIO3_IO;  //��������Ϊ"����"
	TRXEM_GPIO3_IES |= TRXEM_GPIO3_IO;	  // �½���ʱ��λ���Ե�PxIFGx��־
	TRXEM_GPIO3_IFG &= ~ TRXEM_GPIO3_IO;  // ����жϱ�־λ
	TRXEM_GPIO3_IE |= TRXEM_GPIO3_IO;	  // �� P1.0 �ж�
}


/****************************************************************************
*������-Function:	void Initial_CC112x(void)
*����- Description:		��ʼ������:  "CC112x �͹���������Ƶ�շ���"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
void Initial_CC112x(void)  //��ʼ������:  "CC112x �͹���������Ƶ�շ���"
{
////////////////////////////////////////////////////////////////////////////
//==**SPI_B ģ���ʼ��--�ӵ�CC112x��SPI����**===//
	Initial_SPI_CC112x();  //��ʼ��: SPI���нӿ�(CC112x)

////////////////////////////////////////////////////////////////////////////
//==**��ʼ��:  GPIO��ƽ�ж�--CC112x��GPIO3��Ϊ�ж�Դ**===//
	Initial_GPIO_Int_CC112x();  //��ʼ��:  GPIO��ƽ�ж�

////////////////////////////////////////////////////////////////////////////
//==**��ʼ��CC112x�����üĴ���--Write radio registers**=========//
	registerConfig(); 

////////////////////////////////////////////////////////////////////////////
//==**���ݿ����У׼CC112x--Calibrate radio according to errata**=====//
	manualCalibration();

////////////////////////////////////////////////////////////////////////////
//==**��ʼ����CC112x ���ڽ���״̬--Set radio in RX**==========//
	trxSpiCmdStrobe(CC112X_SRX);
}



/****************************************************************************
*������-Function:	void Deal_RX_CC112x(void)
*����- Description:		������ղ���"CC112x �͹���������Ƶ�շ���"
*�������-Input:	None
*�������-output:	None
*ע������-Note�� 
	��01) 	��02) 	��03) 	��04)  
*****************************************************************************/
void Deal_RX_CC112x(void)  //������ղ���"CC112x �͹���������Ƶ�շ���"
{
	unsigned char rxBuffer[128] = {0};
	unsigned char rxBytes;
	unsigned char marcStatus;


	//�ж�CC112x�Ƿ���յ����� //Wait for packet received interrupt 
	//�����ճɹ�һ�����ݰ�ʱ����Ӧ��GPIOx����"�½����ж�"(������ѡ��GPIO3)
	if(packetSemaphore == ISR_ACTION_REQUIRED)
	{
		//�������յ��������ֽ���// Read number of bytes in rx fifo
		cc112xSpiReadReg(CC112X_NUM_RXBYTES, &rxBytes, 1);

		//����ֽ�����Ϊ0�����RX FIFO�������յ�������// Check that we have bytes in fifo
		if(rxBytes != 0)
		{
			//��ȡMARCSTATE�Ĵ�ֵ���鿴�Ƿ���"���մ���"// Read marcstate to check for RX FIFO error
			cc112xSpiReadReg(CC112X_MARCSTATE, &marcStatus, 1);

			//�������"���մ���"�������RX FIFO������// Mask out marcstate bits and check if we have a RX FIFO error
			if((marcStatus & 0x1F) == RX_FIFO_ERROR)
			{
				//���RX FIFO������// Flush RX Fifo
				trxSpiCmdStrobe(CC112X_SFRX);
			}
			else   //û�з���"���մ���"�����RX FIFO�������������յ���n������
			{
				//��RX FIFO�������յ���n������// Read n bytes from rx fifo
				cc112xSpiReadRxFifo(rxBuffer, rxBytes);  

				// RX FIFO ��������ֽ�ΪCRCУ����
				// Check CRC ok (CRC_OK: bit7 in second status byte)
				// This assumes status bytes are appended in RX_FIFO
				// (PKT_CFG1.APPEND_STATUS = 1.)
				// If CRC is disabled the CRC_OK field will read 1
				//У���ֵ����һ���ֽڵ����λΪCRC_OK
				//CRC_OK=1ʱ����ʾ���ݰ���ȷ���ա�
				if(rxBuffer[rxBytes-1] & 0x80)
				{
					// Update packet counter
					CC112x_RX_PacketCnt++;
				}
			}
		}


		//��������յ������ݰ�����λ���ݰ�״̬����// Reset packet semaphore
		packetSemaphore = ISR_IDLE;

		//����CC112x ���ڽ���״̬// Set radio back in RX
		trxSpiCmdStrobe(CC112X_SRX);

	}


}


/****************************************************************************
*������-Function:	void TX_String_CC112x(void)
*����- Description:		CC112x��������(�ַ���)-- "CC112x �͹���������Ƶ�շ���"
*�������-Input:	pData: Ҫ���͵��ַ�������;  len:���͵����ֽ���
*�������-output:	None
*ע������-Note�� 
	��01) len <= 128
	��02) 	��03) 	��04)  
*****************************************************************************/
void TX_String_CC112x(unsigned char *pData, unsigned char len) //CC112x��������(�ַ���)-- "CC112x �͹���������Ƶ�շ���"
{
	//��Ҫ���͵����ݣ�д��TX FIFO ������// Write packet to tx fifo
	cc112xSpiWriteTxFifo(pData,len);
	
	//����CC112xΪ����״̬����������// Strobe TX to send packet
	trxSpiCmdStrobe(CC112X_STX);
	
	// Wait for interrupt that packet has been sent. 
	// (Assumes the GPIO connected to the radioRxTxISR function is set 
	// to GPIOx_CFG = 0x06)
	while(!packetSemaphore);  //�ȴ����ݰ��������
	
	//���������ݰ�����λ���ݰ�״̬����// Clear semaphore flag
	packetSemaphore = ISR_IDLE;
	
	//CC112x ���������ݰ��󣬷��ؽ���״̬// Set radio in RX
	trxSpiCmdStrobe(CC112X_SRX);


}



/****************************************************************************
*������-Function:	void Config_FrequencyBand(unsigned char bandKind)
*����- Description:		����:Ƶ��--"CC112x �͹���������Ƶ�շ���"
*�������-Input:	bandKind
*�������-output:	None
*ע������-Note�� 
	��01) 	Ĭ������Ϊ410.0 - 480.0 MHzƵ��
	��02) 	1<= bandKind <=6
	��03) 	��04)  
*****************************************************************************/
void Config_FrequencyBand(unsigned char bandKind)  //����:Ƶ��--"CC112x �͹���������Ƶ�շ���"
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
		default:    //Ĭ������Ϊ410.0 - 480.0 MHzƵ��
			bandSelect = 0x04;  //0100=410.0 - 480.0 MHz band
			break;
	}

	//�޸���Ӧ�ļĴ���ֵ
	cc112xSpiWriteReg(CC112X_FS_CFG, &bandSelect, 1);  //Ƶ�ʺϳ���������

}


/****************************************************************************
*������-Function:	void Config_CarrierFrequency(unsigned char frenquency_2,unsigned char frenquency_1,unsigned char frenquency_0)
*����- Description:		����:�ز�Ƶ��--"CC112x �͹���������Ƶ�շ���"
*�������-Input:	frenquency_2,frenquency_1,frenquency_0
*�������-output:	None
*ע������-Note�� 
	��01) 	ֻ������410.0 - 480.0 MHzƵ��
	��02) 	�ز�Ƶ�ʵļ��㹫ʽ�������CC112x User's Guide
	��03) 	434Mhz��Ӧ�ļĴ���ֵCC112X_FREQ2=0x6C��CC112X_FREQ1=0x80��CC112X_FREQ0=0x00
	��04)  
*****************************************************************************/
void Config_CarrierFrequency(unsigned char frenquency_2,unsigned char frenquency_1,unsigned char frenquency_0)  //����:�ز�Ƶ��--"CC112x �͹���������Ƶ�շ���"
{
	//�޸���Ӧ�ļĴ���ֵ
	cc112xSpiWriteReg(CC112X_FREQ2, &frenquency_2, 1);  //�ز�Ƶ������
	cc112xSpiWriteReg(CC112X_FREQ1, &frenquency_1, 1);
	cc112xSpiWriteReg(CC112X_FREQ0, &frenquency_0, 1);

}


/****************************************************************************
*������-Function:	void Config_RxFilterBW(unsigned char rxFilterBW)
*����- Description:		����:�����˲�������--"CC112x �͹���������Ƶ�շ���"
*�������-Input:	rxFilterBW
*�������-output:	None
*ע������-Note�� 
	��01) 	�����˲�������ļ��㹫ʽ�������CC112x User's Guide
	��02) 	����CC1120�������˲�������25kbps ��Ӧ�ļĴ���ֵCC112X_CHAN_BW=0x08
	��03) 	  Bite rate(DataRate) < 	RX filter BW /2
	��04)  
*****************************************************************************/
void Config_RxFilterBW(unsigned char rxFilterBW)  //����:�����˲�������--"CC112x �͹���������Ƶ�շ���"
{
	//�޸���Ӧ�ļĴ���ֵ
	cc112xSpiWriteReg(CC112X_CHAN_BW, &rxFilterBW, 1);  //�ŵ��˲�������
}


/****************************************************************************
*������-Function:	void Config_DataRate(unsigned char dataRate_2,unsigned char dataRate_1,unsigned char dataRate_0)
*����- Description:		����:��������--"CC112x �͹���������Ƶ�շ���"
*�������-Input:	dataRate_2,dataRate_1,dataRate_0
*�������-output:	None
*ע������-Note�� 
	��01) 	�������ʵļ��㹫ʽ�������CC112x User's Guide
	��02) 	1.2kbps ��Ӧ�ļĴ���ֵCC112X_DRATE2=0x43��CC112X_DRATE1=0xA9��CC112X_DRATE0=0x2A
	��03) 	  Bite rate(DataRate) < 	RX filter BW /2
	��04)  
*****************************************************************************/
void Config_DataRate(unsigned char dataRate_2,unsigned char dataRate_1,unsigned char dataRate_0)  //����:��������--"CC112x �͹���������Ƶ�շ���"
{
	//�޸���Ӧ�ļĴ���ֵ
	cc112xSpiWriteReg(CC112X_DRATE2, &dataRate_2, 1);  //������������
	cc112xSpiWriteReg(CC112X_DRATE1, &dataRate_1, 1);
	cc112xSpiWriteReg(CC112X_DRATE0, &dataRate_0, 1);

}


/****************************************************************************
*������-Function:	void Config_ModulationFormat_Deviation(unsigned char modulation,unsigned char deviation)
*����- Description:		����:���Ƹ�ʽ��Ƶ��ƫ��--"CC112x �͹���������Ƶ�շ���"
*�������-Input:	modulation,deviation
*�������-output:	None
*ע������-Note�� 
	��01) 	Ƶ��ƫ��ļ��㹫ʽ�������CC112x User's Guide
	��02) 	MODCFG_DEV_E-���Ƹ�ʽ��Ƶ��ƫ������//��λֵ=0x03
				//MODEM_MODE ���ƽ����ģʽ����= 00 =��ͨģʽ
				//MOD_FORMAT ���Ƹ�ʽ=000= "2-FSK"    //001=2-GFSK //010=Reserved //011=ASK/OOK //100=4-FSK //101=4-GFSK //110=SC-MSK unshaped (CC1125, TX only). For CC1120, CC1121, and CC1175this setting is reserved  //111=SC-MSK shaped (CC1125, TX only). For CC1120, CC1121, and CC1175 thissetting is reserved
				//DEV_E  Ƶ��ƫ�ָ�����֣�= 011
	��03) 	Ĭ��MOD_FORMAT ���Ƹ�ʽ=000= "2-FSK", Ƶ��ƫ��= 3.99780 kHz
	               ��Ӧ��modulation=0x00��deviation=0x03
	��04)  
*****************************************************************************/
void Config_ModulationFormat_Deviation(unsigned char modulation,unsigned char deviation)  //����:���Ƹ�ʽ��Ƶ��ƫ��--"CC112x �͹���������Ƶ�շ���"
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
		default:  //Ĭ��MOD_FORMAT ���Ƹ�ʽ=000= "2-FSK"
			configData = 0x00; //bit5:3=000="2-FSK"
			break;
	}

	configData += deviation;

	//�޸���Ӧ�ļĴ���ֵ
	cc112xSpiWriteReg(CC112X_MODCFG_DEV_E, &configData, 1);  //������������
}



/****************************************************************************
*������-Function:	void Config_PA_TxPower(unsigned char txPower)
*����- Description:		����:���书��(���ʷŴ���)--"CC112x �͹���������Ƶ�շ���"
*�������-Input:	txPower
*�������-output:	None
*ע������-Note�� 
	��01) 	Ĭ�Ϸ��书�� = 15 dBm  (�����)
	��02) 		��03) 		��04)  
*****************************************************************************/
void Config_PA_TxPower(unsigned char txPower)  //����:���书��(���ʷŴ���)--"CC112x �͹���������Ƶ�շ���"
{
	unsigned char configData;

	switch(txPower) 
	{
		case CC112X_15dBm_TxPower:	//0x7F=���书��= 15dBm
			configData = 0x7F;
			break;	

		case CC112X_14dBm_TxPower: //0x7D=���书��= 14dBm
			configData = 0x7D;
			break;	

		case CC112X_13dBm_TxPower: //0x7B=���书��= 13dBm
			configData = 0x7B;
			break;	
			
		case CC112X_12dBm_TxPower: //0x79=���书��= 12dBm
			configData = 0x79;
			break;	

		case CC112X_11dBm_TxPower: //0x77=���书��= 11dBm
			configData = 0x77;
			break;	
			
		case CC112X_10dBm_TxPower: //0x74=���书��= 10dBm
			configData = 0x74;
			break;	
		
		case CC112X_09dBm_TxPower: //0x72=���书��= 09dBm
			configData = 0x72;
			break;	
			
		case CC112X_08dBm_TxPower: //0x6F=���书��= 08dBm
			configData = 0x6F;
			break;	
				
		case CC112X_07dBm_TxPower: //0x6D=���书��= 07dBm
			configData = 0x6D;
			break;	
		
		case CC112X_06dBm_TxPower: //0x6B=���书��= 06dBm
			configData = 0x6B;
			break;	
			
		case CC112X_05dBm_TxPower: //0x69=���书��= 05dBm
			configData = 0x69;
			break;	

		case CC112X_04dBm_TxPower: //0x66=���书��= 04dBm
			configData = 0x66;
			break;	
			
		case CC112X_03dBm_TxPower: //0x64=���书��= 03dBm
			configData = 0x64;
			break;	
		
		case CC112X_02dBm_TxPower: //0x62=���书��= 02dBm 
			configData = 0x62;
			break;	
			
		case CC112X_01dBm_TxPower: //0x5F=���书��= 01dBm
			configData = 0x5F;
			break;	
			
		case CC112X_00dBm_TxPower: //0x5D=���书��= 00dBm 
			configData = 0x5D;
			break;	
	
		case CC112X__3dBm_TxPower: //0x56=���书��= -3dBm
			configData = 0x56;
			break;	
			
		case CC112X__6dBm_TxPower: //0x4F=���书��= -6dBm
			configData = 0x4F;
			break;	
			
		case CC112X__11dBm_TxPower: //0x43=���书��= -11dBm
			configData = 0x43;
			break;	

////////////////////////////////////////////////////////////////////////////
		default:  //Ĭ�Ϸ��书�� = 15 dBm  (�����)
			configData = 0x7F;  //0x7F=���书��= 15dBm
			break;
	}

	//�޸���Ӧ�ļĴ���ֵ
	cc112xSpiWriteReg(CC112X_PA_CFG2, &configData, 1);  //���ʷŴ�������
}



/****************************************************************************
*������-Function:	void Config_DeviceAddress(unsigned char deviceAddress) 
*����- Description:		����:�豸��ַ--"CC112x �͹���������Ƶ�շ���"
*�������-Input:	deviceAddress
*�������-output:	None
*ע������-Note�� 
	��01) 	Ĭ���豸��ַDevice Address = 0 
	��02) 	�豸��ַΪ1���ֽ�
	��03)  	�ڽ������ݰ�����ʱʹ�õĵ�ַ
	��04)  ����CC112X_PKT_CFG1.ADDR_CHECK_CFGλ�ε�ֵ�������Ƿ�ʹ�ܵ�ַ��顱
*****************************************************************************/
void Config_DeviceAddress(unsigned char deviceAddress)  //����:�豸��ַ--"CC112x �͹���������Ƶ�շ���"
{
	//�޸���Ӧ�ļĴ���ֵ
	cc112xSpiWriteReg(CC112X_DEV_ADDR, &deviceAddress, 1);  //�豸��ַ����
}






/****************************************************************************
*������-Function:	void TX_String_CC112x(void)
*����- Description:		CC112x��������(�ַ���)-- "CC112x �͹���������Ƶ�շ���"
*�������-Input:	pData: Ҫ���͵��ַ�������;  len:���͵����ֽ���
*�������-output:	None
*ע������-Note�� 
	��01)   	��02) 	��03) 	��04)  
******************************
void TX_String_CC112x(unsigned char *pData, unsigned char len) //CC112x��������(�ַ���)-- "CC112x �͹���������Ƶ�շ���"
{

	
	// Create a random packet with PKTLEN + 2 byte packet counter + n x random bytes
	createPacket(txBuffer);
	
	// Write packet to tx fifo
	cc112xSpiWriteTxFifo(txBuffer,sizeof(txBuffer));
	
	//����CC112xΪ����״̬// Strobe TX to send packet
	trxSpiCmdStrobe(CC112X_STX);
	
	// Wait for interrupt that packet has been sent. 
	// (Assumes the GPIO connected to the radioRxTxISR function is set 
	// to GPIOx_CFG = 0x06)
	while(!packetSemaphore);
	
	//���������ݰ�����λ���ݰ�״̬����// Clear semaphore flag
	packetSemaphore = ISR_IDLE;
	
	//CC112x ���������ݰ��󣬷��ؽ���״̬// Set radio in RX
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


// PORT1 �жϷ������ PORT1 interrupt service routine 
#pragma vector=PORT1_VECTOR
__interrupt void port_1(void)
{
	// Set packet semaphore
	packetSemaphore = ISR_ACTION_REQUIRED;	
	
	TRXEM_GPIO3_IFG &= ~ TRXEM_GPIO3_IO; //����жϱ�־λ  Clear isr flag
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
  PROVIDED �AS IS� WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
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
