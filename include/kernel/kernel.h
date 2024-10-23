#ifndef KERNEL_H
#define KERNEL_H

#include "drivers/keyboard.h"

void shell_input_event(char *input);
void keystroke_event(enum scancode scancode);

#endif
