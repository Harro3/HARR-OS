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

int help_cmd(char *arg);
int clear_cmd(char *arg);
int echo_cmd(char *arg);
int sleep_cmd(char *arg);
int mode_cmd(char *arg);

int exec_cmd(char *cmd);

#endif
