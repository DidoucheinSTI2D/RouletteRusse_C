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

    // Création de la chaîne d'état de jeu
    strcpy(etatJeu, "Etat du jeu: Chargeur: "); // Début de l'état du jeu
    for (int i = 0; i < 6; i++) {
        char temp[4]; // Assez grand pour "0 " ou "1 " et le caractère nul
        sprintf(temp, "%d ", chargeur[i]);
        strcat(etatJeu, temp); // Ajout de l'état de chaque position du chargeur
    }

    // Ajout d'informations supplémentaires si nécessaire
    // Par exemple, les positions occupées par les balles pour faciliter le débogage ou l'affichage côté client
    strcat(etatJeu, "\nPositions des balles: ");
    for (int i = 0; i < 6; i++) {
        if (chargeur[i] == 1) {
            char tempPos[4]; // Pour numéro de position + espace
            sprintf(tempPos, "%d ", i + 1);
            strcat(etatJeu, tempPos);
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

void victoireDefaite(int resultat){
    printf("%d ", resultat); // debug line
    if (resultat) {
        printf("Malheureusement, vous avez perdu.\n"); 
    } else {
        printf("Félicitations, vous avez survécu !\n"); 
    }
}