#include "drivers/keyboard.h"

#include "drivers/tty.h"
#include "kernel/kernel.h"
#include "stdlib/def.h"
#include "x86/isr.h"
#include "x86/ports.h"

#define BUF_SIZE 256

enum scancode last_pressed;

static struct
{
    char input[BUF_SIZE + 1];
    size_t index;

} stream;

#define SC_MAX 57
const char sc_ascii[] = { 0,    0,   '1', '2',  '3', '4', '5', '6', '7',  '8',
                          '9',  '0', '-', '=',  0,   0,   'Q', 'W', 'E',  'R',
                          'T',  'Y', 'U', 'I',  'O', 'P', '[', ']', '\n', 0,
                          'A',  'S', 'D', 'F',  'G', 'H', 'J', 'K', 'L',  ';',
                          '\'', '`', 0,   '\\', 'Z', 'X', 'C', 'V', 'B',  'N',
                          'M',  ',', '.', '/',  0,   0,   0,   ' ' };

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

static void keyboard_callback(registers_t regs)
{
    (void)regs;
    /* The PIC leaves us the scancode in port 0x60 */
    enum scancode scancode = port_byte_in(0x60);

    keystroke_event(scancode);
    last_pressed = scancode;
    if (kernel_mode != SHELL)
    {
        return;
    }

    if (scancode > SC_MAX)
        return;

    if (scancode == BACKSPACE)
    {
        stream_pop();
    }
    else
    {
        stream_push(sc_ascii[scancode]);
    }
}

void init_keyboard(void)
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}
