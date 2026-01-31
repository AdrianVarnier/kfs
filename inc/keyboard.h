#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

#include "terminal.h"
#include "io.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define SC_CTRL_LEFT_PRESS  0x1D
#define SC_CTRL_LEFT_RELEASE 0x9D

#define SC_SHIFT_LEFT_PRESS  0x2A
#define SC_SHIFT_LEFT_RELEASE 0xAA

#define SC_ALT_LEFT_PRESS 0x38
#define SC_ALT_LEFT_RELEASED 0xB8

#define SC_UP_ARROW 0x48
#define SC_DOWN_ARROW 0x50

void    keyboard_handler(void);

#endif
