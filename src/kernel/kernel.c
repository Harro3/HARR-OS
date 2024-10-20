#include "drivers/tty.h"
#include "x86/isr.h"

void prompt(void)
{
    tty_print("ECHOSH$ ");
}

int main(void)
{
    isr_install();
    irq_install();

    tty_clear();
    tty_set_cursor_pos(0, 0);
    prompt();
}

void user_input_event(char *input)
{
    tty_putc('\n');
    tty_puts(input);
    prompt();
}
