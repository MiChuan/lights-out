/** @file console.c 
 *  @brief A console driver.
 *
 *  @author Heather Arthur (harthur)
 *  @bug None known
 */

#include <console.h>
#include <pack_address.h>

/* the current terminal color code */
int term_color = FGND_WHITE | BGND_BLACK;

int putbyte( char ch )
{
  /* get the current location of the cursor */
  int row,col;
  get_cursor(&row, &col);

  if(ch == '\n')
    nextline(row,col);
  else if(ch == '\r')
    set_cursor(row, 0);
  else if(ch == '\b')
    backspace(row, col);
  else if(ch == '\t')
    putbyte(' ');
  else
  {
    draw_char(row, col, ch, term_color);

    /* set the cursor to next space */
    if(col >= (CONSOLE_WIDTH - 1))
      nextline(row, col);
    else
      set_cursor(row, col + 1);
  }
  return 0;
}


void nextline(int row, int col)
{
  /* scroll if necessary */
  if(row == (CONSOLE_HEIGHT - 1))
  {
    int i, j, k;
    for(i = 0; i < CONSOLE_HEIGHT - 1; i++)
    	for(j = 0; j < CONSOLE_WIDTH ; j++)
		draw_char(i,j, get_char(i + 1, j), get_char_color(i + 1, j));

    for(k = 0; k < CONSOLE_WIDTH; k++)
      draw_char(CONSOLE_HEIGHT - 1, k, ' ', term_color);

    set_cursor(row, 0);
  }
 
  else
    set_cursor(row + 1, 0);
}

void backspace(int row, int col)
{
  /* can't backspace */
  if(col == 0 && row == 0)
    return;

  /* cursor at first character - backspace up a row */
  else if(col == 0)
  {
    set_cursor(row - 1, CONSOLE_WIDTH - 1);
    putbyte(' ');
    set_cursor(row - 1, CONSOLE_WIDTH - 1);
    return;
  }

  set_cursor(row, col - 1);
  putbyte(' ');
  set_cursor(row, col - 1);
}

void 
putbytes( const char *s, int len )
{
  if(!s || len <= 0)
    return;

  int i; 
  for(i = 0; i < len; i++)
    putbyte(*(s + i));
}

int
set_term_color( int color )
{
  if(!is_color(color))
    return -1;

  term_color = color;
  return 0;
}

void
get_term_color( int *color )
{
  if(!color)
    return;
  *color = term_color;
}

int set_real_cursor(int row, int col)
{
  int offset = row * CONSOLE_WIDTH + col;

  /* send lower order bits of offset */
  outb(CRTC_IDX_REG, CRTC_CURSOR_LSB_IDX);
  outb(CRTC_DATA_REG, LOWER8(offset));

  /* send higher order bits of offset */
  outb(CRTC_IDX_REG, CRTC_CURSOR_MSB_IDX);
  outb(CRTC_DATA_REG, UPPER8(offset));

  return 0;
}

int get_real_cursor(int *row, int *col)
{
  if(!row || !col)
    return -1;

  /* get lower order bits of offset */
  outb(CRTC_IDX_REG, CRTC_CURSOR_LSB_IDX);
  int low_off  = inb(CRTC_DATA_REG);
  
  /* get higher order bits of offset */
  outb(CRTC_IDX_REG, CRTC_CURSOR_MSB_IDX);
  int high_off = inb(CRTC_DATA_REG);
  
  int offset = low_off | (high_off << 8);
  *col = offset % CONSOLE_WIDTH;
  *row = offset / CONSOLE_WIDTH;

  return 0;
}

int
set_cursor( int row, int col )
{
  if(!is_point(row, col))
    return -1;

  int curr_row, curr_col;
  get_real_cursor(&curr_row, &curr_col);
 
  /* If the cursor is hidden , preserve this */
  if(curr_row >= CONSOLE_HEIGHT)
    return set_real_cursor(row + CONSOLE_HEIGHT, col);

  return set_real_cursor(row, col); 
}

void
get_cursor( int *row, int *col )
{
  if(!row || !col)
    return;

  get_real_cursor(row, col);

  /* normalize to get logical cursor */
  if(*row >= CONSOLE_HEIGHT)
    *row -= CONSOLE_HEIGHT;
}

void
hide_cursor()
{
  int row, col;
  get_real_cursor(&row, &col);

  /* if already hidden */
  if(row >= CONSOLE_HEIGHT)
    return;

  /* otherwise set to a screen-size beyond the offset */
  else
    set_real_cursor(row + CONSOLE_HEIGHT, col);
}

void
show_cursor()
{
  int row, col;
  get_real_cursor(&row, &col);
   
  /* if already shown */
  if(row < CONSOLE_HEIGHT)
    return;

  /* otherwise set to a screen-size less than offset */
  else
    set_real_cursor(row - CONSOLE_HEIGHT, col);
}

void 
clear_console()
{
  /* fill every row with spaces  */
  int i, j;
  for(i = 0; i < CONSOLE_HEIGHT; i++)
     for(j = 0; j < CONSOLE_WIDTH ; j++)
	draw_char(i,j, ' ', term_color);

  set_cursor(0,0);
}

void
draw_char( int row, int col, int ch, int color )
{
  if(!is_point(row,col) || !is_color(color))
    return;

  *(char *)(CONSOLE_MEM_BASE + row*(CONSOLE_WIDTH * 2) + col*2) = ch;
  *(char *)(CONSOLE_MEM_BASE + row*(CONSOLE_WIDTH * 2) + col*2 + 1) = color;  
}

char
get_char( int row, int col )
{
  return *(char *)(CONSOLE_MEM_BASE + row*(CONSOLE_WIDTH * 2) + col*2);
}

char
get_char_color(int row, int col)
{
  return *(char *)(CONSOLE_MEM_BASE + row*(CONSOLE_WIDTH * 2) + col*2 + 1);
}

int 
is_color(int color)
{
  if (color < 0x0 || color > 0x8F)
    return 0;
  return 1;
}

int
is_point(int row, int col)
{
  if(row < 0 || col < 0 || row >= CONSOLE_HEIGHT || col >= CONSOLE_WIDTH)
    return 0;
  return 1;
}
