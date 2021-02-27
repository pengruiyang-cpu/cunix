OUTPUT_FORMAT("elf64-x86-64","elf64-x86-64", "elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(init)

SECTIONS {
	. = 0x0000 + 0x8200;
	.text : {
		_text = .;
		*(.text)
		_etext = .;
	}

	. = ALIGN(8);
	.data : {
		_data = .;
		*(.data);
		_edata = .;
	}

	.rodata : {
		_rodata = .;
		*(.rodata)
		.erodata = .;
	}

	.bss : {
		_bss = .;
		*(.bss)
		_ebss = .;
	}

	_end = .;
}
