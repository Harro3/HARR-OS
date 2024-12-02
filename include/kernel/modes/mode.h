#ifndef MODE_H
#define MODE_H

#include "drivers/keyboard.h"
#include "stdlib/def.h"
#include "x86/types.h"

typedef void (*enter_mode_t)(void);
typedef void (*keystroke_event_mode_t)(enum scancode);

struct kernel_mode
{
    char *name;
    char *help;
    enter_mode_t enter_ptr;
    keystroke_event_mode_t keystroke_event_ptr;
};

enum kernel_mode_index
{
    SHELL = 0,
    SCANCODE,
    SNAKE,
};

extern struct kernel_mode kernel_modes[];
extern struct kernel_mode *kernel_mode;

enum kernel_mode_index get_mode_id(void);
size_t mode_count(void);
void mode_switch(char *mode_name);
void mode_keystroke_event(enum scancode scancode);
void mode_help(void);

#endif
