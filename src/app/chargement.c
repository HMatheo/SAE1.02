#include "chargement.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


Offre** chargement(char* nomFichier, int* nbOffre, int* max){
    int trouve, pos, i;
    int capital, duree, cout, codePostal, numero;
    char travaux[MAX_TRAVAUX], ligne[MAX_TRAVAUX], entreprise[MAX_TRAVAUX], nomRue[MAX_TRAVAUX], ville[MAX_TRAVAUX];
    Adresse adresse;
    FILE* fe;

    if ((fe = fopen(nomFichier, "r")) == NULL){
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    *nbOffre = 0;
    *max = 10;
    Offre** tOffre, **tmp;

    if ((tOffre = (Offre**)malloc(*max * sizeof(Offre*))) == NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while (fgets(ligne, sizeof(ligne), fe) != NULL){
        sscanf(ligne, "%s", travaux);
        printf("Type de travaux lu : %s\n", travaux);  // Débogage
        pos = rechercheDichotomique(tOffre, *nbOffre, travaux, &trouve);
        if (trouve == 0){
            printf("Offre insérée à la position %d:\n", pos);  // Ajoutez cette ligne pour le débogage
            printf("Type de travaux : %s\n", tOffre[pos]->travaux);  // Ajoutez cette ligne pour le débogage
            // Afficher d'autres détails de l'offre pour le débogage...

            // Pour vérifier les pointeurs
            printf("Adresse de l'offre à la position %d : %p\n", pos, (void *)tOffre[pos]);  // Ajoutez cette ligne pour le débogage

            // Pour vérifier les offres précédentes
            for (int j = 0; j < pos; j++) {
                printf("Offre à la position %d:\n", j);  // Ajoutez cette ligne pour le débogage
                printf("Type de travaux : %s\n", tOffre[j]->travaux);  // Ajoutez cette ligne pour le débogage
                // Afficher d'autres détails de l'offre pour le débogage...
            }
            if (*nbOffre == *max){
                *max += 10;
                if ((tmp = (Offre**)realloc(tOffre, *max * sizeof(Offre*))) == NULL){
                    perror("realloc");
                    exit(EXIT_FAILURE);
                }
                tOffre = tmp;
            }
            for (i = *nbOffre; i > pos; --i){
                tOffre[i] = tOffre[i - 1];
            }
            if ((tOffre[pos] = (Offre*)malloc(sizeof(Offre))) == NULL){
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            strcpy(tOffre[pos]->travaux, travaux);
            tOffre[pos]->ldevis = listeVide();
            ++(*nbOffre);
        }

        fgets(ligne, sizeof(ligne), fe);
        sscanf(ligne, "%[^\n]", entreprise);
        printf("Nom de l'entreprise lu : %s\n", entreprise);  // Débogage

        fgets(ligne, sizeof(ligne), fe);
        sscanf(ligne, "%d %[^0-9] %d %s", &numero, nomRue, &codePostal, ville);
        printf("Adresse lu : %d %s, %d %s\n", numero, nomRue, codePostal, ville);  // Débogage

        if (fscanf(fe, "%d", &capital) != 1) {
            printf("Erreur lors de la lecture du capital.\n");
            break;
        }
        printf("Capital lu : %d\n", capital);

        if (fscanf(fe, "%d", &duree) != 1) {
            printf("Erreur lors de la lecture de la durée.\n");
            break;
        }
        printf("Durée lu : %d\n", duree);

        if (fscanf(fe, "%d", &cout) != 1) {
            printf("Erreur lors de la lecture du coût.\n");
            break;
        }
        printf("Coût lu : %d\n", cout);

        adresse.numero = numero;
        strcpy(adresse.nomRue, nomRue);
        strcpy(adresse.ville, ville);
        adresse.codePostal = codePostal;

        nouveauDevis(tOffre, *nbOffre, travaux, entreprise, adresse, capital, duree, cout);
        if (fscanf(fe, "%s", travaux) == EOF) {
            printf("Fin du fichier atteinte.\n");
            break;
        }

    }

    fclose(fe);
    return tOffre;
}


void chargerPrecedences(char* nomFichier) {
    FILE* fe;

    if ( (fe = fopen(nomFichier, "r")) == NULL ) {
        perror("fopen");
        exit(-1);
    }

    fclose(fe);
}
