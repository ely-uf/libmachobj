#include "machobj_lc_spec_iter.h"
#include "machobj_utils.h"

void    machobj_lc_spec_iter_init(t_lcs_iter *it,
                                   uint32_t type,
                                   void *mem,
                                   size_t sz,
                                   bool bswap)
{
    machobj_lc_iter_init(&it->lc_it, mem, sz, bswap);
    it->type = type;
}

void    machobj_lc_spec_iter_reset(t_lcs_iter *iter)
{
    machobj_lc_iter_reset(&iter->lc_it);
}

struct load_command *machobj_lc_spec_next(t_lcs_iter *iter)
{
    struct load_command *lc;

    lc = machobj_lc_next(&iter->lc_it);
    while (lc)
    {
        if (MOBJ_GET32(&iter->lc_it, lc->cmd) == iter->type)
            break ;
        lc = machobj_lc_next(&iter->lc_it);
    }

    return (lc);
}
