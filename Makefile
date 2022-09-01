TARGET := riscv64-elf
CFLAGS := -Wno-builtin-declaration-mismatch -Wno-discarded-qualifiers -mcmodel=medany -ggdb -march='rv64gc' -nostdlib

OBJDIR := src

CC := riscv64-elf-gcc

OBJS := $(addprefix $(OBJDIR)/, a.o string.o dtb.o byte.o malloc.o printf.o)

all: kernel

kernel:  $(OBJS) $(OBJDIR)/main.o
	"$(TARGET)-ld" $^ -T src/myscript.ld -o $@ 

testkernel:  $(OBJS) $(OBJDIR)/test.o
	"$(TARGET)-ld" $^ -T src/myscript.ld -o $@

$(OBJDIR)/%.o: %.c
	"$(TARGET)-gcc" $(CFLAGS) -c $< -o $@ 

$(OBJDIR)/a.o: src/a.s
	"$(TARGET)-gcc" $(CFLAGS) src/a.s -c -nostdlib -o src/a.o

objdump:
	"$(TARGET)-objdump" -D kernel

qemu: kernel
	qemu-system-riscv64 -m 32M -nographic -machine virt -bios kernel -s -S

qemu2: kernel
	qemu-system-riscv64 -m 32M -nographic -machine virt -bios kernel #-smp 2

test: testkernel
	qemu-system-riscv64 -m 32M -nographic -machine virt -bios $< -s -S

test2: testkernel
	qemu-system-riscv64 -m 32M -nographic -machine virt -bios $< #-smp 2

gdb: kernel
	$(TARGET)-gdb -x gdb.gdb kernel

clean:
	-rm src/*.o kernel
