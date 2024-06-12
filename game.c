#include "game.h"
#include <stdlib.h>

void init_game(GameState *game) {
    init_snake(&game->snake);
    game->food.x = rand() % 40;
    game->food.y = rand() % 30;
    game->score = 0;
    game->level = 1;
}

void update_game(GameState *game) {
    move_snake(&game->snake);

    // Verifica colisão com a comida
    if (game->snake.body[0].x == game->food.x && game->snake.body[0].y == game->food.y) {
        grow_snake(&game->snake);
        game->score += 10;
        game->food.x = rand() % 40;
        game->food.y = rand() % 30;
    }

    // Verifica colisão com as bordas
    if (game->snake.body[0].x < 0 || game->snake.body[0].x >= 40 || game->snake.body[0].y < 0 || game->snake.body[0].y >= 30) {
        init_game(game); // Reinicia o jogo
    }

    // Verifica colisão com si mesmo
    for (int i = 1; i < game->snake.length; i++) {
        if (game->snake.body[0].x == game->snake.body[i].x && game->snake.body[0].y == game->snake.body[i].y) {
            init_game(game); // Reinicia o jogo
        }
    }
}

void render_game(GameState *game, SDL_Renderer *renderer) {
    render_snake(&game->snake, renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = { game->food.x * 20, game->food.y * 20, 20, 20 };
    SDL_RenderFillRect(renderer, &rect);
}

int check_collision(GameState *game) {
    // Verifica se a snake colidiu com a comida
    return (game->snake.body[0].x == game->food.x && game->snake.body[0].y == game->food.y);
}

