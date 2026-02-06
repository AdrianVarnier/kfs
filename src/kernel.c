#include "terminal.h"
#include "keyboard.h"
#include "printk.h"
#include "gdt.h"

void    check_gdt() {
    struct gdt_ptr val;
    asm volatile ("sgdt %0" : "=m" (val));
    printk("GDT limit: 0x%x\n", val.limit);
    printk("GDT base : 0x%x\n", val.base);
}

void kernel_main(void) {
    gdt_init();
    terminal_init();
    printk("%s\n", "42");
    check_gdt();
    while (1) {
        terminal_flush();
        keyboard_handler();
    }
}