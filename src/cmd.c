/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:13:28 by avarnier          #+#    #+#             */
/*   Updated: 2026/02/09 18:13:28 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void    reboot(void) {
    outb(0x64, 0xFE);
    asm volatile("cli; hlt");
    while (1) {}
}

void    shutdown(void) {
    outw(0x604, 0x2000);
    asm volatile("cli; hlt");
    while (1) {}
}

void    dumpstack(void) {
    uint32_t *esp;
    asm volatile("mov %%esp, %0" : "=r"(esp));
    for (int i = 0; i < STACK_DUMP_SIZE; i++) {
        printk("%a: %a\n", (uint32_t)(esp + i), esp[i]);
    }
}

void    gdtaddr(void) {
    struct gdt_ptr val;
    asm volatile ("sgdt %0" : "=m" (val));
    printk("GDT address: %a\n", val.base);
}