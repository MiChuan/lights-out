/** @file key_handler.c
 * 
 *  @brief Contains the keyboard interrupt handler function
 *
 *  @author Heather Arthur (harthur)
 *  @bug None known
 **/

#include <keyhelp.h>
#include <x86/pio.h>
#include <interrupts.h>
#include <fifo_buffer.h>

/** @brief The keyboard press handler
 *  
 *  takes the character that caused the interrupt and enqueues it 
 *   in the keyboard buffer
 *
 *  @param Void
 *  @return Void
 */
void key_handler()
{
  /* queue scan code */
  int scancode = inb(KEYBOARD_PORT);
  enqueue_char(scancode);

  /* allow more key interrupts */
  outb(INT_CTL_REG, INT_CTL_DONE); 
}

