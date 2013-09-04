/** @file handler_install.c
 * 
 *  @brief Handler installation function
 *  
 *  Declared in 410_reqs.h
 *
 *  @author Heather Arthur (harthur) 
 *  @bug None known
 **/

#include <410_reqs.h>
#include <timer_defines.h>
#include <keyhelp.h>
#include <handler_wrapper.h>
#include <interrupts.h>
#include <x86/seg.h>
#include <x86/pio.h>
#include <common.h>
#include <pack_address.h>

int handler_install(void (*tickback)(unsigned int numTicks))
{
  /* set timer mode */
  outb(TIMER_MODE_IO_PORT, TIMER_SQUARE_WAVE);

  /* set the timer period */
  outb(TIMER_PERIOD_IO_PORT, LOWER8(TIMER_RATE / 100));
  outb(TIMER_PERIOD_IO_PORT, UPPER8(TIMER_RATE / 100));
 
  /* install timer handler */
  long long *timer_idt = (long long *)sidt() + TIMER_IDT_ENTRY;
  *timer_idt = TRAP_PACK((unsigned int)timer_wrapper, (unsigned int)KERNEL_CS_SEGSEL, 0, 1, 1);

  /* install keyboard handler */
  long long *key_idt = (long long *)sidt() + KEY_IDT_ENTRY;
  *key_idt = TRAP_PACK((unsigned int)key_wrapper, (unsigned int)KERNEL_CS_SEGSEL, 0, 1, 1);

  return 0;
}
