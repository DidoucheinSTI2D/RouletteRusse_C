#define BOUTON_H
#ifdef BOUTON_H

#include <SDL/SDL.h>

typedef struct {
    SDL_Rect rec;
    char* text;
    int nb;
} Bouton;

#endif