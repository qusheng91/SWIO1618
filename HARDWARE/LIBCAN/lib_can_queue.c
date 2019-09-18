#include "lib_can_queue.h"
#include <stdio.h>

struct lib_can_queue can1_tx_queue;
struct lib_can_queue can2_tx_queue;

void lib_can_queue_init(void)
{
    can1_tx_queue.head = 0;
    can1_tx_queue.tail = 0;
    can2_tx_queue.head = 0;
    can2_tx_queue.tail = 0;
}


void lib_can_queue_push(struct lib_can_queue *queue, CanTxMsg *msg)
{
    if (lib_can_queue_get_size(queue) < LIB_CAN_BUFF_SIZE)
    {
        queue->can_msg_buff[queue->head] = *msg;
        queue->head = (queue->head + 1) & LIB_CAN_BUFF_MASK;
    }
    else
    {
        //printf("can queue is full\r\n");
    }
}


int8_t lib_can_queue_pop(struct lib_can_queue *queue, CanTxMsg *msg)
{
    int8_t res = 0;
    
    if (lib_can_queue_get_size(queue) > 0)
    {
        *msg = queue->can_msg_buff[queue->tail];
        queue->tail = (queue->tail + 1) & LIB_CAN_BUFF_MASK;
        res = 0;
    }
    else
    {
        res = -1;
        // printf(error);
    }
    return res;
}

uint32_t lib_can_queue_get_size(struct lib_can_queue *queue)
{
    return (queue->head + LIB_CAN_BUFF_SIZE - queue->tail) & LIB_CAN_BUFF_MASK;
}

uint8_t check_can_mailbox(CAN_TypeDef* CANx)
{
    uint8_t ret = 0;
    
  /* Select one empty transmit mailbox */
  if ((CANx->TSR&CAN_TSR_TME0) == CAN_TSR_TME0)
  {
    ret = 1;
  }
  else if ((CANx->TSR&CAN_TSR_TME1) == CAN_TSR_TME1)
  {
    ret = 1;
  }
  else if ((CANx->TSR&CAN_TSR_TME2) == CAN_TSR_TME2)
  {
    ret = 1;
  }
  else
  {
    ret = 0;
  }
  return ret;
}

void can_queue_main(void)
{
    CanTxMsg can_msg;

    if (check_can_mailbox(CAN1) != 0)
    {
        if (lib_can_queue_pop(&can1_tx_queue, &can_msg) == 0)
        {
            CAN_Transmit(CAN1, &can_msg);  
        }
    }
    
    if (check_can_mailbox(CAN2) != 0)
    {
        if (lib_can_queue_pop(&can2_tx_queue, &can_msg) == 0)
        {
            CAN_Transmit(CAN2, &can_msg);  
        }
    }
}
