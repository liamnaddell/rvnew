.section .text
.globl _start
_start:
	la sp,_stack_top
	jal kmain
.globl m_mode_handler
.align 4
m_mode_handler:
	jal m_mode_c_handler
.globl s_mode_handler
.align 4
s_mode_handler:
	jal s_mode_c_handler
.globl aquire_lock
aquire_lock:
	addi sp,sp,-8
	sw ra,4(sp)
	sw fp,0(sp)
	move fp,sp

	li t1,1

	try_aquire:
		amoswap.w.aq t0,t1,0(a0)
		bnez t0,try_aquire

	move sp,fp
	sw fp,0(sp)
	sw ra,4(sp)
	addi sp,sp,8

	ret
	
.globl release_lock
release_lock:
	amoswap.w.rl x0,x0,0(a0)
	ret
	

#.section .rodata
#.globl hiasm
#	hiasm: .string "Booted to c"
