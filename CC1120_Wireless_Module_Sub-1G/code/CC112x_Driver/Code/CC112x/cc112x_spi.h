/******************************************************************************
    Filename: CC112x_spi.h  
    
    Description: header file that defines a minimum set of neccessary functions
                 to communicate with CC112X over SPI as well as the regsister 
                 mapping. 
*******************************************************************************/

#ifndef CC112x_SPI_H
#define CC112x_SPI_H

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
 * INCLUDES
 */
#include "hal_types.h"
#include "hal_spi_rf_trxeb.h"

/******************************************************************************
 * CONSTANTS
 */
 
////////////////////////////////////////////////////////////////////////////
//ÅäÖÃ¼Ä´æÆ÷/* configuration registers */
#define CC112X_IOCFG3                   0x0000  //IOCFG3 -GPIO3Òý½ÅÅäÖÃ//¸´Î»Öµ=0x06 (¸´Î»Ê±Ñ¡"PKT_SYNC_RXTX" )
#define CC112X_IOCFG2                   0x0001	//IOCFG2 -GPIO2Òý½ÅÅäÖÃ//¸´Î»Öµ=0x07(¸´Î»Ê±Ñ¡"PKT_CRC_OK" )
#define CC112X_IOCFG1                   0x0002	//IOCFG1 -GPIO1Òý½ÅÅäÖÃ//¸´Î»Öµ=0x30(¸´Î»Ê±Ñ¡"HIGHZ"=  ¸ß×è¿¹ )
#define CC112X_IOCFG0                   0x0003	//IOCFG0 -GPIO0Òý½ÅÅäÖÃ//¸´Î»Öµ=0x3C(¸´Î»Ê±Ñ¡"EXT_OSC_EN"=  Ê¹ÄÜÍâ²¿Õñµ´Æ÷ )

	//SYNC0 ~ SYNC3-32Î»Í¬²½×Ö
#define CC112X_SYNC3                    0x0004	//SYNC3 //¸´Î»Öµ=0x93
#define CC112X_SYNC2                    0x0005	//SYNC2 //¸´Î»Öµ=0x0B
#define CC112X_SYNC1                    0x0006	//SYNC1 //¸´Î»Öµ=0x51
#define CC112X_SYNC0                    0x0007	//SYNC0 //¸´Î»Öµ=0xDE

#define CC112X_SYNC_CFG1                0x0008	//SYNC_CFG1-Í¬²½×Ö¼ì²âÅäÖÃ//¸´Î»Öµ=0x0A
#define CC112X_SYNC_CFG0                0x0009	//SYNC_CFG0 - Í¬²½×Ö³¤¶ÈÅäÖÃ//¸´Î»Öµ=0x17H

#define CC112X_DEVIATION_M              0x000A	//DEVIATION_M -ÆµÂÊÆ«²îÅäÖÃ//¸´Î»Öµ=0x06
#define CC112X_MODCFG_DEV_E             0x000B	//MODCFG_DEV_E-µ÷ÖÆ¸ñÊ½ºÍÆµÂÊÆ«²îÅäÖÃ//¸´Î»Öµ=0x03

#define CC112X_DCFILT_CFG               0x000C	//DCFILT_CFG-Êý×ÖÖ±Á÷È¥³ýÅäÖÃ//¸´Î»Öµ=0x4C

#define CC112X_PREAMBLE_CFG1            0x000D	//PREAMBLE_CFG1-Ç°µ¼Âë³¤¶ÈÅäÖÃ//¸´Î»Öµ=00010100
#define CC112X_PREAMBLE_CFG0            0x000E	//PREAMBLE_CFG0-Ç°µ¼Âë³¤¶ÈÅäÖÃ//¸´Î»Öµ=00101010

#define CC112X_FREQ_IF_CFG              0x000F	//FREQ_IF_CFG-RX»ìÆµÆ÷ÆµÂÊÅäÖÃ//¸´Î»Öµ=0x40
#define CC112X_IQIC                     0x0010	//IQIC-Êý×ÖÍ¼ÏñÐÅµÀ²¹³¥ÅäÖÃ//¸´Î»Öµ=11000100

#define CC112X_CHAN_BW                  0x0011	//CHAN_BW-ÐÅµÀÂË²¨Æ÷ÅäÖÃ//¸´Î»Öµ=0x14	

#define CC112X_MDMCFG1                  0x0012	//MDMCFG1-Í¨ÓÃµ÷ÖÆ½âµ÷Æ÷²ÎÊýÅäÖÃ//¸´Î»Öµ=01000110
#define CC112X_MDMCFG0                  0x0013	//MDMCFG0-Í¨ÓÃµ÷ÖÆ½âµ÷Æ÷²ÎÊýÅäÖÃ//¸´Î»Öµ=00001101

#define CC112X_DRATE2                   0x0014	//DRATE2-Êý¾ÝËÙÂÊÅäÖÃÖ¸ÊýºÍÎ²Êý//¸´Î»Öµ=0x43
#define CC112X_DRATE1                   0x0015	//DRATE1-Êý¾ÝËÙÂÊÅäÖÃÎ²Êý[15:8]//¸´Î»Öµ=0xA9
#define CC112X_DRATE0                   0x0016	//DRATE0-Êý¾ÝËÙÂÊÅäÖÃÎ²Êý[7:0]//¸´Î»Öµ=0x2A

#define CC112X_AGC_REF                  0x0017	//AGC_REF-AGC²Î¿¼µçÆ½ÅäÖÃ//¸´Î»Öµ=0x36	
#define CC112X_AGC_CS_THR               0x0018	//AGC_CS_THR-ÔØ²¨¼ì²âãÐÖµÅäÖÃ//¸´Î»Öµ=0x00
#define CC112X_AGC_GAIN_ADJUST          0x0019	//AGC_GAIN_ADJUST-RSSIÆ«ÒÆÅäÖÃ//¸´Î»Öµ=0x00
#define CC112X_AGC_CFG3                 0x001A	//AGC_CFG3-AGCÅäÖÃ//¸´Î»Öµ=10010001
#define CC112X_AGC_CFG2                 0x001B	//AGC_CFG2-AGCÅäÖÃ//¸´Î»Öµ=00100000
#define CC112X_AGC_CFG1                 0x001C	//AGC_CFG1-AGCÅäÖÃ//¸´Î»Öµ=10101010=0xAA
#define CC112X_AGC_CFG0                 0x001D	//AGC_CFG0-AGCÅäÖÃ//¸´Î»Öµ=11000011=0xC3	

#define CC112X_FIFO_CFG                 0x001E	//FIFO_CFG-FIFOÅäÖÃ//¸´Î»Öµ=0x80

#define CC112X_DEV_ADDR                 0x001F	//DEV_ADDR-Éè±¸µØÖ·ÅäÖÃ//¸´Î»Öµ=0x00

#define CC112X_SETTLING_CFG             0x0020	//SETTLING_CFG-//¸´Î»Öµ=00001011

#define CC112X_FS_CFG                   0x0021	//FS_CFG-ÆµÂÊºÏ³ÉÆ÷µÄÅäÖÃ//¸´Î»Öµ=0x02

#define CC112X_WOR_CFG1                 0x0022	//WOR_CFG1-eWORÅäÖÃ//¸´Î»Öµ=00001000
#define CC112X_WOR_CFG0                 0x0023	//WOR_CFG0-eWORÅäÖÃ//¸´Î»Öµ=00100001
#define CC112X_WOR_EVENT0_MSB           0x0024	//WOR_EVENT0_MSB-ÊÂ¼þ0ÅäÖÃ//¸´Î»Öµ=0x00
#define CC112X_WOR_EVENT0_LSB           0x0025	//WOR_EVENT0_LSB-ÊÂ¼þ0ÅäÖÃ//¸´Î»Öµ=0x00

#define CC112X_PKT_CFG2                 0x0026	//PKT_CFG2-°üÅäÖÃ//¸´Î»Öµ=00000100
#define CC112X_PKT_CFG1                 0x0027	//PKT_CFG1-°üÅäÖÃ//¸´Î»Öµ=00000101
#define CC112X_PKT_CFG0                 0x0028	//PKT_CFG0-°üÅäÖÃ//¸´Î»Öµ=0x00

#define CC112X_RFEND_CFG1               0x0029	//RFEND_CFG1 -RFENDÅäÖÃ//¸´Î»Öµ=00001111
#define CC112X_RFEND_CFG0               0x002A	//RFEND_CFG0 -RFENDÅäÖÃ//¸´Î»Öµ=0x00

#define CC112X_PA_CFG2                  0x002B	//PA_CFG2 -¹¦ÂÊ·Å´óÆ÷ÅäÖÃ//¸´Î»Öµ=0111111
#define CC112X_PA_CFG1                  0x002C	//PA_CFG1 -¹¦ÂÊ·Å´óÆ÷ÅäÖÃ//¸´Î»Öµ=01010110
#define CC112X_PA_CFG0                  0x002D	//PA_CFG0 -¹¦ÂÊ·Å´óÆ÷ÅäÖÃ//¸´Î»Öµ=01111100

#define CC112X_PKT_LEN                  0x002E	//PKT_LEN-Êý¾Ý°ü³¤¶ÈÅäÖÃ//¸´Î»Öµ=0x03

////////////////////////////////////////////////////////////////////////////
//À©Õ¹ÅäÖÃ¼Ä´æÆ÷²¿·Ö/* Extended Configuration Registers */
#define CC112X_IF_MIX_CFG               0x2F00	//IF_MIX_CFG-IF»ìºÏÅäÖÃ//¸´Î»Öµ=0x04
#define CC112X_FREQOFF_CFG              0x2F01	//FREQOFF_CFG-ÆµÂÊÆ«ÒÆ¾ÀÕýÅäÖÃ//¸´Î»Öµ=0x20=00100000
#define CC112X_TOC_CFG                  0x2F02	//TOC_CFG -¶¨Ê±Æ«ÒÆÐ£ÕýÅäÖÃ//¸´Î»Öµ=00001011
#define CC112X_MARC_SPARE               0x2F03	//MARC_SPARE -MARC±¸ÓÃ//¸´Î»Öµ=0x00
#define CC112X_ECG_CFG                  0x2F04	//ECG_CFG -Íâ²¿Ê±ÖÓÆµÂÊÅäÖÃ//¸´Î»Öµ=0x00
#define CC112X_SOFT_TX_DATA_CFG         0x2F05	//SOFT_TX_DATA_CFG -Èí¼þÅäÖÃTXÊý¾Ý//¸´Î»Öµ=0x00
#define CC112X_EXT_CTRL                 0x2F06	//EXT_CTRL -Íâ²¿¿ØÖÆÅäÖÃ//¸´Î»Öµ=0x01

#define CC112X_RCCAL_FINE               0x2F07	//RCCAL_FINE-RCÕñµ´Æ÷Ð£×¼£¨¾«£©//¸´Î»Öµ=0x00
#define CC112X_RCCAL_COARSE             0x2F08	//RCCAL_COARSE-RCÕñµ´Æ÷Ð£×¼£¨´Ö£©//¸´Î»Öµ=0x00
#define CC112X_RCCAL_OFFSET             0x2F09	//RCCAL_OFFSET-RCÕñµ´Æ÷Ð£×¼Ê±ÖÓÆ«ÒÆ//¸´Î»Öµ=0x00

#define CC112X_FREQOFF1                 0x2F0A	//FREQOFF1 - ÆµÂÊÆ«ÒÆ£¨MSB£©//¸´Î»Öµ=0x00
#define CC112X_FREQOFF0                 0x2F0B	//FREQOFF0 - ÆµÂÊÆ«ÒÆ£¨LSB£©//¸´Î»Öµ=0x00

#define CC112X_FREQ2                    0x2F0C	//FREQ2-ÆµÂÊÅäÖÃ[23:16]//¸´Î»Öµ=0x00
#define CC112X_FREQ1                    0x2F0D	//FREQ1-ÆµÂÊÅäÖÃ[23:16]//¸´Î»Öµ=0x00
#define CC112X_FREQ0                    0x2F0E	//FREQ0 - ÆµÂÊÅäÖÃ[7:0]//¸´Î»Öµ=0x00

#define CC112X_IF_ADC2                  0x2F0F	//IF_ADC2-Ä£Äâµ½Êý×Ö×ª»»Æ÷ÅäÖÃ//¸´Î»Öµ=0x02
#define CC112X_IF_ADC1                  0x2F10	//IF_ADC1-Ä£Äâµ½Êý×Ö×ª»»Æ÷ÅäÖÃ//¸´Î»Öµ=0xA6
#define CC112X_IF_ADC0                  0x2F11	//IF_ADC0-Ä£Äâµ½Êý×Ö×ª»»Æ÷ÅäÖÃ//¸´Î»Öµ=0x04

#define CC112X_FS_DIG1                  0x2F12	//FS_DIG1-//¸´Î»Öµ=0x08
#define CC112X_FS_DIG0                  0x2F13	//FS_DIG0-//¸´Î»Öµ=01011010
#define CC112X_FS_CAL3                  0x2F14	//FS_CAL3 -//¸´Î»Öµ=0x00
#define CC112X_FS_CAL2                  0x2F15	//FS_CAL2 -//¸´Î»Öµ=0x20
#define CC112X_FS_CAL1                  0x2F16	//FS_CAL1-//¸´Î»Öµ=0x00
#define CC112X_FS_CAL0                  0x2F17	//FS_CAL0-//¸´Î»Öµ=0x00
#define CC112X_FS_CHP                   0x2F18	//FS_CHP - µçºÉ±ÃÅäÖÃ//¸´Î»Öµ=0x28
#define CC112X_FS_DIVTWO                0x2F19	//FS_DIVTWO-³ýÒÔ2//¸´Î»Öµ=0x01
#define CC112X_FS_DSM1                  0x2F1A	//FS_DSM1- Êý×ÖÆµÂÊºÏ³ÉÆ÷Ä£¿éÅäÖÃ//¸´Î»Öµ=0x00
#define CC112X_FS_DSM0                  0x2F1B	//FS_DSM0-Êý×ÖÆµÂÊºÏ³ÉÆ÷Ä£¿éÅäÖÃ//¸´Î»Öµ=0x03
#define CC112X_FS_DVC1                  0x2F1C	//FS_DVC1 - ·ÖÆµÆ÷Á´ÅäÖÃ//¸´Î»Öµ=0xFF
#define CC112X_FS_DVC0                  0x2F1D	//FS_DVC0 - ·ÖÆµÆ÷Á´ÅäÖÃ//¸´Î»Öµ=0x1F
#define CC112X_FS_LBI                   0x2F1E	//FS_LBI - ±¾µØÆ«ÖÃÅäÖÃ//¸´Î»Öµ=0x00
#define CC112X_FS_PFD                   0x2F1F	//FS_PFD - ÏàÎ»ÆµÂÊ¼ì²âÆ÷ÅäÖÃ//¸´Î»Öµ=0x51
#define CC112X_FS_PRE                   0x2F20	//FS_PRE - Ô¤·ÖÆµÆ÷ÅäÖÃ//¸´Î»Öµ=0x2C
#define CC112X_FS_REG_DIV_CML           0x2F21	//FS_REG_DIV_CML- //¸´Î»Öµ=0x11
#define CC112X_FS_SPARE                 0x2F22	//FS_SPARE- //¸´Î»Öµ=0x00
#define CC112X_FS_VCO4                  0x2F23	//FS_VCO4-//¸´Î»Öµ=0x14
#define CC112X_FS_VCO3                  0x2F24	//FS_VCO3-//¸´Î»Öµ=0x00
#define CC112X_FS_VCO2                  0x2F25	//FS_VCO2-//¸´Î»Öµ=0x00
#define CC112X_FS_VCO1                  0x2F26	//FS_VCO1-//¸´Î»Öµ=0x00
#define CC112X_FS_VCO0                  0x2F27	//FS_VCO0- //¸´Î»Öµ=10000001

	//GBIAS6¡«GBIAS0- Í¨ÓÃÆ«ÖÃÅäÖÃ
#define CC112X_GBIAS6                   0x2F28	//GBIAS6 //¸´Î»Öµ=0x00
#define CC112X_GBIAS5                   0x2F29	//GBIAS5 //¸´Î»Öµ=0x02
#define CC112X_GBIAS4                   0x2F2A	//GBIAS4 //¸´Î»Öµ=0x00
#define CC112X_GBIAS3                   0x2F2B	//GBIAS3 //¸´Î»Öµ=0x00
#define CC112X_GBIAS2                   0x2F2C	//GBIAS2 //¸´Î»Öµ=0x10
#define CC112X_GBIAS1                   0x2F2D	//GBIAS1 //¸´Î»Öµ=0x00
#define CC112X_GBIAS0                   0x2F2E	//GBIAS0 //¸´Î»Öµ=0x00

#define CC112X_IFAMP                    0x2F2F	//IFAMP-ÖÐÆµ·Å´óÆ÷ÅäÖÃ//¸´Î»Öµ=0x01
#define CC112X_LNA                      0x2F30	//LNA -µÍÔëÉù·Å´óÆ÷ÅäÖÃ//¸´Î»Öµ=0x01
#define CC112X_RXMIX                    0x2F31	//RXMIX - RX»ìÆµÆ÷ÅäÖÃ//¸´Î»Öµ=0x01

#define CC112X_XOSC5                    0x2F32	//XOSC5-¾§ÌåÕñµ´Æ÷ÅäÖÃ //¸´Î»Öµ=0x0C
#define CC112X_XOSC4                    0x2F33	//XOSC4-¾§ÌåÕñµ´Æ÷ÅäÖÃ//¸´Î»Öµ=0xA0
#define CC112X_XOSC3                    0x2F34	//XOSC3-¾§ÌåÕñµ´Æ÷ÅäÖÃ//¸´Î»Öµ=0x03
#define CC112X_XOSC2                    0x2F35	//XOSC2-¾§ÌåÕñµ´Æ÷ÅäÖÃ//¸´Î»Öµ=00000100
#define CC112X_XOSC1                    0x2F36	//XOSC1-¾§ÌåÕñµ´Æ÷ÅäÖÃ//¸´Î»Öµ=0x00
#define CC112X_XOSC0                    0x2F37	//XOSC0-¾§ÌåÕñµ´Æ÷ÅäÖÃ//¸´Î»Öµ=0x00

#define CC112X_ANALOG_SPARE             0x2F38	//ANALOG_SPARE- //¸´Î»Öµ=0x00
#define CC112X_PA_CFG3                  0x2F39	//PA_CFG3- ¹¦ÂÊ·Å´óÆ÷ÅäÖÃ//¸´Î»Öµ=0x00
#define CC112X_IRQ0M                    0x2F3F	
#define CC112X_IRQ0F                    0x2F40	

////////////////////////////////////////////////////////////////////////////
//×´Ì¬¼Ä´æÆ÷/* Status Registers */
#define CC112X_WOR_TIME1                0x2F64	//WOR_TIME1-eWOR¶¨Ê±Æ÷×´Ì¬£¨MSB£© //¸´Î»Öµ=0x00
#define CC112X_WOR_TIME0                0x2F65	//WOR_TIME0-eWOR¶¨Ê±Æ÷×´Ì¬£¨LSB£© //¸´Î»Öµ=0x00
#define CC112X_WOR_CAPTURE1             0x2F66	//WOR_CAPTURE1 - eWOR¶¨Ê±Æ÷²¶×½£¨MSB£©//¸´Î»Öµ=0x00
#define CC112X_WOR_CAPTURE0             0x2F67	//WOR_CAPTURE0 - eWOR¶¨Ê±Æ÷²¶×½£¨LSB£©//¸´Î»Öµ=0x00
#define CC112X_BIST                     0x2F68	//BIST - MARC BIST- //¸´Î»Öµ=0x00
#define CC112X_DCFILTOFFSET_I1          0x2F69	//DCFILTOFFSET_I1 - Ö±Á÷ÂË²¨Æ÷Æ«ÒÆI£¨MSB£©//¸´Î»Öµ=0x00
#define CC112X_DCFILTOFFSET_I0          0x2F6A	//DCFILTOFFSET_I0 - Ö±Á÷ÂË²¨Æ÷Æ«ÒÆI£¨LSB£©//¸´Î»Öµ=0x00
#define CC112X_DCFILTOFFSET_Q1          0x2F6B	//DCFILTOFFSET_Q1 -Ö±Á÷ÂË²¨Æ÷Æ«ÒÆ Q£¨MSB£©//¸´Î»Öµ=0x00
#define CC112X_DCFILTOFFSET_Q0          0x2F6C	//DCFILTOFFSET_Q0 -Ö±Á÷ÂË²¨Æ÷Æ«ÒÆ Q£¨LSB£©//¸´Î»Öµ=0x00
#define CC112X_IQIE_I1                  0x2F6D	//IQIE_I1 - IQ²»Æ½ºâÖµI£¨MSB£©//¸´Î»Öµ=0x00
#define CC112X_IQIE_I0                  0x2F6E	//IQIE_I0 - IQ²»Æ½ºâÖµI£¨LSB£©//¸´Î»Öµ=0x00
#define CC112X_IQIE_Q1                  0x2F6F	//IQIE_Q1 - IQ²»Æ½ºâÖµQ£¨MSB£©//¸´Î»Öµ=0x00
#define CC112X_IQIE_Q0                  0x2F70	//IQIE_Q0 - IQ²»Æ½ºâÖµQ£¨LSB£©//¸´Î»Öµ=0x00

#define CC112X_RSSI1                    0x2F71	//RSSI1 - ½ÓÊÕÐÅºÅÇ¿¶ÈÖ¸Ê¾Æ÷£¨MSB£©(Ö»¶Á) //¸´Î»Öµ=0x80
#define CC112X_RSSI0                    0x2F72	//RSSI0 - ½ÓÊÕÐÅºÅÇ¿¶ÈÖ¸Ê¾Æ÷£¨LSB£©(Ö»¶Á) //¸´Î»Öµ=0x00

#define CC112X_MARCSTATE                0x2F73	//MARCSTATE - MARC ×´Ì¬(Ö»¶Á) //¸´Î»Öµ=01000001       //MARC (Main Radio Control)

#define CC112X_LQI_VAL                  0x2F74	//LQI_VAL - Á´Â·ÖÊÁ¿Ö¸±êÖµ(Ö»¶Á) //¸´Î»Öµ=0x00

#define CC112X_PQT_SYNC_ERR             0x2F75	//PQT_SYNC_ERROR-Ç°µ¼ÂëºÍÍ¬²½×Ö´íÎó(Ö»¶Á) //¸´Î»Öµ=0xFF

#define CC112X_DEM_STATUS               0x2F76	//DEM_STATUS - ½âµ÷Æ÷×´Ì¬(Ö»¶Á)//¸´Î»Öµ=0x00

#define CC112X_FREQOFF_EST1             0x2F77	//FREQOFF_EST1 - ÆµÆ«¹À¼Æ£¨MSB£©(Ö»¶Á) //¸´Î»Öµ=0x00
#define CC112X_FREQOFF_EST0             0x2F78	//FREQOFF_EST0 - ÆµÆ«¹À¼Æ£¨LSB£©(Ö»¶Á) //¸´Î»Öµ=0x00
#define CC112X_AGC_GAIN3                0x2F79	//AGC_GAIN3-AGCÔöÒæ//¸´Î»Öµ=0x00   //AGC_FRONT_END_GAIN =00  //AGCÇ°¶ËÔöÒæ¡£Êµ¼ÊÓ¦ÓÃµÄ·Ö±æÂÊÎª1 dBÔöÒæ
#define CC112X_AGC_GAIN2                0x2F7A	//AGC_GAIN2-AGCÔöÒæ//¸´Î»Öµ=11101001  //AGC_DRIVES_FE_GAIN  ¸²¸ÇAGCÔöÒæ¿ØÖÆ=1=AGC¿ØÖÆÇ°¶ËÔöÒæ  //AGC_LNA_CURRENT  //AGC_LNA_R_DEGEN
#define CC112X_AGC_GAIN1                0x2F7B	//AGC_GAIN1-AGCÔöÒæ//¸´Î»Öµ=0x00   //AGC_LNA_R_LOAD //AGC_LNA_R_RATIO
#define CC112X_AGC_GAIN0                0x2F7C	//AGC_GAIN0-AGCÔöÒæ//¸´Î»Öµ=00111111  //AGC_IF_MODE  //AGC_IFAMP_GAIN
#define CC112X_SOFT_RX_DATA_OUT         0x2F7D	//SOFT_RX_DATA_OUT-Èí¼þÉèÖÃRXÊý¾ÝÊä³ö//¸´Î»Öµ=0x00   //SOFT_RX_DATA
#define CC112X_SOFT_TX_DATA_IN          0x2F7E	//SOFT_TX_DATA_OUT-Èí¼þÉèÖÃTXÊý¾ÝÊäÈë//¸´Î»Öµ=0x00   //SOFT_TX_DATA
#define CC112X_ASK_SOFT_RX_DATA         0x2F7F	//ASK_SOFT_RX_DATA - AGC ASK Èí¼þÅäÖÃÊä³ö//¸´Î»Öµ=0x30  //ASK_SOFT_RX_DATA_RESERVED5_0 
#define CC112X_RNDGEN                   0x2F80	//RNDGEN - Ëæ»úÊýÖµ//¸´Î»Öµ=0x7F
#define CC112X_MAGN2                    0x2F81	//MAGN2 - CORDICºóµÄÐÅºÅ·ù¶È[16](Ö»¶Á)//¸´Î»Öµ=0x00  //DEM_MAGN_16=0  //CORDICºóµÄË²Ê±ÐÅºÅ·ù¶È£¬17Î»[16]
#define CC112X_MAGN1                    0x2F82	//MAGN1 - CORDICºóµÄÐÅºÅ·ù¶È[15:8](Ö»¶Á)//¸´Î»Öµ=0x00  //DEM_MAGN_15_8=0  //CORDICºóµÄË²Ê±ÐÅºÅ·ù¶È[15:8]
#define CC112X_MAGN0                    0x2F83	//MAGN0 - CORDICºóµÄÐÅºÅ·ù¶È[7:0](Ö»¶Á)//¸´Î»Öµ=0x00  //DEM_MAGN_7_0=0  //CORDICºóµÄË²Ê±ÐÅºÅ·ù¶È[7:0]
#define CC112X_ANG1                     0x2F84	//ANG1 - CORDICºóµÄÐÅºÅ½Ç¶È[9:8](Ö»¶Á)//¸´Î»Öµ=0x00  //CORDICºóµÄË²Ê±ÐÅºÅµÄ½Ç¶È
#define CC112X_ANG0                     0x2F85	//ANG0 - CORDICºóµÄÐÅºÅ½Ç¶È[7:0](Ö»¶Á)//¸´Î»Öµ=0x00  //CORDICºóµÄË²Ê±ÐÅºÅµÄ½Ç¶È
#define CC112X_CHFILT_I2                0x2F86	//CHFILT_I2 - Í¨µÀÉ¸Ñ¡Êý¾ÝµÄÊµ²¿[18:16](Ö»¶Á)//¸´Î»Öµ=0x80  //DEM_CHFILT_STARTUP_VALID=1=ÐÅµÀÂË²¨Æ÷Êý¾ÝÓÐÐ§£¨ºóÖÃ16ÐÅµÀÂË²¨Æ÷ÑùÆ·£©  //DEM_CHFILT_I_18_16
#define CC112X_CHFILT_I1                0x2F87	//CHFILT_I1 - Í¨µÀÉ¸Ñ¡Êý¾ÝµÄÊµ²¿[15:8](Ö»¶Á)//¸´Î»Öµ=0x00   //DEM_CHFILT_I_15_8
#define CC112X_CHFILT_I0                0x2F88	//CHFILT_I0 - Í¨µÀÉ¸Ñ¡Êý¾ÝµÄÊµ²¿[7:0](Ö»¶Á)//¸´Î»Öµ=0x00    //DEM_CHFILT_I_7_0	
#define CC112X_CHFILT_Q2                0x2F89	//CHFILT_Q2 - Í¨µÀÉ¸Ñ¡Êý¾ÝµÄÐé²¿[18:16](Ö»¶Á)//¸´Î»Öµ=0x00  //DEM_CHFILT_Q_18_16
#define CC112X_CHFILT_Q1                0x2F8A	//CHFILT_Q1 - Í¨µÀÉ¸Ñ¡Êý¾ÝµÄÊµ²¿[15:8](Ö»¶Á)//¸´Î»Öµ=0x00   //DEM_CHFILT_Q_15_8
#define CC112X_CHFILT_Q0                0x2F8B	//CHFILT_Q0 - Í¨µÀÉ¸Ñ¡Êý¾ÝµÄÊµ²¿[7:0](Ö»¶Á)//¸´Î»Öµ=0x00    //DEM_CHFILT_Q_7_0

#define CC112X_GPIO_STATUS              0x2F8C	//GPIO_STATUS - GPIO ×´Ì¬//¸´Î»Öµ=0x00
#define CC112X_FSCAL_CTRL               0x2F8D	//FSCAL_CTRL-//¸´Î»Öµ=0x01
#define CC112X_PHASE_ADJUST             0x2F8E	//PHASE_ADJUST-//¸´Î»Öµ=0x00  //½öÓÃÓÚ²âÊÔÄ¿µÄ

#define CC112X_PARTNUMBER               0x2F8F	//PARTNUMBER -Ð¾Æ¬ÐÍºÅ//¸´Î»Öµ=0x00
#define CC112X_PARTVERSION              0x2F90	//PARTVERSION- ²¿·Öµ÷Õû//¸´Î»Öµ=0x00

#define CC112X_SERIAL_STATUS            0x2F91	//SERIAL_STATUS - ´®ÐÐ×´Ì¬//¸´Î»Öµ=0x00

#define CC112X_RX_STATUS                0x2F92	//RX_STATUS- RX  ×´Ì¬(Ö»¶Á) //¸´Î»Öµ=0x01

#define CC112X_TX_STATUS                0x2F93	//TX_STATUS-TX ×´Ì¬(Ö»¶Á)//¸´Î»Öµ=0x00

#define CC112X_MARC_STATUS1             0x2F94	//MARC_STATUS1 -MARC ×´Ì¬(Ö»¶Á)//¸´Î»Öµ=0x00  //ÓÃÓÚ¼ÇÂ¼ÊÇÊ²Ã´ÐÅºÅ²úÉúMARC_MCU_WAKEUPÐÅºÅ
#define CC112X_MARC_STATUS0             0x2F95	//MARC_STATUS0 -MARC ×´Ì¬(Ö»¶Á)//¸´Î»Öµ=0x00  

#define CC112X_PA_IFAMP_TEST            0x2F96	//PA_IFAMP_TEST-//¸´Î»Öµ=0x00 //PA_IFAMP_TEST_RESERVED4_0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
#define CC112X_FSRF_TEST                0x2F97	//FSRF_TEST-//¸´Î»Öµ=0x00     //FSRF_TEST_RESERVED6_0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
#define CC112X_PRE_TEST                 0x2F98	//PRE_TEST-//¸´Î»Öµ=0x00     //PRE_TEST_RESERVED4_0   //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
#define CC112X_PRE_OVR                  0x2F99	//PRE_OVR-//¸´Î»Öµ=0x00   //PRE_TEST_RESERVED4_0   //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
#define CC112X_ADC_TEST                 0x2F9A	//ADC_TEST - ADC Test //¸´Î»Öµ=0x00  //ADC_TEST_RESERVED5_0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
#define CC112X_DVC_TEST                 0x2F9B	//DVC_TEST - DVC Test //¸´Î»Öµ=0x0B  //DVC_TEST_RESERVED4_0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
#define CC112X_ATEST                    0x2F9C	//ATEST-//¸´Î»Öµ=0x40    //ATEST_RESERVED6_0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
#define CC112X_ATEST_LVDS               0x2F9D	//ATEST_LVDS-//¸´Î»Öµ=0x00   //ATEST_LVDS_RESERVED3_0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
#define CC112X_ATEST_MODE               0x2F9E	//ATEST_MODE-//¸´Î»Öµ=0x00   //ATEST_MODE_RESERVED7_0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
#define CC112X_XOSC_TEST1               0x2F9F	//XOSC_TEST1-//¸´Î»Öµ=0x3C   //XOSC_TEST1_RESERVED7_0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
#define CC112X_XOSC_TEST0               0x2FA0	//XOSC_TEST0-//¸´Î»Öµ=0x00   //XOSC_TEST0_RESERVED7_0  //½öÓÃÓÚ²âÊÔÄ¿µÄ£¬Ê¹ÓÃÖµÀ´×ÔSmartRFÌ×¼þ
                                        
#define CC112X_RXFIRST                  0x2FD2	//RXFIRST - RX FIFO Pointer (first entry)//¸´Î»Öµ=0x00  //Ö¸ÏòµÚÒ»¸öÐ´½øRX FIFOµÄ×Ö½Ú   
#define CC112X_TXFIRST                  0x2FD3	//TXFIRST - TX FIFO Pointer (first entry)//¸´Î»Öµ=0x00  //Ö¸ÏòµÚÒ»¸öÐ´½øTX FIFOµÄ×Ö½Ú  
#define CC112X_RXLAST                   0x2FD4	//RXLAST - RX FIFO Pointer (last entry)//¸´Î»Öµ=0x00    //Ö¸Ïò×îºóÒ»¸öÐ´½øRX FIFOµÄ×Ö½Ú 
#define CC112X_TXLAST                   0x2FD5	//TXLAST - TX FIFO Pointer (last entry)//¸´Î»Öµ=0x00    //Ö¸Ïò×îºóÒ»¸öÐ´½øTX FIFOµÄ×Ö½Ú  
#define CC112X_NUM_TXBYTES              0x2FD6  //NUM_TXBYTES - TX FIFO×´Ì¬(Õ¼ÓÃ¿Õ¼ä)//¸´Î»Öµ=0x00  //TXBYTES  TX FIFOÖÐµÄ×Ö½ÚÊý/* Number of bytes in TXFIFO */ 
#define CC112X_NUM_RXBYTES              0x2FD7  //NUM_RXBYTES - RX FIFO×´Ì¬(Õ¼ÓÃ¿Õ¼ä)//¸´Î»Öµ=0x00  //RXBYTES  RX FIFOÖÐµÄ×Ö½ÚÊý/* Number of bytes in RXFIFO */
#define CC112X_FIFO_NUM_TXBYTES         0x2FD8  //FIFO_NUM_TXBYTES - TX FIFO×´Ì¬(¿Õ°×¿Õ¼ä)//¸´Î»Öµ=0x0F  //FIFO_TXBYTES  TX FIFOÖÐ¿Õ°×¿Õ¼äµÄ×Ö½ÚÊý¡£1111£º±íÊ¾»¹ÓÐ>=15¸ö×Ö½ÚµÄ¿Õ¼ä£¬¿ÉÒÔ±»Ð´Èë¡£
#define CC112X_FIFO_NUM_RXBYTES         0x2FD9  //FIFO_NUM_RXBYTES - RX FIFO×´Ì¬(¿É»ñµÃµÄ×Ö½ÚÊý)//¸´Î»Öµ=0x00  //FIFO_RXBYTES  RX FIFOÖÐ¿ÉÒÔ±»¶Á³öµÄ×Ö½ÚÊý£¬1111£º±íÊ¾»¹ÓÐ>=15¸ö×Ö½Ú£¬¿ÉÒÔ¶Á³ö

////////////////////////////////////////////////////////////////////////////                                                                                                                                             
//Êý¾ÝFIFO·ÃÎÊ/* DATA FIFO Access */
#define CC112X_SINGLE_TXFIFO            0x003F      /*  TXFIFO  - Single accecss to Transmit FIFO */
#define CC112X_BURST_TXFIFO             0x007F      /*  TXFIFO  - Burst accecss to Transmit FIFO  */
#define CC112X_SINGLE_RXFIFO            0x00BF      /*  RXFIFO  - Single accecss to Receive FIFO  */
#define CC112X_BURST_RXFIFO             0x00FF      /*  RXFIFO  - Busrrst ccecss to Receive FIFO  */

#define CC112X_LQI_CRC_OK_BM            0x80
#define CC112X_LQI_EST_BM               0x7F


////////////////////////////////////////////////////////////////////////////
//ÃüÁîÑ¡Í¨¼Ä´æÆ÷/* Command strobe registers */
#define CC112X_SRES                     0x30      /*  SRES    - Reset chip. */
#define CC112X_SFSTXON                  0x31      /*  SFSTXON - Enable and calibrate frequency synthesizer. */
#define CC112X_SXOFF                    0x32      /*  SXOFF   - Turn off crystal oscillator. */
#define CC112X_SCAL                     0x33      /*  SCAL    - Calibrate frequency synthesizer and turn it off. */
#define CC112X_SRX                      0x34      /*  SRX     - Enable RX. Perform calibration if enabled. */
#define CC112X_STX                      0x35      /*  STX     - Enable TX. If in RX state, only enable TX if CCA passes. */
#define CC112X_SIDLE                    0x36      /*  SIDLE   - Exit RX / TX, turn off frequency synthesizer. */
#define CC112X_SWOR                     0x38      /*  SWOR    - Start automatic RX polling sequence (Wake-on-Radio) */
#define CC112X_SPWD                     0x39      /*  SPWD    - Enter power down mode when CSn goes high. */
#define CC112X_SFRX                     0x3A      /*  SFRX    - Flush the RX FIFO buffer. */
#define CC112X_SFTX                     0x3B      /*  SFTX    - Flush the TX FIFO buffer. */
#define CC112X_SWORRST                  0x3C      /*  SWORRST - Reset real time clock. */
#define CC112X_SNOP                     0x3D      /*  SNOP    - No operation. Returns status byte. */
#define CC112X_AFC                      0x37      /*  AFC     - Automatic Frequency Correction */

////////////////////////////////////////////////////////////////////////////
//Ð¾Æ¬×´Ì¬·µ»Ø×´Ì¬×Ö½Ú/* Chip states returned in status byte */
#define CC112X_STATE_IDLE               0x00
#define CC112X_STATE_RX                 0x10
#define CC112X_STATE_TX                 0x20
#define CC112X_STATE_FSTXON             0x30
#define CC112X_STATE_CALIBRATE          0x40
#define CC112X_STATE_SETTLING           0x50
#define CC112X_STATE_RXFIFO_ERROR       0x60
#define CC112X_STATE_TXFIFO_ERROR       0x70


/******************************************************************************
 * PROTPTYPES
 */ 

/* basic set of access functions */
rfStatus_t cc112xSpiReadReg(uint16 addr, uint8 *data, uint8 len);
rfStatus_t cc112xGetTxStatus(void);
rfStatus_t cc112xGetRxStatus(void);  
rfStatus_t cc112xSpiWriteReg(uint16 addr, uint8 *data, uint8 len);
rfStatus_t cc112xSpiWriteTxFifo(uint8 *pWriteData, uint8 len);
rfStatus_t cc112xSpiReadRxFifo(uint8 *pReadData, uint8 len);

#ifdef  __cplusplus
}
#endif
/******************************************************************************
  Copyright 2010 Texas Instruments Incorporated. All rights reserved.

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
#endif// CC112x_SPI_H