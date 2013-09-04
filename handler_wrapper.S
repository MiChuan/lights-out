# contains the wrapper functions for interrupt handlers 
	
.globl timer_wrapper
.globl key_wrapper

# wrapper handles storing/saving of registers and calls timer handler 
timer_wrapper:
	pusha			# save general-purpose registers and ebp
       	call	timer_handler	# call the timer handler function
	popa			# restore general-purpose registers and ebp
	iret			# restore flags and return

# wrapper handles storing/saving of registers and calls timer handler 
key_wrapper:
	pusha			# save general-purpose registers and ebp
       	call	key_handler	# call the timer handler function
	popa			# restore general-purpose registers and ebp
	iret			# restore flags and return

