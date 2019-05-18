#include "machobj_err.h"

static const char *arr[MO_LAST] = {
	"All good.",
	"Failed to open file.",
	"Failed to map file in memory.",
	"Failed to allocate memory.",
	"File seems to be truncated or corrupted.",
	"File contents are invalid."
};

static t_machobj_err mach_errno;
const char * mach_err_func;
long unsigned int mach_err_line;

void	_machobj_set_err(t_machobj_err err, const char *f, long unsigned int l)
{
	if (err < MO_OK || err >= MO_LAST) 
		return ;
	mach_errno = err;
	mach_err_func = f;
	mach_err_line = l;
}

const char *machobj_strerr(void)
{
	return (arr[mach_errno]);
}
