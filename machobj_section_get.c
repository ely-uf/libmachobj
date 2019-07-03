#include "machobj_section_get.h"
#include "machobj_lc_spec_iter.h"
#include "machobj_utils.h"
#include "machobj_debug.h"
#include "machobj_err.h"
#include <sys/types.h>

static void *_machobj_section_get_by_num(t_lcs_iter *it, uint32_t num)
{
    struct segment_command  *seg;
    uint32_t                curr_num;
    struct section          *sect;

    curr_num = 1;
    seg = (struct segment_command*)machobj_lc_spec_next(it);
    while (seg)
    {
        if (MOBJ_GET32(&it->lc_it, seg->nsects) && num >= curr_num &&
            num <= curr_num + MOBJ_GET32(&it->lc_it, seg->nsects))
            break ;
        curr_num += MOBJ_GET32(&it->lc_it, seg->nsects);
        seg = (struct segment_command*)machobj_lc_spec_next(it);
    }
    if (!seg)
        return NULL;

    if (MOBJ_GET32(&it->lc_it, seg->nsects) * sizeof(*sect) + sizeof(*seg) >
        MOBJ_GET32(&it->lc_it, seg->cmdsize))
    {
        machobj_set_err(MO_INVALID);
        return NULL;
    }

    sect = (struct section*)((struct segment_command*)seg + 1);
    sect += num - curr_num;

    return sect;
}

static void *_machobj_section_get_by_num64(t_lcs_iter *it, uint32_t num)
{
    struct segment_command_64   *seg;
    uint32_t                    curr_num;
    struct section_64           *sect;

    curr_num = 1;
    seg = (struct segment_command_64*)machobj_lc_spec_next(it);
    while (seg)
    {
        if (MOBJ_GET32(&it->lc_it, seg->nsects) && num >= curr_num &&
            num <= curr_num + MOBJ_GET32(&it->lc_it, seg->nsects))
            break ;
        curr_num += MOBJ_GET32(&it->lc_it, seg->nsects);
        seg = (struct segment_command_64*)machobj_lc_spec_next(it);
    }
    if (!seg)
        return NULL;

    if (MOBJ_GET32(&it->lc_it, seg->nsects) * sizeof(*sect) + sizeof(*seg) >
        MOBJ_GET32(&it->lc_it, seg->cmdsize))
    {
        machobj_set_err(MO_INVALID);
        return NULL;
    }
    sect = (struct section_64*)(seg + 1);
    sect += num - curr_num;

    return sect;
}

void    *machobj_section_get_by_num(t_machobj *obj, uint32_t num)
{
    uint32_t const  cmd = MACHOBJ_IS_32BIT(obj) ? LC_SEGMENT : LC_SEGMENT_64;
    t_lcs_iter      iter;

    machobj_lc_spec_iter_init(&iter, cmd, obj->lc, obj->lc_size, obj->bswap);

    return MACHOBJ_IS_32BIT(obj) ?
        _machobj_section_get_by_num(&iter, num) :
        _machobj_section_get_by_num64(&iter, num);
}
