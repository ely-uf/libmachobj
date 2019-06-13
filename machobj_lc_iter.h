#ifndef __MACHOBJ_LC_ITER_H
# define __MACHOBJ_LC_ITER_H

# include <stdlib.h>
# include <mach-o/loader.h>

# define LC_ITER_INITIALIZER ((lc_iter) { NULL, 0, 0 })

typedef struct  s_lc_iter
{
    void    *mem;
    size_t  size;
    size_t  offset;
}               lc_iter;

void                machobj_lc_iter_init(lc_iter *iter, void *mem, size_t size);
struct load_command *machobj_lc_next(lc_iter *iter);
void                machobj_lc_iter_reset(lc_iter *iter);

#endif
