/**@file time.h
 *
 * @brief contains the global variables representing time for game
 *
 * @author Heather Arthur (harthur)
 */

#ifndef __TIME_H
#define __TIME_H

/* time elapsed during this game in milliseconds */
unsigned int game_time;

/* time elapsed since start-up in milliseconds */
unsigned int total_time;

/* whether tick should increment time */
int can_tick;

#endif
