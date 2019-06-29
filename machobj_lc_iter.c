#include "machobj_lc_iter.h"
#include "machobj_utils.h"
#include "machobj_err.h"

void    machobj_lc_iter_init(lc_iter *iter, void *mem, size_t size, bool bswap)
{
    *iter = (lc_iter){mem, size, 0, bswap};
}

struct load_command *machobj_lc_next(lc_iter *iter)
{
    struct load_command *lc;
    uint32_t            cmdsize;

    if (iter->mem == NULL || iter->offset == iter->size)
    {
        if (iter->mem == NULL)
            machobj_set_err(MO_ITER_INVALID);
        return NULL;
    }

    lc = (struct load_command*)((char*)iter->mem + iter->offset);
    cmdsize = MOBJ_GET32(iter, lc->cmdsize);
    if (cmdsize > iter->size - iter->offset)
    {
        machobj_set_err(MO_TRUNCATED);
        return NULL;
    }

    iter->offset += cmdsize;
    return lc;
}

void    machobj_lc_iter_reset(lc_iter *iter)
{
    iter->offset = 0;
}
