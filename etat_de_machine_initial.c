#include <stdio.h>
#include <stdlib.h>
#include "etat_de_machine_initial.h"


// Retourner calque initial
/* 
    requires : un entier > 0
    assigns : calque_initial
    ensures : retourne un calque dont chaque pixel est de couleur (0,0,0) et d'opacité 0
*/
calque creer_calque_initial(int taille_image)
{
    pixel pixel_initial = {{0,0,0}, 0}; // pixel de couleur (0,0,0) et d'opacité 0
    calque calque_initial = malloc(taille_image*sizeof(pixel*));

    for (int i=0; i<taille_image; i++)
    {
        calque_initial[i] = (pixel*) malloc(taille_image*sizeof(pixel));
    }

    for (int i=0; i<taille_image; i++)
    {
        for (int j=0; j<taille_image; j++)
        {
            calque_initial[i][j] = pixel_initial;
        }
    }
    return calque_initial;
}


// Récupérer la taille de l'image
/* 
    requires : entrée standard avec pour première ligne uniquement un entier > 0
    assigns : nothing
    ensures : retourne la taille de l'image qui est sur la première ligne de stdin
*/
int recup_taille_image()
{
    int taille_image;
    char buffer[128];
    fgets(buffer, 128, stdin);
    sscanf(buffer, "%d" , &taille_image);
    return taille_image;
}


