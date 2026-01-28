#include "terminal.h"
#include "keyboard.h"

void kernel_main(void) {
    terminal_init();
    terminal_write_str("42\n");

    while (1) {
        keyboard_handler();
    }
}
