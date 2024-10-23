#include "kernel/kernel.h"

#include "drivers/keyboard.h"
#include "drivers/tty.h"
#include "kernel/commands.h"
#include "modes/scancode.h"
#include "stdlib/io.h"
#include "stdlib/memory.h"
#include "x86/isr.h"

enum kmode kernel_mode;

void prompt(void)
{
    tty_print("HARR-OS$ ");
}

int main(void)
{
    isr_install();
    irq_install();
    kernel_mode = SHELL;

    tty_clear();
    tty_set_cursor_pos(0, 0);

    tty_puts("Welcome to HARR-OS !\n");
    help();
    tty_putc('\n');

    prompt();
}

void shell_input_event(char *input)
{
    tty_putc('\n');

    parse_command(input);
    if (kernel_mode == SHELL)
    {
        tty_putc('\n');

        prompt();
    }
}

void keystroke_event(enum scancode scancode)
{
    if (kernel_mode != SHELL && scancode == ESC)
    {
        kernel_mode = SHELL;
        tty_clear();
        tty_set_cursor_pos(0, 0);
        prompt();
    }

    switch (kernel_mode)
    {
    case SHELL:
        break;
    case SCANCODE:
        scancode_keystroke_event(scancode);
        break;
    }
}
