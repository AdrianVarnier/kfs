OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)

SECTIONS
{
    . = 2M;
    
    .multiboot_header ALIGN(4) :
    {
        KEEP(*(.multiboot))
    }

    .gdt 0x00000800 :
    {
        KEEP(*(.gdt))
    }

    .text ALIGN(4) :
    {
        *(.text*)
    }

    .rodata ALIGN(4) :
    {
        *(.rodata*)
    }

    .data ALIGN(4) :
    {
        *(.data*)
    }

    .bss ALIGN(4) :
    {
        *(COMMON)
        *(.bss*)
    }
}