#include "printk.h"

static void printk_putd(int value) {
    char buffer[12];
    int i = 0;

    if (value == 0) {
        terminal_putchar('0');
        return;
    }

    if (value < 0) {
        terminal_putchar('-');
        value = -value;
    }

    while (value > 0) {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }

    while (i--)
        terminal_putchar(buffer[i]);
}

static void printk_puts(const char *s) {
    while (*s)
        terminal_putchar(*s++);
}

void printk(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    while (*fmt) {
        if (*fmt == '%' && *(fmt + 1)) {
            fmt++;

            switch (*fmt) {
                case 's': {
                    char *s = va_arg(args, char *);
                    printk_puts(s);
                    break;
                }
                case 'd': {
                    int d = va_arg(args, int);
                    printk_putd(d);
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    terminal_putchar(c);
                    break;
                }
                case '%': {
                    terminal_putchar('%');
                    break;
                }
            }
        }
        else {
            terminal_putchar(*fmt);
        }
        fmt++;
    }
    va_end(args);
}