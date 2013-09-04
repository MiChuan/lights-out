/** @file paint_screen.h
 *
 *  @brief contains definitions of the screen painting functions
 *
 *  @author Heather Arthur (harthur)
 */

#ifndef __PAINT_SCREEN_H
#define __PAINT_SCREEN_H

/* The color combinations*/
#define TOOL_COLOR (FGND_BLACK | BGND_LGRAY)
#define DEFAULT_COLOR (FGND_WHITE | BGND_BLACK)
#define BOUND_COLOR (FGND_WHITE | BGND_BLUE)
#define TITLE_COLOR (FGND_YLLW | BGND_BLACK)
#define ON_COLOR (FGND_BLACK | BGND_LGRAY)
#define OFF_COLOR (FGND_WHITE | BGND_BLACK)

/* The top left corner of the grid - row value */
#define GRID_ROW 2
/* The top left corner of the grid - column value*/
#define GRID_COL (CONSOLE_WIDTH / 2)
/* The width and height of a square in the grid */
#define SQUARE_WIDTH 3
/* The row where the statistic start */
#define STATS_ROW (CONSOLE_HEIGHT / 2 - 3)
/* the column where the statistics start */
#define STATS_COL (CONSOLE_WIDTH / 8)


/* convert from (row, col) to character */
#define TOCHAR(row,col) (97 + row*5 + col)
#define TOROW(ch) ((ch - 97) / 5)
#define TOCOL(ch) ((ch - 97) % 5)

void title_screen();
void game_screen(int grid[5][5], int moves, int wins, int losses);
void win_screen();
void ins_screen();
void paint_toolbar(char *message);
void paint_grid(int grid[5][5]);
void paint_stats(int moves, int wins, int losses);
void paint_title();
void update_time(unsigned int time);
void paint_square(int row, int col, int on);
void paint_row(int row);
void paint_frame();
void init_screen();
#endif
