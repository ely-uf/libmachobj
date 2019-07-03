#ifndef __MACHOBJ_SEGMENT_ITERATOR_H
# define __MACHOBJ_SEGMENT_ITERATOR_H

# include "machobj_lc_iter.h"

typedef struct      s_lcs_iter
{
    uint32_t    type;
    lc_iter     lc_it;
}                   t_lcs_iter;

void                machobj_lc_spec_iter_init(t_lcs_iter *iter,
                                              uint32_t type,
                                              void *mem,
                                              size_t size,
                                              bool bswap);

void                machobj_lc_spec_iter_reset(t_lcs_iter *iter);

struct load_command *machobj_lc_spec_iter_next(t_lcs_iter *iter);

#endif
