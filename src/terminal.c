/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:13:48 by avarnier          #+#    #+#             */
/*   Updated: 2026/02/09 18:13:48 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    for (int i = 0; i < VGA_WIDTH; i++) {
        line[i] = ' ';
    }
}

static void terminal_render(void) {
    terminal_t* t = current_terminal();

    for (int j = 0; j < VGA_HEIGHT; j++) {
        int logical_line = t->view_offset + j;
        char* line_ptr = NULL;
        if (logical_line < t->total_lines) {
            int offset = (t->total_lines > MAX_LINES) ? t->total_lines - MAX_LINES : 0;
            int buffer_index = (t->head + logical_line - offset) % MAX_LINES;
            line_ptr = t->buffer[buffer_index];
        }
        for (int i = 0; i < VGA_WIDTH; i++) {
            char c = ' ';
            if (line_ptr) {
                c = line_ptr[i];
            }
            vga_buffer[j * VGA_WIDTH + i] = vga_entry(c, t->color);
        }
    }
    if (t->cursor_visible) {
        cursor_enable();
        cursor_move(t->cursor_x, t->cursor_y);
    } else {
        cursor_disable();
    }
}

static void terminal_newline_handler(void) {
    terminal_t *t = current_terminal();

    t->cursor_x = 0;
    t->cursor_y++;

    int line_index;
    if (t->total_lines < MAX_LINES) {
        line_index = (t->head + t->total_lines) % MAX_LINES;
    } else {
        line_index = t->head;
        t->head = (t->head + 1) % MAX_LINES;
    }

    clear_line(t->buffer[line_index]);
    t->total_lines++;

    if (t->cursor_y >= VGA_HEIGHT) {
        t->cursor_y = VGA_HEIGHT - 1;
        if (t->total_lines > VGA_HEIGHT)
            t->view_offset = t->total_lines - VGA_HEIGHT;
        else
            t->view_offset = 0;
    }

    t->change = true;
}

static void terminal_backspace_handler(void) {
    terminal_t *t = current_terminal();

    int newest_line = (t->head + t->total_lines - 1) % MAX_LINES;
    t->buffer[newest_line][t->cursor_x - 1] = ' ';
    t->cursor_x--;
}

void terminal_init(void) {
    for (int i = 0; i < MAX_TERMINALS; i++) {
        terminal_t* t = &terminals[i];
        t->head = 0;
        t->total_lines = 1;
        t->view_offset = 0;
        t->cursor_x = 0;
        t->cursor_y = 0;
        t->change = true;
        t->cursor_visible = true;
        t->color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        for (int j = 0; j < VGA_HEIGHT; j++) {
            clear_line(t->buffer[j]);
        }
        active_terminal = i;
        shell_init(i);
    }
    active_terminal = 0;
}

void terminal_putchar(char c) {
    terminal_t *t = current_terminal();

    int max_view = (t->total_lines > VGA_HEIGHT) ? t->total_lines - VGA_HEIGHT : 0;
    if (t->view_offset < max_view) {
        t->view_offset = max_view;
    }

    if (c == '\n') {
        terminal_newline_handler();
    } else if (c == '\b') {
        terminal_backspace_handler();
    } else {
        int logical_line = t->view_offset + t->cursor_y;
        int offset = (t->total_lines > MAX_LINES) ? t->total_lines - MAX_LINES : 0;
        int buffer_index = (t->head + logical_line - offset) % MAX_LINES;

        t->buffer[buffer_index][t->cursor_x] = c;
        t->cursor_x++;

        if (t->cursor_x >= VGA_WIDTH)
            terminal_newline_handler();
    }
    t->change = true;
}

void terminal_scroll_up(void) {
    terminal_t* t = current_terminal();

    int min_view = (t->total_lines > MAX_LINES) ? t->total_lines - MAX_LINES : 0;

    if (t->view_offset > min_view) {
        t->view_offset--;
        t->cursor_visible = false;
        t->change = true;
    }
}

void terminal_scroll_down(void) {
    terminal_t* t = current_terminal();

    int max_view = (t->total_lines > VGA_HEIGHT) ? t->total_lines - VGA_HEIGHT : 0;
    if (t->view_offset < max_view) {
        t->view_offset++;
        if (t->view_offset == max_view) {
            t->cursor_visible = true;
        }
        t->change = true;
    }
}

void terminal_switch(int index) {
    if (index < 0 || index >= MAX_TERMINALS) {
        return;
    }

    active_terminal = index;
    terminal_t* t = current_terminal();
    shell_switch(index);

    if (t->total_lines > VGA_HEIGHT) {
        t->view_offset = t->total_lines - VGA_HEIGHT;
    } else {
        t->view_offset = 0;
    }

    t->change = true;
}

void terminal_setcolor(enum vga_color fg, enum vga_color bg) {
    terminal_t *t = current_terminal();
    t->color = vga_entry_color(fg, bg);
    t->change = true;
}

void    terminal_switch_color(int color_mode) {
    switch (color_mode) {
        case 'b': terminal_setcolor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK); return;
        case 'w': terminal_setcolor(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY); return;
    }
}

void terminal_flush(void) {
    terminal_t *t = current_terminal();
    if (!t->change) {
        return;
    }
    terminal_render();
    t->change = false;
}