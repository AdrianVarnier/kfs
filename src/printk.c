#include "printk.h"

static const char hex_lower[] = "0123456789abcdef";
static const char hex_upper[] = "0123456789ABCDEF";

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

    while (i--) {
        terminal_putchar(buffer[i]);
    }
}

static void printk_putx(uint32_t value, const char *digits) {
    char buf[9];
    int i = 0;

    if (value == 0) {
        terminal_putchar('0');
        return;
    }

    while (value > 0) {
        buf[i++] = digits[value & 0xF];
        value >>= 4;
    }

    while (i--)
        terminal_putchar(buf[i]);
}


static void printk_puts(const char *s) {
    while (*s) {
        terminal_putchar(*s++);
    }
}

void printk(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    while (*fmt) {
        if (*fmt == '%' && *(fmt + 1)) {
            fmt++;

            switch (*fmt) {
                case 's':
                    printk_puts(va_arg(args, char *));
                    break;

                case 'd':
                    printk_putd(va_arg(args, int));
                    break;

                case 'x':
                    printk_putx(va_arg(args, uint32_t), hex_lower);
                    break;

                case 'X':
                    printk_putx(va_arg(args, uint32_t), hex_upper);
                    break;
                case '%':
                    terminal_putchar('%');
                    break;
            }
        } else {
            terminal_putchar(*fmt);
        }
        fmt++;
    }
    va_end(args);
}