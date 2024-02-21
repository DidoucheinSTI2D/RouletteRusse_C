#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "../includes/bouton.h"
#include "../includes/roulette.h"

void drawBouton(SDL_Surface *ecran, Bouton bouton){
    SDL_Rect rect = bouton.rec;
    Uint32 color = SDL_MapRGB(ecran->format, 100, 100, 100); 
    SDL_FillRect(ecran, &rect, color);

    if (TTF_Init() == -1) {
        fprintf(stderr, "Erreur d'initialisation de TTF : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    
    // ici faut remplacer par le location du font sinon ça marche pas, si vous êtes sur debian remplacer juste Mehdi et Desktop :p
    TTF_Font *font = TTF_OpenFont("/home/mehdi/Desktop/RouletteRusse_C/src/fonts/contrast.ttf", 24); 

    SDL_Color textColor = {255, 10, 10}; 

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, bouton.text, textColor);
    SDL_Rect textLocation = { rect.x + (rect.w - textSurface->w) / 2, rect.y + (rect.h - textSurface->h) / 2, 0, 0 };
    SDL_BlitSurface(textSurface, NULL, ecran, &textLocation);
    SDL_FreeSurface(textSurface);

    TTF_CloseFont(font);
    TTF_Quit(); 
};

void affichage(SDL_Surface *ecran, int *menuStatus, Bouton boutons[], int boutonCount, int boucle) {

// ----------- PARTIE DU MENU -----------
    Bouton jouer = {{600, 330, 200, 50}, "Jouer", 1};
    Bouton couperSon = {{600, 430, 200, 50}, "Couper le son", 2};
    Bouton quitter = {{600, 530, 200, 50}, "Quitter", 3};

    boutons[0] = jouer;
    boutons[1] = couperSon;
    boutons[2] = quitter;
    
    
    if (*menuStatus == 0 || *menuStatus == 8 ){
        Mix_ResumeMusic();
        for (int i = 0; i < 3; ++i) {
            drawBouton(ecran, boutons[i]);
        }
    } else if (*menuStatus == 1) {
        // Difficulté mais tu peux aussi l'utiliser pour Solo / Multi lucas 
        Bouton Facile = {{600, 330, 200, 50}, "Facile (1 balle)", 5};
        Bouton Moyen = {{600, 430, 200, 50}, "Moyen (3 balles)", 6};
        Bouton Difficile = {{400, 530, 600, 50}, "Niveau CC2 de M. Trancho (5 balles)", 7};
        Bouton retourMenu = {{600, 630, 200, 50}, "J'ai peur (Menu)", 8};

        boutons[0] = Facile;
        boutons[1] = Moyen;
        boutons[2] = Difficile;
        boutons[3] = retourMenu;

        for (int i = 0; i < boutonCount; ++i) {
            drawBouton(ecran, boutons[i]);
        }
    } else if (*menuStatus == 2) {
        Bouton jouer = {{600, 330, 200, 50}, "Jouer", 1};
        Bouton remettreSon = {{600, 430, 200, 50}, "Remettre le son", 0};
        Bouton quitter = {{600, 530, 200, 50}, "Quitter", 3};

        boutons[0] = jouer;
        boutons[1] = remettreSon;
        boutons[2] = quitter;

        Mix_PauseMusic();

        for (int i = 0; i < 3; ++i) {
            drawBouton(ecran, boutons[i]);
        }
    } 

// ----------- PARTIE DU JEU -----------

    if(*menuStatus >=5 && *menuStatus <= 11){
        Bouton Rouler = {{100, 600, 200, 50}, "Rouler", 10};
        Bouton Tirer = {{400, 600, 200, 50}, "Tirer", 11};
        Bouton Abandonner = {{700, 600, 600, 50}, "Abandonner", 0};

        boutons[0] = Rouler;
        boutons[1] = Tirer;
        boutons[2] = Abandonner;

        for (int i = 0; i < 3; ++i) {
            drawBouton(ecran, boutons[i]);
        }

    }
    
}