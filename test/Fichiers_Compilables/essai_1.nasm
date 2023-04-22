global _start
extern show_registers

section .bss

	c : resb 1

	i : resd 1


section .text



getchar : 

	sub rsp, 8
	mov rax, 0
	mov rdi, 0
	mov rsi, rsp
	mov rdx, 1
	syscall
	pop rax
	ret



putchar : 

	push rdi
	mov rax, 1
	mov rdi, 1
	mov rsi, rsp
	mov rdx, 1
	syscall
	pop rax
	ret



getint : 

	sub rsp, 8
	mov rax, 0
	mov rdi, 0
	mov rsi, rsp
	mov rdx, 4
	syscall
	pop rax
	ret



putint : 

	push rdi
	mov rax, 1
	mov rdi, 1
	mov rsi, rsp
	mov rdx, 4
	syscall
	pop rax
	ret


_start :
	mov rax, 60
	mov rdi, 5
	syscall
