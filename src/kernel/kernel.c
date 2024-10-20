#include "drivers/tty.h"
#include "x86/isr.h"
#include "x86/timer.h"

int main(void)
{
    isr_install();
    tty_clear();
    tty_set_cursor_pos(0, 0);

    // __asm__ __volatile__("sti");
    __asm__ volatile("sti");
    init_timer(50);
}

// faire les dossiers include, obj et dist
