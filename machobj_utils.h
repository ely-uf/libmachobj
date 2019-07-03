#ifndef __MACHOBJ_UTILS_H
# define __MACHOBJ_UTILS_H

# define ARRAY_LEN(_arr) (sizeof(_arr) / sizeof(_arr[0]))
# define UNUSED(x) (void)(x)

# define BSWAP16(b) ((((b) << 8) | ((b) >> 8)) & 0xFFFF)
# define BSWAP32(b) ((BSWAP16((b) & 0xFFFF) << 16) | BSWAP16((b) >> 16))
# define BSWAP64(b) ((BSWAP32((b) & 0xFFFFFFFF) << 32) | BSWAP32((b) >> 32))

# define MOBJ_NEEDS_BSWAP(obj) ((obj)->bswap)

# define MOBJ_GET32(obj, f) (MOBJ_NEEDS_BSWAP(obj) ? BSWAP32(f) : f)
# define MOBJ_GET64(obj, f) (MOBJ_NEEDS_BSWAP(obj) ? BSWAP64(f) : f)

#endif
