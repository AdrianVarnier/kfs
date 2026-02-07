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