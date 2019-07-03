#ifndef __MACHOBJ_SYMBOL_H
# define __MACHOBJ_SYMBOL_H

# include <stdbool.h>
# include <mach-o/nlist.h>

# define _MO_NL_UNDEF_EXT(nl) (MO_NL_IS_UNDEF(nl) && MO_NL_IS_EXT(nl))

# define MO_NL_N_TYPE(nl) ((nl)->n_type & N_TYPE)

# define MO_NL_IS_EXT(nl) ((nl)->n_type & N_EXT)
# define MO_NL_IS_LOCAL(nl) (!MO_NL_IS_EXT(nl))
# define MO_NL_IS_DEBUG(nl) ((nl)->n_type & N_STAB)
# define MO_NL_IS_UNDEF(nl) (!MO_NL_IS_DEBUG(nl) && MO_NL_N_TYPE(nl) == N_UNDF)
# define MO_NL_IS_ABSLT(nl) (!MO_NL_IS_DEBUG(nl) && MO_NL_N_TYPE(nl) == N_ABS)
# define MO_NL_IS_SECT(nl)  (!MO_NL_IS_DEBUG(nl) && MO_NL_N_TYPE(nl) == N_SECT)
# define MO_NL_IS_COMMON(nl) (_MO_NL_UNDEF_EXT(nl) && (nl)->n_value)
# define MO_NL_IS_INDIR(nl) (!MO_NL_IS_DEBUG(nl) && MO_NL_N_TYPE(nl) == N_INDR)

bool    machobj_symbol32_is_valid(struct nlist *, bool swap_b);
bool    machobj_symbol64_is_valid(struct nlist_64 *, bool swap_b);

#endif
