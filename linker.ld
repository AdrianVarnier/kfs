ENTRY(_start)

SECTIONS
{
    .multiboot_header : 
    {
        KEEP(*(.multiboot))
    }

    .gdt 0x00000800 : 
    {
        KEEP(*(.gdt))
    }

    .text 0x00200000 : AT(0x00200000)
    {
        *(.text*)
    }

    .rodata :
    {
        *(.rodata*)
    }

    .data :
    {
        *(.data*)
    }

    .bss :
    {
        *(COMMON)
        *(.bss*)
    }
}