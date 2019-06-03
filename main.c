#include "arbre.h"
#include "stdio.h"

#define FICHIER_TEST "./tests/testVide.txt"

int main(int argc, char * argv[]) {

	noeud_t * racine = NULL;

	/////////////////// Lecture du fichier de test ///////////////////

	FILE * f;
	char buffer[100];

	f = fopen(FICHIER_TEST, "r");
	if(f == NULL) perror("Erreur d'ouverture du fichier de test");
	else {
		while(!feof(f)) { // tant qu'il reste des lignes à lire
			if ( fgets(buffer , 100 , f) != NULL ) // s'il n'y a pas d'erreur de lecture
				insertion(&racine, buffer); // on insere le mote dans l'arbre
		}
		fclose(f);
	}

	//////////////// fin de lecture du fichier de test ///////////////


	char s[100] = {0};
	affichageArbre(racine, s, 0, 1); // fonction d'affichage de l'arbre pour le debugage


	//affichageMots(&racine); // affichage de tous les mots de l'arbre

	affichageMotif(&racine, "abc");

	libererArbre(racine);

	return 0;
}