#include <stdio.h>
#include <stdlib.h>
#include "pile_coordonnee.h"
#include "etat_de_machine_initial.h"

// Utilisé pour la fonction fill dans le module fonction_pixel

// Pile de coordonnées avec un tableau statique de coordonnées de taille 1.000.000 où on stockera les coordonnées à traiter de la fonction fill.

// Empiler une coordonnée dans s
/* 
    requires : adresse de s, coordonnée (entre 0 et taille_image-1)
    assigns : s
    ensures : empile e au sommet de s par effet
*/
void empiler_c(pile_coordonnee* s, coordonnee e) 
{
    if (s->top<1000000)
    {
        s->top += 1;
        s->content[s->top] = e;
    }
}

// Depiler la pile s
/* 
    requires : adresse de s
    assigns : s
    ensures : retourne le sommet de s et change l'indice du sommet de la pile
*/
coordonnee depiler_c(pile_coordonnee *s) 
{

    coordonnee e = s->content[s->top];
    s->top -= 1;
    return e;
}