#include "drivers/tty.h"

#include "string.h"
#include "x86/ports.h"

// FWD
int coords_to_offset(int x, int y);
int offset_to_x(int offset);
int offset_to_y(int offset);
int is_offset_overflow(int offset);
int is_coords_overflow(int x, int y);
void set_cursor_offset(int offset);
int get_cursor_offset(void);
void tty_set_cursor_pos(int x, int y);
int vmem_print_char(int offset, char c);
int get_attr(void);

enum tty_color tty_fg_color = WHITE;
enum tty_color tty_bg_color = BLACK;

// PUBLIC API
void tty_set_fg_color(enum tty_color color)
{
    tty_fg_color = color;
}

void tty_set_bg_color(enum tty_color color)
{
    if (color > 7)
        return;
    tty_bg_color = color;
}

void tty_clear(void)
{
    for (int i = 0; i < TTY_ROWS * TTY_COLS; i++)
    {
        char *vmem = (char *)VIDEO_MEMORY;
        vmem[i * 2] = ' ';
        vmem[i * 2 + 1] = get_attr();
    }
}

void tty_print(char *str)
{
    int offset = get_cursor_offset();

    while (*str && !is_offset_overflow(offset))
    {
        offset = vmem_print_char(offset, *str);
        str++;
    }
}

void tty_putc(char c)
{
    int offset = get_cursor_offset();
    vmem_print_char(offset, c);
}

void tty_puts(char *str)
{
    tty_print(str);
    tty_putc('\n');
}

// PRIVATE API

#define CUR_HIGH 14
#define CUR_LOW 15

int get_attr(void)
{
    return (tty_bg_color << 4) + tty_fg_color;
}

int coords_to_offset(int x, int y)
{
    return (y * TTY_COLS + x) << 1;
}

int offset_to_x(int offset)
{
    return (offset >> 1) % TTY_COLS;
}

int offset_to_y(int offset)
{
    return (offset >> 1) / TTY_COLS;
}

int is_offset_overflow(int offset)
{
    return (offset >> 1) >= TTY_ROWS * TTY_COLS;
}

int is_coords_overflow(int x, int y)
{
    return coords_to_offset(x, y) >= TTY_ROWS * TTY_COLS;
}

void set_cursor_offset(int offset)
{
    offset >>= 1; // div by 2 to account for color encoding

    port_byte_out(TTY_REG_CTRL, CUR_HIGH);
    port_byte_out(TTY_REG_DATA, offset >> 8);
    port_byte_out(TTY_REG_CTRL, CUR_LOW);
    port_byte_out(TTY_REG_DATA, offset & 0xff);
}

int get_cursor_offset(void)
{
    port_byte_out(TTY_REG_CTRL, CUR_HIGH);
    int offset = port_byte_in(TTY_REG_DATA) << 8;
    port_byte_out(TTY_REG_CTRL, CUR_LOW);
    offset += port_byte_in(TTY_REG_DATA);

    return offset << 1;
}

void tty_set_cursor_pos(int x, int y)
{
    set_cursor_offset(coords_to_offset(x, y));
}

int vmem_print_char(int offset, char c)
{
    char *vmem = (char *)VIDEO_MEMORY;
    if (is_offset_overflow(offset))
    {
        return offset;
    }

    if (c == '\n')
    {
        offset >>= 1;
        offset = offset + TTY_COLS - offset % TTY_COLS;
        offset <<= 1;
    }
    else
    {
        vmem[offset] = c;
        vmem[offset + 1] = get_attr();
        offset += 2;
    }

    if (is_offset_overflow(offset))
    {
        for (int i = 1; i < TTY_ROWS; i++)
        {
            char *dest = vmem + coords_to_offset(0, i - 1);
            char *src = vmem + coords_to_offset(0, i);
            memmove(dest, src, TTY_COLS * 2);
        }
        char *last_line = vmem + coords_to_offset(0, TTY_ROWS - 1);
        for (int i = 0; i < TTY_COLS * 2; i++)
        {
            last_line[i] = 0;
        }

        offset = coords_to_offset(0, TTY_ROWS - 1);
    }

    set_cursor_offset(offset);
    return offset;
}
