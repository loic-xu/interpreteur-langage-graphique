#ifndef _FONCTION_PIXEL_H
#define _FONCTION_PIXEL_H
#include "etat_de_machine_initial.h"

// Calcul du pixel courant
/* 
    requires : seau_opacite et seau_couleur
    assigns : nothing
    ensures : retourne le pixel courant
*/
pixel calcul_pixel_courant(list_opacite seau_opacite, list_couleur seau_couleur);

// Avancer curseur de 1 selon la direction 
/* 
    requires : addresse pos_courante, string
    assigns : pos_courante
    ensures : Avance la position courante du curseur de 1 selon la direction
*/
void avancer_curseur(coordonnee* pos_courante, enum cardinal direction, int taille_image);

// Tourner curseur dans le sens horaire
/* 
    requires : addresse direction
    assigns : direction
    ensures : Tourne le curseur dans le sens horaire
*/ 
void tourner_curseur_horaire(enum cardinal* direction);

// Tourner curseur dans le sens anti-horaire
/* 
    requires : addresse direction
    assigns : direction
    ensures : Tourne le curseur dans le sens anti-horaire
*/ 
void tourner_curseur_anti_horaire(enum cardinal* direction);

// Mise à jour de la position marquée qui devient la position courante du curseur
/* 
    requires : adresse pos_marquee, pos_courante
    assigns : pos_marquee
    ensures : pos_marquee devient égale à pos_courante
*/
void update_pos_marque(coordonnee* pos_marquee, coordonnee pos_courante);

// Maximum entre deux entiers positifs utilisé dans la fonction tracer_ligne
/* 
    requires : int a >= 0 et int b >= 0
    assigns : nothing
    ensures : retourne le max entre a et b
*/
int max(int a, int b);

// Changer pixel en (x,y) par le pixel courant
/* 
    requires : adresse calque_courant, position, pixel_courant
    assigns : calque_courant
    ensures : modifie le pixel de calque_courant au coordonnée de position
*/
void changer_pixel(calque* calque_courant, coordonnee position, pixel pixel_courant);

// Tracé de lignes
/* 
    requires : 0 < x0,y0,x1,y1 < taille du calque, pixel_courant, adresse calque_courant
    assigns : calque_courant
    ensures : trace une ligne sur le calque_courant entre la position courante (x0,y0) à la position marquee (x1,y1)
*/
void tracer_ligne(coordonnee position_courante, coordonnee position_marquee, pixel pixel_courant, calque* calque_courant);

// Test d'égalité de pixel
/* 
    requires : pixel_a, pixel_b
    assigns : nothing
    ensures : retourne 1 en cas d'égalité et 0 sinon
*/

int test_pixel(pixel pixel_a, pixel pixel_b);

// Remplissage
/* 
    requires : 0 < x,y < taille du calque, pixel_ancien, pixel_courant, adresse calque_courant & pixel courant soit différent de celui déjà en (x,y)
    assigns : calque_courant
    ensures : rempli une zone de couleur autour de (x,y)
*/
void fill(int x, int y, pixel pixel_ancien, pixel pixel_courant, calque* calque_courant, int taille_image);

// Empiler dans la pile de calques un calque initial (calque dont chaque pixel est de couleur (0,0,0) et d'opacité 0). Si pleine à 10, ne fait rien
/* 
    requires : adresse pile_courant, taille_image
    assigns : pile_courant
    ensures : empile dans pile_courant un calque initial. Fait rien si pile_courant est déjà de taille 10
*/
void empiler_calque_initial(pile* pile_courant, int taille_image);

// Fusion de calques
/*
    requires : adresse pile_courant, taille_image
    assigns : pile_courant
    ensures : fusionne les deux calques au sommet de la pile, ne fait rien si pile_courant est de taille 1
*/
void fusion_calque(pile* pile_courant, int taille_image);

// Découpage de calques
/*
    requires : adresse pile_courant, taille_image
    assigns : pile_courant
    ensures : découpe le calque sous le sommet en utilisant le calque du sommet en masque, ne fait rien si pile_courant est de taille 1
*/
void decouper_calque(pile* pile_courant, int taille_image);


#endif
