#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_thread.h>


#include "../includes/client.h"
#include "../includes/roulette.h"
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
    
    int chargeur[6];
    char etatJeu[256];
    // Générer l'état de la partie ici avant d'accepter les clients
    generationPartie(1, chargeur, etatJeu);
    // Boucle principale du serveur pour accepter les clients
    while(1){
        TCPsocket client = SDLNet_TCP_Accept(serveur);
        if(client != NULL) {
            char* messageConnexion = "Connexion établie avec succès\n";
            SDLNet_TCP_Send(client, messageConnexion, strlen(messageConnexion) + 1); // +1 pour inclure le caractère null de fin de chaîne
        
            // Simuler la génération du résultat de la roulette
            int cran = roulerRoulette();
            int resultat = tir(chargeur, cran);
        
            // Construire le message de résultat
            char messageResultat[256];
            if (resultat == 1) {
                sprintf(messageResultat, "Vous avez gagné !\n");
            } else {
                sprintf(messageResultat, "Vous avez perdu.\n");
            }
    
            // Envoyer le message de résultat au client
            SDLNet_TCP_Send(client, messageResultat, strlen(messageResultat) + 1);
        } else {
            SDL_Delay(100); // Pour éviter une utilisation élevée du CPU
        }
    }

    SDLNet_TCP_Close(serveur);
    SDLNet_Quit();
    return 0;
}


