#ifndef KEYBOARD_H
#define KEYBOARD_H

void init_keyboard(void);

enum scancode
{
    ERR = 0x00,
    ESC = 0x01,
    BACKSPACE = 0x0e,
    ENTER = 0x1c,
    LCTRL = 0x1d,
    LSHIFT = 0x2a,
    RSHIFT = 0x36,
    LALT = 0x38,
    SPACE = 0x39,
    CAPSLOCK = 0x3a,

    F1 = 0x3b,
    F2 = 0x3c,
    F3 = 0x3d,
    F4 = 0x3e,
    F5 = 0x3f,
    F6 = 0x40,
    F7 = 0x41,
    F8 = 0x42,
    F9 = 0x43,
    F10 = 0x44,

    UP_ARROW = 0x48,
    LEFT_ARROW = 0x4b,
    RIGHT_ARROW = 0x4d,
    DOWN_ARROW = 0x50

};

#endif
