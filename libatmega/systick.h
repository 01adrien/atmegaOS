#if !defined(SYSTICK_H)
#define SYSTICK_H

#include "memory_map.h"

void systick_init(void);
uint64_t get_tick(void);
void systick_increment(void);

#endif // SYSTICK_H
