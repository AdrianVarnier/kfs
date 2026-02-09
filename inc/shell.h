/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:13:11 by avarnier          #+#    #+#             */
/*   Updated: 2026/02/09 18:13:11 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
#define SHELL_H

#include "terminal.h"
#include "printk.h"
#include "cmd.h"

#define SHELL_MAX_INPUT 1024

typedef struct shell {
    char    input[SHELL_MAX_INPUT];
    size_t  len;
} shell_t;

void    shell_init(size_t index);
void    shell_handle_char(char c);
void    shell_switch(int index);

#endif