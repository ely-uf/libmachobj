#ifndef __MACHOBJ_HEADER_H
# define __MACHOBJ_HEADER_H

# include <stdbool.h>
# include <mach-o/loader.h>
# include "machobj.h"
# include "machobj_utils.h"

static const uint32_t   machobj_filetypes[] = {
    MH_OBJECT,
    MH_EXECUTE,
    MH_BUNDLE,
    MH_DYLIB,
    MH_PRELOAD,
    MH_CORE,
    MH_DYLINKER,
    MH_DSYM
};

static inline bool machobj_mach_header_filetype_is_valid(uint32_t ftype)
{
    for (size_t i = 0; i < ARRAY_LEN(machobj_filetypes); i++)
    {
        if (ftype == machobj_filetypes[i])
            return true;
    }
    return false;
}

static const cpu_type_t machobj_cputypes[] = {
    CPU_TYPE_VAX,
    CPU_TYPE_MC680x0,
    CPU_TYPE_X86,
    CPU_TYPE_I386,
    CPU_TYPE_X86_64,
    CPU_TYPE_MC98000,
    CPU_TYPE_HPPA,
    CPU_TYPE_ARM,
    CPU_TYPE_ARM64,
    CPU_TYPE_ARM64_32,
    CPU_TYPE_MC88000,
    CPU_TYPE_SPARC,
    CPU_TYPE_I860,
    CPU_TYPE_POWERPC,
    CPU_TYPE_POWERPC64
};

static inline bool machobj_mach_header_cputype_is_valid(cpu_type_t ctype)
{
    for (size_t i = 0; i < ARRAY_LEN(machobj_cputypes);  i++)
    {
        if (ctype == machobj_cputypes[i])
            return true;
    }
    return false;
}

static inline uint32_t machobj_mach_header_get_ncmds(t_machobj *mach)
{
    uint32_t ncmds = 0;

    if (mach->bit_arch == BIT_64)
        ncmds = mach->hdr.mach64->ncmds;
    else if (mach->bit_arch == BIT_32)
        ncmds = mach->hdr.mach32->ncmds;

    if (mach->swap_bytes)
        ncmds = BSWAP32(ncmds);

    return ncmds;
}

int machobj_parse_mach_header_32(t_machobj *mach);
int machobj_parse_mach_header_64(t_machobj *mach);
int machobj_parse_header_arch(t_machobj *mach);
int machobj_parse_header(t_machobj *mach);

#endif
