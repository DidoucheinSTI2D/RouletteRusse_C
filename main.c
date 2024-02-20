#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_mixer.h>

#include "src/includes/jeu.h"
#include "src/includes/affichage.h"

const int largeur = 1400;
const int hauteur = 1080;
const char * titre = "Roulette Russe C";
Jeu jeu;

void affichageSDL(SDL_Surface * ecran) {
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
}

int main(){
    srand( time( NULL ) );
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    Mix_Music *music = Mix_LoadMUS("/home/mehdi/Desktop/RouletteRusse_C/src/sound/music/Ninho_Menu.mp3");
    if (!music) {
        printf("Impossible de lancer la music : %s\n", Mix_GetError());
    }

    if (Mix_PlayMusic(music, -1) == -1) {
        printf("Impossible de jouer la musique : %s\n", Mix_GetError());
    }

    int boucle = 1;
    SDL_Surface * ecran = NULL;
    int menuStatus = 0; 
    Bouton boutons[3]; 
    int nombreBouton = 3;

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
            case SDL_MOUSEBUTTONDOWN:
                for (int i = 0; i < nombreBouton; ++i) {
                    if (menuStatus == 1){
                        nombreBouton = 4;
                    } 
                    if (event.button.x >= boutons[i].rec.x && event.button.x <= (boutons[i].rec.x + boutons[i].rec.w) &&
                        event.button.y >= boutons[i].rec.y && event.button.y <= (boutons[i].rec.y + boutons[i].rec.h)) {
                        menuStatus = boutons[i].nb;
                        /// printf("Status actuel : %d", menuStatus); // Debug line
                        if (menuStatus == 3){
                            boucle = 0;
                        }
                    }
                }
                break;
            case SDL_KEYDOWN : 
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    boucle = 0;
                }
            break;
        }
        affichageSDL(ecran);
        affichage(ecran, &menuStatus, boutons, nombreBouton, 1);
        SDL_Flip(ecran);
    }

    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();
    return EXIT_SUCCESS;
}