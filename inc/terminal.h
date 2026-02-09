/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:13:14 by avarnier          #+#    #+#             */
/*   Updated: 2026/02/09 18:13:14 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "vga.h"
#include "cursor.h"
#include "io.h"
#include "utils.h"
#include "shell.h"

#define MAX_TERMINALS   3
#define MAX_LINES       1024

typedef struct terminal {
    char    buffer[MAX_LINES][VGA_WIDTH];
    int     head;
    int     total_lines;
    int     view_offset;
    int     cursor_x;
    int     cursor_y;
    bool    change;
    bool    cursor_visible;
    uint8_t color;
} terminal_t;

void    terminal_init(void);
void    terminal_putchar(char c);
void    terminal_scroll_up(void);
void    terminal_scroll_down(void);
void    terminal_switch(int index);
void    terminal_setcolor(enum vga_color fg, enum vga_color bg);
void    terminal_switch_color(int color_mode);
void    terminal_flush(void);

#endif