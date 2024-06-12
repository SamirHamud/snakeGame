#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>

void render_menu(SDL_Renderer *renderer, int selectedOption);
int handle_menu_events(SDL_Event *event);

#endif

