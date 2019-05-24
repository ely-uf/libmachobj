#include "machobj_lc_iter.h"

void	machobj_lc_iter_init(lc_iter *iter, void *mem, size_t size)
{
	*iter = (lc_iter){mem, size, 0};
}

struct load_command *machobj_lc_next(lc_iter *iter)
{
	struct load_command	*lc;

	if (iter->mem == NULL || iter->offset == iter->size)
		return NULL;

	lc = (struct load_command*)((char*)iter->mem + iter->offset);
	/*
	** XXX: Error reporting?
	*/
	if (lc->cmdsize > iter->size - iter->offset)
		return NULL;

	iter->offset += lc->cmdsize;
	return lc;
}

void	machobj_lc_iter_reset(lc_iter *iter)
{
	iter->offset = 0;
}
