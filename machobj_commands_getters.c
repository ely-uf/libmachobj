#include <string.h>
#include <stdlib.h>
#include "machobj.h"
#include "machobj_err.h"
#include "machobj_utils.h"
#include "machobj_load_commands.h"

size_t machobj_get_num_of_cmds(t_machobj *obj, uint32_t cmd)
{
    size_t  cmds = 0;

    for (size_t i = 0; i < obj->lc_loaded; i++)
    {
        if (MOBJ_GET32(obj, obj->load_commands[i].lcmd->cmd) == cmd)
            cmds++;
    }

    return cmds;
}

size_t machobj_get_size_of_cmds(t_machobj *obj, uint32_t cmd)
{
    size_t  size = 0;

    for (size_t i = 0; i < obj->lc_loaded; i++)
    {
        if (MOBJ_GET32(obj, obj->load_commands[i].lcmd->cmd) == cmd)
            size += MOBJ_GET32(obj, obj->load_commands[i].lcmd->cmdsize);
    }

    return size;
}

size_t machobj_get_cmds(t_machobj *obj, uint32_t cmd, void *vbuf)
{
    size_t              bytes_written = 0;
    char                *buf = vbuf;
    struct load_command *lc;

    for (size_t i = 0; i < obj->lc_loaded; i++)
    {
        if (MOBJ_GET32(obj, obj->load_commands[i].lcmd->cmd) == cmd)
        {
            /*
            ** Alignment of 4/8.
            */
            lc = obj->load_commands[i].lcmd;
            uint32_t cmdsize = MOBJ_GET32(obj, lc->cmdsize);

            if ((size_t)((void*)lc - obj->data + cmdsize) > obj->size)
            {
                machobj_set_err(MO_TRUNCATED);
                return 0;
            }
            memcpy(buf + bytes_written, lc, cmdsize);
            bytes_written += cmdsize;
        }
    }

    return bytes_written;
}

size_t machobj_get_cmds_m(t_machobj *obj, uint32_t cmd, void **mem)
{
    size_t  expected_size;

    expected_size = machobj_get_size_of_cmds(obj, cmd);
    *mem = malloc(expected_size);
    if (!*mem)
        return 0;

    return machobj_get_cmds(obj, cmd, *mem);
}
