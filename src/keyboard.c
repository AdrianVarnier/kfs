#include "keyboard.h"

static bool ctrl_pressed = false;
static bool shift_pressed = false;
static bool alt_pressed = false;

static char qwerty[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0,
    'a','s','d','f','g','h','j','k','l',';','\'','`',0,
    '\\','z','x','c','v','b','n','m',',','.','/',0,'*',0,' ',
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

static char qwerty_shift[128] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_','+','\b',
    '\t','Q','W','E','R','T','Y','U','I','O','P','{','}','\n',0,
    'A','S','D','F','G','H','J','K','L',':','"','~',0,
    '|','Z','X','C','V','B','N','M','<','>','?',0,'*',0,' ',
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

static char scancode_to_ascii(uint8_t scancode, const char* keymap) {
    if (scancode > 127) {
        return 0;
    }
    char c = keymap[scancode];
    return c;
}

void    keyboard_handler(void) {
    while (!(inb(KEYBOARD_STATUS_PORT) & 0x01)) {
    }
    
    uint8_t scancode = inb(KEYBOARD_DATA_PORT);
    char c = 0;
    if (shift_pressed) {
        c = scancode_to_ascii(scancode, qwerty_shift);
    } else {
        c = scancode_to_ascii(scancode, qwerty);
    }
    
    switch (scancode) {
        case SC_CTRL_LEFT_PRESS: ctrl_pressed = true; return;
        case SC_CTRL_LEFT_RELEASE: ctrl_pressed = false; return;

        case SC_SHIFT_LEFT_PRESS: shift_pressed = true; return;
        case SC_SHIFT_LEFT_RELEASE: shift_pressed = false; return;

        case SC_ALT_LEFT_PRESS: alt_pressed = true; return;
        case SC_ALT_LEFT_RELEASED: alt_pressed = false; return;

        case SC_UP_ARROW: terminal_scroll_up(); return;
        case SC_DOWN_ARROW: terminal_scroll_down(); return;
    }

    if (!c) { 
        return;
    }
    
    if (ctrl_pressed) {
        switch (c) {
            case '1': terminal_switch(0); return;
            case '2': terminal_switch(1); return;
            case '3': terminal_switch(2); return;
        }
        return;
    }
    if (alt_pressed)
    {
        switch (c) {
            case '1': terminal_switch_color('b'); return;
            case '2': terminal_switch_color('w'); return;
        }
        return;
    }
    terminal_putchar(c);
}