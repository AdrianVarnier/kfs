/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printk.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:13:08 by avarnier          #+#    #+#             */
/*   Updated: 2026/02/09 18:13:08 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTK_H
#define PRINTK_H

#include <stdarg.h>
#include "terminal.h"

void    printk(const char *fmt, ...);

#endif