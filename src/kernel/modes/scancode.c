#include "scancode.h"

#include "drivers/tty.h"
#include "stdlib/io.h"

void scancode_enter(void)
{
    tty_clear();
    tty_set_cursor_pos(0, 0);
    tty_puts("SCANCODE MODE");
    tty_puts("=============\n");
}

void scancode_keystroke_event(enum scancode scancode)
{
    printf("- 0x%x\n", scancode);
}
