TARGET=riscv64-elf

all:
	$(TARGET)-gcc src/a.s -c -nostdlib -o src/a.o
	$(TARGET)-gcc -mcmodel=medany -ggdb -c -march='rv64gc' -nostdlib src/main.c -o src/main.o
	$(TARGET)-gcc -mcmodel=medany -ggdb -c -march='rv64gc' -nostdlib src/printf.c -o src/printf.o
	$(TARGET)-gcc -mcmodel=medany -ggdb -c -march='rv64gc' -nostdlib src/string.c -o src/string.o
	$(TARGET)-gcc -mcmodel=medany -ggdb -c -march='rv64gc' -nostdlib src/dtb.c -o src/dtb.o
	$(TARGET)-gcc -mcmodel=medany -ggdb -c -march='rv64gc' -nostdlib src/byte.c -o src/byte.o
	$(TARGET)-gcc -mcmodel=medany -ggdb -c -march='rv64gc' -nostdlib src/malloc.c -o src/malloc.o
	$(TARGET)-ld src/a.o src/main.o src/printf.o src/string.o src/dtb.o src/byte.o src/malloc.o -T src/myscript.ld -o kernel

objdump:
	$(TARGET)-objdump -D kernel

qemu: all
	qemu-system-riscv64 -m 32M -nographic -machine virt -bios kernel -s -S

qemu2: all
	clear
	qemu-system-riscv64 -m 32M -nographic -machine virt -bios kernel -smp 2

gdb: all
	$(TARGET)-gdb -x gdb.gdb kernel

clean:
	-rm src/*.o kernel
