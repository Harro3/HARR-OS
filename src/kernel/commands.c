#include "kernel/commands.h"

#include "drivers/tty.h"
#include "kernel/modes/mode.h"
#include "stdlib/io.h"
#include "stdlib/string.h"

void help(void)
{
    tty_puts("List of available commands:");
    tty_puts("  HELP: Shows this help message");
    tty_puts("  CLEAR: Clears the terminal");
    tty_puts("  ECHO <arg>: Prints <arg> in the terminal");
    tty_puts("  MODE <mode>: Enters specified mode");

    for (size_t i = 0; i < mode_count(); i++)
    {
        printf("    %s: %s\n", kernel_modes[i].name, kernel_modes[i].help);
    }

    tty_puts("\nTo exit any mode, press the ESCAPE key.");
}

void clear(void)
{
    tty_clear();
    tty_set_cursor_pos(0, 0);
}

void echo(char *str)
{
    tty_puts(str);
}

void parse_command(char *str)
{
    char *tmp = str;
    while (*tmp && *tmp != ' ')
    {
        tmp++;
    }

    char *arg = "";

    if (*tmp != 0)
    {
        *tmp = 0;
        arg = tmp + 1;
    }

    if (!strcmp(str, "HELP"))
    {
        help();
    }
    else if (!strcmp(str, "CLEAR"))
    {
        clear();
    }
    else if (!strcmp(str, "ECHO"))
    {
        echo(arg);
    }
    else if (!strcmp(str, "MODE"))
    {
        mode_switch(arg);
    }
    else
    {
        enum tty_color bg = tty_get_bg_color();
        tty_set_bg_color(RED);
        tty_print("ERROR:");
        tty_set_bg_color(bg);
        tty_print(" Unknown command: ");
        tty_puts(str);
    }
}
