#include "machobj_symbol.h"
#include "machobj_utils.h"

bool    machobj_symbol32_is_valid(struct nlist *nl, bool swap_b)
{
    UNUSED(swap_b);

    if (MO_NL_IS_DEBUG(nl))
        return true;
    if (MO_NL_IS_COMMON(nl))
        return !!nl->n_value && nl->n_sect == NO_SECT;
    if (MO_NL_IS_ABSLT(nl) || MO_NL_IS_UNDEF(nl))
        return nl->n_sect == NO_SECT;
    if (MO_NL_IS_INDIR(nl))
        return true;

    return nl->n_sect != 0;
} 

bool    machobj_symbol64_is_valid(struct nlist_64 *nl, bool swap_b)
{
    UNUSED(swap_b);

    if (MO_NL_IS_DEBUG(nl))
        return true;
    if (MO_NL_IS_COMMON(nl))
        return !!nl->n_value && nl->n_sect == NO_SECT;
    if (MO_NL_IS_ABSLT(nl) || MO_NL_IS_UNDEF(nl))
        return nl->n_sect == NO_SECT;
    if (MO_NL_IS_INDIR(nl))
        return true;

    return nl->n_sect != 0;
}
