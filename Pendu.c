#include "Pendu.h"
#include <time.h>

// Fonction pour remplacer les lettres accentuées par des lettres sans accent
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

