#include "Pendu.h"
#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void afficherEtatJeu(const char *mot_secret, const char *mot_affiche, int vies){
    printf("Le mot cherche: %s \n", mot_affiche);
    printf("Le nombre de vie(s) restante(s): %i \n", vies);
}

int jouerTour(const char *mot_secret, char *mot_affiche, int *vies){
    char input[100];
    int trouve = 0;

    printf("Entrez une lettre ou un mot a tester : ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Enlever le '\n' de la saisie
    fflush(stdin);

    // Vérification si l'utilisateur a entré une seule lettre
    if (isalpha(input[0]) && input[1] == '\0') {
        // Recherche de la lettre dans le mot secret
        for (int i = 0; i < strlen(mot_secret); i++) {
            if (mot_secret[i] == input[0]) {
                mot_affiche[i] = input[0];
                trouve++;
            }
        }
        if (trouve == 0) {
            (*vies)--;  // Décrémenter les vies si la lettre n'est pas trouvée
        }
    } else {
        // Si l'utilisateur entre un mot complet, on compare
        if (strcmp(mot_secret, input) == 0) {
            printf("Vous avez gagne ! Le mot etait : %s\n", mot_secret);
            return 1; // Le joueur a gagné
        } else {
            (*vies)--;  // Décrémenter les vies si le mot est incorrect
        }
    }
    return 0; // Le jeu continue
}

int menuRejouer(int *vies){
    char rep[10];
    printf("Voulez-vous jouer ? (o ou n) ");
    fgets(rep, sizeof(rep), stdin);
    fflush(stdin);
    rep[strcspn(rep, "\n")] = '\0'; // Enlever le '\n' de la saisie

    if (strcmp(rep, "o") == 0) {
        printf("Entrez le nombre de vies souhaite (6 max): ");
        scanf("%i", vies);
        fflush(stdin);
        return 1;
    } else {
        return 0;
    }
}

void supprimerAccents(char *mot) {
    for (int i = 0; mot[i] != '\0'; i++) {
        switch (mot[i]) {
            case 'à':
            case 'â':
            case 'ä':   mot[i] = 'a'; break;
            case 'é':
            case 'è':
            case 'ê':
            case 'ë':   mot[i] = 'e'; break;
            case 'î':
            case 'ï':   mot[i] = 'i'; break;
            case 'ô':
            case 'ö':   mot[i] = 'o'; break;
            case 'ù':
            case 'û':
            case 'ü':   mot[i] = 'u'; break;
            case 'ç':   mot[i] = 'c'; break;
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

    // Retirer le saut de ligne et le remplacer par la fin de chaîne
    mot[strcspn(mot, "\n")] = '\0';

    fclose(fichier);
    fflush(stdin);
    return 1;
}

void initialiserPartie(char *mot_secret) {
    if (!chargerMotAleatoire(mot_secret, MAX_MOT)) {
        printf("Erreur lors du chargement du mot secret.\n");
        exit(1);
    }
    supprimerAccents(mot_secret); // Suppression des accents dans le mot secret
}

int runPendu() {
    char mot_secret[MAX_MOT];
    char mot_affiche[MAX_MOT];
    int vies = 6;

    do {
        initialiserPartie(mot_secret);

        if (menuRejouer(&vies) == 0) {
            break;
        }

        memset(mot_affiche, '_', strlen(mot_secret));
        mot_affiche[strlen(mot_secret)] = '\0';

        printf("\n--- Nouveau Jeu du Pendu ---\n");

        while (vies > 0) {
            afficherEtatJeu(mot_secret, mot_affiche, vies);
            if (jouerTour(mot_secret, mot_affiche, &vies)) {
                printf("\nFelicitations ! Vous avez trouve le mot : %s\n", mot_secret);
                break;
            }
        }

        if (vies == 0) {
            printf("\nDommage ! Vous avez perdu. Le mot etait : %s\n", mot_secret);
        }

    } while (1);

    printf("\nMerci d'avoir joue au jeu du pendu !\n");
    return 0;
}
