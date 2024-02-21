#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../includes/roulette.h"

void generationPartie(int balles){
    int chargeur[6];
    int position, tir;
    int cran;

    for (int i = 0; i < balles;i++){
        do {
            position = rand() % 6;
        } while (chargeur[position] == 1);

        chargeur[position] = 1;
    }
    cran = roulerRoulette();

    // Pour débug
    printf("Les balles sont dans les positions suivantes : ");
    for (int i = 0; i < 6; i++){
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
    return chargeur[cran];
}

void victoireDefaite(int resultat){
    if (resultat) {
        printf("Malheureusement, vous avez perdu.\n");   
    } else {
        printf("Félicitations, vous avez survécu !\n"); 
    }
}
