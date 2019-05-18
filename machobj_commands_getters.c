#include <string.h>
#include "machobj.h"
#include "machobj_err.h"
#include "machobj_utils.h"
#include "machobj_load_commands.h"

size_t machobj_get_num_of_cmds(t_machobj *obj, uint32_t cmd)
{
	size_t	cmds = 0;

	for (size_t i = 0; i < obj->lc_loaded; i++)
	{
		if (MOBJ_GET32(obj, obj->load_commands->lcmd->cmd) == cmd)
			cmds++;
	}
	return cmds;
}

size_t machobj_get_size_of_cmds(t_machobj *obj, uint32_t cmd)
{
	size_t	size;

	for (size_t i = 0; i < obj->lc_loaded; i++)
	{
		if (MOBJ_GET32(obj, obj->load_commands->lcmd->cmd) == cmd)
			size += MOBJ_GET32(obj, obj->load_commands->lcmd->cmdsize);
	}

	return size;
}

size_t machobj_get_cmds(t_machobj *obj, uint32_t cmd, void *vbuf)
{
	size_t	bytes_written = 0;
	char	*buf = vbuf;

	for (size_t i = 0; i < obj->lc_loaded; i++)
	{
		if (MOBJ_GET32(obj, obj->load_commands->lcmd->cmd) == cmd)
		{
			/*
			** Alignment of 4/8.
			*/
			uint32_t cmdsize = MOBJ_GET32(obj, obj->load_commands->lcmd->cmdsize);
			memcpy(buf + bytes_written, obj->load_commands->cmd, cmdsize);
			bytes_written += cmdsize;
		}
	}

	return bytes_written;
}
