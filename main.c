#include "main.h"
#include "menu.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void init() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void clean() {
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
                selectedOption = handle_menu_events(&event);
                if (selectedOption == 1) {
                    init_game(&game);
                    inMenu = 0;
                } else if (selectedOption == -1) {
                    running = 0;
                }
            } else {
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        inMenu = 1;
                    } else {
                        game.snake.direction = event.key.keysym.scancode;
                    }
                }
            }
        }

        if (!inMenu) {
            update_game(&game);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            render_game(&game, renderer);
            SDL_RenderPresent(renderer);
            SDL_Delay(100); // Controla a velocidade do jogo
        } else {
            render_menu(renderer, selectedOption);
            SDL_RenderPresent(renderer);
        }
    }

    clean();
    return 0;
}

