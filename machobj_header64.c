#include <stdbool.h>
#include "machobj.h"
#include "machobj_err.h"
#include "machobj_utils.h"
#include "machobj_header.h"

bool	machobj_mach_header_64_is_valid(struct mach_header_64 *hdr)
{
	if (hdr->cputype != CPU_TYPE_POWERPC && hdr->cputype != CPU_TYPE_I386)
		return false;
	/*
	 *	XXX: subtype (?)
	 */

	if (!machobj_mach_header_filetype_is_valid(hdr->filetype))
		return false;

	return true;
}

int		machobj_parse_mach_header_64(t_machobj *mach)
{
	struct mach_header_64	*hdr;

	if (mach->size < sizeof(struct mach_header_64))
	{
		machobj_set_err(MO_TRUNCATED);
		return 1;
	}

	hdr = mach->data;
	if (!machobj_mach_header_64_is_valid(hdr))
	{
		machobj_set_err(MO_INVALID);
		return 1;
	}

	mach->bin_hdr.mach64 = hdr;
	return 0;
}
