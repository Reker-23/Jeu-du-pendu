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

