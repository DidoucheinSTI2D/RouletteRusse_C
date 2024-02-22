#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_thread.h>
#define MAX_PLAYERS 6

#include "../includes/roulette.h"


int clientRun(void *data) {
    if (SDLNet_Init() < 0) {
        fprintf(stderr, "SDLNet_Init Error: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, "localhost", 1337) != 0) {
        fprintf(stderr, "SDLNet_ResolveHost Error: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    TCPsocket serveur;
    if ((serveur = SDLNet_TCP_Open(&ip)) == NULL) {
        fprintf(stderr, "SDLNet_TCP_Open Error: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    char serverMessage[1024];
    int quit = 0;
    while (!quit) {
        memset(serverMessage, 0, sizeof(serverMessage)); // Initialisation du buffer
        if (SDLNet_TCP_Recv(serveur, serverMessage, 1024) > 0) {
            printf("%s\n", serverMessage); // Affiche directement le message reçu

            // Vérification pour sortie
            if (strstr(serverMessage, "vous avez perdu") != NULL || strstr(serverMessage, "vous avez survécu") != NULL) {
                quit = 1; // Sort de la boucle si le jeu est terminé
            }
        } else {
            // Gestion d'erreur ou déconnexion
            printf("Erreur de réception ou serveur déconnecté.\n");
            quit = 1;
        }
    }

    SDLNet_TCP_Close(serveur);
    SDLNet_Quit();
    return 0;
}
