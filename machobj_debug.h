#ifndef __MACHOBJ_DEBUG_H
# define __MACHOBJ_DEBUG_H

# include <stdio.h>
# include <string.h>
# include "machobj.h"

# ifdef DEBUG
#  define mdebug(_fmt, ...) printf("%s[%i]: " _fmt "\n", __func__, __LINE__,##__VA_ARGS__ )
# else
#  define mdebug(_fmt, ...)
# endif

#endif
