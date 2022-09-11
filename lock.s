	.file	"lock.c"
	.option nopic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	aquire
	.type	aquire, @function
aquire:
	addi	sp,sp,-48
	sd	s0,40(sp)
	addi	s0,sp,48
	sd	a0,-40(s0)
	li	a5,1
	sw	a5,-20(s0)
	j	.L2
.L3:
	ld	a5,-40(s0)
 #APP
# 5 "src/lock.c" 1
	amoswap.w.aq a5,a5,a5
# 0 "" 2
 #NO_APP
	sw	a5,-20(s0)
.L2:
	lw	a5,-20(s0)
	sext.w	a5,a5
	bne	a5,zero,.L3
	nop
	nop
	ld	s0,40(sp)
	addi	sp,sp,48
	jr	ra
	.size	aquire, .-aquire
	.align	1
	.globl	relase
	.type	relase, @function
relase:
	addi	sp,sp,-32
	sd	s0,24(sp)
	addi	s0,sp,32
	sd	a0,-24(s0)
	ld	a5,-24(s0)
 #APP
# 11 "src/lock.c" 1
	amoswap.w.rl x0,x0,0(a0)
# 0 "" 2
 #NO_APP
	nop
	ld	s0,24(sp)
	addi	sp,sp,32
	jr	ra
	.size	relase, .-relase
	.ident	"GCC: (Arch Linux Repositories) 12.1.0"
