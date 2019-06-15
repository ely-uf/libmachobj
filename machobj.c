#include "machobj.h"
#include "machobj_debug.h"

int machobj_load(t_machobj *mach, const char *filename)
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
