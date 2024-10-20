#include "x86/timer.h"

#include "x86/isr.h"
#include "x86/ports.h"

u32 tick = 0;

static void timer_callback(registers_t regs)
{
    (void)regs;
    tick++;
}

u32 get_cpu_tick(void)
{
    return tick;
}

void init_timer(u32 freq)
{
    register_interrupt_handler(IRQ0, timer_callback);

    // Get the PIT val, with 1193180Hz clock
    // the PIT is Programmable Interval Timer,
    // It is a chip can can interrupt on IRQ0 at user defined intervals
    u32 divisor = 1193180 / freq;

    u8 lo = (u8)(divisor & 0xFF);
    u8 hi = (u8)((divisor >> 8) & 0xFF);

    // telling the frequency to the PIT chip
    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, lo);
    port_byte_out(0x40, hi);
}
