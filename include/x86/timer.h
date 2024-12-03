#ifndef TIMER_H
#define TIMER_H

#include "x86/types.h"

void init_timer(u32 freq);

void sleep(u32 ms);
u32 get_current_tick(void);

#endif
