#ifndef __MACHOBJ_UTILS_H
# define __MACHOBJ_UTILS_H

# define ARRAY_LEN(_arr) (sizeof(_arr) / sizeof(_arr[0]))

# define BSWAP16(b) ((((b) << 8) | ((b) >> 8)) & 0xFFFF)
# define BSWAP32(b) ((BSWAP16((b) & 0xFFFF) << 16) | BSWAP16((b) >> 16))
# define MOBJ_GET32(obj, f) ((obj)->swap_bytes ? BSWAP32(f) : f)

#endif
