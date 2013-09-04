/** @file game_play.h
 *
 *  @brief contains prototypes of the game play functions
 *
 *  @author Heather Arthur (harthur)
 */

#ifndef __GAME_PLAY_H
#define __GAME_PLAY_H

void game_run();
void handle_win();
void handle_loss();
void handle_ins();
void handle_char(char ch);
void handle_new();
void new_game();
void generate_grid();
void initialize_grid();
void toggle_char(char ch);
void toggle_square(int row, int col);
int is_win();

#endif 
