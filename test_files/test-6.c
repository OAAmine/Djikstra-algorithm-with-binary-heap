/**
 * \file test-6 .c
 * \brief Représentation des graphes par liste de successeurs : fichier de test
 * \version 1
 * \date lundi 30 septembre 2019, 10:04:11 (UTC+0200)
 * \authors Pierre Rousselin, Antoine Rozenknop, Sophie Toulouse
 *
 * fonctions testées :
 * - graphe_supprimer_arete
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graphe-4.h"

int main() {
    graphe g;
    char *nom_fichier = "oriente.dot",  *nom_fichier2 = "oriente2.dot";
    char cmd[100];

    graphe_stable(&g, 5, 1);
    graphe_ajouter_arete(&g, 0, 1, 3.7);
    graphe_ajouter_arete(&g, 0, 1, 3.7);
    graphe_ajouter_arete(&g, 0, 1, 18.);
    graphe_ajouter_arete(&g, 0, 1, -2.3);
    graphe_ajouter_arete(&g, 1, 2, -1.);
    graphe_ajouter_arete(&g, 1, 2, 5.2);
    graphe_ajouter_arete(&g, 1, 2, -7.1);
    graphe_ajouter_arete(&g, 1, 1, 1.3);
    graphe_ajouter_arete(&g, 3, 0, .5);
    graphe_ajouter_arete(&g, 3, 0, 1.9);
    graphe_ajouter_arete(&g, 0, 4, 2.1);
    graphe_ajouter_arete(&g, 4, 3, -.5);
    graphe_ajouter_arete(&g, 4, 2, 10.3);
    
    printf("Initialement le graphe comporte %d arcs\n", g.m);
    graphe_ecrire_dot(&g, nom_fichier, 1);
    sprintf(cmd, "dot -Tx11 %s &", nom_fichier);
    system(cmd);

	printf("graphe_supprimer_arete(&g, %d, %d, %f) renvoie %d\n", 0, 1, 3.7, graphe_supprimer_arete(&g, 0, 1, 3.7));
	printf("graphe_supprimer_arete(&g, %d, %d, %f) renvoie %d\n", 0, 1, 3.7, graphe_supprimer_arete(&g, 1, 0, 3.7));
	printf("graphe_supprimer_arete(&g, %d, %d, %f) renvoie %d\n", 0, 1, 18.1, graphe_supprimer_arete(&g, 0, 1, 18.1));
	printf("graphe_supprimer_arete(&g, %d, %d, %f) renvoie %d\n", 1, 0, 18., graphe_supprimer_arete(&g, 1, 0, 18.));
	printf("graphe_supprimer_arete(&g, %d, %d, %f) renvoie %d\n", 2, 1, 5.2, graphe_supprimer_arete(&g, 2, 1, 5.2));
	printf("graphe_supprimer_arete(&g, %d, %d, %f) renvoie %d\n", 3, 0, 1.9, graphe_supprimer_arete(&g, 3, 0, 1.9));
	printf("graphe_supprimer_arete(&g, %d, %d, %f) renvoie %d\n", 0, 4, 2.1, graphe_supprimer_arete(&g, 0, 4, 2.1));
    
    printf("Finalement le graphe comporte %d arcs\n", g.m);
    graphe_ecrire_dot(&g, nom_fichier2, 1);
    sprintf(cmd, "dot -Tx11 %s &", nom_fichier2);
    system(cmd);

    graphe_detruire(&g);
    
    return EXIT_SUCCESS;
}
