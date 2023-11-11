# Projet PRIM11 - Interpréteur pour un Langage Graphique

## Introduction
Bienvenue dans le projet PRIM11 de programmation impérative. Ce projet consiste en l'implémentation d'un interpréteur pour un langage graphique. L'objectif principal est de créer un programme exécutable capable de lire un fichier décrivant une séquence d'instructions pour générer une image graphique. Cette image sera construite à l'aide d'une machine à états avec plusieurs calques et opérations graphiques. L'exécutable prendra un fichier en entrée, décrivant les opérations graphiques, et produira une image au format PPM en sortie.

## Exemples
Des exemples d'entrées et de sorties sont fournis dans le dossier "exemples_ipi".

Par exemple :  
17  
hvvvvvvvvvvvvavvagpvvvvvvvvlhpvvvvlhpvvvvvvvvlhpvvvvlhhvvvvvvvvapvvvvvvvvlhvvvvphvvvvhvvvvlpavvvvavvvvl

donnerait l'image 

![ExempleOK](exemples_ipi/ok.png)




## Utilisation
Le fichier ipi doit commencer par un entier strictement positif à la première ligne, puis en seconde ligne, une suite de caractères.

Pour exécuter le programme :

./exec < test.ipi | display

ou 

./exec < test.ipi > image.ppm

(Il faudra ouvrir manuellement image.ppm)
Attention, cela écrase le fichier image.ppm s'il existe.



Pour compiler :

gcc -Wall -o exec main.c fonction_pixel.c etat_de_machine_initial.c fonction_seau.c pile_coordonnee.c

