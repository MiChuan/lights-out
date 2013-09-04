/** @file timer_handler.c
 * 
 *  @brief The timer interrupt handler function
 *
 *  @author Heather Arthur 
 *  @bug None known
 **/

#include <410_reqs.h>
#include <interrupts.h>
#include <x86/pio.h>
#include <tickback_addr.h>
#include <kerndebug.h>

/** brief the current number of ticks since startup */
unsigned int ticks = 0;

/** @brief The timer handler
 *  
 *  If the global tickback function address is null, function is
 *  not called
 *
 *  @param Void
 *  @return Void
 */
void timer_handler()
{
  MAGIC_BREAK;
  ticks++;
  if(tickback_addr)
    tickback_addr(ticks);

  outb(INT_CTL_REG, INT_CTL_DONE);
}
