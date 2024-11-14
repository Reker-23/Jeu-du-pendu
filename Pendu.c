#include <stdio.h>
#include <ctype.h>

void afficherEtatJeu(const char *mot_secret, const char *mot_affiche, int vies){
    printf("Le mot chercher: %s \n", mot_affiche);
    printf("Le nobre de vie(s) restante(s): %i \n", vies);
}

int jouerTour(const char *mot_secret, char *mot_affiche, int vies){
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
            printf("vous avez gagné !");
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
        printf("Entrez le nombre de vie souhaité(6 max): ");
        scanf("%i", &vies);
    }
    else{
        rej = 0;
    }
}
