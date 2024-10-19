#include "x86/idt.h"

#include "x86/types.h"

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void set_idt_gate(int n, u32 handler)
{
    idt[n].low_offset = lo16(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].zeros = 0;
    idt[n].flags = 0x8e;
    idt[n].high_offset = hi16(handler);
}

void set_idt(void)
{
    idt_reg.base = (u32)&idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;

    __asm__ __volatile__("lidtl (%0)" : : "r"(&idt_reg));
}
