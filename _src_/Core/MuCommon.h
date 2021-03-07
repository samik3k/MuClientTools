#ifndef MU_COMMON_H
#define MU_COMMON_H

#if (MU_SEASON == 13)

#define ITEM_CATEGORY_MAX 17	//(0-16)	
#define ITEM_INDEX_MAX 512		//(0-511)
#define ITEM_MAKE(cat, idx) (cat * 512 + idx)
#endif	// (MU_SEASON == 13)

#endif // !MU_COMMON_H
