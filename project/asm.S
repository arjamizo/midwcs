.section .data

.section .text

########################################
## int bin_to_dec(int *src, n);
########################################

.globl	bin_to_dec
	.type	bin_to_dec, @function
bin_to_dec:
	xor		%rax, %rax

bin_to_dec_loop:
	dec		%rsi
	shl		$1, %rax
	add		(%rdi, %rsi, 4), %eax

	and		%rsi, %rsi
	jnz		bin_to_dec_loop

	ret

########################################
## void mem_cpy(int *dst, int *src, int n);
########################################

.globl	mem_cpy
	.type	mem_cpy, @function
mem_cpy:
	dec		%rdx
	mov		(%rsi, %rdx, 4), %eax
	mov		%eax, (%rdi, %rdx, 4)
	and		%rdx, %rdx
	jnz		mem_cpy

	ret

########################################
## void mem_set(int *dst, int x, int n);
########################################

.globl	mem_set
	.type	mem_set, @function
mem_set:
	dec		%rdx
	mov		%esi, (%rdi, %rdx, 4)
	and		%rdx, %rdx
	jnz		mem_set

	ret

########################################
## int xor_elements(int *x, int *y, int n);
########################################

.globl	xor_elements
	.type	xor_elements, @function
xor_elements:
	xor		%rax, %rax
xor_elements_loop:
	dec		%rdx
	shl		$1, %rax
	add		(%rdi, %rdx, 4), %eax
	xor		(%rsi, %rdx, 4), %eax

	and		%rdx, %rdx
	jnz		xor_elements_loop

	ret

