#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "src/includes/jeu.h"
#include "src/c/menu.c"


const int largeur = 1400;
const int hauteur = 1080;
const char * titre = "Roulette Russe C";
Jeu jeu;

void affichage(SDL_Surface * ecran) {
	int x, y, i;
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
}

int main(){
    int boucle = 1;
    SDL_Surface * ecran = NULL;
    int menuStatus = 0; 
    Bouton buttons[3]; 

    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    ecran = SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (ecran == NULL) {
        fprintf(stderr, "Impossible de mettre en vidéo mode : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption(titre, NULL);
    SDL_Event event;

    while(boucle){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                boucle = 0;
                break;
            case SDL_KEYDOWN : 
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    boucle = 0;
                }
            break;
        }
        affichage(ecran);
        menu(ecran, &menuStatus, buttons, 3);
        SDL_Flip(ecran);
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}