#include "main.h"
#include "menu.h"
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;

void init() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    font = TTF_OpenFont("Arial.ttf", 24); 
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        exit(1);
    }
}

void clean() {
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    init();
    GameState game;
    int running = 1;
    int inMenu = 1;
    int selectedOption = 0;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }

            if (inMenu) {
                int menuResult = handle_menu_events(&event, &selectedOption);
                if (menuResult == 1) {
                    init_game(&game);
                    inMenu = 0;
                } else if (menuResult == -1) {
                    running = 0;
                }
            } else {
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        inMenu = 1;
                    } else if (event.key.keysym.sym == SDLK_p) {
                        if (game.state == RUNNING) {
                            game.state = PAUSED;
                        } else if (game.state == PAUSED) {
                            game.state = RUNNING;
                        }
                    } else if (game.state == RUNNING) {
                        game.snake.direction = event.key.keysym.scancode;
                    }
                }
            }
        }

        if (!inMenu) {
            if (game.state == RUNNING) {
                update_game(&game);
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            render_game(&game, renderer, font);
            SDL_RenderPresent(renderer);
            SDL_Delay(100 - (game.level * 10)); // Aumenta a velocidade do jogo com o nível
        } else {
            render_menu(renderer, font, selectedOption);
            SDL_RenderPresent(renderer);
        }
    }

    clean();
    return 0;
}

