#ifndef SNAKE_H
#define SNAKE_H

#include "drivers/keyboard.h"

void snake_enter(void);
void snake_exit(void);
void snake_keystroke_event(enum scancode scancode);

#endif // ! SNAKE_H
