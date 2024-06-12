#include "snake.h"
#include <stdlib.h>
#include <string.h>

void init_snake(Snake *snake) {
    snake->length = 1;
    snake->body = (Point *)malloc(sizeof(Point) * 100); // capacidade inicial
    snake->body[0].x = 10;
    snake->body[0].y = 10;
    snake->direction = SDL_SCANCODE_RIGHT;
}

void move_snake(Snake *snake) {
    // Movimenta o corpo da snake
    for (int i = snake->length - 1; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }

    // Movimenta a cabeça da snake
    switch (snake->direction) {
        case SDL_SCANCODE_UP:
            snake->body[0].y -= 1;
            break;
        case SDL_SCANCODE_DOWN:
            snake->body[0].y += 1;
            break;
        case SDL_SCANCODE_LEFT:
            snake->body[0].x -= 1;
            break;
        case SDL_SCANCODE_RIGHT:
            snake->body[0].x += 1;
            break;
    }
}

void grow_snake(Snake *snake) {
    snake->length++;
    // Aloca mais memória se necessário
    if (snake->length % 100 == 0) {
        snake->body = (Point *)realloc(snake->body, sizeof(Point) * (snake->length + 100));
    }
}

void render_snake(Snake *snake, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < snake->length; i++) {
        SDL_Rect rect = { snake->body[i].x * 20, snake->body[i].y * 20, 20, 20 };
        SDL_RenderFillRect(renderer, &rect);
    }
}

