#ifndef _ETAT_DE_MACHINE_INITIAL_H
#define _ETAT_DE_MACHINE_INITIAL_H

// DECLARATIONS DES TYPES


// composante = char non signé
typedef unsigned char composante; // cohérence avec opacité

// couleur -> 3 composantes
typedef struct
{
    composante r ;
    composante g ;
    composante b ;
} couleur;

// opacite = composante
typedef composante opacite;

//pixel -> couleur + opacité
typedef struct{
    couleur coul;
    opacite opac;
} pixel;

// calque = tableau 2D de pixel
typedef pixel** calque;

// seau de couleur = liste chaînée de couleurs
typedef struct maillon_couleur* list_couleur;

struct maillon_couleur
{
    couleur val;
    list_couleur next;
};

// seau d'opacité = liste chaînée d'opacités
typedef struct maillon_opacite* list_opacite;

struct maillon_opacite
{
    opacite val;
    list_opacite next;
};

// coordonnée avec x pour l'abscisse et y pour l'ordonnée
typedef struct
{
    int x;
    int y;
} coordonnee;

// point cardinal
enum cardinal{Nord,Est,Sud,Ouest};

// pile -> tableau de taille maximum 10 composés de calques + indice du sommet de la pile
typedef struct
{
    calque content[10];
    int top; // indice du sommet de la pile
} pile;

// FIN DECLARATIONS DES TYPES


// FONCTIONS

// Retourner calque initial
/* 
    requires : un entier > 0
    assigns : calque_initial
    ensures : retourne un calque dont chaque pixel est de couleur (0,0,0) et d'opacité 0
*/
calque creer_calque_initial(int taille_image);

// Récupérer la taille de l'image
/* 
    requires : entrée standard avec pour première ligne uniquement un entier > 0
    assigns : nothing
    ensures : retourne la taille de l'image qui est sur la première ligne de stdin
*/
int recup_taille_image();

#endif