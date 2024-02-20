#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_thread.h>

#define MAX_PLAYERS 2

int main (void){
    if(SDLNet_Init() < 0) {
        fprintf(stderr, "Error in SDLNet_Init: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    /* Instructions */
    IPaddress ip;
    /* Ciblage de la création d'un serveur au port 1337 : */
    if(SDLNet_ResolveHost(&ip, NULL, 1337) != 0) {
        fprintf(stderr, "Error in SDLNet_ResolveHost: %s\n",SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    
    TCPsocket serveur;
    /* Ouverture du serveur : */
    if((serveur = SDLNet_TCP_Open(&ip)) == NULL) {
        fprintf(stderr, "Erreur SDLNet_TCP_Open : %s\n",SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    printf("Serveur en attente de connexion...\n");

    TCPsocket client;
    /* En attente de clients : */
    /* Lorsqu'un client cherche à se connecter, l'accepter : */
    if((client = SDLNet_TCP_Accept(serveur)) == NULL) {
    /* Si aucun client, attendre à nouveau. */
        SDL_Delay(100);
    }else{
        /* Lancer un thread dédié au client : */
        SDL_Thread * thread = SDL_CreateThread(processClient, client);
    }
    SDLNet_Quit();
    return EXIT_SUCCESS;
}


