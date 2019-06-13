#include "machobj_lc_iter.h"
#include "machobj_err.h"

void    machobj_lc_iter_init(lc_iter *iter, void *mem, size_t size)
{
    *iter = (lc_iter){mem, size, 0};
}

struct load_command *machobj_lc_next(lc_iter *iter)
{
    struct load_command *lc;

    if (iter->mem == NULL || iter->offset == iter->size)
    {
        if (iter->mem == NULL)
            machobj_set_err(MO_ITER_INVALID);
        return NULL;
    }

    lc = (struct load_command*)((char*)iter->mem + iter->offset);
    if (lc->cmdsize > iter->size - iter->offset)
    {
        machobj_set_err(MO_TRUNCATED);
        return NULL;
    }

    iter->offset += lc->cmdsize;
    return lc;
}

void    machobj_lc_iter_reset(lc_iter *iter)
{
    iter->offset = 0;
}
