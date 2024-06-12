#include "menu.h"

void render_menu(SDL_Renderer *renderer, TTF_Font *font, int selectedOption) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Color selectedColor = { 255, 255, 0, 255 }; // Cor amarela para a opção selecionada

    // Renderiza a opção "Iniciar"
    if (selectedOption == 0) {
        render_text(renderer, font, "Iniciar", selectedColor, 350, 200);
    } else {
        render_text(renderer, font, "Iniciar", color, 350, 200);
    }

    // Renderiza a opção "Sair"
    if (selectedOption == 1) {
        render_text(renderer, font, "Sair", selectedColor, 350, 300);
    } else {
        render_text(renderer, font, "Sair", color, 350, 300);
    }
}

int handle_menu_events(SDL_Event *event, int *selectedOption) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_UP:
                if (*selectedOption > 0) {
                    (*selectedOption)--;
                }
                break;
            case SDLK_DOWN:
                if (*selectedOption < 1) {
                    (*selectedOption)++;
                }
                break;
            case SDLK_RETURN:
                return *selectedOption == 0 ? 1 : -1; // 1 para iniciar o jogo, -1 para sair
        }
    }
    return 0;
}

