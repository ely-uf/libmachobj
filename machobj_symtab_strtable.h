#ifndef __MACHOBJ_SYMTAB_STRTABLE_H
# define __MACHOBJ_SYMTAB_STRTABLE_H

# include "machobj.h"

const char  *machobj_symtab_strtable_get(t_machobj *obj,
                                         struct symtab_command *sc,
                                         long idx);

int         machobj_symtab_strtable_get_safe(t_machobj *obj,
                                             struct symtab_command *sc,
                                             long idx,
                                             char *buf,
                                             size_t bufsize);

char        *machobj_symtab_strtable_get_safe_m(t_machobj *obj,
                                                struct symtab_command *sc,
                                                long idx);

#endif
