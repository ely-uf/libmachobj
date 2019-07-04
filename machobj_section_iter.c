#include "machobj_section_iter.h"
#include "machobj_utils.h"

void    machobj_sect_iter_init(t_machobj *obj, t_sect_iter *it,
                               struct segment_command *seg)
{
    it->seg = seg;
    it->sect = (struct section*)(seg + 1);
    it->nsect = 0;
    it->bswap = MOBJ_NEEDS_BSWAP(obj);
}

struct section  *machobj_sect_next(t_sect_iter *iter)
{
    if (iter->nsect == 0)
    {
        iter->nsect = 1;
        return (iter->sect);
    }

    if (iter->nsect + 1 > MOBJ_GET32(iter, iter->seg->nsects))
        return (NULL);

    iter->sect++;
    return (iter->sect);
}

void                machobj_sect_iter_64_init(t_machobj *obj,
                                              t_sect_iter_64 *it,
                                              struct segment_command_64 *seg)
{
    it->seg = seg;
    it->sect = (struct section_64*)(seg + 1);
    it->nsect = 0;
    it->bswap = MOBJ_NEEDS_BSWAP(obj);
}

struct section_64   *machobj_sect_64_next(t_sect_iter_64 *iter)
{
    if (iter->nsect == 0)
    {
        iter->nsect = 1;
        return (iter->sect);
    }

    if (iter->nsect + 1 > MOBJ_GET32(iter, iter->seg->nsects))
        return (NULL);

    iter->sect++;
    iter->nsect++;
    return (iter->sect);
}
