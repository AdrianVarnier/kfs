/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:13:38 by avarnier          #+#    #+#             */
/*   Updated: 2026/02/09 18:13:38 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "keyboard.h"
#include "printk.h"
#include "gdt.h"
#include "shell.h"

void    check_gdt() {
    struct gdt_ptr val;
    asm volatile ("sgdt %0" : "=m" (val));
    printk("GDT base : 0x%x\n", val.base);
}

void kernel_main(void) {
    gdt_init();
    terminal_init();
    while (1) {
        terminal_flush();
        keyboard_handler();
    }
}