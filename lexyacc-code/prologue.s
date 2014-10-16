.section .bss
vars:
	.space	26 * 4

.section .data
ifmt:
	.string "%d\n"

.section .text
.global main
main:
