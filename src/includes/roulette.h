#ifndef ROULETTE_H  
    #define ROULETTE_H

void generationPartie(int balles, int chargeur[6], char *etatJeu);
int roulerRoulette();
int tir(int chargeur[6], int cran);
const char* victoireDefaite(int resultat);

#endif