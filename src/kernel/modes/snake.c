#include "kernel/modes/snake.h"

#include "drivers/tty.h"

void snake_enter(void)
{
    tty_clear();
    tty_set_cursor_pos(0, 0);
    tty_puts("SNAKE MODE");
}

void snake_keystroke_event(enum scancode scancode)
{
    (void)scancode;
}
