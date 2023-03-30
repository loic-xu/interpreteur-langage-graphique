#include <stdio.h>
#include <stdlib.h>
#include "fonction_seau.h"
#include "etat_de_machine_initial.h"

// Ajouter une des 8 couleurs dans le seau de couleurs
/* 
    requires : seau_couleur, couleur_a_ajouter parmi (noir,rouge,vert,bleu,jaune,magenta,cyan,blanc)
    assigns : m
    ensures : retourne un seau de couleur avec couleur_a_ajouter au sommet
*/
list_couleur cons_couleur(list_couleur seau_couleur, couleur couleur_a_ajouter)
{
    struct maillon_couleur* m;
    m = malloc(sizeof(struct maillon_couleur));
    m->val = couleur_a_ajouter;
    m->next = seau_couleur;
    return m;
}

// Ajouter opacité transparente ou complète
/* 
    requires : seau_opacite, opacite_a_ajouter parmi (trans,comp)
    assigns : m
    ensures : retourne un seau d'opacité avec opacite_a_ajouter au sommet
*/
list_opacite cons_opacite(list_opacite seau_opacite, opacite opacite_a_ajouter)
{
    struct maillon_opacite* m;
    m = malloc(sizeof(struct maillon_opacite));
    m->val = opacite_a_ajouter;
    m->next = seau_opacite;
    return m;
}

// Vider les sceaux de couleurs et d'opacité
/* 
    requires : adresse seau_couleur et adresse seau_opacite à vider
    assigns : seau_couleur et seau_opacite, tmp
    ensures : Vide les sceaux donnés en paramètre de la procédure en libérant les maillons de la mémoire
*/
void vider_sceaux(list_couleur* seau_couleur, list_opacite* seau_opacite)
{
    while (*seau_couleur != NULL)
    {
        list_couleur tmp = *seau_couleur; // à free 
        *seau_couleur = (*seau_couleur)->next;
        free(tmp);
    }

    while (*seau_opacite != NULL)
    {
        list_opacite tmp = *seau_opacite; // à free
        *seau_opacite = (*seau_opacite)->next;
        free(tmp);
    }
}
