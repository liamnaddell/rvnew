.section .text
.globl _start
_start:
	la sp,_stack_top
	jal kmain
.globl csrread
csrread:
	csrrs a0, misa, x0
	ret


.section .rodata
.globl hiasm
	hiasm: .string "Booted to c"
