#include "machobj_symtab_strtable.h"
#include "machobj_err.h"
#include <string.h>

const char  *machobj_symtab_strtable_get(t_machobj *obj,
                                         struct symtab_command *sc,
                                         long lookup_idx)
{
    const char  *strtable;

    if (lookup_idx == 0)
        return "";
    if (sc->stroff + sc->strsize > obj->size)
    {
        machobj_set_err(MO_TRUNCATED);
        return NULL;
    }

    strtable = (char*)obj->data + sc->stroff;

	return &strtable[lookup_idx];
}
