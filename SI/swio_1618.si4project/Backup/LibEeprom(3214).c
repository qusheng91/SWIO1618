#include "LibEeprom.h"
#include "LibVarDefine.h"
#include "delay.h"

SPI_InitTypeDef  SPI_InitStructure;
//SPI��ʼ������
void LibSpiInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1, ENABLE );	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//ѡ���˴���ʱ�ӵ���̬:ʱ�����ո�
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//���ݲ����ڵڶ���ʱ����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI1, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
	SPI_Cmd(SPI1, ENABLE); //ʹ��SPI����
}

//SPI �ٶ����ú���
//SpeedSet:
//SPI_BaudRatePrescaler_2   2��Ƶ   (SPI 36M@sys 72M)
//SPI_BaudRatePrescaler_8   8��Ƶ   (SPI 9M@sys 72M)
//SPI_BaudRatePrescaler_16  16��Ƶ  (SPI 4.5M@sys 72M)
//SPI_BaudRatePrescaler_256 256��Ƶ (SPI 281.25K@sys 72M)
  
void LibSpiSetSpeed(u8 SpeedSet)
{
	SPI_InitStructure.SPI_BaudRatePrescaler = SpeedSet ;
  	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1,ENABLE);
}

//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 LibSpiReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI_I2S_SendData(SPI1, TxData); //ͨ������SPIx����һ������
	retry=0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)//���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI1); //����ͨ��SPIx������յ�����					    
}

//eeprom��ʼ������
void LibEepromInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	LibSpiInit();
	LibSpiSetSpeed(SPI_BaudRatePrescaler_8);
}

//��һ���ֽں���
u8 LibReadOneByte(u16 addr)
{
	u8 res;
	SPI_Cmd(SPI1,ENABLE);
	SPI_EEPROM_CS = 0;
	LibSpiReadWriteByte(READ);
	LibSpiReadWriteByte((addr>>8));
	LibSpiReadWriteByte(addr % 256);
	res = LibSpiReadWriteByte(0xff);
	SPI_EEPROM_CS = 1;
	SPI_Cmd(SPI1,DISABLE);
	return res;
}

//дһ���ֽں���
//����ֵΪ0ʱ��д��������ȷ������ֵΪ1ʱ��д�����
u8 LibWriteOneByte(u16 addr,u8 data)
{
	u8 Congfirm_data;
	if(addr > 4080)
	{
		return 1;
	}
	SPI_Cmd(SPI1,ENABLE);
	SPI_EEPROM_CS = 0;
	LibSpiReadWriteByte(WREN);
	SPI_EEPROM_CS = 1;
	SPI_EEPROM_CS = 0;
	LibSpiReadWriteByte(WRITE);
	LibSpiReadWriteByte(addr>>8);
	LibSpiReadWriteByte(addr % 256);
	LibSpiReadWriteByte(data);
	SPI_EEPROM_CS = 1;
	SPI_Cmd(SPI1,DISABLE);
	//��֤д�������Ƿ���ȷ
	delay_ms(1);
	Congfirm_data = LibReadOneByte(addr);
	if(Congfirm_data == data)
		return 0;
	else
		return 1;
}

