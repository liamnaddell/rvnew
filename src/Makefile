all:	
	$(HOST)-as a.s -o a.o
	$(HOST)-gcc -mcmodel=medany -ggdb -c -march='rv64gc' main.c -nostdlib -o main.o
	$(HOST)-ld a.o main.o -T myscript.ld
	#riscv64-elf-none-objcopy -O binary a.out a.bin
