/** @file console.h
 *  @brief Function prototypes for the console driver.
 *
 *  This contains the prototypes and global variables for the console
 *  driver
 *
 *  @author Michael Berman (mberman)
 *  @bug No known bugs.
 */

#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <video_defines.h>
#include <x86/pio.h>

/** @brief Prints character ch at the current location
 *         of the cursor.
 *
 *  If the character is a newline ('\n'), the cursor is
 *  be moved to the beginning of the next line (scrolling if necessary).
 *  If the character is a carriage return ('\r'), the cursor
 *  is immediately reset to the beginning of the current
 *  line, causing any future output to overwrite any existing
 *  output on the line.  If backsapce ('\b') is encountered,
 *  the previous character is erased.  See the main console.c description
 *  for more backspace behavior.
 *
 *  @param ch the character to print
 *  @return The input character
 */
int putbyte( char ch );

/** @brief Sets the cursor to the beginning of the next line and scrolls
 *         if necessary
 *
 *  If the effective row (normalizing for hidden cursor behavior)
 *  is greater than or equal to the console height, the current display
 *  is shifted up one line, any data on the top line is lost. The cursor
 *  is set to the next effective row and column 0.
 *
 *  @param row, col position of the current cursor
 *  @return Void
 */
void nextline(int row, int col);

/** @brief Overwrites the character in front of the cursor with a space
 *
 *  If the logical cursor is at position (0,0) this does nothing,
 *  if the logical cursor is at the end of a row, the last character
 *  on the row above it is overwritten with a space. Otherwise the
 *  character one column less than the cursor on the same row is over
 *  written with a space. In all cases the logical cursor is then set
 *  to the overwritten space. 
 *
 *  @param row, col position of the current cursor
 *  @return Void
 */
void backspace(int row, int col);

/** @brief Prints the string s, starting at the current
 *         location of the cursor.
 *
 *  If the string is longer than the current line, the
 *  string fills up the current line and then
 *  continues on the next line. If the string exceeds
 *  available space on the entire console, the screen
 *  scrolls up one line, and then the string
 *  continues on the new line.  If '\n', '\r', and '\b' are
 *  encountered within the string, they are handled
 *  as per putbyte. If len is not a positive integer or s
 *  is null, the function has no effect.
 *
 *  @param s The string to be printed.
 *  @param len The length of the string s.
 *  @return Void.
 */
void putbytes(const char* s, int len);

/** @brief Changes the foreground and background color
 *         of future characters printed on the console.
 *
 *  If the color code is invalid, the function has no effect.
 *
 *  @param color The new color code.
 *  @return 0 on success or integer error code less than 0 if
 *          color code is invalid.
 */
int set_term_color(int color);

/** @brief Writes the current foreground and background
 *         color of characters printed on the console
 *         into the argument color.
 *  @param color The address to which the current color
 *         information will be written.
 *  @return Void.
 */
void get_term_color(int* color);

/** @brief Sets the value of the cursor to the offset
 *    obtained from the row and col arguments.
 *
 *  Takes the value of row and col, whatever they are, and
 *  sets the cursor to this.
 *
 *  @param row The new row for the cursor (or hidden value of row).
 *  @param col The new column for the cursor.
 *  @return 0 on success or integer error code less than 0 if
 *          cursor location is invalid.
 */
int set_real_cursor(int row, int col);

/** @brief Writes the current position (non-logical)
 *         of the cursor into the arguments row and col.
 *  @param row The address to which the current cursor
 *         row will be written.
 *  @param col The address to which the current cursor
 *         column will be written.
 *  @return Void.
 */
int get_real_cursor(int *row, int *col);

/** @brief Sets the position of the cursor to the
 *         position (row, col).
 *
 *  Subsequent calls to putbytes should cause the console
 *  output to begin at the new position. If the cursor is
 *  currently hidden, a call to set_cursor() does not show
 *  the cursor.
 *
 *  @param row The new row for the cursor.
 *  @param col The new column for the cursor.
 *  @return 0 on success or integer error code less than 0 if
 *          cursor location is invalid.
 */
int set_cursor(int row, int col);

/** @brief Writes the current position of the cursor
 *         into the arguments row and col.
 *  @param row The address to which the current cursor
 *         row will be written.
 *  @param col The address to which the current cursor
 *         column will be written.
 *  @return Void.
 */
void get_cursor(int* row, int* col);

/** @brief Hides the cursor.
 *
 *  Subsequent calls to putbytes do not cause the
 *  cursor to show again.
 *
 *  @return Void.
 */
void hide_cursor();

/** @brief Shows the cursor.
 *  
 *  If the cursor is already shown, the function has no effect.
 *
 *  @return Void.
 */
void show_cursor();

/** @brief Clears the entire console.
 *
 * The cursor is reset to the first row and column
 *
 *  @return Void.
 */
void clear_console();

/** @brief Prints character ch with the specified color
 *         at position (row, col).
 *
 *  If any argument is invalid, the function has no effect.
 *
 *  @param row The row in which to display the character.
 *  @param col The column in which to display the character.
 *  @param ch The character to display.
 *  @param color The color to use to display the character.
 *  @return Void.
 */
void draw_char(int row, int col, int ch, int color);

/** @brief Returns the character displayed at position (row, col).
 *  @param row Row of the character.
 *  @param col Column of the character.
 *  @return The character at (row, col).
 */
char get_char(int row, int col);

/** @brief Returns the color of the character displayed at position (row, col).
 *  @param row Row of the character.
 *  @param col Column of the character.
 *  @return The color of the character at (row, col).
 */
char get_char_color(int row, int col);

/** @brief Returns if the color is a valid color combination or not
 *  @param color - the color code to test
 *  @return 1 if is a color, 0 otherwise
 */
int is_color(int color);

/** @brief Returns wether the row, column combination is in the console
 *  @param row - the row of the point
 *  @param col - the column of the point
 *  @return 1 if it is in the console, 0 otherwise 
 */
int is_point(int row, int col);

#endif /* _CONSOLE_H */
