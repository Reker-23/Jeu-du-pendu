#ifndef PENDU_H
#define PENDU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes
#define MAX_MOT 100
#define MAX_VIES 6
#define FICHIER_MOTS "listeDeMotsFrancais.txt"


int chargerMotAleatoire(char *mot, int longueur_max);


void initialiserPartie(char *mot_secret);


void afficherEtatJeu(const char *mot_secret, const char *mot_affiche, int vies);


int jouerTour(const char *mot_secret, char *mot_affiche);


int menuRejouer();

int runPendu();

#endif // PENDU_H
