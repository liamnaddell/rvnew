.section .text
.globl _start
_start:
	la sp,_stack_top
	jal kmain

.section .rodata
.globl hiasm
	hiasm: .string "Booted to c"
