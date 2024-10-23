#ifndef SHELL_H
#define SHELL_H

#include "kernel/modes/shell.h"

#include "drivers/keyboard.h"
#include "drivers/tty.h"
#include "kernel/commands.h"
#include "kernel/modes/mode.h"

#define BUF_SIZE 256

static struct
{
    char input[BUF_SIZE + 1];
    size_t index;

} stream;

const char sc_ascii[] = { 0,    0,   '1', '2',  '3', '4', '5', '6', '7',  '8',
                          '9',  '0', '-', '=',  0,   0,   'Q', 'W', 'E',  'R',
                          'T',  'Y', 'U', 'I',  'O', 'P', '[', ']', '\n', 0,
                          'A',  'S', 'D', 'F',  'G', 'H', 'J', 'K', 'L',  ';',
                          '\'', '`', 0,   '\\', 'Z', 'X', 'C', 'V', 'B',  'N',
                          'M',  ',', '.', '/',  0,   0,   0,   ' ' };

void prompt(void)
{
    tty_print("HARR-OS$ ");
}
void shell_input_event(char *input)
{
    tty_putc('\n');

    parse_command(input);
    if (get_mode_id() != SHELL)
    {
        return;
    }

    tty_putc('\n');

    prompt();
}
static void stream_flush(void)
{
    stream.input[stream.index] = 0;
    shell_input_event(stream.input);
    stream.index = 0;
}

static void stream_push(char c)
{
    if (stream.index >= BUF_SIZE)
    {
        stream_flush();
    }

    if (c == 0)
    {
        return;
    }

    if (c == '\n')
    {
        stream_flush();
    }
    else
    {
        tty_putc(c);
        stream.input[stream.index] = c;
        stream.index++;
    }
}

static void stream_pop(void)
{
    if (stream.index > 0)
    {
        tty_backspace();
        stream.index--;
    }
}

void shell_enter(void)
{
    tty_clear();
    tty_set_cursor_pos(0, 0);
    tty_puts("Welcome to HARR-OS !\n");
    help();
    tty_putc('\n');

    prompt();
}

void shell_keystroke_event(enum scancode scancode)
{
    if (scancode == BACKSPACE)
    {
        stream_pop();
    }
    else
    {
        stream_push(sc_ascii[scancode]);
    }
}

#endif
