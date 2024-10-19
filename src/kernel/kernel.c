#include "drivers/tty.h"

int main(void)
{
    tty_clear();
    tty_set_cursor_pos(0, 0);

    while (1)
    {
        tty_puts("Bonsoir");
    }
}

// faire les dossiers include, obj et dist
