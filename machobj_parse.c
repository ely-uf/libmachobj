#include "machobj.h"
#include "machobj_err.h"
#include "machobj_debug.h"
#include "machobj_header.h"

int     machobj_parse_magic(t_machobj *mach)
{
    uint32_t    magic;

    if (mach->size < sizeof(magic))
    {
        machobj_set_err(MO_TRUNCATED);
        return 1;
    }
    magic = *(uint32_t*)mach->data;
    if (magic == MH_MAGIC)
    {
        mach->bit_arch = BIT_32;
        mach->bswap = false;
    }
    else if (magic == MH_CIGAM)
    {
        mach->bit_arch = BIT_32;
        mach->bswap = true;
    }
    else if (magic == MH_MAGIC_64)
    {
        mach->bit_arch = BIT_64;
        mach->bswap = false;
    }
    else if (magic == MH_CIGAM_64)
    {
        mach->bit_arch = BIT_64;
        mach->bswap = true;
    }
    else
    {
        mdebug("Invalid magic: %u", magic);
        machobj_set_err(MO_INVALID);
        return 1;
    }

    return 0;
}

int     machobj_parse_header_arch(t_machobj *mach)
{
    if (mach->bit_arch == BIT_64)
        return machobj_parse_mach_header_64(mach);
    else if (mach->bit_arch == BIT_32)
        return machobj_parse_mach_header_32(mach);
    return 1;
}

int     machobj_parse_header(t_machobj *mach)
{
    int res;

    res = machobj_parse_magic(mach);
    if (res != 0)
        return res;
    res = machobj_parse_header_arch(mach);
    /*
     *  XXX: TBD
     */
    return res;
}
