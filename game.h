#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "snake.h"

typedef enum { RUNNING, PAUSED, GAME_OVER } GameStateType;

typedef struct {
    Snake snake;
    Point food;
    int score;
    int level;
    GameStateType state;
} GameState;

void init_game(GameState *game);
void update_game(GameState *game);
void render_game(GameState *game, SDL_Renderer *renderer, TTF_Font *font);
int check_collision(GameState *game);
void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, int x, int y);

#endif

