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

//SPI初始化函数
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
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    EEPROM_CS_DISABLE;

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                       //设置SPI工作模式:设置为主SPI
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                   //设置SPI的数据大小:SPI发送接收8位帧结构
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                         //选择了串行时钟的稳态:时钟悬空高
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                        //数据捕获于第二个时钟沿
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                           //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;  //定义波特率预分频的值:波特率预分频值为256
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                  //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
    SPI_InitStructure.SPI_CRCPolynomial = 7;                            //CRC值计算的多项式
    SPI_Init(SPI1, &SPI_InitStructure);                                 //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
    SPI_Cmd(SPI1, ENABLE); //使能SPI外设
}

static int8_t eeprom_read_write_byte(uint8_t w_data, uint8_t *r_data)
{       
    uint8_t retry = 0;                  
    
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
    {
        retry++;
        if (retry > 200)
            return -1;
    }             
    SPI_I2S_SendData(SPI1, w_data); //通过外设SPIx发送一个数据

    retry = 0;
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)//检查指定的SPI标志位设置与否:接受缓存非空标志位
    {
        retry++;
        if(retry > 200)
            return -1;
    }
    if (r_data != NULL)
    {
        *r_data = SPI_I2S_ReceiveData(SPI1); //返回通过SPIx最近接收的数据            
    }
    else
    {
        SPI_I2S_ReceiveData(SPI1); //返回通过SPIx最近接收的数据 
    }
    
    return 1;
}

//读一个字节函数
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

