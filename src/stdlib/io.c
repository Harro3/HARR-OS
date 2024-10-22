#include "io.h"

#include "drivers/tty.h"

int handle_base(unsigned int val, int base)
{
    if (val == 0)
    {
        tty_putc('0');
        return 1;
    }

    unsigned int pow = 1;
    unsigned int tmp = val;
    while (tmp / base)
    {
        tmp /= base;
        pow *= base;
    }

    int res = 0;
    while (pow)
    {
        int digit = val / pow;
        val -= digit * pow;
        pow /= base;

        if (digit < 10)
        {
            tty_putc('0' + digit);
        }
        else
        {
            tty_putc('a' + digit - 10);
        }

        res++;
    }

    return res;
}

int handle_decimal(int val)
{
    int res = 0;
    if (val < 0)
    {
        val = -val;
        res++;
        tty_putc('-');
    }
    res += handle_base(val, 10);
    return res;
}

int handle_unsigned(unsigned int val)
{
    return handle_base(val, 10);
}

int handle_string(char *val)
{
    if (!val)
    {
        return handle_string("(null)");
    }
    int res = 0;
    while (val[res])
    {
        tty_putc(val[res]);
        res++;
    }
    return res;
}

int handle_char(char val)
{
    tty_putc(val);
    return 1;
}

int handle_octal(unsigned int val)
{
    return handle_base(val, 8);
}

int handle_hexa(unsigned int val)
{
    return handle_base(val, 16);
}

int handle_directive(const char *format, int *ap)
{
    switch (*(format + 1))
    {
    case '%':
        tty_putc('%');
        return 1;
    case 'd':
        return handle_decimal(*ap);
    case 'u':
        return handle_unsigned(*ap);
    case 's':
        return handle_string((char *)*ap);
    case 'c':
        return handle_char(*ap);
    case 'o':
        return handle_octal(*ap);
    case 'x':
        return handle_hexa(*ap);
    default:
        tty_putc('%');
        tty_putc(*(format + 1));
        return 2;
    }
}

int printf(const char *format, ...)
{
    if (!format)
        return 0;

    int res = 0;

    int *ap = (int *)&format;
    ap++;

    while (*format)
    {
        char c = *format;

        if (c != '%' || *(format + 1) == 0)
        {
            tty_putc(c);
            res++;
            format++;
        }
        else
        {
            res += handle_directive(format, ap);
            ap++;
            format += 2;
        }
    }

    return res;
}
