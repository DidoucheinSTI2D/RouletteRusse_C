#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../includes/roulette.h"



void generationPartie(int balles, int chargeur[6], char *etatJeu) {

    srand(time(NULL)); // Assurez-vous d'appeler srand une seule fois au début du programme principal

    for (int i = 0; i<6; i++){
        chargeur[i] = 0;
    }

    for (int i = 0; i < balles; i++) {
        int position;
        do {
            position = rand() % 6;
        } while (chargeur[position] == 1);
        chargeur[position] = 1;
    }

    // Pour débug
    printf("Chargeur : ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", chargeur[i]);
   }
    printf("\n Les balles sont dans les positions suivantes : ");
    for (int i = 0; i < 6; i++) {
        if (chargeur[i] == 1) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
}

int roulerRoulette() {
    int cran = rand() % 6; 
    // pour debug
    printf("Cran sélectionné : %d\n", cran + 1); 
    return cran;
}

int tir(int chargeur[6], int cran) {
    int retour = chargeur[cran];
    return retour;
}

const char* victoireDefaite(int resultat){
    static char message[128]; // Définir une taille suffisante pour le message
    if (resultat) {
        snprintf(message, sizeof(message), "Malheureusement, vous avez perdu.\n");
    } else {
        snprintf(message, sizeof(message), "Félicitations, vous avez survécu !\n");
    }
    return message;
}
