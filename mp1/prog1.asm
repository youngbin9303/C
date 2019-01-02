; Young Bin Jo
; UIN : 659575499
; This code counts the number of appearance for each alphabet (including non-alphabet in a single group)
; I used -27 to calculate the offset between x5B which is [. Maximum difference gives @ which is group of non-alphabet
; Minimum difference gives Z which is the last alphabet to be printed out
; To check whether it is number or alphabet for hex expression, I deducted 9 and if the value is positive it is alphabet.
; I mainly used the flow chart from lab1 to create the code
; I used NewLine x000A and space x0020 to keep the same format given in wiki page. 

;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming studio, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop

; R0 - OUT and temporary register
; R1 - address of histogram
; R2 - -27 loop counter to print alphabet
; R3 - Digit Counter
; R4 - Bit Counter
; R5 - Digit
; R6 - Value stored in histogram address

PRINT_HIST
	LD R1, HIST_ADDR
	
	LD R2, NUM_BINS
	AND R3, R3, #0		; initialize digit counter
	NOT R2, R2
	ADD R2, R2, #1		; make -27 to count the loop

;This part prints alphabet and space

PRINT_ALPHA
	BRz	DONE		; if -27 becomes 0 it represents 27 alphabets are printed. 
	LDR R6, R1, #0		; load MDR in x3F00 in R6
	LD R0,	ASCII_MAX	; load x5B to calculate the offset between -27 loop
	ADD R0, R0, R2		; Add x5B with R2 to check which alphabet to print
	OUT
	LD R0, ASCII_SPACE	; Print space between alphabet and hex number
	OUT
	
; This part is from flow chart of lab 1 

NEXT_DIGIT
	ADD R0, R3, #-4		; check whether 4 digits are printed or not
	BRzp NEWLINE	
	AND R4, R4, #0		; init bit counter
	AND R5, R5, #0		; init digit 
NEXT_BIT
	ADD R0, R4, #-4		; check whether bit counter is more than 4 or not
	BRzp PRINT_DIGIT

	ADD R5, R5, R5		; shift digit left
	ADD R6, R6, #0		; check whether MSB is 1 or not
	BRzp #1		
	ADD R5, R5, #1		; if value is negative add 1 to digit
	ADD R4, R4, #1		; increment bit counter
	ADD R6, R6, R6		; shift value left
	BR NEXT_BIT

PRINT_DIGIT
	ADD R0, R5, #-9		; check whether digit is number or alphabet
	BRnz NUM		
	LD R0, ASCII_A		; load ascii value 'A' if digit is alphabet
	ADD R0, R0, #-10	; 'A' - 10
	ADD R0, R0, R5		; ADD 'A' - 10 to digit
	OUT		
	ADD R3, R3, #1		; increment digit counter
	BR NEXT_DIGIT
NUM	
	LD R0, ASCII_ZERO	; load ascii value '0' if digit is number
	ADD R0, R0, R5		
	OUT
	ADD R3, R3, #1
	BR NEXT_DIGIT

; Move to next alphabet
NEWLINE
	LD R0, ASCII_NL		; print new line
	OUT
	AND R3, R3, #0		; clear digit counter
	ADD R1, R1, #1		; move to next address of histogram address
	ADD R2, R2, #1		; increment -27 loop for next alphabet

	BR PRINT_ALPHA

DONE	HALT			; done


; the data needed by the program
ASCII_A		.FILL x41
ASCII_ZERO	.FILL x30
ASCII_NL	.FILL x0A
ASCII_MAX	.FILL x5B
ASCII_SPACE	.FILL x20
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
