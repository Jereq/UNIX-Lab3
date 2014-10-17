.section .text
.global gcd
gcd:
	movl	4(%esp), %ecx
	movl	8(%esp), %eax
	
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
	ret

.global fact
fact:
	movl	4(%esp), %ecx
	movl	$1, %eax
	cmpl	$0, %ecx
	jle	2f
1:
	imull	%ecx
	loop	1b
2:
	ret

.global lntwo
lntwo:
	bsrl	4(%esp), %eax
	ret
	