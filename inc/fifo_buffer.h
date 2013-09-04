/** @file fifo_buffer.h
 *
 *  @brief contains prototypes of keyboard queue manipulators and
 *		the buffer global variables	
 *
 *  @author Heather Arthur (harthur)
 */

#ifndef __FIFO_BUFFER_H
#define __FIFO_BUFFER_H

#define BUFF_SIZE 1024

/* character buffer */
extern int head;
extern int tail;
extern char buffer[BUFF_SIZE];


void enqueue_char(int scancode);
int dequeue_char();

#endif
