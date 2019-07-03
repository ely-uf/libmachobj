#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "machobj.h"
#include "machobj_err.h"

int     machobj_mmap(t_machobj *mach, int fd)
{
    struct stat buf;
    size_t  size;
    void    *mem;

    if (fstat(fd, &buf) != 0)
        return 1;
    size = buf.st_size;

    mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (mem == MAP_FAILED)
        return 1;

    mach->data = mem;
    mach->size = size;
    return 0;
}

int     machobj_open(t_machobj *mach, const char *filename)
{
    int fd;
    int res = 0;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        machobj_set_err(MO_OPEN_FAILED);
        return 1;
    }

    res = machobj_mmap(mach, fd);
    if (res != 0)
        machobj_set_err(MO_MMAP_FAILED);

    close(fd);
    return res;
}

void    machobj_close(t_machobj *mach)
{
    if (mach->data)
    {
        munmap(mach->data, mach->size);
        mach->data = NULL;
        mach->size = 0;
    }
}
