#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_thread.h>
#define MAX_PLAYERS 6


int main (void){
    if(SDLNet_Init() < 0) {
        fprintf(stderr, "Error in SDLNet_Init: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    /* Instructions */
    IPaddress ip;
    /* Ciblage d'une machine distante au port 1337 : */
    /* Remplacer "localhost" par le nom de la machine */
    if(SDLNet_ResolveHost(&ip, "localhost", 1337) != 0) {
        fprintf(stderr, "Error in SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    /* Affichage de l'adresse IP de la cible : */
    Uint32 intip = SDL_SwapBE32(ip.host);
    printf("Target IP is %s at %d.%d.%d.%d:%u\n", SDLNet_ResolveIP(&ip), intip >> 24, (intip >> 16) & 0xff,(intip >> 8) & 0xff, intip & 0xff, ip.port);
    
    TCPsocket serveur;
    /* Connexion à la machine distante : */
    if((serveur = SDLNet_TCP_Open(&ip)) == NULL) {
        fprintf(stderr, "Erreur SDLNet_TCP_Open : %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    char choix;
    while(choix != 'q'){
        printf("Entrez votre choix (q pour quitter): ");
        scanf(" %c", &choix);

        if(SDLNet_TCP_Send(serveur, &choix, sizeof(choix)) < sizeof(choix)) {
            fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
            // Gérer l'erreur d'envoi
            break;
        }
    }

    SDLNet_TCP_Close(serveur);
    SDLNet_Quit();
    return EXIT_SUCCESS;
}

