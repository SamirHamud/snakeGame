#include "game.h"
#include <stdlib.h>
#include <string.h>

void init_game(GameState *game) {
    init_snake(&game->snake);
    game->food.x = rand() % 40;
    game->food.y = rand() % 30;
    game->score = 0;
    game->level = 1;
    game->state = RUNNING;
}

void update_game(GameState *game) {
    if (game->state == RUNNING) {
        move_snake(&game->snake);

        // Verifica colisão com a comida
        if (game->snake.body[0].x == game->food.x && game->snake.body[0].y == game->food.y) {
            grow_snake(&game->snake);
            game->score += 10;
            game->food.x = rand() % 40;
            game->food.y = rand() % 30;

            // Aumenta o nível a cada 50 pontos
            if (game->score % 50 == 0) {
                game->level++;
            }
        }

        // Verifica colisão com as bordas
        if (game->snake.body[0].x < 0 || game->snake.body[0].x >= 40 || game->snake.body[0].y < 0 || game->snake.body[0].y >= 30) {
            game->state = GAME_OVER;
        }

        // Verifica colisão com si mesmo
        for (int i = 1; i < game->snake.length; i++) {
            if (game->snake.body[0].x == game->snake.body[i].x && game->snake.body[0].y == game->snake.body[i].y) {
                game->state = GAME_OVER;
            }
        }
    }
}

void render_game(GameState *game, SDL_Renderer *renderer, TTF_Font *font) {
    render_snake(&game->snake, renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = { game->food.x * 20, game->food.y * 20, 20, 20 };
    SDL_RenderFillRect(renderer, &rect);

    // Renderiza a pontuação e o nível
    char scoreText[50];
    sprintf(scoreText, "Score: %d", game->score);
    SDL_Color color = { 255, 255, 255, 255 };
    render_text(renderer, font, scoreText, color, 10, 10);

    sprintf(scoreText, "Level: %d", game->level);
    render_text(renderer, font, scoreText, color, 10, 40);

    if (game->state == PAUSED) {
        render_text(renderer, font, "PAUSED", color, 350, 250);
    } else if (game->state == GAME_OVER) {
        render_text(renderer, font, "GAME OVER", color, 350, 250);
    }
}

int check_collision(GameState *game) {
    // Verifica se a snake colidiu com a comida
    return (game->snake.body[0].x == game->food.x && game->snake.body[0].y == game->food.y);
}

void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, int x, int y) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dest = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

