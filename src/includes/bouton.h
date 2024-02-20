#ifndef BOUTON_H
    #define BOUTON_H

#include <SDL/SDL.h>

typedef struct {
    SDL_Rect rec;
    char* text;
    int nb;
} Bouton;

#endif