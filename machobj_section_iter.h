#ifndef __MACHOBJ_SECTION_ITER_H
# define __MACHOBJ_SECTION_ITER_H

# include <stdlib.h>
# include <stdbool.h>
# include <mach-o/loader.h>
# include "machobj.h"

typedef struct  s_sect_iter
{
    struct segment_command  *seg;
    struct section          *sect;
    size_t                  nsect;
    bool                    bswap;
}               t_sect_iter;

typedef struct  s_sect_iter_64
{
    struct segment_command_64   *seg;
    struct section_64           *sect;
    size_t                      nsect;
    bool                        bswap;
}               t_sect_iter_64;

void                machobj_sect_iter_init(t_machobj *obj, t_sect_iter *it,
                                           struct segment_command *seg);
struct section      *machobj_sect_next(t_sect_iter *iter);

void                machobj_sect_iter_64_init(t_machobj *o, t_sect_iter_64 *it,
                                              struct segment_command_64 *seg);
struct section_64   *machobj_sect_64_next(t_sect_iter_64 *it);

void                machobj_sect_iter_reset(void *generic_iter);

#endif
