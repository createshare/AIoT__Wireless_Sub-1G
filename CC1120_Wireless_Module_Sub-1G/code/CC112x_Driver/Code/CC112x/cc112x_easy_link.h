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
01. Ƶ��ѡ��Band Select = 410.0 - 480.0 MHzƵ��
02. �ز�Ƶ��Carrier frequency = 434.000000  MHz
03. ��������Symbol rate = 1.2  ksps
04. ��������Bit rate = 1.2  kbps
05. ���书��TX power = 15 dBm
06. �����˲�������RX filter BW = 25.000000 KHz
07. Ƶ��ƫ��Deviation = 3.997803  KHz
08. ���Ƹ�ʽModulation format = 2-FSK 
09. ����˹��ʹ��Manchester enable = ���� 
10. ���ݰ׻�Whitening =  ���� 
11. ���ݰ�����ģʽPacket length mode = �ɱ����ݰ�����ģʽ(ͬ���ֺ��յ��ĵ�һ���ֽ�Ϊ���ݰ���������)
12. ���ݰ�����Packet length = 255 ���ֽ�
13. ���ʷŴ�PA ramping = ʹ�� 
14. ��ַ���ʹ��Address Check = ����
15. �豸��ַDevice address = 0 
16. GPIO3����=����Ϊ���ݰ�����/���ճɹ���ָʾ����
*************************************************************/



static const registerSetting_t preferredSettings[]= 
{  
//IOCFG3 -GPIO3��������//��λֵ=0x06 (��λʱѡ"PKT_SYNC_RXTX" )
	//GPIO3_ATRAN ģ�⴫��ʹ��= 0=ѡ���׼����GPIO
	//GPIO3_INV ��ת���ʹ��= 0=��ֹ�����ת
	//GPIO3_CFG ���ѡ��= 000110=ѡ"PKT_SYNC_RXTX" =CC1120����/���յ�ͬ����ʱ��λ���������ݰ���ĩβȡ����λ��
	{CC112X_IOCFG3,            0x06}, 

//IOCFG2 -GPIO2��������//��λֵ=0x07(��λʱѡ"PKT_CRC_OK" )
	//GPIO2_ATRAN ģ�⴫��ʹ��= 1=��������GPIO
	//GPIO2_INV ��ת���ʹ��= 0=��ֹ�����ת
	//GPIO2_CFG ���ѡ��= 110000=ѡ"HIGHZ" =  ���迹����̬��
	{CC112X_IOCFG2,            0xB0},
	
//IOCFG1 -GPIO1��������//��λֵ=0x30(��λʱѡ"HIGHZ"=  ���迹 )
//ע�⣺GPIO1��SPI��MISO���Ÿ��á���CSn��Ч���͵�ƽ����GPIO1��ΪMISO������š�
//ע�⣺ϵͳ����ͨ�������Ӳ��ȷ�� MISO����������
	//GPIO1_ATRAN ģ�⴫��ʹ��= 1=��������GPIO
	//GPIO1_INV ��ת���ʹ��= 0=��ֹ�����ת
	//GPIO1_CFG ���ѡ��= 110000=ѡ"HIGHZ" =  ���迹����̬��
	{CC112X_IOCFG1,            0xB0},

//IOCFG0 -GPIO0��������//��λֵ=0x3C(��λʱѡ"EXT_OSC_EN"=  ʹ���ⲿ���� )
	//GPIO0_ATRAN ģ�⴫��ʹ��= 1=��������GPIO
	//GPIO0_INV ��ת���ʹ��= 0=��ֹ�����ת
	//GPIO0_CFG ���ѡ��= 110000=ѡ"HIGHZ" =  ���迹����̬��
	{CC112X_IOCFG0,            0xB0},

//SYNC0 ~ SYNC3-32λͬ����
	{CC112X_SYNC3,             0xD3},//SYNC3 //��λֵ=0x93
	{CC112X_SYNC2,             0x91},//SYNC2 //��λֵ=0x0B
	{CC112X_SYNC1,             0xD3},//SYNC1 //��λֵ=0x51
	{CC112X_SYNC0,             0x91},//SYNC0 //��λֵ=0xDE
	
//SYNC_CFG1-ͬ���ּ������//��λֵ=0x0A
	//DEM_CFG ǰ��������ֵʹ��λ =000=����ǰ��������ֵ (PQT),
	//SYNC_THR ������õ�ͬ������ֵ=0x0B��
	{CC112X_SYNC_CFG1,         0x0B},
	
//care--δ��ʼ��//SYNC_CFG0 - ͬ���ֳ�������//��λֵ=0x17H
	//SYNC_MODE ͬ���ֳ�������=101=ѡ��32ͬ����//32 bits
	//SYNC_NUM_ERROR λͬ���ּ��=11=���������޶�������У��λ����  //Bit Error Qualifier disabled. No check on bit errors

//care--δ��ʼ��//DEVIATION_M -Ƶ��ƫ������//��λֵ=0x06
	//Ƶ��ƫ�β����һ���֣�DEV_M  = 0x06

//care--δ��ʼ��//MODCFG_DEV_E-���Ƹ�ʽ��Ƶ��ƫ������//��λֵ=0x03
	//MODEM_MODE ���ƽ����ģʽ����= 00 =��ͨģʽ
	//MOD_FORMAT ���Ƹ�ʽ=000= "2-FSK"    //001=2-GFSK //010=Reserved //011=ASK/OOK //100=4-FSK //101=4-GFSK //110=SC-MSK unshaped (CC1125, TX only). For CC1120, CC1121, and CC1175this setting is reserved  //111=SC-MSK shaped (CC1125, TX only). For CC1120, CC1121, and CC1175 thissetting is reserved
	//DEV_E  Ƶ��ƫ�ָ�����֣�= 011
		//������Ƹ�ʽ = "2-FSK"
		//����Ƶ��ƫ�� Deviation = 3.997803

//DCFILT_CFG-����ֱ��ȥ������//��λֵ=0x4C
	//DCFILT_FREEZE_COEFF ֱ���˲�������=0 =ֱ���˲��㷨���ƺͲ���ֱ�����
	//DCFILT_BW_SETTLE AGC��������ȶ���=011=256 samples
	//DCFILT_BW ֱ���˲�������= 100;
	{CC112X_DCFILT_CFG,        0x1C},
									
//PREAMBLE_CFG1-ǰ���볤������//��λֵ=00010100
	//NUM_PREAMBLE ����Ҫ�����͵�ǰ��λ����С��Ŀ= 0110 = 4�ֽ�
	//PREAMBLE_WORD ǰ�����ֽ�����= 00 = ѡ��10101010 (0xAA)
	{CC112X_PREAMBLE_CFG1,     0x18},

//care--δ��ʼ��//PREAMBLE_CFG0-ǰ���볤������//��λֵ=00101010
	//PQT_EN ǰ������ʹ��λ = 1=ʹ��ǰ������
	//PQT_VALID_TIMEOUT PQT������ʱ��  = 0=16����Ԫ
	//PQT  �������PQT   (ǰ��������ֵ)= 0x0A  

//care--δ��ʼ��//FREQ_IF_CFG-RX��Ƶ��Ƶ������//��λֵ=0x40
	//FREQ_IF ���ֽ��ջ���Ƶ��Ƶ��=0x40

//IQIC-����ͼ���ŵ���������//��λֵ=11000100
	//IQIC_EN  IQͼ�񲹳�ʹ��λ=1=����ͼ�񲹳�
	//IQIC_UPDATE_COEFF_EN  IQIC����ϵ��ʹ�� = 1=ʹ��IQICϵ�����£�����IQIE_I1 IQIE_I0��IQIE_Q1��IQIE_Q0�Ĵ�����
	//IQIC_BLEN_SETTLE  �ȶ�ʱ��IQIC�鳤��ֵ=00=8������
	//IQIC_BLEN  IQIC�鳤��ֵ=01=32������
	//IQIC_IMGCH_LEVEL_THR   IQICͼ���ŵ���ƽ��ֵ=10=ѡ��>1024��
	{CC112X_IQIC,              0xC6},

//CHAN_BW-�ŵ��˲�������//��λֵ=0x14
	//CHFILT_BYPASS  �ŵ��˲�����· =0=ʹ���ŵ��˲���������·��
	//ADC_CIC_DECFACT  ��һ����ȡ����ѡ��λ=0=��ȡ����Ϊ20
	//BB_CIC_DECFACT  �ڶ�����ȡ����ѡ��λ= 001000=��СRX�˲�������BWΪ8KHz
		//����"RX filter BW = 25KHz"
	{CC112X_CHAN_BW,           0x08},  

//care--δ��ʼ��//MDMCFG1-ͨ�õ��ƽ������������//��λֵ=01000110
	//CARRIER_SENSE_GATE  ͬ������������= 0=ͬ��������������CSΪʲô״̬
	//FIFO_EN  FIFOʹ�� =1=��������/���ͨ��FIFO
	//MANCHESTER_EN  ����˹��ʹ��= 0=NRZ����ʹ�ܣ�
	//INVERT_DATA_EN  ���ݷ�תʹ��=0=��ֹ���ݷ�ת
	//COLLISION_DETECT_EN  ��ͻ���ʹ��=0=���ó�ͻ���
	//DVGA_GAIN  �̶�DVGA��������=11=9 dB DVGA
	//SINGLE_ADC_EN  ���û�Ľ����ŵ�������=0=IQ-�ŵ�
		//�����������˹��
	
//MDMCFG0-ͨ�õ��ƽ������������//��λֵ=00001101
	//TRANSPARENT_MODE_EN  ͸��ģʽʹ��=0=����͸��ģʽʹ��
	//TRANSPARENT_INTFACT  ͸���źŲ�ֵ����=00=1*͸���źŲ�ֵ���ǰһ�Σ���λ��//00    1x transparent signal interpolated one time before output (reset)
	//DATA_FILTER_EN  ͸�������ݹ��˺���չ���ݹ���ʹ��=0=��ֹ͸�����ݹ��˺ͽ�����չ�����ݹ�����
	//VITERBI_EN ά�رȼ��ʹ��=1=ʹ��ʹ��=1=ʹ��
	//MDMCFG0_RESERVED1_0  =01=�����ڲ���Ŀ�ģ�ʹ��ֵ��"SmartRF"�׼�
	{CC112X_MDMCFG0,           0x05},

//care--δ��ʼ��//DRATE2-������������ָ����β��//��λֵ=0x43
	//DATARATE_E  �������ʣ�ָ�����֣�=0100=0x04
	//DATARATE_M_19_16  �����ʣ�β������[19-16λ]��=0011

//care--δ��ʼ��//DRATE1-������������β��[15:8]//��λֵ=0xA9
	//DATARATE_M_15_8  ������������β��[15:8] = 0xA9

//care--δ��ʼ��//DRATE0-������������β��[7:0]//��λֵ=0x2A
	//DATARATE_M_7_0   ������������β��[7:0]  =0x2A
		//������������=1.2 kbps

//AGC_REF-AGC�ο���ƽ����//��λֵ=0x36
	//AGC_REFERENCE  AGC�ο���ƽ= 0x20      //AGC: �Զ��������
	{CC112X_AGC_REF,           0x20},

//AGC_CS_THR-�ز������ֵ����//��λֵ=0x00
	//AGC_CS_THRESHOLD   AGC�ز������ֵ= 0x19    //AGC: �Զ��������
	{CC112X_AGC_CS_THR,        0x19},

//care--δ��ʼ��//AGC_GAIN_ADJUST-RSSIƫ������//��λֵ=0x00
	//GAIN_ADJUSTMENT  AGC�������= 0x00     //AGC: �Զ��������

//care--δ��ʼ��//AGC_CFG3-AGC����//��λֵ=10010001
	//RSSI_STEP_THR = 1=RSSI��ֵ��6 dB (RSSI :�����ź�ǿ��ָʾ)
	//AGC_ASK_BW  =00=�����ݹ�����
	//AGC_MIN_GAIN  AGC��С����=0x11
	
//care--δ��ʼ��//AGC_CFG2-AGC����//��λֵ=00100000
	//START_PREVIOUS_GAIN_EN  = 0 =���������ֵ��ʼ����
	//FE_PERFORMANCE_MODE  ѡ��Ӧ�õ������=01=��������ģʽ
	//AGC_MAX_GAIN   AGC  ������� = 00000

//AGC_CFG1-AGC����//��λֵ=10101010=0xAA
	//AGC_SYNC_BEHAVIOR  AGCͬ���ּ���Ĳ��� = 101=ͬʱ����AGC�����RSSI
	//AGC_WIN_SIZE  AGC���ִ����е�ÿһ��ֵ�Ĵ�С = 010=32������
	//AGC_SETTLE_WAIT  ����AGC�������֮��ĵȴ�ʱ�� = 01=32������
	{CC112X_AGC_CFG1,          0xA9},

//AGC_CFG0-AGC����//��λֵ=11000011=0xC3
	//AGC_HYST_LEVEL  AGC���͵ȼ� = 11=10 dB
	//AGC_SLEWRATE_LIMIT  AGCб������= 00= 60 dB
	//RSSI_VALID_CNT  ���뵽ƽ���˲�����������= 11=9
	//AGC_ASK_DECAY  ��ASK/ OOKģʽ,����˥������ = 11=1/128 IIR˥��
	{CC112X_AGC_CFG0,          0xCF},

//FIFO_CFG-FIFO����//��λֵ=0x80
	//CRC_AUTOFLUSH  = 0= ���һ��CRC���������Զ�ˢ��RX FIFO������յ������ݰ��������λ���رգ�Ӧ�ٴδ򿪣������ȷ�һ��SFRXѡͨ�ź�
	//FIFO_THR  RX��TX FIFO����ֵ = 0x00=�ﵽ��ֵʱ��FIFO_THR= 0��ʾTX FIFO����127�ֽڣ�RX FIFO����1���ֽڣ���FIFO_THR= 127 ��ʾTX FIFO����0�ֽڣ�RX FIFO��128�ֽڡ�
	{CC112X_FIFO_CFG,          0x00},

//care--δ��ʼ��//DEV_ADDR-�豸��ַ����//��λֵ=0x00
	//DEVICE_ADDR  �豸��ַ=0x00=�ڽ������ݰ�����ʱʹ�õĵ�ַ
		//�����豸��ַ=0x00

//SETTLING_CFG-//��λֵ=00001011
	//FS_AUTOCAL   �Զ�����У׼=00= �Ӳ����ֶ�У׼ʹ��SCALѡͨ�źţ�
	//LOCK_TIME  ���õ�Ƶ�ʺϳ������Խ������״̬��ʱ��= 01=  75/30 ��s
	//FSREG_TIME Ƶ�ʺϳ������ȶ�ʱ�䣨ʹ��ֵ����SmartRF�׼���= 1 = 60 ��s
	{CC112X_SETTLING_CFG,      0x03},

//FS_CFG-Ƶ�ʺϳ���������//��λֵ=0x02
	//FS_LOCK_EN  ����������ʹ��= 0 = ��������������
	//FSD_BANDSELECT  Ƶ��ѡ������LO��Ƶ�� = 0100 = 410.0 - 480.0 MHzƵ�Σ�LO��Ƶ��= 8��//0010=820.0 - 960.0 MHz band //100=410.0 - 480.0 MHz band //0110=273.3 - 320.0 MHz band //1000=205.0 - 240.0 MHz band //1010=164.0 - 192.0 MHz band //1011=136.7 - 160.0 MHz band 
		//����Ƶ��ѡ��= 410.0 - 480.0 MHzƵ�Σ�LO��Ƶ��= 8�� //Frequency Synthesizer Configuration
	{CC112X_FS_CFG,            0x04},
		

//care--δ��ʼ��//WOR_CFG1-eWOR����//��λֵ=00001000
	//WOR_RES    eWOR��ʱ���ֱ���= 00 =�߷ֱ���
	//WOR_MODE   eWOR ģʽ= 001 = ����ģʽ
	//EVENT1   �¼�1��ʱ = 000 =4

//care--δ��ʼ��//WOR_CFG0-eWOR����//��λֵ=00100001
	//DIV_256HZ_EN   ʱ�ӷ�Ƶʹ��(��˯��ģʽ������ʱ�ӷ�Ƶ) = 1 = ����ʱ�ӷ�Ƶ
	//EVENT2_CFG      �¼�2��ʱ = 00 =����
	//RC_MODE  RCOSCУ׼ģʽ = 00 = ����RCOSCУ׼
	//RC_PD   RCOSC�����ź�λ = 1 =RCOSC���ڵ���״̬

//care--δ��ʼ��//WOR_EVENT0_MSB-�¼�0����//��λֵ=0x00
	//EVENT0_15_8   �¼�0��ʱ��MSB��= 0x00

//care--δ��ʼ��//WOR_EVENT0_LSB-�¼�0����//��λֵ=0x00
	//EVENT0_7_0    �¼�0��ʱ��LSB��= 0x00

//PKT_CFG2-������//��λֵ=00000100
	//PKT_CFG2_RESERVED5  = 0  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	//CCA_MODE   CCAģʽ= 000 = ���Ǹ�һ����ȷ���ŵ�ָʾ
	//PKT_FORMAT  ���ݰ���ʽ���� = 00=����ģʽ/ FIFOģʽ��MDMCFG1.FIFO_EN��������Ϊ1��MDMCFG0.TRANSPARENT_MODE_EN��������Ϊ0��
	{CC112X_PKT_CFG2,          0x00},

//care--δ��ʼ��//PKT_CFG1-������//��λֵ=00000101
	//WHITE_DATA   �׻�ʹ�� = 0 =�������ݰ׻�
	//ADDR_CHECK_CFG    ��ַ������� = 00=�޵�ַ���
	//CRC_CFG   CRC���� = 01 = TXģʽʱ������CRC����RXģʽ�����CRC
	//BYTE_SWAP_EN   TX/ RX�����ֽڽ���ʹ��= 0 = ���ã��ֽڵ����ݽ���
	//APPEND_STATUS   ����״̬�ֽڵ�RX FIFOʹ��= 1 =����״̬�ֽ�
		//����������ݰ׻�     
		//�����޵�ַ���     
		//����CRC���� = 01 = TXģʽʱ������CRC����RXģʽ�����CRC

//PKT_CFG0-������//��λֵ=0x00
	//PKT_CFG0_RESERVED7  = 0 //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	//LENGTH_CONFIG  ���ݰ���������= 01=�ɱ����ݰ�����ģʽ��ͬ���ֺ��յ��ĵ�һ���ֽ�Ϊ���ݰ��������� //00�̶����ݰ�����ģʽ�����ݰ�����ͨ��PKT_LEN�Ĵ�������
	//PKT_BIT_LEN = 000  //���ڹ̶����ݰ�����ģʽ��PKT_BIT_LEN����Ϊ�㣩��ʾ��λ����/���յ�PKT_LEN���ֽ�����
	//UART_MODE_EN  UARTģʽʹ��= 0=����UARTģʽ  //1=ʹ��UARTģʽ��������ʱ�����ݰ����潫����/ɾ����ʼ��ֹͣλ/����/���յ��ֽ�
	//UART_SWAP_EN   ������ֹͣλֵ����ʹ�� = 0=���ý���������/ֹͣλֵ��'1'/'0'
		//����ɱ����ݰ�����ģʽ��ͬ���ֺ��յ��ĵ�һ���ֽ�Ϊ���ݰ��������� 
	{CC112X_PKT_CFG0,          0x20}, 

//care--δ��ʼ��//RFEND_CFG1 -RFEND����//��λֵ=00001111
	//RXOFF_MODE  RXOFFģʽ= 00=����  //01= FSTXON //10=TX //11=RX  //��оƬ���յ����õ����ݰ��󣬾���CC1120������ʲô״̬��
	//RX_TIME  RX��RXͬ����������ʱ����= 111
	//RX_TIME_QUAL  RX��ʱ�޶���= 1= ���û������ͬ���֣���ﵽPQT����CS��Чʱ����RX��ʱ������������RXģʽ

//care--δ��ʼ��//RFEND_CFG0 -RFEND����//��λֵ=0x00
	//CAL_END_WAKE_UP_EN  У׼�������ӵĻ�������ʹ�� = 0 =��ֹ���ӵĻ�������
	//TXOFF_MODE   TXOFFģʽ =00=����  //01=FSTXON //10=TX //11=RX
	//TERM_ON_BAD_PACKET_EN	��ֹ��������ݰ�ʹ�� =0=������ֹ��������һ����������ݰ������գ���ַ�����Ȼ�CRC�д���ʱ������оƬ����״̬��RFEND_CFG1.RXOFF_MODEȷ��
	//ANT_DIV_RX_TERM_CFG   ֱ��RX��ֹ�����߷ּ�����= 000=���ã���CS/ PQT���������߷ּ�����ֹ����

//care--δ��ʼ��//PA_CFG2 -���ʷŴ�������//��λֵ=01111111
	//PA_CFG2_RESERVED6  = 1  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	//PA_POWER_RAMP   PA����б��Ŀ��ˮƽ=111111  //��ʱ�������=��PA_POWER_RAMP+1��/2  -18 = 14   //0x7F=���书��15dBm //0x7D=14dBm //0x7B=13dBm //0x79=12dBm  //0x77=11dBm //0x74=10dBm  //0x72=9dBm //0x6F=8dBm   //0x6D=7dBm //0x6B=6dBm   //0x69=5dBm //0x66=4dBm   //0x64=3dBm //0x62=2dBm   //0x5F=1dBm //0x5D=0dBm   //0x56=-3dBm //0x4F=-6dBm //0x43=-11dBm
		//���ﵱPA_CFG2=0x7F����Ӧ�ķ��书�� TX power=15dB 
		
//care--δ��ʼ��//PA_CFG1 -���ʷŴ�������//��λֵ=01010110
	//FIRST_IPL = 010=��һ�м书�ʵȼ�����һ�м书�ʵȼ������Ա�̷�ΧΪ0 - 7/16 (��1/16�Ӽ���
	//SECOND_IPL = 101=�ڶ��м书�ʵȼ����ڶ��м书�ʵȼ������Ա�̷�ΧΪ8/16 - 15/16 (��1/16�Ӽ���
	//RAMP_SHAPE   PAб��ʱ���ASK / OOK��״�ĳ���=10=3����б��ʱ���1/8����ASK / OOK��״�ĳ��ȣ��Ϸ���UPSAMPLER_Pֵ��4��8��16��32��64��
	
//care--δ��ʼ��//PA_CFG0 -���ʷŴ�������//��λֵ=01111100
	//ASK_DEPTH  ASK / OOK��ȵģ�2 dB������=1111
	//UPSAMPLER_P   ����TX�ϲ����Ŀɱ���Ƶ��������P=100= TX��Ƶ��������P =16

//PKT_LEN-���ݰ���������//��λֵ=0x03
	//PACKET_LENGTH  =0xFF  //�ڹ̶�����ģʽ�£���ʾ�����ݰ��ĳ��ȣ�ֵΪ0��ʾ�ĳ���Ϊ256�ֽڡ��ڿɱ䳤�ȵ����ݰ�ģʽ�£���ֵָʾ���������󳤶ȵ����ݰ���
		//�����������󳤶ȵ����ݰ�Ϊ255�ֽ�(��ʼ��Ϊ���ɱ䳤�ȵ����ݰ�ģʽ��)
	{CC112X_PKT_LEN,           0xFF},
	
//IF_MIX_CFG-IF�������//��λֵ=0x04
	//IF_MIX_CFG_RESERVED3_0 =0x00   //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	{CC112X_IF_MIX_CFG,        0x00},
	
//FREQOFF_CFG-Ƶ��ƫ�ƾ�������//��λֵ=0x20=00100000
	//FOC_EN   Ƶ��ƫ��У��ʹ�� = 1=ʹ��Ƶ��ƫ��У��
	//FOC_CFG  Ƶ��ƫ��У������ =00=�ŵ��˲����󣬽���FOC���ȶ�����ֵ0 - 1ǰ���ֽڣ�
	//FOC_LIMIT  FOC���� = 0=RX�˲�������/4   //1=RX�˲�������/8   //��������Ƶ�ʺϳ����е�Ƶ��ƫ��У����ֻ��FOC_CFG��= 00B��Чʱ.
	//FOC_KI_FACTOR  Ƶ��ƫ�ƾ��� =10=Ƶ��ƫ�Ʋ��������ݰ����ջ�·����ϵ��=1/64
	{CC112X_FREQOFF_CFG,       0x22},

//care--δ��ʼ��//TOC_CFG -��ʱƫ��У������//��λֵ=00001011
	//TOC_LIMIT   ��ʱƫ��У������ =00=ѡ < 2000 ppm
	//TOC_PRE_SYNC_BLOCKLEN   =001=(ǰ��TOC_LIMIT = 0) 16�������ϴ���//(ǰ��TOC_LIMIT != 0)x11=���ȵı���ϵ��= 1/16
	//TOC_POST_SYNC_BLOCKLEN  = 011=(ǰ��TOC_LIMIT = 0) 64�������ϴ���//(ǰ��TOC_LIMIT != 0)x11=���ֱ�������= 1/32

//care--δ��ʼ��//MARC_SPARE -MARC����//��λֵ=0x00
	//MARC_SPARE_RESERVED3_0 =0x00  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	
//care--δ��ʼ��//ECG_CFG -�ⲿʱ��Ƶ������//��λֵ=0x00
	//EXT_CLOCK_FREQ   �ⲿʱ��Ƶ�ʡ����Ʒ�Ƶ���ӡ� =0x00=64

//care--δ��ʼ��//SOFT_TX_DATA_CFG -�������TX����//��λֵ=0x00
	//SYMBOL_MAP_CFG   ����ӳ������ = 00  //���ݲ�ͬ�ĵ��Է�ʽ���в�ͬ�ĺ��塣��������ο�User Guider��
	//SOFT_TX_DATA_CFG_RESERVED4_1  =0000    //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	//SOFT_TX_DATA_EN  ��TX����ģʽʹ��=0=���� ��TX����ģʽ
	
//care--δ��ʼ��//EXT_CTRL -�ⲿ��������//��λֵ=0x01
	//PIN_CTRL_EN  ���ſ���ʹ��=0=�������ſ���  //���ſ����ظ�ʹ��SPI�ӿ�����ִ��SRX��STX��SPWD�Ϳ��������
	//EXT_32K_CLOCK_EN  �ⲿ32Kʱ��ʹ��=0=���� �ⲿ32Kʱ��
	//BURST_ADDR_INCR_EN  ͻ����ַ����ʹ�� =1=ͻ����ַ�������ã�����ͻ�����ʣ���ַ������

//care--δ��ʼ��//RCCAL_FINE-RC����У׼������//��λֵ=0x00
	//RCC_FINE   =0x00=32kHz��RCOSCУ׼����

//care--δ��ʼ��//RCCAL_COARSE-RC����У׼���֣�//��λֵ=0x00
	//RCC_COARSE  =0x00=32kHz��RCOSCУ׼��ֵ

//care--δ��ʼ��//RCCAL_OFFSET-RC����У׼ʱ��ƫ��//��λֵ=0x00
	//RCC_CLOCK_OFFSET_RESERVED4_0  = 0x00  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�

//care--δ��ʼ��//FREQOFF1 - Ƶ��ƫ�ƣ�MSB��//��λֵ=0x00
	//FREQ_OFF_15_8  = 0x00   //Ƶ��ƫ��[15:8]�����û���SAFC�������¡���ֵ��2�Ĳ����ʽ.//SAFCָAutomatic Frequency Compensation

//care--δ��ʼ��//FREQOFF0 - Ƶ��ƫ�ƣ�LSB��//��λֵ=0x00
	//FREQ_OFF_7_0 = 0x00   //Ƶ��ƫ��[7:0]�����û���SAFC�������¡���ֵ��2�Ĳ����ʽ.//SAFCָAutomatic Frequency Compensation

//FREQ2-Ƶ������[23:16]//��λֵ=0x00
	//FREQ_23_16  Ƶ��[23:16]  =0x6C
	{CC112X_FREQ2,             0x6C},
	
//FREQ1-Ƶ������[23:16]//��λֵ=0x00
	//FREQ_15_8  Ƶ��[15:8]  =0x80
	{CC112X_FREQ1,             0x80}, 
	
//care--δ��ʼ��//FREQ0 - Ƶ������[7:0]//��λֵ=0x00
	//FREQ_7_0 Ƶ��[7:0] = 0x00	
		//�����ز�Ƶ�� = 434MHz 

//care--δ��ʼ��//IF_ADC2-ģ�⵽����ת��������//��λֵ=0x02
	//IF_ADC2_RESERVED1_0 = 0x02   //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�

//care--δ��ʼ��//IF_ADC1-ģ�⵽����ת��������//��λֵ=0xA6
	//IF_ADC1_RESERVED7_0  = 0xA6   //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�

//care--δ��ʼ��//IF_ADC0-ģ�⵽����ת��������//��λֵ=0x04
	//IF_ADC0_RESERVED2_0   = 0x04  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�

//FS_DIG1-//��λֵ=0x08
	//FS_DIG1_RESERVED3_0  = 0x00    //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	{CC112X_FS_DIG1,           0x00},
	
//FS_DIG0-//��λֵ=01011010
	//FS_DIG0_RESERVED7_4  = 0x05 //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	//RX_LPF_BW    ��RX��FS��·���� =11=170.8 kHz
	//TX_LPF_BW    ��TX��FS��·���� =11=170.8 kHz
	{CC112X_FS_DIG0,           0x5F},

//care--δ��ʼ��//FS_CAL3 -//��λֵ=0x00
	//KVCO_HIGH_RES_CFG  KVCO�߷ֱ���ʹ��=0=���ø߷ֱ��ʣ������ֱ���ģʽ��
	//FS_CAL3_RESERVED3_0   =0000    //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�

//care--δ��ʼ��//FS_CAL2 -//��λֵ=0x20
	//VCDAC_START    =0x20    //VCDAC��ʼֵ��ʹ��ֵ����SmartRF�׼�

//FS_CAL1-//��λֵ=0x00
	//FS_CAL1_RESERVED7_0  =0x40     //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	{CC112X_FS_CAL1,           0x40},

//FS_CAL0-//��λֵ=0x00
	//LOCK_CFG   ����������ƽ��ʱ��=11=����ƽ��   //00=ƽ������512�εĲ���
	//FS_CAL0_RESERVED1_0  =10   //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	{CC112X_FS_CAL0,           0x0E},

//care--δ��ʼ��//FS_CHP - ��ɱ�����//��λֵ=0x28
	//CHP_CAL_CURR  =0x28   //��ɱõ�����У׼��ʹ��ֵ����SmartRF�׼�

//FS_DIVTWO-����2//��λֵ=0x01
	//FS_DIVTWO_RESERVED1_0  = 11   //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	{CC112X_FS_DIVTWO,         0x03},

//care--δ��ʼ��//FS_DSM1- ����Ƶ�ʺϳ���ģ������//��λֵ=0x00
	//FS_DSM1_RESERVED2_0 =000  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�

//FS_DSM0-����Ƶ�ʺϳ���ģ������//��λֵ=0x03
	//FS_DSM0_RESERVED7_0  = 0x33    //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	{CC112X_FS_DSM0,           0x33},

//care--δ��ʼ��//FS_DVC1 - ��Ƶ��������//��λֵ=0xFF
	//FS_DVC1_RESERVED7_0  = 0xFF   //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�

//FS_DVC0 - ��Ƶ��������//��λֵ=0x1F
	//FS_DVC0_RESERVED4_0  =0x17   //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	{CC112X_FS_DVC0,           0x17},

//care--δ��ʼ��//FS_LBI - ����ƫ������//��λֵ=0x00
	//δʹ��

//FS_PFD - ��λƵ�ʼ��������//��λֵ=0x51
	//FS_PFD_RESERVED6_0   = 0x50   //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	{CC112X_FS_PFD,            0x50},

//FS_PRE - Ԥ��Ƶ������//��λֵ=0x2C
	//FS_PRE_RESERVED6_0  =0x6E  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	{CC112X_FS_PRE,            0x6E},

//FS_REG_DIV_CML- //��λֵ=0x11
	//FS_REG_DIV_CML_RESERVED4_0   =0x14  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	{CC112X_FS_REG_DIV_CML,    0x14},

//FS_SPARE- //��λֵ=0x00
	//FS_SPARE_RESERVED7_0 =0xAC   //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	{CC112X_FS_SPARE,          0xAC},

//care--δ��ʼ��//FS_VCO4-//��λֵ=0x14
	//FSD_VCO_CAL_CURR  =0x14   //VCO����У׼����������
	
//care--δ��ʼ��//FS_VCO3-//��λֵ=0x00
	//FS_VCO3_RESERVED0  =0x00  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	
//care--δ��ʼ��//FS_VCO2-//��λֵ=0x00
	//FSD_VCO_CAL_CAPARR  =0x00  //��У׼�����еĵ�VCOñ�������ü�
	
//care--δ��ʼ��//FS_VCO1-//��λֵ=0x00
	//FSD_VCDAC  VCDAC������ =000000=��С160����  //���ڿ���CALģʽ����Ҫע�����AVDD�ڲ�VCO�ĵ��ڵ�ѹ
	//FS_VCO1_RESERVED1_0 =00  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�

//FS_VCO0- //��λֵ=10000001
	//FS_VCO0_RESERVED7 =1    //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	//FS_VCO0_RESERVED6_0  =0110100 //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	{CC112X_FS_VCO0,           0xB4},

//care--δ��ʼ��//GBIAS6��GBIAS0- ͨ��ƫ������
	//GBIAS6 //��λֵ=0x00
	//GBIAS5 //��λֵ=0x02
	//GBIAS4 //��λֵ=0x00
	//GBIAS3 //��λֵ=0x00
	//GBIAS2 //��λֵ=0x10
	//GBIAS1 //��λֵ=0x00
	//GBIAS0 //��λֵ=0x00

//care--δ��ʼ��//IFAMP-��Ƶ�Ŵ�������//��λֵ=0x01
	//IFAMP_RESERVED1_0 = 01  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�

//care--δ��ʼ��//LNA -�������Ŵ�������//��λֵ=0x01
	//LNA_RESERVED1_0  = 01  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�

//care--δ��ʼ��//RXMIX - RX��Ƶ������//��λֵ=0x01
	//RXMIX_RESERVED1_0  = 01  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�

//XOSC5-������������ //��λֵ=0x0C
	//XOSC5_RESERVED3_0  = 0x0E   //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	{CC112X_XOSC5,             0x0E},   

//care--δ��ʼ��//XOSC4-������������//��λֵ=0xA0
	//XOSC4_RESERVED7_0  =0xA0 //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�

//care--δ��ʼ��//XOSC3-������������//��λֵ=0x03
	//XOSC3_RESERVED7_0  =0x03   //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�

//care--δ��ʼ��//XOSC2-������������//��λֵ=00000100
	//XOSC2_RESERVED3_1 = 010 //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	//XOSC_CORE_PD_OVERRIDE  = 0=��� SXOFF��SPWD��SWOR�����������XOSC�����ر�
	
//XOSC1-������������//��λֵ=0x00
	//XOSC1_RESERVED2 = 0   //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	//XOSC_BUF_SEL XOSC������ѡ��ѡ���ڲ�XOSC�������Ƶ���໷= 1=����λ��������ֻ��������͹�������ʱ�ӻ�������ʹ�ã� //0=�͹��ģ����˻���������ֻ��������رգ�
	//XOSC_STABLE =1=XOSC���ȶ��ģ�������ȶ���
	{CC112X_XOSC1,             0x03},   //{CC112X_XOSC1,         0x07},
	
//care--δ��ʼ��//XOSC0-������������//��λֵ=0x00
	//XOSC0_RESERVED1_0 =00  //�����ڲ���Ŀ��

///////////////////////////////////////////////////
//care--δ��ʼ��//ANALOG_SPARE- //��λֵ=0x00
//care--δ��ʼ��//PA_CFG3- ���ʷŴ�������//��λֵ=0x00
//care--δ��ʼ��//WOR_TIME1-eWOR��ʱ��״̬��MSB�� //��λֵ=0x00
//care--δ��ʼ��//WOR_TIME0-eWOR��ʱ��״̬��LSB�� //��λֵ=0x00
//care--δ��ʼ��//WOR_CAPTURE1 - eWOR��ʱ����׽��MSB��//��λֵ=0x00
//care--δ��ʼ��//WOR_CAPTURE0 - eWOR��ʱ����׽��LSB��//��λֵ=0x00
//care--δ��ʼ��//BIST - MARC BIST- //��λֵ=0x00
//care--δ��ʼ��//DCFILTOFFSET_I1 - ֱ���˲���ƫ��I��MSB��//��λֵ=0x00
//care--δ��ʼ��//DCFILTOFFSET_I0 - ֱ���˲���ƫ��I��LSB��//��λֵ=0x00
//care--δ��ʼ��//DCFILTOFFSET_Q1 -ֱ���˲���ƫ�� Q��MSB��//��λֵ=0x00
//care--δ��ʼ��//DCFILTOFFSET_Q0 -ֱ���˲���ƫ�� Q��LSB��//��λֵ=0x00
//care--δ��ʼ��//IQIE_I1 - IQ��ƽ��ֵI��MSB��//��λֵ=0x00
//care--δ��ʼ��//IQIE_I0 - IQ��ƽ��ֵI��LSB��//��λֵ=0x00
//care--δ��ʼ��//IQIE_Q1 - IQ��ƽ��ֵQ��MSB��//��λֵ=0x00
//care--δ��ʼ��//IQIE_Q0 - IQ��ƽ��ֵQ��LSB��//��λֵ=0x00
///////////////////////////////////////////////////

//care--δ��ʼ��//RSSI1 - �����ź�ǿ��ָʾ����MSB��(ֻ��) //��λֵ=0x80
	//RSSI_11_4   �����ź�ǿ��ָʾ��[11:4]=0x80

//care--δ��ʼ��//RSSI0 - �����ź�ǿ��ָʾ����LSB��(ֻ��) //��λֵ=0x00
	//RSSI_3_0  �����ź�ǿ��ָʾ��[3:0]=0x00
	//CARRIER_SENSE  �ز�����=0=���ز����
	//CARRIER_SENSE_VALID  �ز�������Чʹ��=0= �ز�������Ч
	//RSSI_VALID   RSSI��Чʹ��=0=RSSI��Ч
		//�������ز����,�ز�������Ч,RSSI��Ч 

//care--δ��ʼ��//MARCSTATE - MARC ״̬(ֻ��) //��λֵ=01000001       //MARC (Main Radio Control)
	//MARC_2PIN_STATE   MARC2����״ֵ̬=10=����IDLE   //00=SETTLING //01=TX //11=RX
	//MARC_STATE    MARC ״̬=00001=����IDLE   //00000=SLEEP //00001=IDLE //00010=XOFF //00011=BIAS_SETTLE_MC //00100=REG_SETTLE_MC //00101=MANCAL //00110=BIAS_SETTLE //00111=REG_SETTLE //01000=STARTCAL //01001=BWBOOST //01010=FS_LOCK //01011=IFADCON //01100=ENDCAL //01101=RX //01110=RX_END //01111=Reserved //10000=TXRX_SWITCH //10001=RX_FIFO_ERR //10010=FSTXON //10011=TX //10100=TX_END //10101=RXTX_SWITCH //10110=TX_FIFO_ERR //10111=IFADCON_TXRX

//care--δ��ʼ��//LQI_VAL - ��·����ָ��ֵ(ֻ��) //��λֵ=0x00
	//CRC_OK  = 0=CRCУ�鲻���������룩
	//LQI  ��������ָ��=0x00  //�ϵ�ֵ�����ӱȽϸ�ֵ������Ҫ��

//care--δ��ʼ��//PQT_SYNC_ERROR-ǰ�����ͬ���ִ���(ֻ��) //��λֵ=0xFF
	//PQT_ERROR  ǰ�����޶���ֵ= 1111   //
	//SYNC_ERROR ͬ�����޶���ֵ= 1111  //

//care--δ��ʼ��//DEM_STATUS - �����״̬(ֻ��)//��λֵ=0x00
	//RSSI_STEP_FOUND  (ֻ��)  //�����ݰ�����ʱ���������RSSI������λ
	//COLLISION_FOUND  (ֻ��)  //�����ݰ�����ʱ�������⵽ͬ���֣�����λ
	//SYNC_LOW0_HIGH1  ���DualSync = 0=ͬ���ַ���=[SYNC15_8 SYNC7_0]   //1=ͬ���ַ���=[SYNC31_24 SYNC23_16]
	//DEM_STATUS_RESERVED4_1  =0000  //�����ڲ���Ŀ��
	//IMAGE_FOUND    ͼ��̽����=0=δ����Ӱ��

//care--δ��ʼ��//FREQOFF_EST1 - Ƶƫ���ƣ�MSB��(ֻ��) //��λֵ=0x00
//care--δ��ʼ��//FREQOFF_EST0 - Ƶƫ���ƣ�LSB��(ֻ��) //��λֵ=0x00
//care--δ��ʼ��//AGC_GAIN3-AGC����//��λֵ=0x00   //AGC_FRONT_END_GAIN =00  //AGCǰ�����档ʵ��Ӧ�õķֱ���Ϊ1 dB����
//care--δ��ʼ��//AGC_GAIN2-AGC����//��λֵ=11101001  //AGC_DRIVES_FE_GAIN  ����AGC�������=1=AGC����ǰ������  //AGC_LNA_CURRENT  //AGC_LNA_R_DEGEN
//care--δ��ʼ��//AGC_GAIN1-AGC����//��λֵ=0x00   //AGC_LNA_R_LOAD //AGC_LNA_R_RATIO
//care--δ��ʼ��//AGC_GAIN0-AGC����//��λֵ=00111111  //AGC_IF_MODE  //AGC_IFAMP_GAIN
//care--δ��ʼ��//SOFT_RX_DATA_OUT-�������RX�������//��λֵ=0x00   //SOFT_RX_DATA
//care--δ��ʼ��//SOFT_TX_DATA_OUT-�������TX��������//��λֵ=0x00   //SOFT_TX_DATA
//care--δ��ʼ��//ASK_SOFT_RX_DATA - AGC ASK ����������//��λֵ=0x30  //ASK_SOFT_RX_DATA_RESERVED5_0 

//care--δ��ʼ��//RNDGEN - �����ֵ//��λֵ=0x7F
	//RNDGEN_EN  �����������ʹ�� =0=���������������
	//RNDGEN_VALUE �����ֵ=0x7F

//care--δ��ʼ��//MAGN2 - CORDIC����źŷ���[16](ֻ��)//��λֵ=0x00  //DEM_MAGN_16=0  //CORDIC���˲ʱ�źŷ��ȣ�17λ[16]
//care--δ��ʼ��//MAGN1 - CORDIC����źŷ���[15:8](ֻ��)//��λֵ=0x00  //DEM_MAGN_15_8=0  //CORDIC���˲ʱ�źŷ���[15:8]
//care--δ��ʼ��//MAGN0 - CORDIC����źŷ���[7:0](ֻ��)//��λֵ=0x00  //DEM_MAGN_7_0=0  //CORDIC���˲ʱ�źŷ���[7:0]
//care--δ��ʼ��//ANG1 - CORDIC����źŽǶ�[9:8](ֻ��)//��λֵ=0x00  //CORDIC���˲ʱ�źŵĽǶ�
//care--δ��ʼ��//ANG0 - CORDIC����źŽǶ�[7:0](ֻ��)//��λֵ=0x00  //CORDIC���˲ʱ�źŵĽǶ�
//care--δ��ʼ��//CHFILT_I2 - ͨ��ɸѡ���ݵ�ʵ��[18:16](ֻ��)//��λֵ=0x80  //DEM_CHFILT_STARTUP_VALID=1=�ŵ��˲���������Ч������16�ŵ��˲�����Ʒ��  //DEM_CHFILT_I_18_16
//care--δ��ʼ��//CHFILT_I1 - ͨ��ɸѡ���ݵ�ʵ��[15:8](ֻ��)//��λֵ=0x00   //DEM_CHFILT_I_15_8
//care--δ��ʼ��//CHFILT_I0 - ͨ��ɸѡ���ݵ�ʵ��[7:0](ֻ��)//��λֵ=0x00    //DEM_CHFILT_I_7_0
//care--δ��ʼ��//CHFILT_Q2 - ͨ��ɸѡ���ݵ��鲿[18:16](ֻ��)//��λֵ=0x00  //DEM_CHFILT_Q_18_16
//care--δ��ʼ��//CHFILT_Q1 - ͨ��ɸѡ���ݵ�ʵ��[15:8](ֻ��)//��λֵ=0x00   //DEM_CHFILT_Q_15_8
//care--δ��ʼ��//CHFILT_Q0 - ͨ��ɸѡ���ݵ�ʵ��[7:0](ֻ��)//��λֵ=0x00    //DEM_CHFILT_Q_7_0

//care--δ��ʼ��//GPIO_STATUS - GPIO ״̬//��λֵ=0x00
	//GPIO_STATUS_RESERVED7_4  =0000  //�����ڲ���Ŀ��
	//GPIO_STATE  GPIO���ŵĵ�״̬=0000

//care--δ��ʼ��//FSCAL_CTRL-//��λֵ=0x01
	//FSCAL_CTRL_RESERVED6_1  =0x00 //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
	//LOCK  ����ָʾ�ƣ�FS_CFG.FS_LOCK_EN������1��=1=FS��δ��⵽   //�ź�״ֻ̬������RX��TX��FSTXON״̬

//care--δ��ʼ��//PHASE_ADJUST-//��λֵ=0x00  //�����ڲ���Ŀ��

//PARTNUMBER -оƬ�ͺ�//��λֵ=0x00
	//PARTNUM   оƬID=0x48=CC1120  //0x40=CC1121 //0x48=CC1120 //0x58=CC1125 //0x5A=CC1175
	{CC112X_PARTNUMBER,        0x48},
	
//PARTVERSION- ���ֵ���//��λֵ=0x00
	//PARTVER  оƬ�޶�=0x21
	{CC112X_PARTVERSION,       0x21},

//care--δ��ʼ��//SERIAL_STATUS - ����״̬//��λֵ=0x00
	//CLK32K (ֻ��) =0=�ڲ�32 kHz RC����ʱ��
	//IOC_SYNC_PINS_EN  ͬ��IO����ʹ�� =0
	//SOFT_TX_DATA_CLK(ֻ��) =0   //������������ʱ�ӣ���̵��������ʵ�16�����ϣ�
	//SERIAL_RX(ֻ��) =0   //���н�������
	//SERIAL_RX_CLK(ֻ��) =0   //���н�������ʱ��

//RX_STATUS- RX  ״̬(ֻ��) //��λֵ=0x01
	//SYNC_FOUND =0  //����SYNC_EVENTʱ��λ������SRXʱ����λ
	//RXFIFO_FULL =0 //���ֽ�������RX FIFO��ֵʱ����λ�� ��RX FIFOΪ��ʱ����λ
	//RXFIFO_OVER_THR =0  //���ֽ�������RX FIFO��ֵʱ����λ�� ��RX FIFOС�ڻ������ֵʱ����λ��
	//RXFIFO_EMPTY =0  //RX FIFO Ϊ��ʱ����λ
	//RXFIFO_OVERFLOW =0 //��RX FIFO���ʱ����λ; �� RX FIFO�����ʱ����λ��
	//RXFIFO_UNDERFLOW =0 //����û��ӿյ�RX FIFO ��ȡ����ʱ����λ��  �� RX FIFO�����ʱ����λ��
	//PQT_REACHED =0 //��⵽ǰͬ���루ǰ���޶���ֵС���趨��PQT��ֵ��ʱ����λ����λ�������UserGuider
	//PQT_VALID =1 //���յ�16λ��43λ��ȡ����PREAMBLE_CFG0.PQT_VALID_TIMEOUT���ã�ʱ�����⵽ǰ����ʱ����λ��
	{CC112X_RX_STATUS,         0x10},

//care--δ��ʼ��//TX_STATUS-TX ״̬(ֻ��)//��λֵ=0x00
	//TX_STATUS_RESERVED5   =0  //�����ڲ���Ŀ��
	//SYNC_SENT =0  //������ͬ�������һλ
	//TXFIFO_FUL =0  //��TX FIFO ��ʱ����λ�� ��������С��TX FIFO��ֵʱ����λ
	//TXFIFO_OVER_THR =0  //�������ڴ��ڻ����TX FIFO��ֵʱ����λ
	//TXFIFO_OVERFLOW =0  //��TX FIFO���ʱ���û���������TXFIFOд���ݣ�ʱ����λ�� TX FIFO�����ʱ����λ
	//TXFIFO_UNDERFLOW =0  //��TX FIFO ���磨�����ݰ�����ǰ��TX FIFOΪ�գ�ʱ����λ�� ��TX FIFO�����ʱ����λ
	
//care--δ��ʼ��//MARC_STATUS1 -MARC ״̬(ֻ��)//��λֵ=0x00  //���ڼ�¼��ʲô�źŲ���MARC_MCU_WAKEUP�ź�
	//MARC_STATUS_OUT =00000000=û�д��󣨾�������� User Guide��

//care--δ��ʼ��//MARC_STATUS0 -MARC ״̬(ֻ��)//��λֵ=0x00  
	//MARC_STATUS0_RESERVED3 =0  //�����ڲ���Ŀ��
	//TXONCCA_FAILED =0=�ŵ�����������ߵ������TX״̬  //1=�ŵ���æ�����ߵ罫������RX״̬  //��TXONCCA_DONE�ź���Ч֮�󣬲��ܶ�ȡ��λ��
	//MCU_WAKE_UP MCU�����ź�=0  //��MARC_STATUS1.MARC_STATUS_OUT���һ����¼���ԭ��
	//RCC_CAL_VALID =0   //RCOSC�Ѿ�����У׼һ��


//care--δ��ʼ��//PA_IFAMP_TEST-//��λֵ=0x00 //PA_IFAMP_TEST_RESERVED4_0  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
//care--δ��ʼ��//FSRF_TEST-//��λֵ=0x00     //FSRF_TEST_RESERVED6_0  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
//care--δ��ʼ��//PRE_TEST-//��λֵ=0x00     //PRE_TEST_RESERVED4_0   //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
//care--δ��ʼ��//PRE_OVR-//��λֵ=0x00   //PRE_TEST_RESERVED4_0   //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
//care--δ��ʼ��//ADC_TEST - ADC Test //��λֵ=0x00  //ADC_TEST_RESERVED5_0  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
//care--δ��ʼ��//DVC_TEST - DVC Test //��λֵ=0x0B  //DVC_TEST_RESERVED4_0  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
//care--δ��ʼ��//ATEST-//��λֵ=0x40    //ATEST_RESERVED6_0  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
//care--δ��ʼ��//ATEST_LVDS-//��λֵ=0x00   //ATEST_LVDS_RESERVED3_0  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
//care--δ��ʼ��//ATEST_MODE-//��λֵ=0x00   //ATEST_MODE_RESERVED7_0  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
//care--δ��ʼ��//XOSC_TEST1-//��λֵ=0x3C   //XOSC_TEST1_RESERVED7_0  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
//care--δ��ʼ��//XOSC_TEST0-//��λֵ=0x00   //XOSC_TEST0_RESERVED7_0  //�����ڲ���Ŀ�ģ�ʹ��ֵ����SmartRF�׼�
//care--δ��ʼ��//RXFIRST - RX FIFO Pointer (first entry)//��λֵ=0x00  //ָ���һ��д��RX FIFO���ֽ�
//care--δ��ʼ��//TXFIRST - TX FIFO Pointer (first entry)//��λֵ=0x00  //ָ���һ��д��TX FIFO���ֽ�  
//care--δ��ʼ��//RXLAST - RX FIFO Pointer (last entry)//��λֵ=0x00    //ָ�����һ��д��RX FIFO���ֽ�
//care--δ��ʼ��//TXLAST - TX FIFO Pointer (last entry)//��λֵ=0x00    //ָ�����һ��д��TX FIFO���ֽ�  
//care--δ��ʼ��//NUM_TXBYTES - TX FIFO״̬(ռ�ÿռ�)//��λֵ=0x00  //TXBYTES  TX FIFO�е��ֽ���
//care--δ��ʼ��//NUM_RXBYTES - RX FIFO״̬(ռ�ÿռ�)//��λֵ=0x00  //RXBYTES  RX FIFO�е��ֽ���
//care--δ��ʼ��//FIFO_NUM_TXBYTES - TX FIFO״̬(�հ׿ռ�)//��λֵ=0x0F  //FIFO_TXBYTES  TX FIFO�пհ׿ռ���ֽ�����1111����ʾ����>=15���ֽڵĿռ䣬���Ա�д�롣
//care--δ��ʼ��//FIFO_NUM_RXBYTES - RX FIFO״̬(�ɻ�õ��ֽ���)//��λֵ=0x00  //FIFO_RXBYTES  RX FIFO�п��Ա��������ֽ�����1111����ʾ����>=15���ֽڣ����Զ���
};


////////////////////////////////////////////////////////////////////////////
//==blues==����API���==////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//--**Ƶ��ѡ��**----------------------------------------------//
#define CC112X_820_band    (1)  //820.0 - 960.0 MHz band
#define CC112X_410_band    (2)  //410.0 - 480.0 MHz band
#define CC112X_273_3_band  (3)  //273.3 - 320.0 MHz band
#define CC112X_205_band    (4)  //205.0 - 240.0 MHz band
#define CC112X_164_band    (5)  //164.0 - 192.0 MHz band
#define CC112X_136_7_band  (6)  //136.7 - 160.0 MHz band

////////////////////////////////////////////////////////////////////////////
//--**���Ƹ�ʽ**--------------------------------------------------//
#define CC112X_2_FSK_mode    (1)  //bit5:3=000="2-FSK"
#define CC112X_2_GFSK_mode   (2)  //bit5:3=001=2-GFSK
#define CC112X_ASK_OOK_mode  (3)  //bit5:3=011=ASK/OOK
#define CC112X_4_FSK_mode    (4)  //bit5:3=100=4-FSK
#define CC112X_4_GFSK_mode   (5)  //bit5:3=101=4-GFSK 

////////////////////////////////////////////////////////////////////////////
//--**���书��**--------------------------------------------------//
#define CC112X_15dBm_TxPower    ( 1)  //0x7F=���书��= 15dBm
#define CC112X_14dBm_TxPower    ( 2)  //0x7D=���书��= 14dBm
#define CC112X_13dBm_TxPower    ( 3)  //0x7B=���书��= 13dBm
#define CC112X_12dBm_TxPower    ( 4)  //0x79=���书��= 12dBm
#define CC112X_11dBm_TxPower    ( 5)  //0x77=���书��= 11dBm
#define CC112X_10dBm_TxPower    ( 6)  //0x74=���书��= 10dBm
#define CC112X_09dBm_TxPower    ( 7)  //0x72=���书��= 09dBm
#define CC112X_08dBm_TxPower    ( 8)  //0x6F=���书��= 08dBm
#define CC112X_07dBm_TxPower    ( 9)  //0x6D=���书��= 07dBm
#define CC112X_06dBm_TxPower    (10)  //0x6B=���书��= 06dBm
#define CC112X_05dBm_TxPower    (11)  //0x69=���书��= 05dBm
#define CC112X_04dBm_TxPower    (12)  //0x66=���书��= 04dBm
#define CC112X_03dBm_TxPower    (13)  //0x64=���书��= 03dBm
#define CC112X_02dBm_TxPower    (14)  //0x62=���书��= 02dBm
#define CC112X_01dBm_TxPower    (15)  //0x5F=���书��= 01dBm
#define CC112X_00dBm_TxPower    (16)  //0x5D=���书��= 00dBm
#define CC112X__3dBm_TxPower    (17)  //0x56=���书��= -3dBm
#define CC112X__6dBm_TxPower    (18)  //0x4F=���书��= -6dBm
#define CC112X__11dBm_TxPower   (19)  //0x43=���书��= -11dBm


////////////////////////////////////////////////////////////////////////////
//--** **--------------------------------------------------//



////////////////////////////////////////////////////////////////////////////
//--** **--------------------------------------------------//



////////////////////////////////////////////////////////////////////////////
//--** **--------------------------------------------------//



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern unsigned int CC112x_RX_PacketCnt;
extern unsigned int CC112x_TX_PacketCnt;
extern unsigned char CC112x_TxBuf[128]; // ���ͻ��������ֽ���<128


////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"��������**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////
static void Initial_GPIO_Int_CC112x(void);  //��ʼ��:  GPIO��ƽ�ж�
static void Initial_SPI_CC112x(void);  //��ʼ��: SPI���нӿ�(CC112x)

static void registerConfig(void);
static void manualCalibration(void);
//static void createPacket(uint8 randBuffer[]);



////////////////////////////////////////////////////////////////////////////
//==**"�ⲿ" API ��������**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

	//��ʼ������:  "CC112x �͹���������Ƶ�շ���"
extern void Initial_CC112x(void);  

	//������ղ���"CC112x �͹���������Ƶ�շ���"
extern void Deal_RX_CC112x(void);  

	//CC112x��������(�ַ���)-- "CC112x �͹���������Ƶ�շ���"
extern void TX_String_CC112x(unsigned char *pData, unsigned char len); 

////////////////////////////////////////////////////////////////////////////

	//����:Ƶ��--"CC112x �͹���������Ƶ�շ���"
extern void Config_FrequencyBand(unsigned char bandKind);  

	//����:�ز�Ƶ��--"CC112x �͹���������Ƶ�շ���"
extern void Config_CarrierFrequency(unsigned char frenquency_2,unsigned char frenquency_1,unsigned char frenquency_0);  

	//����:�����˲�������--"CC112x �͹���������Ƶ�շ���"
extern void Config_RxFilterBW(unsigned char rxFilterBW);  

	//����:��������--"CC112x �͹���������Ƶ�շ���"
extern void Config_DataRate(unsigned char dataRate_2,unsigned char dataRate_1,unsigned char dataRate_0);  

	//����:���Ƹ�ʽ��Ƶ��ƫ��--"CC112x �͹���������Ƶ�շ���"
extern void Config_ModulationFormat_Deviation(unsigned char modulation,unsigned char deviation);  

	//����:���书��(���ʷŴ���)--"CC112x �͹���������Ƶ�շ���"
extern void Config_PA_TxPower(unsigned char txPower);  

	//����:�豸��ַ--"CC112x �͹���������Ƶ�շ���"
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
*******************************************************************************/
#endif

