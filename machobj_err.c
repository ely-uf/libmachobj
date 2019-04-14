#include "machobj_err.h"

static const char *arr[MO_LAST] = {
	"All good.",
	"Failed to open file.",
	"Failed to map file in memory.",
	"File seems to be truncated or corrupted.",
	"File contents are invalid."
};

static t_machobj_err mach_errno;

void	machobj_set_err(t_machobj_err err)
{
	if (err < MO_OK || err >= MO_LAST) 
		return ;
	mach_errno = err;
}

const char *machobj_strerr(void)
{
	return (arr[mach_errno]);
}
