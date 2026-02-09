/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gdt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:13:35 by avarnier          #+#    #+#             */
/*   Updated: 2026/02/09 18:13:35 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gdt.h"

extern void gdt_flush(void* gdt_ptr);

struct gdt_entry gdt_entries[GDT_SIZE] __attribute__((section(".gdt"))); 
struct gdt_ptr gdt_ptr;

void    gdt_init() {
    gdt_ptr.limit = (sizeof(struct gdt_entry) * GDT_SIZE) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    set_gdt_gate(0, 0, 0, 0, 0);
    set_gdt_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); //Kernel code
    set_gdt_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); //Kernel data
    set_gdt_gate(3, 0, 0x000FFFFF, 0x96, 0xC0); //Kernel stack
    set_gdt_gate(4, 0, 0xFFFFFFFF, 0xFA, 0xCF); //User code
    set_gdt_gate(5, 0, 0xFFFFFFFF, 0xF2, 0xCF); //User data
    set_gdt_gate(6, 0, 0x000FFFFF, 0xF6, 0xC0); //User stack

    gdt_flush(&gdt_ptr);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
}

void    set_gdt_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit = (limit & 0xFFFF);
    gdt_entries[num].flags = (limit >> 16) & 0x0F;
    gdt_entries[num].flags |= (gran & 0xF0);

    gdt_entries[num].access = access;
}
