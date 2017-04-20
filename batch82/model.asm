
section .bss
	ri1 : 	resd	1
	ri2 : 	resd	1
	ri3 : 	resd	1
	ri4 : 	resd	1
	ri5 : 	resd	1
	ri6 : 	resd	1
	ri7 : 	resd	1
	ri8 : 	resd	1
	ri9 : 	resd	1
	ri10 : 	resd	1
	ri11 : 	resd	1
	ri12 : 	resd	1
	ri13 : 	resd	1
	ri14 : 	resd	1
	ri15 : 	resd	1
	ri16 : 	resd	1
	ri17 : 	resd	1
	ri18 : 	resd	1
	ri19 : 	resd	1
	ri20 : 	resd	1
	ri21 : 	resd	1
	ri22 : 	resd	1
	ri23 : 	resd	1

section .text
	global _start
_start : 
	; getting a value into a variable
	mov	edx, 4
	mov	eax, 3
	mov	ebx, 2
	mov	ecx, 1
	int	80h
	; getting a value into a variable
	mov	edx, 4
	mov	eax, 3
	mov	ebx, 2
	mov	ecx, 1
	int	80h
	mov [ri9], dword 19

	;assignment expression
	mov eax, [ri9]
	mov [ri6], eax
	mov eax, [ri4]
	cmp eax, 1
	jne label1
	mov eax, [ri5]
	cmp eax, 1
	jne label1
	mov [ri10], dword 1
	jmp label2
label2 :
	mov [ri10], dword 0
	;assignment expression
	mov eax, [ri10]
	mov [ri3], eax
	mov [ri15], dword 17

	;substracting two numbers
	mov eax, [ri15]
	mov ebx, [ri6]
	sub eax, ebx
	mov [ri16], eax

	mov [ri13], dword 4

	;multiplying two numbers
	mov eax, [ri7]
	mov ebx, [ri13]
	imul ebx
	mov [ri14], eax

	;adding two numbers
	mov eax, [ri14]
	mov ebx, [ri16]
	add eax, ebx
	mov [ri17], eax

	mov [ri11], dword 20

	;multiplying two numbers
	mov eax, [ri8]
	mov ebx, [ri11]
	imul ebx
	mov [ri12], eax

	;substracting two numbers
	mov eax, [ri12]
	mov ebx, [ri17]
	sub eax, ebx
	mov [ri18], eax

	;assignment expression
	mov eax, [ri18]
	mov [ri2], eax
	;multiplying two numbers
	mov eax, [ri8]
	mov ebx, [ri7]
	imul ebx
	mov [ri21], eax

	mov [ri19], dword 2

	;multiplying two numbers
	mov eax, [ri6]
	mov ebx, [ri19]
	imul ebx
	mov [ri20], eax

	;substracting two numbers
	mov eax, [ri20]
	mov ebx, [ri21]
	sub eax, ebx
	mov [ri22], eax

	;adding two numbers
	mov eax, [ri2]
	mov ebx, [ri22]
	add eax, ebx
	mov [ri23], eax

	;assignment expression
	mov eax, [ri23]
	mov [ri1], eax
	; printing a value
	mov	edx, 4
	mov	eax, 4
	mov	ebx, 1
	mov	ecx, 1
	int	80h
	; printing a value
	mov	edx, 4
	mov	eax, 4
	mov	ebx, 1
	mov	ecx, 1
	int	80h
	;a block of statements


;exit code
mov eax, 1
mov ebx, 0
int 80h
