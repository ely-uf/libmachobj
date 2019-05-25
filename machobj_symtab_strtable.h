#ifndef __MACHOBJ_SYMTAB_STRTABLE_H
# define __MACHOBJ_SYMTAB_STRTABLE_H

# include "machobj.h"

const char  *machobj_symtab_strtable_get(t_machobj *obj,
                                         struct symtab_command *sc,
                                         long idx);

#endif
