#ifndef _FONCTION_SEAU_H
#define _FONCTION_SEAU_H
#include "etat_de_machine_initial.h"


// Ajouter une des 8 couleurs dans le seau de couleurs
/* 
    requires : seau_couleur, couleur_a_ajouter
    assigns : m
    ensures : retourne un seau de couleur avec la couleur_a_ajouter au sommet
*/
list_couleur cons_couleur(list_couleur seau_couleur, couleur couleur_a_ajouter);

// Ajouter opacité transparente ou complète
/* 
    requires : seau_opacite, opacite_a_ajouter parmi (trans,comp)
    assigns : m
    ensures : retourne un seau d'opacité avec opacite_a_ajouter au sommet
*/
list_opacite cons_opacite(list_opacite seau_opacite, opacite opacite_a_ajouter);

// Vider les sceaux de couleurs et d'opacité
/* 
    requires : adresse seau_couleur et adresse seau_opacite à vider
    assigns : seau_couleur et seau_opacite, tmp
    ensures : Vide les sceaux donnés en paramètre de la procédure en libérant les maillons de la mémoire
*/
void vider_sceaux(list_couleur* seau_couleur, list_opacite* seau_opacite);


#endif