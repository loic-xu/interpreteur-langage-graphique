#include <stdio.h>
#include <stdlib.h>
#include "fonction_pixel.h"
#include "etat_de_machine_initial.h"
#include "pile_coordonnee.h"

// Calcul du pixel courant
/* 
    requires : seau_opacite et seau_couleur
    assigns : nothing
    ensures : retourne le pixel courant
*/
pixel calcul_pixel_courant(list_opacite seau_opacite, list_couleur seau_couleur) 
{
    
    // Calcul opacité courante
    opacite opacite_courant;
    int longueur_seau_opacite;
    int tmp_opacite = 0;

    // cas seau d'opacité non vide : moyenne des opacites dans le seau d'opacite
    while (seau_opacite != NULL)
    {
        longueur_seau_opacite += 1;
        tmp_opacite += seau_opacite->val;
        seau_opacite = seau_opacite->next; 
    }

    // cas seau d'opacité vide
    if (longueur_seau_opacite == 0)
    {
        opacite_courant = 255;
    }
    else
    {
        opacite_courant = tmp_opacite / longueur_seau_opacite; // on ne divise pas par 0 car longueur_seau_opacite != 0 sinon on serait dans le cas du if
    }

    // Calcul couleur courante
    couleur couleur_courant = {0,0,0};
    int longueur_seau_couleur = 0;
    int tmp_r = 0;
    int tmp_g = 0;
    int tmp_b = 0;

    while (seau_couleur != NULL)
    {
        longueur_seau_couleur += 1;
        tmp_r += (seau_couleur->val).r;
        tmp_g += (seau_couleur->val).g;
        tmp_b += (seau_couleur->val).b;
        seau_couleur = seau_couleur->next; 
    }

    if (longueur_seau_couleur != 0)
    {
        couleur_courant.r = tmp_r / longueur_seau_couleur * opacite_courant / 255;
        couleur_courant.g = tmp_g / longueur_seau_couleur * opacite_courant / 255;
        couleur_courant.b = tmp_b / longueur_seau_couleur * opacite_courant / 255;
    }

    // On assemble les deux dans pixel_courant
    pixel pixel_courant = {couleur_courant, opacite_courant};
    return pixel_courant;
}


// Modulo positif utilisé dans la procédure avancer_curseur
/* 
    requires : int a, int b > 0
    assigns : nothing
    ensures : Retourne a modulo b tel qu'il soit compris entre 0 et b
*/
int modulo(int a, int b)
{
    int r = a % b;
    if (r<0)
    {
        return r+b;
    }
    else
    {
        return r;
    }
}

// Avancer curseur de 1 selon la direction 
/* 
    requires : addresse pos_courante, direction parmi (Nord,Est,Sud,Ouest), taille_image > 0
    assigns : pos_courante
    ensures : Avance la position courante du curseur de 1 selon la direction et repasse de l'autre côté si au bord de l'image
*/
void avancer_curseur(coordonnee* pos_courante, enum cardinal direction, int taille_image)
{
    switch(direction)
    {
        case Nord:
            pos_courante->y = modulo(pos_courante->y - 1,taille_image);
            break;
        case Sud:
            pos_courante->y = modulo(pos_courante->y + 1,taille_image);
            break;
        case Est:
            pos_courante->x = modulo(pos_courante->x + 1,taille_image);
            break;
        case Ouest:
            pos_courante->x = modulo(pos_courante->x - 1,taille_image);
            break;
    }
}

// Tourner curseur dans le sens horaire
/* 
    requires : addresse direction
    assigns : direction
    ensures : Tourne le curseur dans le sens horaire
*/ 
void tourner_curseur_horaire(enum cardinal* direction)
{
    switch(*direction)
    {
        case Nord:
            *direction = Est;
            break;
        case Sud:
            *direction = Ouest;
            break;
        case Est:
            *direction = Sud;
            break;
        case Ouest:
            *direction = Nord;
            break;
    }
}

// Tourner curseur dans le sens anti-horaire
/* 
    requires : addresse direction
    assigns : direction
    ensures : Tourne le curseur dans le sens anti-horaire
*/ 
void tourner_curseur_anti_horaire(enum cardinal* direction)
{
    switch(*direction)
    {
        case Nord:
            *direction = Ouest;
            break;
        case Sud:
            *direction = Est;
            break;
        case Est:
            *direction = Nord;
            break;
        case Ouest:
            *direction = Sud;
            break;
    }
}

// Mise à jour de la position marquée qui devient la position courante du curseur
/* 
    requires : adresse pos_marquee, pos_courante
    assigns : pos_marquee
    ensures : pos_marquee devient égale à pos_courante
*/
void update_pos_marque(coordonnee* pos_marquee, coordonnee pos_courante)
{
    pos_marquee->x = pos_courante.x;
    pos_marquee->y = pos_courante.y;
}

// Maximum entre deux entiers positifs utilisé dans la fonction tracer_ligne
/* 
    requires : int a >= 0 et int b >= 0
    assigns : nothing
    ensures : retourne le max entre a et b
*/
int max(int a, int b)
{
    int res;
    if (a<b)
    {
        res = b;
    }
    else
    {
        res = a;
    }
    return res;
}

// Changer pixel en (x,y) par le pixel courant utilisé dans tracer_ligne
/* 
    requires : adresse calque_courant, position avec 0 < x,y < taille du calque, pixel_courant
    assigns : calque_courant
    ensures : modifie le pixel de calque_courant au coordonnée de position
*/
void changer_pixel(calque* calque_courant, coordonnee position, pixel pixel_courant)
{
    (*calque_courant)[position.x][position.y] = pixel_courant;
}


// Tracé de lignes
/* 
    requires : 0 < x0,y0,x1,y1 < taille du calque, pixel_courant, adresse calque_courant
    assigns : calque_courant
    ensures : trace une ligne sur le calque_courant entre la position courante (x0,y0) à la position marquee (x1,y1)
*/
void tracer_ligne(coordonnee position_courante, coordonnee position_marquee, pixel pixel_courant, calque* calque_courant)
{
    int x0 = position_courante.x;
    int y0 = position_courante.y;
    int x1 = position_marquee.x;
    int y1 = position_marquee.y;
    coordonnee position;

    int dx = x1 - x0;
    int dy = y1 - y0;
    int s;
    
    int d = max(abs(dx),abs(dy));

    if (dx != 0 && dy != 0 && dx*dy > 0)
    {
        s = 0;
    }
    else
    {
        s = 1;
    }

    int x = x0 * d + (d - s)/2;
    int y = y0 * d + (d - s)/2;

    for (int i=0; i<d; i++)
    {
        position.x = x/d;
        position.y = y/d;
        changer_pixel(calque_courant, position, pixel_courant);
        x = x + dx;
        y = y + dy;
    }

    position.x = x1;
    position.y = y1;
    changer_pixel(calque_courant, position, pixel_courant);
}


// Test d'égalité de pixel
/* 
    requires : pixel_a, pixel_b
    assigns : nothing
    ensures : retourne 1 en cas d'égalité et 0 sinon
*/
int test_pixel(pixel pixel_a, pixel pixel_b)
{
    if (pixel_a.opac != pixel_b.opac)
    {
        return 0;
    }
    if (pixel_a.coul.r != pixel_b.coul.r)
    {
        return 0;
    }
    if (pixel_a.coul.g != pixel_b.coul.g)
    {
        return 0;
    }
    if (pixel_a.coul.b != pixel_b.coul.b)
    {
        return 0;
    }
    return 1;
}

// Remplissage
/* 
    requires : 0 < x,y < taille du calque, pixel_ancien, pixel_courant, adresse calque_courant & pixel courant soit différent de celui déjà en (x,y)
    assigns : calque_courant
    ensures : rempli une zone de couleur autour de (x,y)
*/
void fill(int x, int y, pixel pixel_ancien, pixel pixel_courant, calque* calque_courant, int taille_image)
{
    
    pile_coordonnee pile_a_traiter;
    pile_a_traiter.top = -1;

    coordonnee e;
    e.x = x;
    e.y = y;

    coordonnee tmp;

    empiler_c(&pile_a_traiter, e);
    
        
    do
    {
        e = depiler_c(&pile_a_traiter);

        if (test_pixel((*calque_courant)[e.x][e.y], pixel_ancien) && !(test_pixel((*calque_courant)[e.x][e.y], pixel_courant)))
        {
            (*calque_courant)[e.x][e.y] = pixel_courant;

            if (e.x>0)
            {
                tmp.x = e.x-1;
                tmp.y = e.y;
                empiler_c(&pile_a_traiter, tmp);
            }
            if (e.y>0)
            {
                tmp.x = e.x;
                tmp.y = e.y-1;
                empiler_c(&pile_a_traiter, tmp);
            }
            if (e.x<taille_image-1)
            {
                tmp.x = e.x+1;
                tmp.y = e.y;
                empiler_c(&pile_a_traiter, tmp);
               

            }
            if (e.y<taille_image-1)
            {
                tmp.x = e.x;
                tmp.y = e.y+1;
                empiler_c(&pile_a_traiter, tmp);
            }
        }
    }
    while (pile_a_traiter.top >= 0);
}

// Empiler dans la pile de calques un calque initial (calque dont chaque pixel est de couleur (0,0,0) et d'opacité 0). Si pleine à 10, ne fait rien
/* 
    requires : adresse pile_courant, taille_image
    assigns : pile_courant
    ensures : empile dans pile_courant un calque initial, ne fait rien si pile_courant est déjà de taille 10
*/
void empiler_calque_initial(pile* pile_courant, int taille_image)
{
    if (pile_courant->top<9)
    {
        pile_courant->top += 1;
        pile_courant->content[pile_courant->top] = creer_calque_initial(taille_image);
    }
}

// Fusion de calques
/*
    requires : adresse pile_courant, taille_image
    assigns : pile_courant
    ensures : fusionne les deux calques au sommet de la pile, ne fait rien si pile_courant est de taille 1
*/
void fusion_calque(pile* pile_courant, int taille_image)
{
    if (pile_courant->top>0)
    {
        opacite new_opa;
        couleur new_coul;
        pixel new_pixel;

        for (int i=0; i<taille_image; i++)
        {
            for (int j=0; j<taille_image; j++)
            {
                opacite a0 = ((pile_courant->content[pile_courant->top])[i][j]).opac;
                couleur c0;
                c0.r = ((pile_courant->content[pile_courant->top])[i][j]).coul.r;
                c0.g = ((pile_courant->content[pile_courant->top])[i][j]).coul.g;
                c0.b = ((pile_courant->content[pile_courant->top])[i][j]).coul.b;

                opacite a1 = ((pile_courant->content[pile_courant->top-1])[i][j]).opac;
                couleur c1;
                c1.r = ((pile_courant->content[pile_courant->top-1])[i][j]).coul.r;
                c1.g = ((pile_courant->content[pile_courant->top-1])[i][j]).coul.g;
                c1.b = ((pile_courant->content[pile_courant->top-1])[i][j]).coul.b;

                new_opa = a0 + (a1*(255-a0)/255);
                new_coul.r = c0.r + (c1.r*(255-a0)/255);
                new_coul.g = c0.g + (c1.g*(255-a0)/255);
                new_coul.b = c0.b + (c1.b*(255-a0)/255);

                new_pixel.opac = new_opa;
                new_pixel.coul.r = new_coul.r;
                new_pixel.coul.g = new_coul.g;
                new_pixel.coul.b = new_coul.b;

                pile_courant->content[pile_courant->top-1][i][j] = new_pixel;
            }
        }
        pile_courant->top -= 1;
    }
}

// Découpage de calques
/*
    requires : adresse pile_courant, taille_image
    assigns : pile_courant
    ensures : découpe le calque sous le sommet en utilisant le calque du sommet en masque, ne fait rien si pile_courant est de taille 1
*/
void decouper_calque(pile* pile_courant, int taille_image)
{
    if (pile_courant->top>0)
    {
        opacite new_opa;
        couleur new_coul;
        pixel new_pixel;

        for (int i=0; i<taille_image; i++)
        {
            for (int j=0; j<taille_image; j++)
            {
                opacite a0 = ((pile_courant->content[pile_courant->top])[i][j]).opac;
                opacite a1 = ((pile_courant->content[pile_courant->top-1])[i][j]).opac;
                couleur c1;
                c1.r = ((pile_courant->content[pile_courant->top-1])[i][j]).coul.r;
                c1.g = ((pile_courant->content[pile_courant->top-1])[i][j]).coul.g;
                c1.b = ((pile_courant->content[pile_courant->top-1])[i][j]).coul.b;

                new_opa = a1 * a0/255;
                new_coul.r = c1.r * a0/255;
                new_coul.g = c1.g * a0/255;
                new_coul.b = c1.b * a0/255;

                new_pixel.opac = new_opa;
                new_pixel.coul.r = new_coul.r;
                new_pixel.coul.g = new_coul.g;
                new_pixel.coul.b = new_coul.b;

                pile_courant->content[pile_courant->top-1][i][j] = new_pixel;
            }
        }
        pile_courant->top -= 1;
    }
}
