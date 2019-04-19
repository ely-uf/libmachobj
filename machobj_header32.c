#include <stdbool.h>
#include <string.h>
#include "machobj.h"
#include "machobj_err.h"
#include "machobj_utils.h"
#include "machobj_header.h"

bool	machobj_mach_header_32_is_valid(struct mach_header *hdr, bool swap_bytes)
{
	cpu_type_t	cputype = swap_bytes ? BSWAP32(hdr->cputype) : hdr->cputype;
	uint32_t	filetype = swap_bytes ? BSWAP32(hdr->filetype) : hdr->filetype;

	if (!machobj_mach_header_cputype_is_valid(cputype))
		return false;
	/*
	 *	XXX: subtype (?)
	 */

	if (!machobj_mach_header_filetype_is_valid(filetype))
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
	if (!machobj_mach_header_32_is_valid(hdr, mach->swap_bytes))
	{
		machobj_set_err(MO_INVALID);
		return 1;
	}

	mach->hdr.mach32 = hdr;
	return 0;
}
