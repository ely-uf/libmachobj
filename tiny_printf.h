#ifndef __TINY_PRINTF_H
# define __TINY_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>

#define TINY_BUF_SIZE   4096

size_t  tiny_vprintf(const char *fmt, va_list lst);
size_t  tiny_printf(const char *fmt, ...);

#endif
