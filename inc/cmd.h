/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:12:52 by avarnier          #+#    #+#             */
/*   Updated: 2026/02/09 18:12:52 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
#define CMD_H

#include "io.h"
#include "printk.h"
#include "gdt.h"

#define STACK_DUMP_SIZE 32

void    shutdown(void);
void    reboot(void);
void    dumpstack(void);
void    gdtaddr(void);

#endif