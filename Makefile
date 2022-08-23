TARGET=riscv64-none-elf

all:
	$(TARGET)-as src/a.s -o src/a.o
	$(TARGET)-gcc -mcmodel=medany -ggdb -c -march='rv64gc' -nostdlib src/main.c -o src/main.o
	$(TARGET)-gcc -mcmodel=medany -ggdb -c -march='rv64gc' -nostdlib src/printf.c -o src/printf.o
	$(TARGET)-gcc -mcmodel=medany -ggdb -c -march='rv64gc' -nostdlib src/string.c -o src/string.o
	$(TARGET)-gcc -mcmodel=medany -ggdb -c -march='rv64gc' -nostdlib src/dtb.c -o src/dtb.o
	$(TARGET)-ld src/a.o src/main.o src/printf.o src/string.o src/dtb.o -T src/myscript.ld -o kernel

objdump:
	$(TARGET)-objdump -D src/a.out

qemu: all
	qemu-system-riscv64 -m 32M -nographic -machine virt -bios kernel -s -S

qemu2: all
	qemu-system-riscv64 -m 32M -nographic -machine virt -bios kernel

gdb: all
	$(TARGET)-gdb -x gdb.gdb src/a.out

clean:
	-rm src/*.o kernel
