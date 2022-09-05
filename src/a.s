.section .text
.globl _start
_start:
	la sp,_stack_top
	jal kmain
.globl m_mode_handler
.align 4
m_mode_handler:
	jal m_mode_c_handler

.section .rodata
.globl hiasm
	hiasm: .string "Booted to c"
