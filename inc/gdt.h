/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gdt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:13:00 by avarnier          #+#    #+#             */
/*   Updated: 2026/02/09 18:13:00 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GDT_H
#define GDT_H

#include <stdint.h>

#define GDT_SIZE 7

struct gdt_entry {
    uint16_t    limit;
    uint16_t    base_low;
    uint8_t     base_middle;
    uint8_t     access;
    uint8_t     flags;
    uint8_t     base_high;
} __attribute__((packed));

struct gdt_ptr {
    uint16_t        limit;
    unsigned int    base;
} __attribute__((packed));

void    gdt_init();
void    set_gdt_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

#endif