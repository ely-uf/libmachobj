#include "machobj.h"
#include "machobj_debug.h"
#include <fcntl.h>
#include <unistd.h>

bool	machobj_is_mach_o_file(const char *filename)
{
	int			fd;
	uint32_t	magic;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return false;

	if (read(fd, &magic, sizeof(magic)) != sizeof(magic))
	{
		close(fd);
		return false;
	}

	close(fd);

	return (magic == MH_MAGIC || magic == MH_CIGAM ||
			magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}

int     machobj_load(t_machobj *mach, const char *filename)
{
	int res = 0;

	mdebug("Opening file...");
	res = machobj_open(mach, filename);
	if (res != 0)
		return res;

	mdebug("Parsing header...");
	res = machobj_parse_header(mach);
	if (res != 0)
		return res;

	mdebug("Parsing load commands...");
	res = machobj_parse_load_commands(mach);
	if (res != 0)
		return res;

	return res;
}
