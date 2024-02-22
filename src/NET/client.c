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
            printf("État du jeu reçu: %s\n", serverMessage);

            // Traitement de l'état du jeu
            char *positionsPart = strstr(serverMessage, "Positions: ");
            char *cranPart = strstr(serverMessage, "Cran: ");

            if (positionsPart != NULL && cranPart != NULL) {
                printf("Positions des balles: ");
                char *positionsStart = positionsPart + strlen("Positions: ");
                char *positionsEnd = cranPart;
                while (positionsStart < positionsEnd) {
                    printf("%c ", *positionsStart);
                    positionsStart += 2; // On saute l'espace après chaque position
                }

                int cran;
                sscanf(cranPart, "Cran: %d", &cran);
                printf("\nPosition initiale du cran: %d\n", cran);
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
