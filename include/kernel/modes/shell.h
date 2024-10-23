#ifndef SHELL_H
#define SHELL_H

#include "drivers/keyboard.h"

void shell_enter(void);
void shell_keystroke_event(enum scancode scancode);

#endif
