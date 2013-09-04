/** @file tick.c
 * 
 *  @author Heather Arthur (harthur)
 *  @bug None known
 **/

#include <410_reqs.h>
#include <paint_screen.h>
#include <time.h>
#include <stdio.h>

/**@brief Tick function, to be called by the timer interrupt handler
 * 
 * @param numTicks the number of ticks since last interrupt 
 *
 **/
void tick(unsigned int numTicks)
{
  total_time = numTicks;
  if(can_tick)
  {
    game_time++;
    if(game_time % 100 == 0)
      update_time(game_time);
  }
}
