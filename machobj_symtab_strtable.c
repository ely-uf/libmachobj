#include "machobj_symtab_strtable.h"
#include "machobj_utils.h"
#include "machobj_err.h"

const char  *machobj_symtab_strtable_get(t_machobj *obj,
                                         struct symtab_command *sc,
                                         long lookup_idx)
{
    const char  *strtable;
    uint32_t    stroff = MOBJ_GET32(obj, sc->stroff);
    uint32_t    strsize = MOBJ_GET32(obj, sc->strsize);

    if (lookup_idx == 0)
        return "";
    if (stroff + strsize > obj->size)
    {
        machobj_set_err(MO_TRUNCATED);
        return NULL;
    }

    strtable = (char*)obj->data + stroff;

    return &strtable[lookup_idx];
}
