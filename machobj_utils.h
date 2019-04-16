#ifndef __MACHOBJ_UTILS_H
# define __MACHOBJ_UTILS_H

# define ARRAY_LEN(_arr) (sizeof(_arr) / sizeof(_arr[0]))
# define ARRAY_FOR_EACH(_arr, iter)							\
	for (int _i1 = 0, typeof ((_arr)[0]) iter = (_arr)[0]; _i1 < ARRAY_LEN(_arr);  _i1++, iter = (_arr)[_i1])

#endif
