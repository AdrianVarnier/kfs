#include "terminal.h"

static uint16_t* vga_buffer = (uint16_t*)VGA_MEMORY;
static terminal_t terminals[MAX_TERMINALS];
static int active_terminal = 0;

static terminal_t *current_terminal(void) {
    return &terminals[active_terminal];
}

static inline int write_line(terminal_t *t) {
    return t->total_lines - VGA_HEIGHT + t->cursor_y;
}

static void clear_line(char *line) {
    for (int i = 0; i < VGA_WIDTH; i++)
        line[i] = ' ';
}

static void terminal_render(void) {
    terminal_t *t = current_terminal();

    for (int y = 0; y < VGA_HEIGHT; y++) {
        int line = t->view_offset + y;

        for (int x = 0; x < VGA_WIDTH; x++) {
            char c = ' ';
            if (line < t->total_lines)
                c = t->buffer[line][x];

            vga_buffer[y * VGA_WIDTH + x] =
                vga_entry(c, t->color);
        }
    }
    cursor_move(t->cursor_x, t->cursor_y);
}

static void terminal_newline_handler(void) {
    terminal_t *t = current_terminal();

    t->cursor_x = 0;
    t->cursor_y++;
    t->total_lines++;

    if (t->total_lines >= MAX_LINES)
        t->total_lines = MAX_LINES - 1;

    if (t->cursor_y >= VGA_HEIGHT) {
        t->view_offset++;
        t->cursor_y = VGA_HEIGHT - 1;
    }

    clear_line(t->buffer[t->total_lines - 1]);
}

void terminal_init(void) {
    for (int i = 0; i < MAX_TERMINALS; i++) {
        terminal_t *t = &terminals[i];

        t->total_lines = 1;
        t->view_offset = 0;
        t->cursor_x = 0;
        t->cursor_y = 0;
        t->color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

        for (int y = 0; y < MAX_LINES; y++)
            clear_line(t->buffer[y]);
        t->change = 1;
    }
}

void terminal_putchar(char c) {
    terminal_t *t = current_terminal();

    if (c == '\n') {
        terminal_newline_handler();
    }
    else {
        t->buffer[t->view_offset + t->cursor_y][t->cursor_x] = c;
        t->cursor_x++;
        if (t->cursor_x >= VGA_WIDTH)
            terminal_newline_handler();
    }
    t->change = 1;
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

void terminal_write_str(const char* data) {
    terminal_write(data, strlen(data));
}

void terminal_scroll_up(void) {
    terminal_t *t = current_terminal();
    if (t->view_offset > 0) {
        t->view_offset--;
        t->change = 1;
    }
}

void terminal_scroll_down(void) {
    terminal_t *t = current_terminal();
    if (t->view_offset + VGA_HEIGHT < t->total_lines) {
        t->view_offset++;
        t->change = 1;
    }
}

void terminal_switch(int index) {
    if (index < 0 || index >= MAX_TERMINALS)
        return;

    active_terminal = index;
    terminals[index].change = 1;
}

void    terminal_setcolor(enum vga_color fg, enum vga_color bg) {
    terminal_t *t = current_terminal();
    t->color = vga_entry_color(fg, bg);
}

void terminal_flush(void) {
    terminal_t *t = current_terminal();
    if (!t->change)
        return;
    terminal_render();
    t->change = 0;
}