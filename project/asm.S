.section .data

.section .text

##################################

.globl	bin_to_dec
	.type	bin_to_dec, @function
bin_to_dec:
	xor		%rax, %rax

bin_to_dec_loop:
	dec		%rsi
	shl		$1, %rax
	add		(%rdi, %rsi, 4), %rax

	and		%rsi, %rsi
	jnz		bin_to_dec_loop

	ret

####################################

