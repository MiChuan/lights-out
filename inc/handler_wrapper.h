/** @file handler_wrapper.h
 *  @brief contains definitions of the handler wrapper functions
 *
 *  @author Heather Arthur (harthur)
 */

#ifndef __HANDLER_WRAPPER_H
#define __HANDLER_WRAPPER_H

/** @brief Wrapper function for an exception handler
 *  
 *  Protects registers and calls the handler
 *
 *  @param Void
 *  @return Void
 */
void timer_wrapper( void );
void key_wrapper( void );

#endif 
