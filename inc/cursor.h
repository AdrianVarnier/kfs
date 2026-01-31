#ifndef CURSOR_H
#define CURSOR_H

#include <stdint.h>
#include "io.h"
#include "vga.h"

void    cursor_move(int x, int y);
void    cursor_disable();
void    cursor_enable();

#endif