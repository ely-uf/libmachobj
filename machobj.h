#ifndef __MACHOBJ_H
# define __MACHOBJ_H

# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <stddef.h>
# include <stdbool.h>

# define _MALIGN(_v, _al) (((_v) + ((_al) - ((_v) % (_al)))))
# define MACHOBJ_ALIGN(_b, _v) ((_b) == BIT_64 ? _MALIGN(_v, 8) : _MALIGN(_v, 4))
# define MACHOBJ_IS_32BIT(_obj) ((_obj)->bit_arch == BIT_32)
# define MACHOBJ_IS_64BIT(_obj) ((_obj)->bit_arch == BIT_64)

typedef enum    e_bitarch
{
    BIT_32,
    BIT_64
}               t_bitarch;

union           u_hdr
{
    struct mach_header      *mach32;
    struct mach_header_64   *mach64;
    /* struct fat_header    *fat; */
};

typedef struct  s_lcommand
{
    struct load_command *lcmd;
}               t_lcommand;

typedef struct  s_machobj
{
    void            *data;
    size_t          size;

    bool            swap_bytes;
    t_bitarch       bit_arch;
    union u_hdr     hdr;

    size_t          lc_loaded;
    t_lcommand      *load_commands;
}               t_machobj;

int     machobj_parse_header(t_machobj *mach);
int     machobj_parse_load_commands(t_machobj *mach);
int     machobj_open(t_machobj *mach, const char *filename);
int     machobj_load(t_machobj *mach, const char *filename);
void    machobj_close(t_machobj *mach);

#endif
