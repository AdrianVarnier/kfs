#include "keyboard.h"
#include "terminal.h"
#include "io.h"

static const char keymap[128] = {
    0,  0, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
    'a','s','d','f','g','h','j','k','l',';','\'','`', 0,'\\','z',
    'x','c','v','b','n','m',',','.','/', 0, 0, 0, ' ', 0, 0, 0
};

static char scancode_to_ascii(uint8_t scancode) {
    if (scancode > 127) {
        return 0;
    }

    return keymap[scancode];
}

void    keyboard_handler(void) {
    while (!(inb(KEYBOARD_STATUS_PORT) & 0x01)) {
    }
    uint8_t scancode = inb(KEYBOARD_DATA_PORT);
    char c = scancode_to_ascii(scancode);
    if (c) {
        terminal_putchar(c);
    }
}