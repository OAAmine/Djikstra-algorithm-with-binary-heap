/**
 * \file test-7 .c
 * \brief Représentation des graphes par liste de successeurs : fichier de test
 * \version 1
 * \date lundi 30 septembre 2019, 10:04:11 (UTC+0200)
 * \authors Pierre Rousselin, Antoine Rozenknop, Sophie Toulouse
 *
 * fonctions testées :
 * - graphe_est_biparti
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graphe-4.h"

/* sous-routine du programme test */
void test_biparti(graphe* g, char *nom_fichier);

/* ____ programme test */
int main() {
    graphe g;
    int n =6;
    
	if(graphe_stable(&g, n, 0))
		puts("une erreur est survenue lors du deroulement de la fonction graphe_stable\n");
	else {
		/* __ premier test: graphe biparti */
		graphe_ajouter_arete(&g, 0, 1, 1);
		graphe_ajouter_arete(&g, 2, 3, 1);
		graphe_ajouter_arete(&g, 3, 4, 1);
		graphe_ajouter_arete(&g, 4, 5, 1);
		graphe_ajouter_arete(&g, 5, 2, 1);
		test_biparti(&g, "biparti.dot");

		/* __ deuxième test: graphe non biparti */
		graphe_ajouter_arete(&g, 3, 5, 1);
		test_biparti(&g, "non_biparti.dot");
	}

    graphe_detruire(&g);
    return EXIT_SUCCESS;
}

/* sous-routine du programme test */
void test_biparti(graphe* g, char *nom_fichier) {
    int is_bip;
    char cmd[100] = "dot -Tx11 ";

	/* __ vérification existence de cycle impair dans le graphe */
	is_bip =graphe_est_biparti(g);

	/* __ restitution */
	if(is_bip <0)
		puts("une erreur est survenue lors du deroulement de la fonction graphe_est_biparti\n");
	else {
		/* le graphe est-il biparti */
		printf("Le graphe %s biparti\n", is_bip ? "est" : "n'est pas");
		/* affichage du graphe */
		graphe_ecrire_dot(g, nom_fichier, 1);
		sprintf(cmd, "dot -Tx11 %s", nom_fichier);
		system(cmd);
	}
}
