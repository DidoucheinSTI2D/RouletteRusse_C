#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "../includes/bouton.h"

void drawBouton(SDL_Surface *screen, Bouton bouton){
    SDL_Rect rect = bouton.rec;
    Uint32 color = SDL_MapRGB(screen->format, 100, 100, 100); 
    SDL_FillRect(screen, &rect, color);

    if (TTF_Init() == -1) {
        fprintf(stderr, "Erreur d'initialisation de TTF : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    
    // ici faut remplacer par le location du font sinon ça marche pas, si vous êtes sur debian remplacer juste Mehdi et Desktop :p
    TTF_Font *font = TTF_OpenFont("/home/lucas/Bureau/GitHub_Russian/RouletteRusse_C/src/fonts/contrast.ttf", 24); 

    SDL_Color textColor = {255, 10, 10}; 

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, bouton.text, textColor);
    SDL_Rect textLocation = { rect.x + (rect.w - textSurface->w) / 2, rect.y + (rect.h - textSurface->h) / 2, 0, 0 };
    SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
    SDL_FreeSurface(textSurface);

    TTF_CloseFont(font);
    TTF_Quit(); 

};

void menu(SDL_Surface *screen, int *menuStatus, Bouton boutons[], int boutonCount) {

    Bouton jouer = {{600, 330, 200, 50}, "Jouer", 1};
    Bouton couperSon = {{600, 430, 200, 50}, "Couper le son", 2};
    Bouton quitter = {{600, 530, 200, 50}, "Quitter", 3};

    boutons[0] = jouer;
    boutons[1] = couperSon;
    boutons[2] = quitter;

    for (int i = 0; i < boutonCount; ++i) {
        drawBouton(screen, boutons[i]);
    }
    
    
}