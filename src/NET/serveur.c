#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_thread.h>

#include "../includes/thread.h"
#include "../includes/client.h"
#define MAX_PLAYERS 6


int serveurRun (void *data){
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
    int clientID = 0;
    TCPsocket client;
    /* En attente de clients : */
    for(;;){
        /* Lorsqu'un client cherche à se connecter, l'accepter : */
        if((client = SDLNet_TCP_Accept(serveur)) != NULL) {
            ClientInfo* clientInfo = (ClientInfo*)malloc(sizeof(ClientInfo));
            if(clientInfo != NULL){
                clientInfo->id = clientID++;
                clientInfo->socket = client;
                clientInfo->ip = *SDLNet_TCP_GetPeerAddress(client);
                /* Lancer un thread dédié au client : */
                SDL_Thread * thread = SDL_CreateThread(processClient, (void*)clientInfo);
                if(thread == NULL){
                    fprintf(stderr, "Could not create thread: %s\n", SDL_GetError());
                    free(clientInfo);
                }
            }
        } else {
            SDL_Delay(100);
        }
            
    }
    SDLNet_TCP_Close(serveur);
    SDLNet_Quit();
    return 0;
}


