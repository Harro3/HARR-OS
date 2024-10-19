#include "drivers/tty.h"
#include "string.h"
#include "x86/isr.h"

int main(void)
{
    isr_install();
    tty_clear();
    tty_set_cursor_pos(0, 0);

    char buf[4];

    for (int i = 10; i > -1; i--)
    {
        int c = 10 / i;

        itoa(c, buf);
        tty_puts(buf);
    }
    /* Test the interrupts */
    /*__asm__ __volatile__("int $2");*/
    /*__asm__ __volatile__("int $3");*/
}

// faire les dossiers include, obj et dist
