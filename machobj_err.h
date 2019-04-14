#ifndef __MACHOBJ_ERR_H
# define __MACHOBJ_ERR_H

typedef enum	e_machobj_err
{
	MO_OK,
	MO_OPEN_FAILED,
	MO_MMAP_FAILED,
	MO_LAST
}				t_machobj_err;

void			machobj_set_err(t_machobj_err err);
const char		*machobj_strerr(void);

#endif
