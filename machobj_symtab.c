#include "machobj_symtab.h"
#include "machobj_utils.h"
#include "machobj_err.h"

int     machobj_get_nlist_32(t_machobj *obj,
                             nlist_iter *iter,
                             struct symtab_command *s)
{
    u_int32_t symoff = MOBJ_GET32(obj, s->symoff);
    u_int32_t nsyms = MOBJ_GET32(obj, s->nsyms);

    if (symoff + nsyms * sizeof(struct nlist) > obj->size)
    {
        machobj_set_err(MO_TRUNCATED);
        return 1;
    }

    iter->nlist = (struct nlist*)((char*)obj->data + symoff);
    iter->nsyms = nsyms;
    iter->idx = 0;

    return 0;
}

int     machobj_get_nlist_64(t_machobj *obj,
                             nlist_iter_64 *iter,
                             struct symtab_command *s)
{

    u_int32_t symoff = MOBJ_GET32(obj, s->symoff);
    u_int32_t nsyms = MOBJ_GET32(obj, s->nsyms);

    if (symoff + nsyms * sizeof(struct nlist_64) > obj->size)
    {
        machobj_set_err(MO_TRUNCATED);
        return 1;
    }

    iter->nlist = (struct nlist_64*)((char*)obj->data + symoff);
    iter->nsyms = nsyms;
    iter->idx = 0;

    return 0;
}

struct nlist    *machobj_nlist_32_next(nlist_iter *iter)
{
    struct nlist    *res;

    if (iter->idx >= iter->nsyms)
        return NULL;

    res = &iter->nlist[iter->idx];
    iter->idx++;

    return res;
}

struct nlist_64 *machobj_nlist_64_next(nlist_iter_64 *iter)
{
    struct nlist_64 *res;

    if (iter->idx >= iter->nsyms)
        return NULL;

    res = &iter->nlist[iter->idx];
    iter->idx++;

    return res;
}

void            machobj_nlist_reset(void *iter)
{
    ((nlist_iter *)iter)->idx = 0;
}
