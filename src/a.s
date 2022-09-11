.section .text
.globl _start
_start:
	#code is broken, SMP totally wrecks my code
	csrr a0, mhartid
	beq a0, x0, core0
	core1:
		la sp,_stack2_top
		j jmain
	core0:
		la sp,_stack1_top
		j jmain
	jmain:
		jal kmain
.globl m_mode_handler
.align 4
m_mode_handler:
	jal m_mode_c_handler
.globl s_mode_handler
.align 4
s_mode_handler:
	jal s_mode_c_handler
/*.globl aquire_lock
aquire_lock:
	li t0,1

	try_aquire:
		amoswap.w.aq t0,t0,0(a0)
		bnez t0,try_aquire
	jr ra
	
.globl release_lock
release_lock:
	amoswap.w.rl x0,x0,0(a0)
	ret*/
	

#.section .rodata
#.globl hiasm
#	hiasm: .string "Booted to c"
