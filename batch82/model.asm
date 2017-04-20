
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
	ri24 : 	resd	1
	ri25 : 	resd	1
	ri26 : 	resd	1
	ri27 : 	resd	1
	ri28 : 	resd	1
	ri29 : 	resd	1
	ri30 : 	resd	1
	ri31 : 	resd	1

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
	mov [ri8], dword 19

	;assignment expression
	mov eax, [ri8]
	mov [ri5], eax
	mov [ri13], dword 17

	;substracting two numbers
	mov eax, [ri13]
	mov ebx, [ri5]
	sub eax, ebx
	mov [ri14], eax

	mov [ri11], dword 4

	;multiplying two numbers
	mov eax, [ri6]
	mov ebx, [ri11]
	imul ebx
	mov [ri12], eax

	;adding two numbers
	mov eax, [ri12]
	mov ebx, [ri14]
	add eax, ebx
	mov [ri15], eax

	mov [ri9], dword 20

	;multiplying two numbers
	mov eax, [ri7]
	mov ebx, [ri9]
	imul ebx
	mov [ri10], eax

	;substracting two numbers
	mov eax, [ri10]
	mov ebx, [ri15]
	sub eax, ebx
	mov [ri16], eax

	;assignment expression
	mov eax, [ri16]
	mov [ri3], eax
	;assignment expression
	mov eax, []
	mov [ri4], eax
label2 :
	cmp [ri4], dword 1
	jne label3
	mov [ri20], dword 5

	;multiplying two numbers
	mov eax, [ri7]
	mov ebx, [ri6]
	imul ebx
	mov [ri19], eax

	;substracting two numbers
	mov eax, [ri19]
	mov ebx, [ri20]
	sub eax, ebx
	mov [ri21], eax

	mov [ri17], dword 2

	;multiplying two numbers
	mov eax, [ri5]
	mov ebx, [ri17]
	imul ebx
	mov [ri18], eax

	;substracting two numbers
	mov eax, [ri18]
	mov ebx, [ri21]
	sub eax, ebx
	mov [ri22], eax

	;adding two numbers
	mov eax, [ri3]
	mov ebx, [ri22]
	add eax, ebx
	mov [ri23], eax

	;assignment expression
	mov eax, [ri23]
	mov [ri2], eax
	mov [ri24], dword 100

	;assignment expression
	mov eax, [ri24]
	mov [ri1], eax
	;a block of statements
	jmp label1

label3 :
	cmp [ri4], dword 0
	jne label4
	mov [ri28], dword 20

	;multiplying two numbers
	mov eax, [ri7]
	mov ebx, [ri6]
	imul ebx
	mov [ri27], eax

	;substracting two numbers
	mov eax, [ri27]
	mov ebx, [ri28]
	sub eax, ebx
	mov [ri29], eax

	mov [ri25], dword 3

	;multiplying two numbers
	mov eax, [ri5]
	mov ebx, [ri25]
	imul ebx
	mov [ri26], eax

	;substracting two numbers
	mov eax, [ri26]
	mov ebx, [ri29]
	sub eax, ebx
	mov [ri30], eax

	;assignment expression
	mov eax, [ri30]
	mov [ri2], eax
	mov [ri31], dword 200

	;assignment expression
	mov eax, [ri31]
	mov [ri1], eax
	;a block of statements
	jmp label1

label4 :
label1 :
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
