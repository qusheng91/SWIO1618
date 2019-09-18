#include "serial.h"
#include "stm32f10x.h"


def_queue serial_rx_buffer;
def_queue serial_tx_buffer;


void serial_init(uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
        
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure USART Rx as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	RTS_RINGBUFFER_INIT(serial_rx_buffer);
    RTS_RINGBUFFER_INIT(serial_tx_buffer);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    USART_Cmd(USART1, ENABLE);
}

uint16_t serial_read(uint8_t *pbBuffer, uint16_t uiSize)
{
	unsigned int i;
	
	if (!pbBuffer || !uiSize)		
		return 0;

	i = MIN(RTS_RINGBUFFER_GET_FILL_SIZE(serial_rx_buffer), uiSize);
	RTS_RINGBUFFER_READ(pbBuffer, serial_rx_buffer, i);

	if (i < uiSize)
	{
		/* Enable the Read data register not empty interrupt */
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	}
	
	return i;
}

uint16_t serial_write(uint8_t *pbBuffer, uint16_t uiSize)
{
	unsigned int i;
    
	if (!pbBuffer || !uiSize)
		return 0;	
	
	i = MIN(RTS_RINGBUFFER_GET_FREE_SIZE(serial_tx_buffer), uiSize);
	RTS_RINGBUFFER_WRITE(pbBuffer, serial_tx_buffer, i);

	/* Enable the Tx buffer empty interrupt */
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

	return i; 
}

uint16_t serial_get_readable_size(void)
{
	uint16_t ret;
	
	ret = RTS_RINGBUFFER_GET_FILL_SIZE(serial_rx_buffer);
	return ret;
}

void USART1_IRQHandler(void)
{	
	unsigned int i;
	unsigned char data;
	
	/* USART in Transmitter mode */
	if (USART_GetITStatus(USART1, USART_IT_TXE) == SET)
	{	
        i = MIN(RTS_RINGBUFFER_GET_FILL_SIZE(serial_tx_buffer), 1);

		/* something to trasmit? */
		if (i) 
		{
			RTS_RINGBUFFER_READ(&data, serial_tx_buffer, i);

			/* Send Transaction data */
			USART_SendData(USART1, data);	
		}
		else
		{
			/* Disable the Tx buffer empty interrupt */
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);	
		}	
	}	
	
	/* USART in Receiver mode */
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		i = MIN(RTS_RINGBUFFER_GET_FREE_SIZE(serial_rx_buffer), 1);

		/* Receive Transaction data */
      	data = USART_ReceiveData(USART1);
		
    	RTS_RINGBUFFER_WRITE(&data, serial_rx_buffer, i);	
  	}
}


#if 1
int fputc(int ch, FILE *f)
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    USART_SendData(USART1, (uint8_t) ch);

    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {}

    return ch;
}
#endif
