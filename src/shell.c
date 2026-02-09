/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:13:46 by avarnier          #+#    #+#             */
/*   Updated: 2026/02/09 18:13:46 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static shell_t  shells[MAX_TERMINALS];
static int active_shell = 0;

static shell_t*    current_shell() {
    return &shells[active_shell];
}

static void shell_execute() {
    shell_t* sh = current_shell();
    
    if (sh->input[0] == '\0') {
        return;
    }

    if (!strcmp(sh->input, "help")) {
        printk("%s\n", "Available commands:");
        printk("%s\n", "  help: show available command");
        printk("%s\n", "  shutdown: poweroff the machine");
        printk("%s\n", "  reboot: restart the machine");
        printk("%s\n", "  dumpstack: print stack");
        printk("%s\n", "  gdtaddr: print GDT address");
        return ;
    }

    if (!strcmp(sh->input, "shutdown")) {
        printk("%s\n", "Shutting down...");
        shutdown();
        return ;
    }

    if (!strcmp(sh->input, "reboot")) {
        printk("%s\n", "Rebooting...");
        reboot();
        return ;
    }

    if (!strcmp(sh->input, "dumpstack")) {
        dumpstack();
        return ;
    }

    if (!strcmp(sh->input, "gdtaddr")) {
        gdtaddr();
        return ;
    }

    printk("%s %s\n", "Unknow command:", sh->input);
}

void    shell_init(size_t index) {
        shells[index].len = 0;
        printk("%s", "kfs> ");
}

void    shell_handle_char(char c) {
    shell_t* sh = current_shell();
    if (c == '\n') {
        terminal_putchar('\n');
        sh->input[sh->len] = '\0';
        shell_execute();
        sh->len = 0;
        printk("%s", "kfs> ");
    }
    else if (c == '\b') {
        if (sh->len > 0) {
            sh->input[sh->len - 1] = '\0';
            sh->len--;
            terminal_putchar('\b');
        }
        return ;
    }
    else {
        if (sh->len < SHELL_MAX_INPUT - 1) {
            terminal_putchar(c);
            sh->input[sh->len++] = c;
        }
    }
}

void    shell_switch(int index) {
    if (index < 0 || index >= MAX_TERMINALS) {
        return;
    }
    active_shell = index;
}