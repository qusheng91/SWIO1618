#ifndef XXX_QUEUE_H_
#define XXX_QUEUE_H_
#include <stdint.h>
#include <string.h>

#ifndef MIN
#define MIN(x,y)	((x)<(y)?(x):(y))
#endif

#define QUEUE_SIZE	0x100U

typedef struct { \
	uint32_t uiReadPos; \
	uint32_t uiWritePos; \
	uint8_t ucBuf[QUEUE_SIZE]; \
} def_queue;

/**
 * <description> 
 * Ring buffer initialization
 * </description>
 */
#define RTS_RINGBUFFER_INIT(rbuf) (rbuf.uiReadPos = rbuf.uiWritePos = 0)

/**
 * <description> 
 * Get the length of written data in ring buffer, must be called before reading from buffer!
 * </description>
 */
#define RTS_RINGBUFFER_GET_FILL_SIZE(rbuf) ( (sizeof(rbuf.ucBuf) - rbuf.uiReadPos + rbuf.uiWritePos) % sizeof(rbuf.ucBuf) )

/**
 * <description> 
 * Get the length of available space in ring buffer, must be called before writing into buffer!
 * Always return one byte less than actual space size to avoid collision.
 * </description>
 */
#define RTS_RINGBUFFER_GET_FREE_SIZE(rbuf) ( (sizeof(rbuf.ucBuf) + rbuf.uiReadPos - rbuf.uiWritePos -1) % sizeof(rbuf.ucBuf) )

/**
 * <description> 
 * Read data from ring buffer. 
 * sizeToRead is the actual data length to be read from the buffer!
 * Comparison between filled data length in buffer and the length needs to be read must be done before calling this function!
 * Example:
 * sizeToRead = MIN(RTS_RINGBUFFER_GET_FILL_SIZE(rbuf), usSize);
 * RTS_RINGBUFFER_READ(dest, rbuf, sizeToRead);
 * </description>
 */
#define RTS_RINGBUFFER_READ(dest, rbuf, sizeToRead)\
	do{\
		uint32_t sizeSectionA, sizeSectionB;\
		sizeSectionA = MIN(sizeof(rbuf.ucBuf) - rbuf.uiReadPos, sizeToRead);\
		sizeSectionB = sizeToRead - sizeSectionA;\
		memcpy(dest, &rbuf.ucBuf[rbuf.uiReadPos], sizeSectionA);\
		memcpy(dest + sizeSectionA, &rbuf.ucBuf[0], sizeSectionB);\
		rbuf.uiReadPos = (rbuf.uiReadPos + sizeToRead) % sizeof(rbuf.ucBuf);\
	}while(0)

/**
 * <description>
 * Read single byte of data from ring buffer.
 * </description>
 */
#define RTS_RINGBUFFER_READB(c, rbuf)\
	do{\
		c = rbuf.ucBuf[rbuf.uiReadPos];\
		rbuf.uiReadPos = (rbuf.uiReadPos + 1) % sizeof(rbuf.ucBuf);\
	}while(0)

/**
 * <description> 
 * Write data into ring buffer.
 * sizeToWrite is the actual data length to be written into the buffer!
 * Comparison between free buffer length and the length needs to be written must be done before calling this function!
 * Example:
 * sizeToWrite = MIN(RTS_RINGBUFFER_GET_FREE_SIZE(rbuf), usSize);
 * RTS_RINGBUFFER_WRITE(src, rbuf, sizeToWrite);
 * </description>
 */
#define RTS_RINGBUFFER_WRITE(src, rbuf, sizeToWrite)\
	do{\
		uint32_t sizeSectionA, sizeSectionB;\
		sizeSectionA = MIN(sizeof(rbuf.ucBuf) - rbuf.uiWritePos, sizeToWrite);\
		sizeSectionB = sizeToWrite - sizeSectionA;\
		memcpy(&rbuf.ucBuf[rbuf.uiWritePos], src, sizeSectionA);\
		memcpy(&rbuf.ucBuf[0], src + sizeSectionA, sizeSectionB);\
		rbuf.uiWritePos = (rbuf.uiWritePos + sizeToWrite) % sizeof(rbuf.ucBuf);\
	}while(0)


/**
 * <description>
 * Write single byte of data into ring buffer.
 * </description>
 */
#define RTS_RINGBUFFER_WRITEB(c, rbuf)\
	do{\
		rbuf.ucBuf[rbuf.uiWritePos] = c;\
		rbuf.uiWritePos = (rbuf.uiWritePos + 1) % sizeof(rbuf.ucBuf);\
	}while(0)

#endif
