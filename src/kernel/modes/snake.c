#include "kernel/modes/snake.h"

#include "drivers/tty.h"
#include "memory.h"

char *screen;

void snake_enter(void)
{
    tty_clear();
    tty_set_cursor_pos(0, 0);
    tty_puts("SNAKE MODE");

    screen = malloc(TTY_ROWS * TTY_COLS * sizeof(char));
}

void snake_exit(void)
{
    free(screen);
}

void snake_keystroke_event(enum scancode scancode)
{
    (void)scancode;
}
