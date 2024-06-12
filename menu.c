#include "menu.h"

void render_menu(SDL_Renderer *renderer, int selectedOption) {
    // Limpa a tela com a cor azul
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);

    // Define a cor dos retângulos
    SDL_Color color;
    if (selectedOption == 0) {
        color = (SDL_Color){ 255, 255, 0, 255 }; // Amarelo para "Start" selecionado
    } else {
        color = (SDL_Color){ 255, 255, 255, 255 }; // Branco para "Start" não selecionado
    }

    // Renderiza o retângulo "Start"
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect startRect = { 300, 200, 200, 50 };
    SDL_RenderFillRect(renderer, &startRect);

    if (selectedOption == 1) {
        color = (SDL_Color){ 255, 255, 0, 255 }; // Amarelo para "Exit" selecionado
    } else {
        color = (SDL_Color){ 255, 255, 255, 255 }; // Branco para "Exit" não selecionado
    }

    // Renderiza o retângulo "Exit"
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect exitRect = { 300, 300, 200, 50 };
    SDL_RenderFillRect(renderer, &exitRect);
}

int handle_menu_events(SDL_Event *event) {
    static int selectedOption = 0;
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_UP:
                selectedOption = 0; // Seleciona "Start"
                break;
            case SDLK_DOWN:
                selectedOption = 1; // Seleciona "Exit"
                break;
            case SDLK_RETURN:
                return selectedOption == 0 ? 1 : -1; // 1 para iniciar o jogo, -1 para sair
        }
    }
    return selectedOption;
}

