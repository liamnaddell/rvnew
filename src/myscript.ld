ENTRY(_start)

SECTIONS {
	. = 0x80000000;
	.text : { *(.text) }
	PROVIDE(_text_end = .);

	. = _text_end + 0x1000;
	. = ALIGN(0x1000);
	PROVIDE(_stack1_top = .);

	. = ALIGN(0x1000);
	. = _stack1_top + 0x1000;
	PROVIDE(_stack2_top = .);
	. = ALIGN(0x1000);

	.rodata : {
		*(.rodata .rodata.*)
	}
	. = ALIGN(0x1000);
	PROVIDE(_fw_end = .);
}
MEMORY {
	DRAM (a) : ORIGIN = 0x80000000, LENGTH = 0x1000000
}
