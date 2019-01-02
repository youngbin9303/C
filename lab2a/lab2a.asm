;modified POP to store value in R6.
;read comments
;
.ORIG x3000
	AND R6, R6, #0
	ST R0, MainR0
	ST R7, MainR7
	JSR IS_BALANCED
	LD R0, MainR0
	LD R7, MainR7


HALT

SPACE	.FILL x0020
NEW_LINE	.FILL x000A
CHAR_RETURN	.FILL x000D
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;if ( push onto stack if ) pop from stack and check if popped value is (
;input - R0 holds the input
;output - R5 set to -1 if unbalanced. else not modified.
IS_BALANCED
	ST R0, SaveR0
	ST R7, SaveR7
	
LOOP_1  
	GETC
	OUT

	LD R2, SPACE
	NOT R2, R2
	ADD R2, R2, #1
	ADD R2, R2, R0
	BRz LOOP_1	; Check whether input character is space
	LD R2, NEW_LINE
	NOT R2, R2
	ADD R2, R2, #1
	ADD R2, R2, R0
	BRz LOOP_2	; Check whether input character is New Line
	LD R2, CHAR_RETURN
	NOT R2, R2
	ADD R2, R2, #1
	ADD R2, R2, R0
	BRz LOOP_2	; Check whether input character is Char-return
	LD R2, NEG_OPEN
	ADD R2, R2, R0
	BRnp LOOP_4
	JSR PUSH	; If input is open bracket push to the stack
	BR LOOP_1

LOOP_4
	JSR POP		; If input is close bracket pop from the stack
	ADD R5, R5, #0	; Check whether it is underflow or not
	BRp LOOP_3
	BR LOOP_1

LOOP_2
	ST R0, Save_R0
	ST R7, Save_R7
	JSR POP
	LD R0, Save_R0
	LD R7, Save_R7	
	ADD R5, R5, #0		
	BRnz LOOP_3		; If stack is not empty go to DONE_1
	ADD R6, R6, #1		; If stack is empty add 1 in R6
	BR DONE

LOOP_3
	ADD R6, R6, #-1
	BR DONE
DONE
	LD R0, SaveR0
	LD R7, SaveR7
	RET

NEG_OPEN .FILL xFFD8
NEG_CLOSE .FILL xFFD7
KBSR .FILL xFE00
KBDR .FILL xFE02
DSR  .FILL xFE04
DDR  .FILL xFE06
MainR0	.BLKW #1
MainR7	.BLKW #1

Save_R0	.BLKW #1
Save_R7	.BLKW #1
SaveR0	.BLKW #1
SaveR7	.BLKW #1

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
        ST R3, POP_SaveR3       ;save R3
        ST R4, POP_SaveR4       ;save R3
        AND R5, R5, #0          ;clear R5
        LD R3, STACK_START      ;
        LD R4, STACK_TOP        ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz UNDERFLOW           ;
        ADD R4, R4, #1          ;
        LDR R0, R4, #0          ;
        ST R4, STACK_TOP        ;
        BRnzp DONE_POP          ;
UNDERFLOW
        ADD R5, R5, #1          ;
DONE_POP
        LD R3, POP_SaveR3       ;
        LD R4, POP_SaveR4       ;
        RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;

.END


