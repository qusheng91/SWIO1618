#include "LibEeprom.h"
#include "stm32f10x.h"
#include "delay.h"

#define DE_GAP  10

#define EEPROM_CS_ENABLE     GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define EEPROM_CS_DISABLE    GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define EEPROM_WRSR_CMD     0x01
#define EEPROM_WRITE_CMD    0x02
#define EEPROM_READ_CMD     0x03
#define EEPROM_WRDI_CMD     0x04
#define EEPROM_RDSR_CMD     0x05
#define EEPROM_WREN_CMD     0x06

#define NULL    ((void *)0)

static int8_t eeprom_read_write_byte(uint8_t w_data, uint8_t *r_data);

//SPI��ʼ������
void eeprom_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
        
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    EEPROM_CS_DISABLE;

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                       //����SPI����ģʽ:����Ϊ��SPI
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                   //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                         //ѡ���˴���ʱ�ӵ���̬:ʱ�����ո�
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                        //���ݲ����ڵڶ���ʱ����
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                           //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;  //���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                  //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
    SPI_InitStructure.SPI_CRCPolynomial = 7;                            //CRCֵ����Ķ���ʽ
    SPI_Init(SPI1, &SPI_InitStructure);                                 //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
    SPI_Cmd(SPI1, ENABLE); //ʹ��SPI����
}

static int8_t eeprom_read_write_byte(uint8_t w_data, uint8_t *r_data)
{       
    uint8_t retry = 0;                  
    
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
    {
        retry++;
        if (retry > 200)
            return -1;
    }             
    SPI_I2S_SendData(SPI1, w_data); //ͨ������SPIx����һ������

    retry = 0;
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)//���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
    {
        retry++;
        if(retry > 200)
            return -1;
    }
    if (r_data != NULL)
    {
        *r_data = SPI_I2S_ReceiveData(SPI1); //����ͨ��SPIx������յ�����            
    }
    else
    {
        SPI_I2S_ReceiveData(SPI1); //����ͨ��SPIx������յ����� 
    }
    
    return 1;
}

//��һ���ֽں���
int8_t eeprom_read_byte(uint16_t addr, uint8_t *data)
{
    int8_t res = -1;

    if(addr >= 4096)
    {
        return -1;
    }
    
    EEPROM_CS_ENABLE;
    delay_us(DE_GAP);
    res = eeprom_read_write_byte(EEPROM_READ_CMD, NULL);
    if (res == -1)
    {
        return res;
    }

    res = eeprom_read_write_byte(addr >> 8, NULL);
    if (res == -1)
    {
        return res;
    }

    res = eeprom_read_write_byte(addr % 256, NULL);
    if (res == -1)
    {
        return res;
    }

    res = eeprom_read_write_byte(0xff, data);     
    EEPROM_CS_DISABLE;
    delay_ms(3);
    return res;
}

void eeprom_write_enable(void)
{
    EEPROM_CS_ENABLE;
    delay_us(DE_GAP);
    eeprom_read_write_byte(EEPROM_WREN_CMD, NULL);
    EEPROM_CS_DISABLE;
    delay_us(DE_GAP);
}

int8_t eeprom_write_byte(uint16_t addr, uint8_t data)
{
    uint8_t data_tmp;
    int8_t res = -1;

    if(addr >= 4096)
    {
        return -1;
    }
    
    eeprom_write_enable();

    EEPROM_CS_ENABLE;
    delay_us(DE_GAP);

    res = eeprom_read_write_byte(EEPROM_WRITE_CMD, NULL);
    if (res == -1)
    {
        return res;
    }
    delay_us(DE_GAP);

    res = eeprom_read_write_byte(addr >> 8, NULL);    
    if (res == -1)
    {
        return res;
    }

    res =  eeprom_read_write_byte(addr % 256, NULL);
    if (res == -1)
    {
        return res;
    }
    
    res = eeprom_read_write_byte(data, NULL);
    
    EEPROM_CS_DISABLE;

    delay_ms(3);
    return res;
}


int8_t eeprom_write(uint16_t addr, uint8_t *data, uint16_t size)
{
    int8_t res;
    uint16_t i;
    
    if(addr + size >= 4096)
    {
        return -1;
    }
    
    eeprom_write_enable();

    EEPROM_CS_ENABLE;
    delay_us(DE_GAP);

    res = eeprom_read_write_byte(EEPROM_WRITE_CMD, NULL);
    if (res == -1)
    {
        EEPROM_CS_DISABLE;
        return res;
    }

    res = eeprom_read_write_byte(addr >> 8, NULL);    
    if (res == -1)
    {
        EEPROM_CS_DISABLE;
        return res;
    }

    res =  eeprom_read_write_byte(addr % 256, NULL);
    if (res == -1)
    {
        EEPROM_CS_DISABLE;
        return res;
    }

    for (i = 0; i < size; i++)
    {
        res = eeprom_read_write_byte(data[i], NULL);
    }

    EEPROM_CS_DISABLE;
    delay_ms(3);
}

