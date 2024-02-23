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

    char messageConfirmation[1024];
    if (SDLNet_TCP_Recv(serveur, messageConfirmation, 1024) > 0) {
        printf("%s", messageConfirmation); // Affiche le message de confirmation de connexion
    } else {
        fprintf(stderr, "Erreur de réception du message de confirmation.\n");
        SDLNet_TCP_Close(serveur);
        SDLNet_Quit();
        exit(EXIT_FAILURE);
    }
        // Procédez avec le reste de la logique client...
        char serverMessage[1024];
        if (SDLNet_TCP_Recv(serveur, serverMessage, 1024) > 0) {
            printf("%s\n", serverMessage); // Affiche le message envoyé par le serveur
        } else {
            fprintf(stderr, "Erreur de réception du message du serveur.\n");
        }
        /* BOUCLE POUR RECEVOIR PLUSIEURS MESSAGES
        int quit = 0;
        while (!quit) {
            memset(serverMessage, 0, sizeof(serverMessage)); // Initialisation du buffer
    
            // Réception des données du serveur
            int receivedBytes = SDLNet_TCP_Recv(serveur, serverMessage, 1024);
            if (receivedBytes > 0) {
                printf("%s\n", serverMessage); // Affiche directement le message reçu

                // Vérification pour sortie
                if (strstr(serverMessage, "Vous avez perdu.") != NULL || strstr(serverMessage, "Vous avez gagné !") != NULL) {
                    quit = 1; // Sort de la boucle si le jeu est terminé
                }
            } else if (receivedBytes == 0) {
                // Si la connexion est fermée par le serveur
                printf("Le serveur a fermé la connexion.\n");
                quit = 1;
            } else {
                // Gestion d'erreur de réception
                printf("Erreur de réception ou serveur déconnecté.\n");
                quit = 1;
            }
        }*/

    
    


    SDLNet_TCP_Close(serveur);
    SDLNet_Quit();
    return 0;
}
