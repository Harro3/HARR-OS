#include "kernel/modes/mode.h"

#include "drivers/tty.h"
#include "kernel/modes/scancode.h"
#include "kernel/modes/shell.h"
#include "stdlib/io.h"
#include "stdlib/string.h"

struct kernel_mode kernel_modes[] = {
    [SHELL] = { .name = "SHELL",
                .help =
                    "Type commands to perform various actions or switch mode",
                .enter_ptr = shell_enter,
                .keystroke_event_ptr = shell_keystroke_event },
    [SCANCODE] = { .name = "SCANCODE",
                   .help =
                       "Displays scancodes as received by the CPU in real time",
                   .enter_ptr = scancode_enter,
                   .keystroke_event_ptr = scancode_keystroke_event

    }

};
struct kernel_mode *kernel_mode;

size_t mode_count(void)
{
    return sizeof(kernel_modes) / sizeof(struct kernel_mode);
}

enum kernel_mode_index get_mode_id(void)
{
    return (kernel_mode - kernel_modes);
}

void mode_switch(char *mode_name)
{
    size_t count = mode_count();

    for (size_t i = 0; i < count; i++)
    {
        if (!strcmp(mode_name, kernel_modes[i].name))
        {
            kernel_mode = kernel_modes + i;
            kernel_modes[i].enter_ptr();
            return;
        }
    }
    enum tty_color bg = tty_get_bg_color();
    tty_set_bg_color(RED);
    tty_print("ERROR:");
    tty_set_bg_color(bg);
    tty_print(" Unknown mode: ");
    tty_puts(mode_name);
}

void mode_keystroke_event(enum scancode scancode)
{
    kernel_mode->keystroke_event_ptr(scancode);
}

void mode_help(void)
{
    printf("%s: %s\n", kernel_mode->name, kernel_mode->help);
}
