 ; Lab 1 
 ; assignment: develop a code to print a value stored in a register 
 ;             as a hexadecimal number to the monitor
 ; algorithm: turnin each group of four bits into a digit
 ;            calculate the corresponding ASCII character;
 ;            print the character to the monitor




 ;R1 - Digit counter
 ;R2 - Digit
 ;R3 - Value to be printed out
 ;R4 - Bit Counter
 ;R5 - ASCII_A and ASCII_0
 .ORIG x3000

	AND R1, R1, #0	; Initialize digit counter
LP_1
	ADD R0, R1, #-4 ; Check number of digits printed
	BRzp DONE
	
	AND R2, R2, #0	; Initialize digit
	AND R4, R4, #0	; Initialize bit counter


	
LP_2
	ADD R0, R4, #-4 ; Check number of bits 
	BRzp LP_3
	ADD R2, R2, R2	; shift digit left
	ADD R3, R3, #0	; check whether msb is 1 or 0
	BRzp #1				
	ADD R2, R2, #1	; if msb is 1 add 1 to digit
	ADD R3, R3, R3	; shift R3 left
	ADD R4, R4, #1	; increment bit counter
	BR LP_2


LP_3
	ADD R0, R2, #-9	; is digit number or alphabet
	BRnz	NUM
	LD R5, ASCII_A
	ADD R0, R2, R5
	ADD R0, R0, #-10
	OUT
	ADD R1, R1, #1
	BR LP_1

NUM
	LD R5, ASCII_0
	ADD R0, R2, R5
	OUT
	ADD R1, R1, #1
	BR LP_1
 ; stop the computer
DONE
 HALT

 ; program data section starts here

ASCII_A	.FILL	x41	
ASCII_0	.FILL	x30
 .END

