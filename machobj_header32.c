#include <stdbool.h>
#include "machobj.h"
#include "machobj_err.h"
#include "machobj_utils.h"
#include "machobj_header.h"

bool	machobj_mach_header_32_is_valid(struct mach_header *hdr)
{
	if (!machobj_mach_header_cputype_is_valid(hdr->cputype))
		return false;
	/*
	 *	XXX: subtype (?)
	 */

	if (!machobj_mach_header_filetype_is_valid(hdr->filetype))
		return false;

	return true;
}

int		machobj_parse_mach_header_32(t_machobj *mach)
{
	struct mach_header	*hdr;

	if (mach->size < sizeof(struct mach_header))
	{
		machobj_set_err(MO_TRUNCATED);
		return 1;
	}

	hdr = mach->data;
	if (!machobj_mach_header_32_is_valid(hdr))
	{
		machobj_set_err(MO_INVALID);
		return 1;
	}

	mach->bin_hdr.mach32 = hdr;
	return 0;
}
