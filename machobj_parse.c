#include "machobj.h"
#include "machobj_err.h"
#include "machobj_header.h"

int		machobj_parse_bitarch(t_machobj *mach)
{
	uint32_t	magic;

	if (mach->size < sizeof(magic))
	{
		machobj_set_err(MO_TRUNCATED);
		return 1;
	}
	magic = *(uint32_t*)mach->data;
	if (magic == MH_MAGIC)
		mach->bit_arch = BIT_32;
	else if (magic == MH_MAGIC_64)
		mach->bit_arch = BIT_64;
	else
	{
		machobj_set_err(MO_INVALID);
		return 1;
	}

	return 0;
}

int		machobj_parse_header_arch(t_machobj *mach)
{
	if (mach->bit_arch == BIT_64)
		return machobj_parse_mach_header_64(mach);
	else if (mach->bit_arch == BIT_32)
		return machobj_parse_mach_header_32(mach);
	return 1;
}

int		machobj_parse_header(t_machobj *mach)
{
	int	res;

	res = machobj_parse_bitarch(mach);
	if (res != 0)
		return res;
	res = machobj_parse_header_arch(mach);
	/*
	 *	XXX: TBD
	 */
	return 0;
}

int		machobj_parse(t_machobj *mach)
{
	int	res;

	res = machobj_parse_header(mach);
	if (res != 0)
		return res;

	/*
	 *	TBD
	 */

	return 0;
}
