#ifndef __MACHOBJ_ERR_H
# define __MACHOBJ_ERR_H

typedef enum	e_machobj_err
{
	MO_OK,
	MO_OPEN_FAILED,
	MO_MMAP_FAILED,
	MO_MALLOC_FAILED,
	MO_TRUNCATED,
	MO_INVALID,
	MO_LAST
}				t_machobj_err;

void			_machobj_set_err(t_machobj_err e, const char *f, long unsigned int l);
const char		*machobj_strerr(void);

# define machobj_set_err(_err) _machobj_set_err(_err, __func__, __LINE__)

#endif
