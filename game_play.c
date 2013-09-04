/** @file game_play.c
 * 
 *  @brief Functions and states to control game flow
 *  
 *  @author Heather Arthur (harthur) 
 *  @bug None known
 **/

#include <410_reqs.h>
#include <paint_screen.h>
#include <game_play.h>
#include <console.h>
#include <rand.h>
#include <time.h>

/** @brief an upper bound on the number of moves needed to win */
#define GAME_DEPTH 10

/* the state of the game */
int grid[5][5];
int moves;
int wins;
int losses;

/** @brief the main loop of the program
 *  
 *  If a key is pressed that is not associated with
 *  an option it will have no effect. 
 *
 *  @return Void
 */
void game_run()
{
  hide_cursor();
  handle_new();
  can_tick = 1;

  while(1)
  {
    int ch = readchar();
    if(ch > 0)
    {
      if(ch >= 'a' && ch <= 'y')
      {
	handle_char((char)ch);
	if(is_win())
	  handle_win();
      }
      else if(ch == 'N')
	handle_loss();
      else if(ch ==  'I')
	handle_ins();
      else if(ch == 'Q')
	handle_new();
    }

  }
}

/** @brief handles displaying/logging a win
 *  
 *  @return Void
 */
void handle_win()
{
  can_tick = 0;
  moves = 0;
  game_time = 0;
  wins++;
  win_screen();
  
  while(1) 
    if((int)readchar() > 0)
	break;
  new_game();
  can_tick = 1;
}

/** @brief handles displaying/logging a loss (new game)
 *  
 *  @return Void
 */
void handle_loss()
{
  can_tick = 0;
  losses++;
  game_time = 0;
  moves = 0;
  new_game();
  can_tick = 1;
}

/** @brief handles the press of an a-y character key
 *  
 *  @return Void
 */
void handle_char(char ch)
{
  toggle_char(ch);
  moves++;
  paint_stats(moves, wins, losses);
}

/** @brief the setup of a completely new game
 *  
 *  @param Void
 *  @return Void
 */
void handle_new()
{
  can_tick = 0;
  title_screen();

  while(1) 
    if((int)readchar() > 0)
	break;

  game_time = 0;
  moves = 0;
  wins = 0;
  losses = 0;
  new_game();
  can_tick = 1;
}

/** @brief handles displaying instruction screen
 *  
 *  @param Void
 *  @return Void
 */
void handle_ins()
{
  can_tick = 0;
  ins_screen();

  while(1) 
    if((int)readchar() > 0)
	break;

  game_screen(grid, moves, wins, losses);
  can_tick = 1;
}

/** @brief displays a new game screen
 *  
 *  @param Void
 *  @return Void 
 */
void new_game()
{
  generate_grid();
  game_screen(grid, moves, wins, losses);
}

/** @brief generates a winnable starting grid
 *  
 *  @param Void
 *  @return Void
 */
void generate_grid()
{
  initialize_grid();
  sgenrand(total_time);
  int i;

  /* just do series of toggles on random squares */
  for(i = 0; i < GAME_DEPTH; i++)
  {
    unsigned long square = (genrand() % 25) + 97;
    toggle_char(square);
  }
}

/** @brief turns all squares off in grid
 *  
 *  @param Void
 *  @return Void
 */
void initialize_grid()
{
  int i, j;
  for(i = 0; i < 5; i++)
    for(j = 0; j < 5; j++)
      grid[i][j] = 0;
}

/** @brief toggles the squares associated with this character
 *  
 *  Flips the color of the square associated with ch and the
 *  squares above, below, left, and right of it. If the char
 *  is on the edge of the grid, only the squares around it on
 *  the grid are toggled
 *
 *  @param ch the character associated with the square to toggle
 *  @return Void
 */
void toggle_char(char ch)
{
  int row = TOROW(ch);
  int col = TOCOL(ch);

  toggle_square(row, col);

  if(row)
    toggle_square(row - 1, col);
  if(row != 4)
    toggle_square(row + 1, col);
  if(col)
    toggle_square(row, col - 1);
  if(col != 4)
    toggle_square(row, col + 1);
}

/** @brief toggles a square
 *  
 *  Flips the color of the square at (row,col) in the grid
 *
 *  @param row the row in the grid of the square
 *  @param col the column in the grid of the square
 *  @return Void
 */
void toggle_square(int row, int col)
{
  grid[row][col] = !(grid[row][col]);
  paint_square(row, col, grid[row][col]);
}

/** @brief returns whether the grid is in a win state
 *  
 *  @param ch the character associated with the square to toggle
 *  @return non-zero if win
 */
int is_win()
{  
  int i, j;
  for(i = 0; i < 5; i++)
    for(j = 0; j < 5; j++)
      if(grid[i][j] == 1)
	return 0;
  return 1;
}
