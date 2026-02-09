/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:13:30 by avarnier          #+#    #+#             */
/*   Updated: 2026/02/09 18:13:30 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cursor.h"

void    cursor_move(int x, int y) {
    uint16_t pos = y * VGA_WIDTH + x;

    outb(VGA_CTRL_PORT, 0x0E);
    outb(VGA_DATA_PORT, (uint8_t)((pos >> 8) & 0xFF));

    outb(VGA_CTRL_PORT, 0x0F);
    outb(VGA_DATA_PORT, (uint8_t)(pos & 0xFF));
}

void    cursor_disable() {
    outb(VGA_CTRL_PORT, 0x0A);
    outb(VGA_DATA_PORT, 0x20);
}

void    cursor_enable() {
    outb(VGA_CTRL_PORT, 0x0A);
    outb(VGA_DATA_PORT, 14);
    outb(VGA_CTRL_PORT, 0x0B);
    outb(VGA_DATA_PORT, 15);
}