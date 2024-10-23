#include "kernel/kernel.h"

#include "drivers/keyboard.h"
#include "drivers/tty.h"
#include "kernel/modes/mode.h"
#include "x86/isr.h"

int main(void)
{
    isr_install();
    irq_install();

    tty_clear();
    tty_set_cursor_pos(0, 0);

    mode_switch("SHELL");
}

void keystroke_event(enum scancode scancode)
{
    if (scancode == ESC)
    {
        mode_switch("SHELL");
    }
    mode_keystroke_event(scancode);
}
