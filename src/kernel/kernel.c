#include "drivers/tty.h"
#include "kernel/commands.h"
#include "string.h"
#include "x86/isr.h"

extern void *end;

void prompt(void)
{
    tty_print("HARR-OS$ ");
}

int main(void)
{
    isr_install();
    irq_install();

    tty_clear();
    tty_set_cursor_pos(0, 0);

    tty_puts("Welcome to HARR-OS !\n");
    help();
    tty_putc('\n');

    /*char asc[256];*/
    /*itoa((int)(&end), asc);*/
    /*tty_print("END ADDR: ");*/
    /*tty_puts(asc);*/

    prompt();
}

void user_input_event(char *input)
{
    tty_putc('\n');

    parse_command(input);
    tty_putc('\n');

    prompt();
}
