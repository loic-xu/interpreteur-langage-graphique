#include <stdio.h>
#include <stdlib.h>
#include "etat_de_machine_initial.h"
#include "fonction_pixel.h"
#include "fonction_seau.h"
#include "pile_coordonnee.h"


// tableau de couleurs dans l'ordre : noir, rouge, vert, bleu, jaune, magenta, cyan, blanc
couleur tab_couleur[] = {{0,0,0}, {255,0,0}, {0,255,0}, {0,0,255}, {255,255,0}, {255,0,255}, {0,255,255},{255,255,255}};

// couleur à ajouter dans le seau de couleurs
couleur couleur_a_ajouter;

// tableau d'opacités dans l'ordre : transparente ou complète
opacite tab_opacite[] = {0,255};
// opacité à ajouter dans le seau d'opacités
opacite opacite_a_ajouter;

// definition du pixel courant qu'on va mettre à jour à chaque fois qu'on voudra tracer/remplir
pixel pixel_courant;

// definition du pixel ancien nécessaire pour la fonction fill
pixel pixel_ancien;

int main()
{
    // #################### ETAT DE LA MACHINE INITIAL ####################

    // on récupère la taille de l'image
    int taille_image = recup_taille_image();

    // position courante et marquée initiale
    coordonnee pos_courante = {0,0};
    coordonnee pos_marquee = {0,0};

    // point cardinal initial
    enum cardinal direction = Est; // "Est" à l'état initial,  direction est une variable de type unsigned int

    // seau de couleurs et seau d'opacités initiales vides
    list_couleur seau_couleur = NULL;
    list_opacite seau_opacite = NULL;

    // calque dont chaque pixel est de couleur (0,0,0) et d'opacité 0
    calque calque_initial = creer_calque_initial(taille_image);

    // pile initiale de calques avec un calque dont chaque pixel est de couleur (0,0,0) et d'opacité 0 avec indice du sommet à 0
    pile pile_initial = {{calque_initial}, 0};


    // #################### FIN ETAT DE LA MACHINE INITIAL ####################


    // #################### FORMAT D'ENTREE ####################
    char char_courant = getc(stdin);
    if (char_courant == EOF)
        {
            printf("Fichier ipi non valide");
            return 0;
        }
    
    while(char_courant != EOF)
    {
        switch(char_courant)
        {
            // Ajouter couleurs parmi (noir, rouge, vert, bleu, jaune, magenta, cyan, blanc) dans le seau de couleur
            case 'n':
                couleur_a_ajouter = tab_couleur[0];
                seau_couleur = cons_couleur(seau_couleur, couleur_a_ajouter);
                break;
            case 'r':
                couleur_a_ajouter = tab_couleur[1];
                seau_couleur = cons_couleur(seau_couleur, couleur_a_ajouter);      
                break;
            case 'g':
                couleur_a_ajouter = tab_couleur[2];
                seau_couleur = cons_couleur(seau_couleur, couleur_a_ajouter);
                break;
            case 'b':
                couleur_a_ajouter = tab_couleur[3];
                seau_couleur = cons_couleur(seau_couleur, couleur_a_ajouter);
                break;
            case 'y':
                couleur_a_ajouter = tab_couleur[4];
                seau_couleur = cons_couleur(seau_couleur, couleur_a_ajouter);
                break;
            case 'm':
                couleur_a_ajouter = tab_couleur[5];
                seau_couleur = cons_couleur(seau_couleur, couleur_a_ajouter);
                break;
            case 'c':
                couleur_a_ajouter = tab_couleur[6];
                seau_couleur = cons_couleur(seau_couleur, couleur_a_ajouter);
                break;
            case 'w':
                couleur_a_ajouter = tab_couleur[7];
                seau_couleur = cons_couleur(seau_couleur, couleur_a_ajouter);
                break;

            // Ajouter opacite parmi (transparent, complet) dans le seau d'opacite
            case 't':
                opacite_a_ajouter = tab_opacite[0];
                seau_opacite = cons_opacite(seau_opacite, opacite_a_ajouter);
                break;
            case 'o':
                opacite_a_ajouter = tab_opacite[1];
                seau_opacite = cons_opacite(seau_opacite, opacite_a_ajouter);
                break;

            // Vider les seaux de couleurs et d'opacité
            case 'i':
                vider_sceaux(&seau_couleur, &seau_opacite);
                break;

            // Avancer curseur selon la direction courante et repasse de l'autre côté si on est au bord
            case 'v':
                avancer_curseur(&pos_courante, direction, taille_image);
                break;

            // Tourner direction curseur
            case 'h':
                tourner_curseur_horaire(&direction);
                break;
            case 'a':
                tourner_curseur_anti_horaire(&direction);
                break;     

            // Mise à jour de la position marquée qui devient la position courante du curseur
            case 'p':
                update_pos_marque(&pos_marquee, pos_courante);
                break;

            // Tracer une ligne sur le calque courant entre la position courante à la position marquee
            case 'l':
                pixel_courant = calcul_pixel_courant(seau_opacite, seau_couleur);
                tracer_ligne(pos_courante, pos_marquee, pixel_courant, &(pile_initial.content[pile_initial.top]));
                break;
            
            // Remplir une zone de couleur autour de position courante (x,y)
            case 'f':
                pixel_courant = calcul_pixel_courant(seau_opacite, seau_couleur);
                pixel_ancien = pile_initial.content[pile_initial.top][pos_courante.x][pos_courante.y];
                fill(pos_courante.x , pos_courante.y, pixel_ancien, pixel_courant, &(pile_initial.content[pile_initial.top]), taille_image);
                break;
            
            // Ajouter un nouveau calque initial ie calque dont chaque pixel est de couleur (0,0,0) et d'opacité 0 dans la pile de calques, ne fait rien s'il y a deja 10 calques dans la pile
            case 's':
                empiler_calque_initial(&pile_initial, taille_image);
                break;
            
            // Fusionner les deux calques les plus hauts dans la pile, ne fait rien s'il n'y a qu'un seul calque dans la pile
            case 'e':
                fusion_calque(&pile_initial, taille_image);
                break;
            
            // Découper le calque situé juste en dessous du sommet de la pile en utilisant comme masque les opacités de celui au sommet, ne fait rien s'il n'y a qu'un seul calque dans la pile
            case 'j':
                decouper_calque(&pile_initial, taille_image);
                break;
        }
        char_courant = getc(stdin);
    }

    if (!(feof(stdin))) // Vérifie si on est bien en fin de fichier
    {
        printf(" Erreur : lecture du fichier incomplète");
        return 0;
    }


    // #################### FIN FORMAT D'ENTREE ####################


    // #################### PRODUCTION DE L'IMAGE FINALE ####################

    fprintf(stdout, "P6\n");
    fprintf(stdout, "%i %i\n", taille_image, taille_image);
    fprintf(stdout, "255\n");

    for (int j=0; j<taille_image; j++)
    {
        for (int i=0; i<taille_image; i++)
        {
            fwrite(&(calque_initial[i][j]), sizeof(couleur), 1, stdout);
        }
    }

    // #################### FIN PRODUCTION DE L'IMAGE FINALE ####################

    return 0;
}