#include "machobj.h"
#include "machobj_err.h"
#include "machobj_header.h"
#include "machobj_load_commands.h"
#include "machobj_debug.h"
#include <stdlib.h>

#define LC_INIT_OFFSET(mach) ((mach)->bit_arch == BIT_64 ?      \
                                sizeof(struct mach_header_64) : \
                                sizeof(struct mach_header))

t_lcommand  *machobj_load_commands_get(t_machobj *mach, uint32_t *ncmds)
{
    if (mach->load_commands == NULL)
    {
        *ncmds = 0;
        machobj_set_err(MO_NOT_PARSED);
        return NULL;
    }

    *ncmds = mach->lc_loaded;
    if (mach->lc_loaded == 0)
        return NULL;

    return mach->load_commands;
}

static int  machobj_do_parse_load_commands(t_machobj *mach,
                                           uint32_t ncmds,
                                           void *lc_address)
{
    mach->lc_loaded = 0;
    while (mach->lc_loaded < ncmds)
    {
        if (lc_address - mach->data + sizeof(struct load_command) > mach->size)
        {
            machobj_set_err(MO_TRUNCATED);
            /*
            ** In case the last load command does not fit, just let it go...
            */
            if ((size_t)(lc_address - mach->data) > mach->size)
                mach->lc_loaded = mach->lc_loaded ? mach->lc_loaded - 1 : 0;
            return 1;
        }
        mach->load_commands[mach->lc_loaded].lcmd = lc_address;
        lc_address += mach->load_commands[mach->lc_loaded].lcmd->cmdsize;
        mach->lc_loaded++;
    }

    return 0;
}

int machobj_load_commands_parse(t_machobj *mach)
{
    void        *lc_address = mach->data + LC_INIT_OFFSET(mach);
    uint32_t    ncmds = machobj_mach_header_get_ncmds(mach);
    int         res;

    if (ncmds == 0)
    {
        mach->load_commands = NULL;
        return 0;
    }

    mach->load_commands = (t_lcommand*)malloc(sizeof(t_lcommand) * ncmds);
    if (!mach->load_commands)
    {
        machobj_set_err(MO_MALLOC_FAILED);
        return 1;
    }

    res = machobj_do_parse_load_commands(mach, ncmds, lc_address);
    if (res != 0)
        return res;

    return 0;
}
