#include "terminal.h"
#include "io.h"

/* VGA constants */
#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000

/* VGA helpers */
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

static inline void move_cursor(size_t row, size_t column) {
    uint16_t pos = row * VGA_WIDTH + column;

    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
}

/* Terminal state */
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

void terminal_init(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void    terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

static void terminal_scroll(void) {
    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            terminal_buffer[(y - 1) * VGA_WIDTH + x] = terminal_buffer[y * VGA_WIDTH + x];
        }
    }

    size_t last_row = VGA_HEIGHT - 1;
    for (size_t x = 0; x < VGA_WIDTH; x++) {
        terminal_buffer[last_row * VGA_WIDTH + x] = vga_entry(' ', terminal_color);
    }

    terminal_row = VGA_HEIGHT - 1;
    terminal_column = 0;
}

void    terminal_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
            terminal_scroll();
    }
    else {
        terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] = vga_entry(c, terminal_color);
        if (++terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT)
                terminal_scroll();
        }
    }
    move_cursor(terminal_row, terminal_column);
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

void terminal_write_str(const char* data) {
    terminal_write(data, strlen(data));
}
