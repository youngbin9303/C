;Assuming user will only enter ' ' 0-9 *+/-
;
;Young Bin Jo
;ECE 220 MP2
;659575499
;This MP works as a calculator. It requires at least 2 operands and 1 operator to perform the calculation. It uses postfix notation. Requires numbers first and operator after. It uses only 
;positive integers. This could bring negative value for minus operation but addition, multiplication and division will not consider negative integers. One issue that I countered was stack.
;If my input is 6 3 /, stack pops up in 3 6 order which brings 3/6 = 0. Therefore I stored 3 in R4 first and 6 in R3 later to perform 6/3. It worked same for exponent.
;I also added division by 0 or multiplication by 0 or power of 0. If it is division by 0, I coded to print invalid expression. If it is multiplication by 0, I coded to print 0.
;For exponent of 0, I coded to print 1.
;I assumed that result of calculation had to be stored in R5 in subroutine evaluation. However, R5 was required to use as a indicator to check whether stack is underflow or not. Therefore 
;I used blkw to store the value of R5 and loaded just before halt.
.ORIG x3000
	
;your code goes here
;This part gets a input from keyboard and check whether input is New line Carriage return or space. If input is non of those, it goes to evaluation subroutine.

NEXT_CHAR
	GETC		; Get input from keyboard and echo it
	OUT
	LD R1, ASCII_NL	; Check whether input is New line or not
	NOT R1, R1
	ADD R1, R1, #1
	ADD R2, R1, R0
	BRz GET_RESULT	; If it is new line go to GET_RESULT
	LD R1, ASCII_CR	; Check whether input is carriage return
	NOT R1, R1
	ADD R1, R1, #1
	ADD R2, R1, R0
	BRz GET_RESULT
	LD R1, ASCII_SPACE
	NOT R1, R1
	ADD R1, R1, #1
	ADD R2, R1, R0
	BRz NEXT_CHAR	; If input is space, ignore it and get new character
	JSR EVALUATE	; If input is non of those three, go to subroutine evaluate to check whether input is either operator or operand
	ADD R5, R5, #0	; After evaluation, we found that input is invalid, move to halt
	BRp DONE
	BR NEXT_CHAR	; Get new character

; This part pops the result of calculation when the input is new line
	
GET_RESULT
	JSR POP		; Pop the value in stack twice 
	JSR POP
	ADD R5, R5, #0	; 
	BRz ERROR	; After popping twice and stack is still not underflow print error message
	ADD R3, R0, #0	; Copy the value to R3 for PRINT_HEX
	JSR PRINT_HEX

	BR DONE
ERROR
	LEA R0, MESSAGE	; Print error msg
	PUTS
	BR DONE
DONE
	LD R5, Save_R5	; Load the result in R5
	HALT

ASCII_NL	.FILL	xA
ASCII_CR	.FILL	xD
ASCII_SPACE	.FILL	x20
MESSAGE		.STRINGZ "\Invalid Expression"
Save_R5		.BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
;This part is from lab1. Print the value stored in R3
PRINT_HEX

	;init registers 
	AND R1, R1, #0	; Initialize digit counter
	ST R7, SaveR7
	

	
NEXT_DIGIT
	ADD R0, R1, #-4 ; Check number of digits printed
	BRzp DONE_2
	
	AND R2, R2, #0	; Initialize digit
	AND R4, R4, #0	; Initialize bit counter


	
NEXT_BIT
	ADD R0, R4, #-4 ; Check number of bits 
	BRzp PRINT_DIGIT
	ADD R2, R2, R2	; shift digit left
	ADD R3, R3, #0	; check whether msb is 1 or 0
	BRzp #1				
	ADD R2, R2, #1	; if msb is 1 add 1 to digit
	ADD R3, R3, R3	; shift R3 left
	ADD R4, R4, #1	; increment bit counter
	BR NEXT_BIT


PRINT_DIGIT
	ADD R0, R2, #-9	; is digit number or alphabet
	BRnz	NUM
	LD R5, ASCII_A
	ADD R0, R2, R5
	ADD R0, R0, #-10
	OUT
	ADD R1, R1, #1
	BR NEXT_DIGIT

NUM
	LD R5, ASCII_0
	ADD R0, R2, R5
	OUT
	ADD R1, R1, #1
	BR NEXT_DIGIT
	
DONE_2	
	LD R7, SaveR7	
	RET	

ASCII_A		.FILL x41
ASCII_0		.FILL x30
SaveR7		.BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R5 - current numerical output
;

EVALUATE

;your code goes here
	ST R7, EV_R7
	LD R1, ASCII_ZERO	; Load ASCII_ZERO
	NOT R1, R1
	ADD R1, R1, #1
	ADD R2, R0, R1		
	BRn OPER	; If input is smaller than ASCII_ZERO it is operator + - / *
	LD R1, ASCII_NINE	; Load ASCII_NINE
	NOT R1, R1
	ADD R1, R1, #1
	ADD R2, R0, R1
	BRp POWER	; If input is bigger than ASCII_NINE it is exponent
	LD R1, ASCII_ZERO
	NOT R1, R1
	ADD R1, R1, #1
	ADD R0, R0, R1	; Push the ASCII_NUMBER - x30 
	JSR PUSH	; Otherwise number
	BR DONE_1


OPER
	LD R1, ASCII_DIV	; Check whether input is + or not
	NOT R1, R1
	ADD R1, R1, #1
	ADD R2, R0, R1
	BRz EV_DIV
	ADD R1, R1, #2	; Offset between ASCII_DIV and ASCII_MINUS is 2
	ADD R2, R0, R1
	BRz EV_MINUS
	ADD R1, R1, #2	; Offset between ASCII_MINUS and ASCII_PLUS is 2
	ADD R2, R0, R1
	BRz EV_PLUS
	ADD R1, R1, #1	; Offset between ASCII_PLUS and ASCII_MULT is 1
	ADD R2, R0, R1
	BRz EV_MULT
	
POWER
	LD R1, ASCII_POW	; Check whether input is ^ or nots
	NOT R1, R1
	ADD R1, R1, #1
	ADD R2, R0, R1
	BRz EV_POW	
	BR ERROR_1	; If it is non of those, print error msg
	
EV_PLUS
	JSR POP		; Pop the value
	ADD R4, R0, #0
	ADD R5, R5, #0
	BRp ERROR_1	; Check underflow
	JSR POP
	ADD R3, R0, #0
	ADD R5, R5, #0
	BRp ERROR_1
	JSR PLUS	; Run subroutine for addition
	ADD R5, R0, #0	; Copy the result in R5
	ST R5, Save_R5	; Save it
	JSR PUSH	; Store the result 
	BR DONE_1
EV_MINUS
	JSR POP
	ADD R4, R0, #0
	ADD R5, R5, #0
	BRp ERROR_1
	JSR POP
	ADD R3, R0, #0
	ADD R5, R5, #0
	BRp ERROR_1
	JSR MIN
	ADD R5, R0, #0	; Copy the result in R5
	ST R5, Save_R5	; Save it
	JSR PUSH
	BR DONE_1
EV_MULT
	JSR POP
	ADD R4, R0, #0
	ADD R5, R5, #0
	BRp ERROR_1
	JSR POP
	ADD R3, R0, #0
	ADD R5, R5, #0
	BRp ERROR_1
	JSR MUL
	ADD R5, R0, #0	; Copy the result in R5
	ST R5, Save_R5	; Save it
	JSR PUSH
	BR DONE_1
EV_DIV
	JSR POP
	ADD R4, R0, #0
	ADD R5, R5, #0
	BRp ERROR_1
	JSR POP
	ADD R3, R0, #0
	ADD R5, R5, #0
	BRp ERROR_1
	ADD R4, R4, #0	; If divisor is 0 it is invalid input
	BRz LP_5
	JSR DIV
	ADD R5, R0, #0	; Copy the result in R5
	ST R5, Save_R5	; Save it
	JSR PUSH
	BR DONE_1
LP_5

	BR ERROR_1
EV_POW
	JSR POP
	ADD R4, R0, #0
	ADD R5, R5, #0
	BRp ERROR_1
	JSR POP
	ADD R3, R0, #0
	ADD R5, R5, #0
	BRp ERROR_1
	JSR EXP
	ADD R5, R0, #0	; Copy the result in R5
	ST R5, Save_R5	; Save it
	JSR PUSH
	BR DONE_1

ERROR_1
	LEA R0, MESSAGE
	PUTS
	ADD R5, R5, #1	; Modify R5 value in order to prevent message getting printed twice
	BR DONE_1
DONE_1
	LD R0, ASCII_SPACE
	OUT
	LD R7, EV_R7
	RET
	
ASCII_ZERO	.FILL x30
ASCII_NINE	.FILL x39
ASCII_PLUS	.FILL x2B
ASCII_MINUS	.FILL x2D
ASCII_MULT	.FILL x2A
ASCII_DIV	.FILL x2F
ASCII_POW	.FILL x5E
EV_R7		.BLKW #1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
	ADD R0, R3, R4
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here

	NOT R4, R4
	ADD R4, R4, #1
	ADD R0, R3, R4

	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
	ADD R3, R3, #0
	BRz MULT_1
	ADD R4, R4, #0
	BRz MULT_1	; If one of input is zero go to MULT_1
	
	AND R0, R0, #0
MULT
	ADD R0, R0, R3
	ADD R4, R4, #-1
	BRp MULT
	BR MULT_2

MULT_1
	AND R0, R0, #0
MULT_2
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here

	AND R0, R0, #0	; Clear R0
	
	NOT R4, R4
	ADD R4, R4, #1	; Complement divisor
DIVI	
	ADD R3, R3, R4
	BRn LOOP_A
	ADD R0, R0, #1	; After loop, increment quotient by 1
	ADD R3, R3, #0
	BRp DIVI
LOOP_A


	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0	
EXP
;your code goes here

	
	AND R0, R0, #0
	ADD R4, R4, #0	; If x^0 solution is 1
	BRz LP_1
	ADD R4, R4, #-1	; Reduce one for additional loop
	ADD R6, R0, R3	; Copy R3 in R6

EXP_2
	ADD R5, R3, #0	; Copy R3 in R5
EXP_1

	ADD R0, R0, R6	; Add R3 value is R0
	ADD R5, R5, #-1	; Decrement counter
	BRp EXP_1
	ADD R6, R0, #0	; Copy R0 is R6
	AND R0, R0, #0	; Clear R0
	ADD R4, R4, #-1	; Decrement loop counter
	BRp EXP_2
	ADD R0, R6, #0	; Copy the result in R0
	BR	LP_2
LP_1
	ADD R0, R0, #1
LP_2
	RET
	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
