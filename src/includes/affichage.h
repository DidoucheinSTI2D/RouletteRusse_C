#ifndef AFFICHAGE_H
    #define AFFICHAGE_h

#include "bouton.h"

void drawBouton(SDL_Surface *ecran, Bouton bouton);
void affichage(SDL_Surface *ecran, int *menuStatus, Bouton boutons[], int boutonCount, int boucle);

#endif