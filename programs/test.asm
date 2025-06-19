	.org $8000

main:
	lda #$42
	;; Making a infinite loop
	jmp main

