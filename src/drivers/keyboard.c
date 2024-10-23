#include "drivers/keyboard.h"

#include "drivers/tty.h"
#include "kernel/kernel.h"
#include "stdlib/def.h"
#include "x86/isr.h"
#include "x86/ports.h"

#define SC_MAX 57

static void keyboard_callback(registers_t regs)
{
    (void)regs;
    /* The PIC leaves us the scancode in port 0x60 */
    enum scancode scancode = port_byte_in(0x60);
    if (scancode > SC_MAX)
        return;

    keystroke_event(scancode);
}

void init_keyboard(void)
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}
