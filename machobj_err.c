#include "machobj_err.h"

static const char *arr[MO_LAST] = {
    [MO_OK]             =   "All good.",
    [MO_NOT_PARSED]     =   "Seems like you forgot to parse the file after opening!",
    [MO_OPEN_FAILED]    =   "Failed to open file.",
    [MO_MMAP_FAILED]    =   "Failed to map file in memory.",
    [MO_MALLOC_FAILED]  =   "Failed to allocate memory.",
    [MO_TRUNCATED]      =   "File seems to be truncated or corrupted.",
    [MO_INVALID]        =   "File contents are invalid.",
    [MO_ITER_INVALID]   =   "Iterator has not been initialized.",
};

static t_machobj_err mach_errno;
const char * mach_err_func;
long unsigned int mach_err_line;

void    _machobj_set_err(t_machobj_err err, const char *f, long unsigned int l)
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
