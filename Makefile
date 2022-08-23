HOST=riscv64-none-elf
all: kernel

objdump:
	riscv64-elf-none-objdump -D src/a.out

qemu: all
	qemu-system-riscv64 -nographic -machine virt -bios src/a.out -s  -S

qemu2: all
	qemu-system-riscv64 -nographic -machine virt -bios src/a.out

gdb: all
	$(HOST)-gdb -x gdb.gdb src/a.out

kernel:
	cd src && make HOST=$(HOST)

clean:
	rm main.o a.out a.o


