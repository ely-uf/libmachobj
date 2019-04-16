#include "machobj.h"

int machobj_load(t_machobj *mach, const char *filename)
{
	int res = 0;

	res = machobj_open(mach, filename);
	if (res != 0)
		return res;

	res = machobj_parse(mach);
	if (res != 0)
		return res;

	return res;
}
