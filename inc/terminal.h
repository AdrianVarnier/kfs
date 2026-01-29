#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include <stddef.h>
#include "vga.h"
#include "cursor.h"
#include "io.h"
#include "utils.h"

#define MAX_TERMINALS   3
#define MAX_LINES       256

typedef struct terminal {
    char buffer[MAX_LINES][VGA_WIDTH];
    int total_lines;
    int view_offset;
    int cursor_x;
    int cursor_y;
    int change;
    uint8_t color;
} terminal_t;

void terminal_init(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_write_str(const char* data);
void terminal_scroll_up(void);
void terminal_scroll_down(void);
void terminal_switch(int index);
void terminal_setcolor(enum vga_color fg, enum vga_color bg);
void terminal_flush(void);

#endif