#include "kernel/commands.h"

#include "drivers/tty.h"
#include "kernel/modes/mode.h"
#include "stdlib/io.h"
#include "stdlib/string.h"
#include "x86/timer.h"

int help_cmd(char *arg)
{
    tty_puts("List of available commands:");
    for (enum command_id id = 0; id < get_command_count(); id++)
    {
        printf("  %s: %s\n", commands[id].name, commands[id].help);
        if (id == MODE)
        {
            for (size_t i = 0; i < mode_count(); i++)
            {
                printf("    %s: %s\n", kernel_modes[i].name,
                       kernel_modes[i].help);
            }
        }
    }

    tty_puts("\nTo exit any mode, press the ESCAPE key.");
    (void)arg;
    return 0;
}
int clear_cmd(char *arg)
{
    tty_clear();
    tty_set_cursor_pos(0, 0);
    (void)arg;
    return 0;
}
int echo_cmd(char *arg)
{
    tty_puts(arg);
    return 0;
}
int sleep_cmd(char *arg)
{
    if (arg == NULL)
    {
        sleep(1000);
    }
    else
    {
        sleep(atoi(arg));
    }
    return 0;
}
int mode_cmd(char *arg)
{
    mode_switch(arg);
    return 0;
}

int exec_cmd(char *cmd)
{
    char *tmp = cmd;
    while (*tmp && *tmp != ' ')
    {
        tmp++;
    }

    char *arg = NULL;
    if (*tmp != 0)
    {
        *tmp = 0;
        arg = tmp + 1;
    }

    size_t commands_count = get_command_count();

    for (enum command_id id = 0; id < commands_count; id++)
    {
        if (!strcmp(cmd, commands[id].name))
        {
            return commands[id].callback(arg);
        }
    }

    enum tty_color bg = tty_get_bg_color();
    tty_set_bg_color(RED);
    tty_print("ERROR:");
    tty_set_bg_color(bg);
    tty_print(" Unknown command: ");
    tty_puts(cmd);
    return 1;
}

struct command commands[] = {
    [HELP] = { .name = "HELP",
               .help = "Shows this help message.",
               .callback = help_cmd },
    [CLEAR] = { .name = "CLEAR",
                .help = "Clears the terminal",
                .callback = clear_cmd },
    [ECHO] = { .name = "ECHO",
               .help = "Prints the arguemnts in the terminal",
               .callback = echo_cmd },
    [SLEEP] = { .name = "SLEEP",
                .help = "Halts the CPU for the number of milliseconds "
                        "specified as argument",
                .callback = sleep_cmd },
    [MODE] = { .name = "MODE",
               .help = "Enters the specified mode, available modes are:",
               .callback = mode_cmd }
};

size_t get_command_count(void)
{
    return sizeof(commands) / sizeof(struct command);
}
