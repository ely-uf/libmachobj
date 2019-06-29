#ifndef __MACHOBJ_DEBUG_H
# define __MACHOBJ_DEBUG_H

# include <string.h>
# include "machobj.h"
# include "tiny_printf.h"

# ifdef DEBUG
#  define mdebug(_fmt, ...) tiny_printf("%s[%i]: " _fmt "\n", __func__, __LINE__,##__VA_ARGS__ )
# else
#  define mdebug(_fmt, ...)
# endif

#endif
