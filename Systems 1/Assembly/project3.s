	section	.data
prompt:	db 'enter an integer : '
aholder:	resb 64

prompt2:	db 'enter another integer : '
bholder:	resb 64
__buffer	db	0x0
__nls:		db	0xa
	section	.text
	global	_start
_start:

	mov	rdx, 26 	;print prompt
	mov	rcx, prompt
	mov	rax, 4
	mov 	rbx, 1
	int 	0x80
	
	mov	edx, 20		;read input into aholder
	mov	rcx, aholder
	mov	rax, 3
	mov 	rbx, 0
	int 	0x80
	
	mov	rcx, 0		;digit number
	mov	rax, 0		;running total
	mov	rdx, 10
	mov	rbx, 0
addDigit:	

	add	rax, rbx
	mul	rdx
	inc	rcx
	mov	rsp, [aholder + rcx] ;value of current digit
	cmp	rsp, 0x0a
	jne	addDigit
	mov	rsp, rax
	
	mov	rdx, 33 	;print prompt2
	mov	rcx, prompt2
	mov	rax, 4
	mov 	rbx, 1
	int 	0x80
	
	
	mov	rdx, 20		;read input into bholder
	mov	rcx, bholder
	mov	rax, 3
	mov 	rbx, 0
	int 	0x80
		
	mov	rcx, 1		;digit number
	mov	rax, 0		;running total
	mov	rdx, 10
	mov	rbx, [bholder] ;value of current digit
	
addDigitB:
	
	add	rax, rbx
	mul	rdx
	mov	rbx, [bholder + rcx] ;value of current digit

	inc	rcx
	cmp	rbx, 0x0a
	jne	addDigitB
	mov	rbp, rax
	
	
GCD:
	cmp	rbp, 0
	je	returna
	cmp	rsp,rbp
	jl	returnba
	cmp	rbp, rsp
	jle	returnmod
	
returna:
	jmp	endGCD
returnba:
	mov	rcx, rsp
	mov	rsp, rbp
	mov	rbp, rcx
	jmp	GCD
returnmod:
	mov	rax, rsp
	mov	rdx, 0x0
	div	rbp
	mov	rcx, rdx
	mov	rsp, rbp
	mov	rbp, rdx
	jmp 	GCD
endGCD:
	;print
printRAX:
	mov	rax, rsp
	push	rax
	push	rbx
	push	rcx
	push	rdx
	
printPos:	
	mov	rcx, 0		; no digits seen yet
doDigit:	
	mov	rbx, 0xa	;0xa = 10
	mov	rdx, 0x0
	div	rbx		;div by 10 rem in rdx

	mov	rsi,rax	; backup number
	mov	al, dl		; dl is "lowest" byte of rdx
	push	rax		; save digit to print later
	
	mov	rax,rsi	; restore number

	inc	rcx     ;  add 1 to count of digits seen
	
	cmp	rax, 0
	jne	doDigit

nextDigit:	
	pop 	rax
	push	rax
	push	rbx
	push	rcx
	push	rdx

	add	al, '0'		; convert digit to ascii equivalent
	mov	[__buffer], al
	
	mov	rax, 4		; write a string
	mov	rbx, 1		; write to stdout
	mov	rcx, __buffer
	mov	rdx, 1
	int 	0x80

	pop	rdx
	pop	rcx
	pop	rbx
	pop	rax

	dec	rcx
	cmp	rcx, 0
	jne	nextDigit


	
	pop	rdx
	pop	rcx
	pop	rbx
	pop	rax
	
	push	rax
	push	rbx
	push	rcx
	push	rdx

	mov	rax, 4		; write a string
	mov	rbx, 1		; write to stdout
	mov	rcx, __nls 
	mov	rdx, 1
	int 	0x80

	pop	rdx
	pop	rcx
	pop	rbx
	pop	rax
	
	
	
	
	
	
	
	mov	rax, 1		;return control to linux
	mov	rbx, 0
	int	0x80
