	.org $8000

main:
	lda $60, X
	;; Making a infinite loop
	jmp main

