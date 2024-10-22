#include "drivers/tty.h"
#include "kernel/commands.h"
#include "stdlib/io.h"
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

    printf("END PTR: 0x%x\n", &end);

    prompt();
}

void user_input_event(char *input)
{
    tty_putc('\n');

    parse_command(input);
    tty_putc('\n');

    prompt();
}
