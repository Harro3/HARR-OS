#ifndef IDT_H
#define IDT_H

#include "types.h"

// Kernel segment selector, index in the gdt to put the idt
#define KERNEL_CS 0x08

// define structures for the idt elements (interrupt handler). This is very
// similar to the gdt.asm in the boot directory
typedef struct
{
    u16 low_offset; // lo16 of handler function address
    u16 sel; // kernel segment selector
    u8 zeros;

    // Bit 7: "Interupt is present"
    // Bits 6-5: privilege level of caller (0 = kernel)
    // Bit 4: Set to 0
    // Bit 3-0: 1110: "32 bit interrupt gate"
    u8 flags;
    u16 high_offset; /// hi16 of handler function address
} __attribute__((packed)) idt_gate_t;

// Pointer to the array of handlers
typedef struct
{
    u16 limit;
    u32 base;
} __attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256
extern idt_gate_t idt[IDT_ENTRIES];
extern idt_register_t idt_reg;

void set_idt_gate(int n, u32 handler);
void set_idt(void);

#endif
