/** @file readchar.c 
 *  @brief The keyboard device driver
 *
 *  @author Heather Arthur (harthur)
 *  @bug None known
 */

#include <410_reqs.h>
#include <fifo_buffer.h>
#include <keyhelp.h>
#include <x86/proc_reg.h>


/** @brief function read a character from console
 *
 *  @return character code if character in queue, -1 otherwise 
 */
int
readchar(void)
{
  int scancode = dequeue_char();
  kh_type augchar = process_scancode(scancode);
  
  if(KH_HASDATA(augchar) && KH_ISMAKE(augchar))
    return KH_GETCHAR(augchar);
  return -1;
}
