/** @file fifo_buffer.c
 * 
 *  @brief Functions to manipulate the keyboard buffer
 *  
 *  @author Heather Arthur (harthur) 
 *  @bug If the buffer is full, characters will be lost 
 **/

#include <fifo_buffer.h>


int head = 0;
int tail = 0;

/** @brief the keyboard buffer */
char buffer[BUFF_SIZE];

/** @brief Queues a scancode in the keyboard buffer 
 *
 *  Adds a buffer item for this scancode to the end of the
 *    keyboard queue
 *
 *  @param scancode - the scancode to queue
 *  @return Void
 */
void enqueue_char(int scancode)
{
  buffer[head] = scancode;
  head++;
  if(head == BUFF_SIZE)
    head = 0;
}

/** @brief Dequeues the top scancode in the keyboard buffer 
 *
 *  Returns and removes the head of the keyboard buffer, (the oldest
 *    item in queue)
 *
 *  @param none
 *  @return the scancode of the head of the queue 
 */
int dequeue_char()
{
  if(head == tail)
    return -1;
  int next_code = buffer[tail];
  tail++;
  if(tail == BUFF_SIZE)
    tail = 0;
  return next_code;
}
