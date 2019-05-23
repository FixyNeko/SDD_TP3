#include "arbre.h"
#include "stdio.h"

#define FICHIER_TEST "./tests/test1.txt"

int main(int argc, char * argv[]) {

	noeud_t * racine = NULL;

	FILE * f;
	char buffer[100];

	f = fopen(FICHIER_TEST, "r");
	if(f == NULL) perror("Erreur d'ouverture du fichier de test");
	else {
		while(!feof(f)) {
			if ( fgets(buffer , 100 , f) == NULL ) break;

			insertion(&racine, buffer);
		}
		fclose(f);
	}

	char s[100] = {0};
	affichage(racine, s, 0, 1);

	affichageMots(&racine);

	return 0;
}