#ifndef TIMER_H
#define TIMER_H

#include "x86/types.h"

void init_timer(u32 freq);

u32 get_cpu_tick(void);

#endif
