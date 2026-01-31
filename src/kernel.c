#include "terminal.h"
#include "keyboard.h"
#include "printk.h"

void kernel_main(void) {
    terminal_init();
    printk("%s", "42");
    while (1) {
        terminal_flush();
        keyboard_handler();
    }
}