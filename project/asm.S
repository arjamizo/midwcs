.section .data

.section .text

########################################
## int abs_modulo(long int x, long int q);
########################################

.globl	abs_modulo
	.type	abs_modulo, @function
abs_modulo:
	xor		%rdx, %rdx
	mov		%rdi, %rax
	div		%rsi
	mov		%rdx, %rax

	and		%rax, %rax
	jns		abs_modulo_finish
	add		%rsi, %rax
abs_modulo_finish:
	ret

########################################
## int add_elements(int x, int y, int *zech, int n);
########################################

.globl	add_elements
	.type	add_elements, @function
add_elements:
	mov		%rdi, %rax

	and		%rdi, %rdi
	jz		add_elements_zero
	and		%rsi, %rsi
	jz		add_elements_zero

	jmp		add_elements_skip_zero
add_elements_zero:
	add		%rsi, %rax
	jmp		add_elements_finish
add_elements_skip_zero:

	sub		%rsi, %rax
	jnz		add_elements_skip_equal
	xor		%rax, %rax
	jmp 	add_elements_finish

add_elements_skip_equal:
	jns		add_elements_abs
	neg		%rax
	xchg	%rsi, %rdi
add_elements_abs:
	dec		%rax
	mov		(%rdx, %rax, 4), %eax
	add		%rsi, %rax
	dec		%rax
	xor		%rdx, %rdx
	dec		%rcx
	div		%rcx
	inc		%rdx
	mov		%rdx, %rax
add_elements_finish:

	ret

########################################
## int bin_to_dec(int *src, int n);
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
## int fill_zech_array(int *zech, int n, int m, int *index, int **elements, int *gen);
########################################

.globl	fill_zech_array
	.type	fill_zech_array, @function
fill_zech_array:
	mov		%rsi, %r11
	dec		%r11
	mov		%rdx, %r12
	mov		%rdi, %r13
	mov		$3, %r14
	xor		%r15, %r15

	xor		%rsi, %rsi
	mov		%r11, %rdx
	dec		%rdx
	call	mem_set

fill_zech_array_check:
	mov		4(%r9, %r15, 4), %eax
	inc		%r15
	and		%rax, %rax
	jz		fill_zech_array_check

	mov		%r13, %rdi
	mov		%r15, %rsi
	mov		%r12, %rdx
	call	get_zech
	mov		%eax, (%r13, %r15, 4)

	mov		%r15, %r10
fill_zech_array_main_loop:
	cmp		%r14, %r11
	jl		fill_zech_array_finish

	cmp		%r15, %r10
	jz		fill_zech_array_skip_search
fill_zech_array_next_search:
	mov		(%r13, %r10, 4), %eax
	and		%rax, %rax
	jz		fill_zech_array_skip_search
	inc		%r10
	jmp		fill_zech_array_next_search
fill_zech_array_skip_search:

	mov		%r13, %rdi
	mov		%r10, %rsi
	mov		%r12, %rdx
	call	get_zech
	mov		%rax, %r15

	mov		$1, %rax
	mov		$2, %rsi
fill_zech_array_loop_1:
	push	%rax
	mov		%r11, %rbx	#q
	sub		%r10, %rbx	#q-y
	dec		%rbx		#q-y-1
	xor		%rdx, %rdx
	imul	%rbx		#(q-y-1)*2^i
	idiv	%r11		#(q-y-1)*2^i%q
	and		%rdx, %rdx
	jns		fill_zech_array_no_sign_1
	add		%r11, %rdx	#abs_modulo((q-y-1)*2^i%q, q)
fill_zech_array_no_sign_1:

	pop		%rax
	dec		%rdx
	mov		(%r13, %rdx, 4), %ebx
	and		%rbx, %rbx
	jnz		fill_zech_array_loop_1_finish

	push	%rax
	mov		%rdx, %r9
	mov		%r15, %rbx	#zech
	sub		%r10, %rbx	#zech-y
	dec		%rbx		#zech-y-1

	xor		%rdx, %rdx
	imul	%rbx		#(zech-y-1)*2^i
	idiv	%r11		#(zech-y-1)*2^i%q
	and		%rdx, %rdx
	jns		fill_zech_array_no_sign_2
	add		%r11, %rdx	#abs_modulo((zech-y-1)*2^i%q, q)
fill_zech_array_no_sign_2:

	mov		%edx, (%r13, %r9, 4)
	inc		%r14

	pop		%rax
	mul		%rsi

	jmp		fill_zech_array_loop_1
fill_zech_array_loop_1_finish:

	mov		$2, %rax
	mov		$2, %rsi
fill_zech_array_loop_2:
	push	%rax
	mov		%r10, %rbx	#y
	inc		%rbx		#y+1
	xor		%rdx, %rdx
	imul	%rbx		#(y+1)*2^i
	idiv	%r11		#(y+1)*2^i%q
	and		%rdx, %rdx
	jns		fill_zech_array_no_sign_3
	add		%r11, %rdx	#abs_modulo((y+1)*2^i%q, q)
fill_zech_array_no_sign_3:

	pop		%rax
	dec		%rdx
	mov		(%r13, %rdx, 4), %ebx
	and		%rbx, %rbx
	jnz		fill_zech_array_loop_2_finish

	push	%rax
	mov		%rdx, %r9
	mov		%r15, %rbx	#zech
	xor		%rdx, %rdx
	imul	%rbx		#(zech)*2^i
	idiv	%r11		#(zech)*2^i%q
	and		%rdx, %rdx
	jns		fill_zech_array_no_sign_4
	add		%r11, %rdx	#abs_modulo((zech)*2^i%q, q)
fill_zech_array_no_sign_4:

	mov		%edx, (%r13, %r9, 4)
	inc		%r14

	pop		%rax
	mul		%rsi

	jmp		fill_zech_array_loop_2
fill_zech_array_loop_2_finish:

	xor		%r15, %r15
	inc		%r10
	jmp		fill_zech_array_main_loop
fill_zech_array_finish:

	mov		%r11, %rax
	inc		%rax
	sub		%r14, %rax
	not		%rax
	ret

########################################
## int generate(int *a0, int *gen, int **elements, int *index, int n, int m);
########################################

.globl	generate
	.type	generate, @function
generate:
	mov		%rdi, %r10
	mov		%rsi, %r11
	mov		%rdx, %r12
	mov		%rcx, %r13

	mov		%r13, %rdi
	xor		%rsi, %rsi
	mov		%r8, %rdx
	call	mem_set

	mov		(%r12), %rdi
	mov		%r9, %rdx
	call	mem_set

	mov		8(%r12), %rdi
	mov		%r10, %rsi
	mov		%r9, %rdx
	call	mem_cpy

	mov		%r10, %rdi
	mov		%r9, %rsi
	call	bin_to_dec
	movl	$1, (%r13, %rax, 4)

	mov		$2, %r14
generate_main_loop:
	cmp		%r14, %r8
	jle		generate_finish

	mov		(%r12, %r14, 8), %rdi
	mov		%r14, %rdx
	dec		%rdx
	mov		(%r12, %rdx, 8), %rsi
	mov		%rsi, %r15
	add		$4, %rsi
	mov		%r9, %rdx
	dec		%rdx
	call	mem_cpy

	xor		%rax, %rax
	mov		%r9, %rcx
generate_gen_loop:
	dec		%rcx

	mov		(%r11, %rcx, 4), %edx
	and		(%r15, %rcx, 4), %edx
	xor		%rdx, %rax

	and		%rcx, %rcx
	jnz		generate_gen_loop

	mov		(%r12, %r14, 8), %rdi
	mov		%r9, %rsi
	dec		%rsi
	mov		%eax, (%rdi, %rsi, 4)

	mov		%r9, %rsi
	call	bin_to_dec

	mov		(%r13, %rax, 4), %edx
	and		%rdx, %rdx
	jz		generate_skip_fail

	xor		%rax, %rax
generate_skip_fail:

	mov		%r14, %rdx
	mov		%edx, (%r13, %rax, 4)

	inc		%r14
	jmp		generate_main_loop
generate_finish:
	ret

########################################
## int get_zech(int *zech, int at, int m, int *index, int **elements);
########################################

.globl	get_zech
	.type	get_zech, @function
get_zech:
	mov		(%rdi, %rsi, 4), %eax
	and		%rax, %rax
	jnz		get_zech_finish

	mov		8(%r8), %rdi
	mov		16(%r8, %rsi, 8), %rsi

	call	xor_elements
	dec		%rax
get_zech_finish:

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
## int mul_elements(int x, int y, int n);
########################################

.globl	mul_elements
	.type	mul_elements, @function
mul_elements:
	mov		%rdi, %rax

	and		%rdi, %rdi
	jz		mul_elements_zero
	and		%rsi, %rsi
	jz		mul_elements_zero

	jmp		mul_elements_skip_zero
mul_elements_zero:
	xor		%rax, %rax
	jmp		mul_elements_finish
mul_elements_skip_zero:

	add		%rsi, %rax
	sub		$2, %rax
	dec		%rdx
	mov		%rdx, %rsi
	xor		%rdx, %rdx
	div		%rsi
	inc		%rdx
	mov		%rdx, %rax
mul_elements_finish:

	ret

########################################
## int powa(long int x, int y);
########################################

.globl	powa
	.type	powa, @function
powa:
	mov		$1, %rax
powa_loop:
	and		%rsi, %rsi
	jz		powa_finish
	dec		%rsi

	imul	%rdi
	jmp		powa_loop
powa_finish:
	ret

########################################
## int xor_elements(int *x, int *y, int m, int *index);
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
	mov		(%rcx, %rax, 4), %eax

	ret


