#ifndef COMMANDS_H
#define COMMANDS_H

#include "stdlib/def.h"

typedef int (*command_callback_t)(char *);

enum command_id
{
    HELP = 0,
    CLEAR,
    ECHO,
    SLEEP,
    MODE
};

struct command
{
    char *name;
    char *help;
    command_callback_t callback;
};

extern struct command commands[];

size_t get_command_count(void);

int exec_cmd(char *cmd);

#endif
