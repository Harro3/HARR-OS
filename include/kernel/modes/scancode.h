#ifndef SCANCODE_H
#define SCANCODE_H

#include "drivers/keyboard.h"

void scancode_enter(void);
void scancode_keystroke_event(enum scancode scancode);

#endif
