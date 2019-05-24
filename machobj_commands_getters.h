#ifndef __MACHOBJ_COMMANDS_GETTERS
# define __MACHOBJ_COMMANDS_GETTERS

size_t machobj_get_num_of_cmds(t_machobj *obj, uint32_t cmd);
size_t machobj_get_size_of_cmds(t_machobj *obj, uint32_t cmd);
size_t machobj_get_cmds(t_machobj *obj, uint32_t cmd, void *vbuf);
size_t machobj_get_cmds_m(t_machobj *obj, uint32_t cmd, void **mem);

#endif
