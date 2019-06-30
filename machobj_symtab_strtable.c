#include "machobj_symtab_strtable.h"
#include "machobj_utils.h"
#include "machobj_err.h"
#include <stdlib.h>
#include <string.h>

const char  *machobj_symtab_strtable_get(t_machobj *obj,
                                         struct symtab_command *sc,
                                         long lookup_idx)
{
    const char  *strtable;
    uint32_t    stroff = MOBJ_GET32(obj, sc->stroff);
    uint32_t    strsize = MOBJ_GET32(obj, sc->strsize);

    if (lookup_idx <= 0)
        return "";
    if (stroff + strsize > obj->size || stroff + lookup_idx > obj->size)
    {
        machobj_set_err(MO_TRUNCATED);
        return NULL;
    }

    strtable = (char*)obj->data + stroff;

    return &strtable[lookup_idx];
}

size_t          machobj_symtab_strtable_strlen(t_machobj *obj,
                                               struct symtab_command *sc,
                                               long lookup_idx)
{
    const char      *strtable;
    const uint32_t  stroff = MOBJ_GET32(obj, sc->stroff);
    const uint32_t  strsize = MOBJ_GET32(obj, sc->strsize);
    size_t          i;

    if (lookup_idx <= 0)
        return 0;
    if (stroff + strsize > obj->size || stroff + lookup_idx > obj->size)
        return 0;

    strtable = (char*)obj->data + stroff;
    i = lookup_idx;
    while ((strtable - (char*)obj->data + i) < obj->size && strtable[i])
        i++;

    return i - lookup_idx;
}

int             machobj_symtab_strtable_get_safe(t_machobj *obj,
                                                 struct symtab_command *sc,
                                                 long lookup_idx,
                                                 char *buf,
                                                 size_t buflen)
{
    const char      *entry = machobj_symtab_strtable_get(obj, sc, lookup_idx);
    const size_t    len = machobj_symtab_strtable_strlen(obj, sc, lookup_idx);
    const size_t    size = len < buflen ? len : buflen ;

    if (!entry || !buf || !buflen)
        return 1;

    strncpy(buf, entry, size);
    buf[size] = 0;

    return 0;
}

char            *machobj_symtab_strtable_get_safe_m(t_machobj *obj,
                                                    struct symtab_command *sc,
                                                    long lookup_idx)
{
    const uint32_t  size = machobj_symtab_strtable_strlen(obj, sc, lookup_idx);
    char            *buf = (char*)malloc(size + 1);

    if (!buf)
    {
        machobj_set_err(MO_MALLOC_FAILED);
        return NULL;
    }

    if (machobj_symtab_strtable_get_safe(obj, sc, lookup_idx, buf, size))
    {
        free(buf);
        return NULL;
    }

    return buf;
}
