/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:12:57 by avarnier          #+#    #+#             */
/*   Updated: 2026/02/09 18:12:57 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURSOR_H
#define CURSOR_H

#include <stdint.h>
#include "io.h"
#include "vga.h"

void    cursor_move(int x, int y);
void    cursor_disable();
void    cursor_enable();

#endif