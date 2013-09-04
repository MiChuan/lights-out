/** @file paint_screen.c
 * 
 *  @brief Functions to display game screen
 *  
 *  @author Heather Arthur (harthur) 
 *  @bug None known
 **/

#include <stdio.h>
#include <console.h>
#include <video_defines.h>
#include <paint_screen.h>

/** @brief paints the title screen  
 *
 *  Writes the name and author of the game to the screen
 *
 *  @param Void
 *  @return Void
 */
void title_screen()
{
  init_screen();
  set_term_color(TITLE_COLOR);
  set_cursor(CONSOLE_HEIGHT/2, CONSOLE_WIDTH/2  - 5);
  printf("LIGHTS OUT!");
  set_cursor(CONSOLE_HEIGHT/2 + 1, CONSOLE_WIDTH/2 - 8);
  printf("by Heather Arthur");
  
  paint_toolbar("Press any key to continue");
}

/** @brief paints the current game screen  
 *
 *  Paints the game screen (grid, toolbar, and statistics)
 *
 *  @param Void
 *  @return Void
 */
void game_screen(int grid[5][5], int moves, int wins, int losses)
{
  init_screen();
  paint_toolbar("Press <a-y> to toggle square <I> Instructions <N> New game <Q> Quit");
  paint_grid(grid);
  paint_stats(moves, wins, losses);
  paint_title();
}

/** @brief paints the win screen  
 *
 *  Writes a win message to the screen
 *
 *  @param Void
 *  @return Void
 */
void win_screen()
{
  init_screen();
  set_cursor(CONSOLE_HEIGHT/2, CONSOLE_WIDTH/2 - 8);
  printf("CONGRATULATIONS!");
  set_cursor(CONSOLE_HEIGHT/2 + 1, CONSOLE_WIDTH/2 - 3);
  printf("You won");
  
  paint_toolbar("Press any key to start a new game");
}

/** @brief paints the instruction screen  
 *
 *  Writes the game instructions to the screen
 *
 *  @param Void
 *  @return Void
 */
void ins_screen()
{
  init_screen();
  printf("Use the following keys at any point in the game:\n\n");
  printf("<a-y> to toggle the light at this grid location\n");
  printf("<N> to end the current game (and lose) and begin a new one\n");
  printf("<I> to access these instructions\n");
  printf("<Q> to quit the game\n\n");
  printf("The goal of this game is to turn out all the lights on the grid.\n");
  printf("Pressing a character a-y will flip the light at that respective \n");
  printf("grid location and also flip the lights at the locations above,\n");
  printf("below, and to the left and right of this character location.\n");

  paint_toolbar("Press any key to resume game");
}

/** @brief paints the toolbar of the game screen  
 *
 *  Writes the toolbar to the bottom row of the screen
 *
 *  @param message the message to print on the toolbar
 *  @return Void
 */
void paint_toolbar(char *message)
{
  set_term_color(TOOL_COLOR);
  paint_row(CONSOLE_HEIGHT -1);
  printf("%s",message);
}

/** @brief paints the current grid of the game screen  
 *
 *  Writes the game grid to the screen based on the values in 
 *  the grid
 *
 *  @param Void
 *  @return Void
 */
void paint_grid(int grid[5][5])
{
  paint_frame();

  int i,j;
  for(i = 0; i < 5; i++)
    for(j = 0; j < 5; j++)
      paint_square(i,j,grid[i][j]);
}

/** @brief paints the current statistics for the game  
 *
 *  Writes the game statistics to the left of the screen.
 *  Will write over old statistics if they are there.
 *
 *  @param moves the number of moves in this game
 *  @param wins the number of wins so far
 *  @param losses the number of losses so far
 *  @return Void
 */
void paint_stats(int moves, int wins, int losses)
{
  set_term_color(DEFAULT_COLOR);
  set_cursor(STATS_ROW, 0);
  printf("moves made:\n%d\n", moves);
  printf("time elapsed:\n\n" );
  printf("wins:\n%d\n", wins);
  printf("losses:\n%d\n", losses);
  printf("record:\n%d/%d\n",wins, losses + wins);
}

/** @brief paints the title on game screen  
 *
 *  @return Void
 */
void paint_title()
{
  set_cursor(CONSOLE_HEIGHT/4, CONSOLE_WIDTH/4);
  set_term_color(TITLE_COLOR);
  printf("LIGHTS OUT!");
}

/** @brief paints new time to the screen
 *
 *  Writes new time value (in seconds) over the old one on the screen
 *
 *  @param time the time elapsed since last call to update
 *  @return Void
 */
void update_time(unsigned int time)
{
  unsigned int seconds = time / 100;
  set_term_color(DEFAULT_COLOR);
  set_cursor(STATS_ROW + 3, 0);
  printf("%u   ", seconds);
}

/** @brief paints a square to the grid of the game screen  
 *
 *  Writes the square to the (row, col) of the grid
 *
 *  @param row the row of the square to paint
 *  @param col the col of the squeare to paint
 *  @param on  boolean on/off value
 *  @return Void
 */
void paint_square(int row, int col, int on)
{
  int i,j;
  int color;
  if(on)
    color = ON_COLOR;
  else
    color = OFF_COLOR;

  /* color in the square*/
  int start_row = GRID_ROW + 1 + row*(SQUARE_WIDTH + 1);
  int start_col = GRID_COL + 1 + col*(SQUARE_WIDTH + 1);
  for(i = 0; i < SQUARE_WIDTH; i++)
    for(j = 0; j < SQUARE_WIDTH; j++)
      draw_char(start_row + i, start_col + j, ' ', color);

  /* add the character */
  int char_row = start_row + SQUARE_WIDTH / 2;
  int char_col = start_col + SQUARE_WIDTH / 2;
  draw_char(char_row, char_col, TOCHAR(row, col), color);
}

/** @brief paints a row in the current background color
 *
 *   No action if row is not on the console
 *
 *  @param row the row to paint
 *  @return Void
 */
void paint_row(int row)
{
  if(row < 0 || row > CONSOLE_HEIGHT)
    return;
  set_cursor(row, 0);
  int i;
  for(i = 0; i < (CONSOLE_WIDTH - 1); i++)
    putbyte(' ');

  /* paint last character of this row to avoid scrolling */
  draw_char(row, CONSOLE_WIDTH - 1, ' ', TOOL_COLOR);
  putbyte('\r');  
}

/** @brief paints the frame of the grid
 *
 *  @param Void
 *  @return Void
 */
void paint_frame()
{
  /* columns */
  int i, j;
  for(i = 0; i < 6; i++)
    for(j = GRID_ROW; j < (GRID_ROW + SQUARE_WIDTH*5 + 6); j++)
      draw_char(j ,GRID_COL + i*4,' ',BOUND_COLOR);

  /* rows */
  int p, q;
  for(p = 0; p <= 6; p++)
    for(q = GRID_COL; q < (GRID_COL + SQUARE_WIDTH*5 + 6); q++)
      draw_char(GRID_ROW + p*4, q, ' ', BOUND_COLOR);
}

/** @brief sets console up for a new screen
 *
 *  Clears the console and changes colors to default
 *
 *  @param Void
 *  @return Void
 */
void init_screen()
{
  set_term_color(DEFAULT_COLOR);
  clear_console();
}




