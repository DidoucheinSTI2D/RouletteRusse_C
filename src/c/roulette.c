#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generationPartie(int balles){
    int resultat = roulerRoulette(balles);
    victoireDefaite(resultat);
}

int roulerRoulette(int balles){
    int positionBalle = rand() % 6 + 1;
    printf("Position de la première balle : %d\n", positionBalle);
    int tir = rand() % 6 + 1; 
    printf("Vous avez tiré le numéro : %d\n", tir);

    int touche = 0;
    for (int i = 0; i < balles; i++) {
        if (tir == ((positionBalle + 2*i) % 6) + 1) {
            touche = 1;
            break;
        }
    }

    return touche;
}

void victoireDefaite(int resultat){
    if (resultat) {
        printf("Malheureusement, vous avez perdu.\n");
    } else {
        printf("Félicitations, vous avez survécu !\n");
    }
}
