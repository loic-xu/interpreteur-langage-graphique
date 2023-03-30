#ifndef _PILE_COORDONNEE_H
#define _PILE_COORDONNEE_H
#include "etat_de_machine_initial.h"

// Utilisé pour la fonction fill dans le module fonction_pixel

// Pile de coordonnées avec un tableau statique de coordonnées de taille 1.000.000 où on stockera les coordonnées à traiter de la fonction fill.
typedef struct
{
    coordonnee content[1000000];
    int top; // indice du sommet de la pile
} pile_coordonnee;

// Empiler une coordonnée dans s
/* 
    requires : adresse de s, coordonnée (entre 0 et taille_image-1)
    assigns : s
    ensures : empile e au sommet de s par effet
*/
void empiler_c(pile_coordonnee* s, coordonnee e);

// Depiler la pile s
/* 
    requires : adresse de s
    assigns : s
    ensures : retourne le sommet de s et change l'indice du sommet de la pile
*/
coordonnee depiler_c(pile_coordonnee *s);

#endif