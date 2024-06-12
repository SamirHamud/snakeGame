#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point *body;
    int length;
    int direction;
} Snake;

void init_snake(Snake *snake);
void move_snake(Snake *snake);
void grow_snake(Snake *snake);
void render_snake(Snake *snake, SDL_Renderer *renderer);

#endif

