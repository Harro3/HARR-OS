#include "kernel/modes/snake.h"

#include "drivers/tty.h"
#include "io.h"
#include "kernel/modes/mode.h"
#include "memory.h"
#include "string.h"
#include "x86/timer.h"

// FWD
enum snake_direction
{
    UP = 0,
    LEFT,
    DOWN,
    RIGHT
};

struct snake_elt
{
    int x;
    int y;
    struct snake_elt *next;
};

struct snake
{
    struct snake_elt *head;
    struct snake_elt *tail;
    enum snake_direction direction;
    enum snake_direction prev_frame_direction;
    size_t length;
};

struct snake *snake_init(int x, int y);
void snake_destroy(struct snake *snake);
void snake_update(struct snake *snake, int *apple_x, int *apple_y);
void snake_change_dir(struct snake *snake, enum snake_direction dir);
void spawn_apple(struct snake *snake, int *apple_x, int *apple_y);

// MODE API
static struct snake *snake;

#define FRAME_PERIOD_MS 100

int running = 1;

void snake_enter(void)
{
    tty_clear();
    tty_set_cursor_pos(0, 0);
    snake = snake_init(10, 10);

    int apple_x;
    int apple_y;

    running = 1;

    spawn_apple(snake, &apple_x, &apple_y);

    while (running)
    {
        snake_update(snake, &apple_x, &apple_y);
        snake->prev_frame_direction = snake->direction;
        sleep(FRAME_PERIOD_MS);
    }

    tty_clear();
    char *msg = "GAME OVER !";
    tty_set_cursor_pos(TTY_COLS / 2 - strlen(msg) / 2, TTY_ROWS / 2);
    tty_puts(msg);
    tty_set_cursor_pos(0, 0);

    sleep(3000);

    mode_switch("SHELL");
}

void snake_exit(void)
{
    free(snake);

    running = 0;
}

void snake_keystroke_event(enum scancode scancode)
{
    switch (scancode)
    {
    case SC_W:
        snake_change_dir(snake, UP);
        break;
    case SC_A:
        snake_change_dir(snake, LEFT);
        break;
    case SC_S:
        snake_change_dir(snake, DOWN);
        break;
    case SC_D:
        snake_change_dir(snake, RIGHT);
        break;
    default:
        break;
    }
}

// PRIVATE FUNCTIONS
struct snake *snake_init(int x, int y)
{
    struct snake *res = malloc(sizeof(struct snake));
    res->head = malloc(sizeof(struct snake_elt));
    res->tail = res->head;
    res->head->x = x;
    res->head->y = y;
    res->head->next = NULL;
    res->length = 1;
    res->direction = RIGHT;
    res->prev_frame_direction = RIGHT;
    return res;
}

void snake_destroy(struct snake *snake)
{
    while (snake->head)
    {
        struct snake_elt *tmp = snake->head;
        snake->head = snake->head->next;
        free(tmp);
    }
    free(snake);
}

void snake_update(struct snake *snake, int *apple_x, int *apple_y)
{
    if (!snake || !snake->head)
        return;

    int prev_x = snake->head->x;
    int prev_y = snake->head->y;

    switch (snake->direction)
    {
    case UP:
        prev_y--;
        break;
    case LEFT:
        prev_x--;
        break;
    case DOWN:
        prev_y++;
        break;
    case RIGHT:
        prev_x++;
        break;
    }

    int new_head_x = prev_x;
    int new_head_y = prev_y;

    if (new_head_x < 0 || new_head_x >= TTY_COLS || new_head_y < 0
        || new_head_y >= TTY_ROWS)
    {
        running = 0;
    }

    for (struct snake_elt *tmp = snake->head; tmp; tmp = tmp->next)
    {
        if (tmp->x == new_head_x && tmp->y == new_head_y)
        {
            running = 0;
        }
        int tmp_x = tmp->x;
        int tmp_y = tmp->y;
        tmp->x = prev_x;
        tmp->y = prev_y;
        prev_x = tmp_x;
        prev_y = tmp_y;
    }

    if (snake->head->x == *apple_x && snake->head->y == *apple_y)
    {
        struct snake_elt *new = malloc(sizeof(struct snake_elt));
        new->x = prev_x;
        new->y = prev_y;
        new->next = NULL;
        snake->tail->next = new;
        snake->tail = new;
        snake->length++;
        spawn_apple(snake, apple_x, apple_y);
    }
    else
    {
        tty_set_cursor_pos(prev_x, prev_y);
        tty_putc(' ');
    }

    tty_set_cursor_pos(snake->head->x, snake->head->y);
    tty_putc('#');

    tty_set_cursor_pos(0, 0);
}

void snake_change_dir(struct snake *snake, enum snake_direction dir)
{
    switch (dir)
    {
    case LEFT:
        if (snake->prev_frame_direction != RIGHT)
            snake->direction = LEFT;
        break;
    case DOWN:
        if (snake->prev_frame_direction != UP)
            snake->direction = DOWN;
        break;
    case RIGHT:
        if (snake->prev_frame_direction != LEFT)
            snake->direction = RIGHT;
        break;
    case UP:
        if (snake->prev_frame_direction != DOWN)
            snake->direction = UP;
        break;
    }
}

void idx_to_coords(int *idx, int *x, int *y)
{
    *x = *idx % TTY_COLS;
    *y = *idx / TTY_COLS;
}

void spawn_apple(struct snake *snake, int *apple_x, int *apple_y)
{
    const int total_cells = TTY_ROWS * TTY_COLS;

    int valid_pos_count = total_cells - snake->length;
    int current_tick = get_current_tick();

    int pos = current_tick % valid_pos_count;
    int x;
    int y;
    int pos_is_valid = 0;
    while (!pos_is_valid)
    {
        idx_to_coords(&pos, &x, &y);
        pos_is_valid = 1;
        for (struct snake_elt *tmp = snake->head; tmp; tmp = tmp->next)
        {
            if (tmp->x == x && tmp->y == y)
            {
                pos_is_valid = 0;
                pos++;
                break;
            }
        }
    }

    *apple_x = x;
    *apple_y = y;
    tty_set_fg_color(RED);
    tty_set_cursor_pos(x, y);
    tty_putc('#');
    tty_set_default_color();
}
