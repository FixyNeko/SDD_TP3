#include "arbre.h"

int main(int argc, char * argv[]) {

	noeud_t * racine = NULL;

	insertion(&racine, "");
	insertion(&racine, "b");
	insertion(&racine, "a");
	insertion(&racine, "c");
	insertion(&racine, "abcdefgh");
	insertion(&racine, "abcd");
	insertion(&racine, "acde");
	insertion(&racine, "abbb");
	insertion(&racine, "roses");
	insertion(&racine, "are");
	insertion(&racine, "red");
	insertion(&racine, "violets");
	insertion(&racine, "are");
	insertion(&racine, "blue");
	insertion(&racine, "i");
	insertion(&racine, "love");
	insertion(&racine, "sdd");
	insertion(&racine, "mots");
	insertion(&racine, "mot");


	char s[100] = {0};
	affichage(racine, s, 0, 1);

	affichageMots(&racine);

	return 0;
}