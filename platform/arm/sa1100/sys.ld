SECTIONS 
{
	/*
	This needs to have a section offset of 0xf0000, since the high vector location is 0xffff0000.
	Also putting this in the linker script is kind of weird.
	*/
	
	_VECTORS_RELOCATE = 0x000f0000;
	
	. = 0x00010000;
	_TEXT_START = .;
	.text : 
	{ 
		*sys.o(.startup);
		KEEP(*(.startup));
		*(.text) 		
		
		*(.vectors)
	}

	.ctors :
	{
		KEEP (*(SORT(.ctors.*)))
		KEEP (*(.ctors))
	}
	
	_TEXT_END = .;

	. = 0xc1000000;

	_DATA_START = .;

	.rodata : ALIGN(4k)
	{ 
		*(.rodata) 
	}

	.data : ALIGN(4k)
	{ 
		*(.data) 
	}

	.benchmarks : ALIGN(4k)
	{
		. = ALIGN(8);
		_BENCHMARKS_START = .;
		KEEP(*(.benchmarks));
		_BENCHMARKS_END = .;
	}
	
	.bss : ALIGN(4k)
	{ 
		*(COMMON)
		*(.bss) 
	}

	_DATA_END = .;

}

ENTRY(reset_handler)
