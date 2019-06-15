#ifndef __MACHOBJ_SYMTAB_H
# define __MACHOBJ_SYMTAB_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/stab.h>
# include <stdlib.h>
# include "machobj.h"

typedef struct  nlist_iter
{
    struct nlist    *nlist;
    u_int32_t       nsyms;
    size_t          idx;
}               nlist_iter;

typedef struct  nlist_iter_64
{
    struct nlist_64 *nlist;
    u_int32_t       nsyms;
    size_t          idx;
}               nlist_iter_64;

int             machobj_get_nlist_32(t_machobj *obj,
                                      nlist_iter *iter,
                                      struct symtab_command *s);
int             machobj_get_nlist_64(t_machobj *obj,
                                      nlist_iter_64 *iter,
                                      struct symtab_command *s);

struct nlist    *machobj_nlist_32_next(nlist_iter *iter);
struct nlist_64 *machobj_nlist_64_next(nlist_iter_64 *iter);

void            machobj_nlist_reset(void *iter);

#endif
