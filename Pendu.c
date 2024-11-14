#include "Pendu.h"
#include <time.h>
#include <stdio.h>
#include <ctype.h>

void afficherEtatJeu(const char *mot_secret, const char *mot_affiche, int vies){
    printf("Le mot chercher: %s \n", mot_affiche);
    printf("Le nobre de vie(s) restante(s): %i \n", vies);
}

int jouerTour(const char *mot_secret, char *mot_affiche, int *vies){
    char input[100];
    int i = 0;
    int lettre = 0;
    int trouve = 0;

    printf("Entrez une lettre ou un mot a teste : ");
    fgets(input, sizeof(input), stdin);
    while(input[i] != '\0') {
        if(input[i] == '\n') {
            input[i] = '\0';
            break;
        }
        i++;
    }
    if(isalpha(input[0])){
        if(input[1] != '\0'){
            lettre = 0;
        }
        else{
            lettre = 1;
        }
    }
    return lettre;

    if(lettre == 1){
        for (int i = 0; i < strlen(mot_secret); i++) {
            if(mot_secret[i] == input) {
                    mot_affiche[i] = input;
                    trouve++;
            }
        }
        if(trouve == 0){
            vies--;
        }
    }
    else{
        if(mot_secret != input){
            vies--;
        }
        else{
            printf("vous avez gagne !");
        }
    }
}

int menuRejouer(){
    char rep[10];
    int rej = 0;
    int vies = 0;
    printf("Voulez vous rejouer ? (oui ou non) ");
    fgets(rep, sizeof(rep), stdin);
    if(rep == 'oui'){
        rej = 1;
        printf("Entrez le nombre de vie souhaite(6 max): ");
        scanf("%i", &vies);
    }
    else{
        rej = 0;
    }

// Fonction pour remplacer les lettres accentu�es par des lettres sans accent
void supprimerAccents(char *mot) {
    for (int i = 0; mot[i] != '\0'; i++) {
        switch (mot[i]) {
            case 'à':
            case 'â':
            case 'ä':   mot[i] = 'a';
                        break;
            case 'é':
            case 'è':
            case 'ê':
            case 'ë':   mot[i] = 'e';
                        break;
            case 'î':
            case 'ï':   mot[i] = 'i';
                        break;
            case 'ô':
            case 'ö':   mot[i] = 'o';
                        break;
            case 'ù':
            case 'û':
            case 'ü':   mot[i] = 'u';
                        break;
            case 'ç':   mot[i] = 'c';
                        break;

        }
    }
}

int chargerMotAleatoire(char *mot, int longueur_max) {
    FILE *fichier = fopen(FICHIER_MOTS, "r");
    if (fichier == NULL) {
        printf("Erreur : impossible de charger le fichier de mots.\n");
        return 0;
    }

    // Compter le nombre de mots dans le fichier
    int nombre_de_mots = 0;
    char buffer[MAX_MOT];
    while (fgets(buffer, MAX_MOT, fichier) != NULL) {
        nombre_de_mots++;
    }

    if (nombre_de_mots == 0) {
        fclose(fichier);
        printf("Erreur : le fichier de mots est vide.\n");
        return 0;
    }

    // Choisir un mot aléatoire
    srand(time(NULL));
    int index_aleatoire = rand() % nombre_de_mots;

    // Aller au mot choisi
    rewind(fichier);
    for (int i = 0; i <= index_aleatoire; i++) {
        fgets(mot, longueur_max, fichier);
    }

    // Retirer le saut de ligne et le remplacer par la fin de chaine
    mot[strcspn(mot, "\n")] = '\0';

    fclose(fichier);
    return 1;
}


void initialiserPartie(char *mot_secret) {
    if (!chargerMotAleatoire(mot_secret, MAX_MOT)) {
        printf("Erreur lors du chargement du mot secret.\n");
        exit(1);
    }
    supprimerAccents(mot_secret); // Suppression des accents dans le mot secret
}
