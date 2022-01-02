/**
 * \file test-8 .c
 * \brief Représentation des graphes par liste de successeurs : fichier de test
 * \version 1
 * \date lundi 30 septembre 2019, 10:04:11 (UTC+0200)
 * \authors Pierre Rousselin, Antoine Rozenknop, Sophie Toulouse
 *
 * fonctions testées :
 * - graphe_est_sanscircuit
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graphe-4.h"

/* sous-routine du programme test */
void test_sans_circuit(graphe* g, char *nom_fichier);

/* ____ programme test */
int main() {
    graphe g;
    int n =6;
    
	if(graphe_stable(&g, n, 1))
		puts("une erreur est survenue lors du deroulement de la fonction graphe_stable\n");
	else {
		/* __ premier test: graphe sans circuit */
		graphe_ajouter_arc(&g, 0, 1, 1);
		graphe_ajouter_arc(&g, 0, 1, 1);
		graphe_ajouter_arc(&g, 2, 5, 1);
		graphe_ajouter_arc(&g, 2, 4, 1);
		graphe_ajouter_arc(&g, 2, 3, 1);
		graphe_ajouter_arc(&g, 3, 5, 1);
		graphe_ajouter_arc(&g, 3, 4, 1);
		graphe_ajouter_arc(&g, 4, 5, 1);
		
		test_sans_circuit(&g, "avec_circuit.dot");
		
		/* __ deuxième test: graphe avec circuit */
		graphe_ajouter_arc(&g, 5, 2, 1);
		test_sans_circuit(&g, "avec_circuit.dot");
	}

    graphe_detruire(&g);
    return EXIT_SUCCESS;
}

/* sous-routine du programme test */
void test_sans_circuit(graphe* g, char *nom_fichier) {
    int v, *topo, stat;
    char cmd[100] = "dot -Tx11 ";

	/* __ vérification existence de circuit dans le graphe */
	topo =graphe_est_sanscircuit(g, &stat);

	/* __ restitution */
	/* ordre topologique ou présence de circuit */
	if(stat <0)
		puts("une erreur est survenue lors du deroulement de la fonction graphe_est_sanscircuit\n");
	else {
		if(topo) {
			printf("Le graphe sans circuit admet l'ordre topologique suivant:\n");
			for(v =0 ; v < graphe_get_n(g) ; v ++)
				printf("- sommet %d de rang %d\n", v, topo[v]);
		}
		else
			printf("Le graphe contient un circuit\n");
	}
	/* affichage du graphe */
	graphe_ecrire_dot(g, nom_fichier, 1);
	strcat(cmd, nom_fichier);
	system(cmd);
}
