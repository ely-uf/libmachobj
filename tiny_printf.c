#include "tiny_printf.h"
#include <unistd.h>

static size_t   tiny_putnbr(char tiny_buf[TINY_BUF_SIZE],
                            size_t tiny_off,
                            ssize_t arg)
{
    size_t  res;

    if (tiny_off >= TINY_BUF_SIZE - 1)
        return 0;

    if (arg < 0)
    {
        tiny_buf[tiny_off] = '-';
        return 1 + tiny_putnbr(tiny_buf, tiny_off + 1, -arg);
    }

    if (arg < 10)
    {
        tiny_buf[tiny_off] = arg + 48;
        return 1;
    }

    res = tiny_putnbr(tiny_buf, tiny_off, arg / 10);
    return res + tiny_putnbr(tiny_buf, tiny_off + res, arg % 10);
}

static size_t   tiny_putnbr_u(char tiny_buf[TINY_BUF_SIZE],
                              size_t tiny_off,
                              size_t arg)
{
    size_t res;

    if (tiny_off >= TINY_BUF_SIZE - 1)
        return 0;

    if (arg < 10)
    {
        tiny_buf[tiny_off] = arg + 48;
        return 1;
    }

    res = tiny_putnbr_u(tiny_buf, tiny_off, arg / 10);
    return res + tiny_putnbr_u(tiny_buf, tiny_off + res, arg % 10);
}

static size_t   tiny_putstr(char tiny_buf[TINY_BUF_SIZE],
                            size_t tiny_off,
                            const char *arg)
{
    size_t  i;

    i = 0;
    while (arg[i] && tiny_off < TINY_BUF_SIZE - 1)
    {
        tiny_buf[tiny_off] = arg[i];
        i++;
        tiny_off++;
    }

    return i;
}

static size_t   tiny_format(char format_spec,
                            char tiny_buf[TINY_BUF_SIZE],
                            size_t tiny_off,
                            va_list lst)
{
        if (format_spec == '%')
        {
            tiny_buf[tiny_off] = '%';
            return 1;
        }
        else if (format_spec == 'd' || format_spec == 'i')
            return tiny_putnbr(tiny_buf, tiny_off, va_arg(lst, int));
        else if (format_spec == 's')
            return tiny_putstr(tiny_buf, tiny_off, va_arg(lst, const char *));
        else if (format_spec == 'u')
            return tiny_putnbr_u(tiny_buf, tiny_off, va_arg(lst, unsigned));

        return 0;
}

size_t  tiny_vprintf(char const *fmt, va_list lst)
{
    size_t  i = 0;
    char    tiny_buf[TINY_BUF_SIZE] = {0};
    size_t  tiny_off = 0;

    while (fmt[i] && tiny_off < TINY_BUF_SIZE - 1)
    {
        if (fmt[i] != '%')
        {
            tiny_buf[tiny_off] = fmt[i];
            tiny_off++;
            i++;
            continue ;
        }
        tiny_off += tiny_format(fmt[i + 1], tiny_buf, tiny_off, lst);
        i += 2;
    }

    tiny_buf[tiny_off] = 0;

    write(1, tiny_buf, tiny_off);
    return tiny_off;
}

size_t  tiny_printf(char const *fmt, ...)
{
    va_list lst;
    int     len;

    va_start(lst, fmt);
    len = tiny_vprintf(fmt, lst);
    va_end(lst);

    return len;
}
