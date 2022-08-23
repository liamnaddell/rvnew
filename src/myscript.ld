ENTRY(_start)

SECTIONS {
    . = 0x80000000;
	.text : { *(.text) }
	PROVIDE(_kernel_end = .);
	. = _kernel_end + 0x1000;
	. = ALIGN(0x1000);
	PROVIDE(_stack_top = .);
	. = ALIGN(0x1000);
	.rodata : {
		*(.rodata .rodata.*)
	}
}
MEMORY {
	DRAM (a) : ORIGIN = 0x80000000, LENGTH = 0x1000
}
