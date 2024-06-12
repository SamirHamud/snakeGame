#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "snake.h"

typedef struct {
    Snake snake;
    Point food;
    int score;
    int level;
} GameState;

void init_game(GameState *game);
void update_game(GameState *game);
void render_game(GameState *game, SDL_Renderer *renderer);
int check_collision(GameState *game);

#endif

