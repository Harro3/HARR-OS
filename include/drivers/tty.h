#ifndef TTY_H
#define TTY_H

#define VIDEO_MEMORY 0xb8000
#define TTY_ROWS 25
#define TTY_COLS 80

#define WHITE_ON_BLACK 0x0f

#define TTY_REG_CTRL 0x3d4
#define TTY_REG_DATA 0x3d5

enum tty_color
{
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    MAROON = 6,
    GRAY = 7,
    DARK_DRAY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

void tty_set_fg_color(enum tty_color color);
void tty_set_bg_color(enum tty_color color);

void tty_set_cursor_pos(int x, int y);
void tty_clear(void);

void tty_print(char *str);
void tty_puts(char *str);
void tty_putc(char c);
void tty_backspace(void);

#endif /* TTY_H */
