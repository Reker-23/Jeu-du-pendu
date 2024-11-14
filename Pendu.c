#include "Pendu.h"
#include <time.h>

// Fonction pour remplacer les lettres accentu�es par des lettres sans accent
void supprimerAccents(char *mot) {
    for (int i = 0; mot[i] != '\0'; i++) {
        switch (mot[i]) {
            case '�':
            case '�':
            case '�':   mot[i] = 'a';
                        break;
            case '�':
            case '�':
            case '�':
            case '�':   mot[i] = 'e';
                        break;
            case '�':
            case '�':   mot[i] = 'i';
                        break;
            case '�':
            case '�':   mot[i] = 'o';
                        break;
            case '�':
            case '�':
            case '�':   mot[i] = 'u';
                        break;
            case '�':   mot[i] = 'c';
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

    // Choisir un mot al�atoire
    srand(time(NULL));
    int index_aleatoire = rand() % nombre_de_mots;

    // Aller au mot choisi
    rewind(fichier);
    for (int i = 0; i <= index_aleatoire; i++) {
        fgets(mot, longueur_max, fichier);
    }

    // Retirer le saut de ligne et le remplacer par la fin de cha�ne
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
