
.section .text
gcd:
	pushl	%ebp
	movl	%esp, %ebp

	movl	8(%ebp), %ecx
	movl	12(%ebp), %eax
	
1:
	cmpl	%eax, %ecx
	je	1f
	cmpl	%ecx, %eax
	jle	2f
	subl	%ecx, %eax
	jmp	1b
2:
	subl	%eax, %ecx
	jmp	1b

1:
	leave
	ret

.section .bss
vars:
	.space	26 * 4

.section .data
ifmt:
	.string "%d\n"

.section .text
.global main
main:
