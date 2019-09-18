#ifndef CAN_QUEUE_H_
#define CAN_QUEUE_H_

#include "stdint.h"
#include "stm32f10x_can.h"

#define LIB_CAN_BUFF_SIZE 128U
#define LIB_CAN_BUFF_MASK (LIB_CAN_BUFF_SIZE - 1)

struct lib_can_queue
{
    uint32_t head;
    uint32_t tail;
    CanTxMsg can_msg_buff[LIB_CAN_BUFF_SIZE];
};


extern struct lib_can_queue can1_tx_queue;
extern struct lib_can_queue can2_tx_queue;

extern void lib_can_queue_init(void);
extern void lib_can_queue_push(struct lib_can_queue *queue, CanTxMsg *msg);
extern int8_t lib_can_queue_pop(struct lib_can_queue *queue, CanTxMsg *msg);
extern uint32_t lib_can_queue_get_size(struct lib_can_queue *queue);
extern uint8_t check_can_mailbox(CAN_TypeDef* CANx);
extern void can_queue_main(void);

#endif

