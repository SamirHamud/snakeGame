#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void render_menu(SDL_Renderer *renderer, TTF_Font *font, int selectedOption);
int handle_menu_events(SDL_Event *event, int *selectedOption);

#endif

