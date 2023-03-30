Le fichier ipi doit commencer par un entier strictement positif à la première ligne
Puis en seconde ligne, une suite de caractères.


Pour exécuter le programme :

./exec < test.ipi | display

ou 

./exec < test.ipi > image.ppm

(Il faudra ouvrir manuellement image.ppm)
Attention, cela écrase le fichier image.ppm s'il existe.



Pour compiler :

gcc -Wall -o exec main.c fonction_pixel.c etat_de_machine_initial.c fonction_seau.c pile_coordonnee.c

