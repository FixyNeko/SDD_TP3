#include "arbre.h"

noeud_t * creerNoeud(element_arbre valeur) {
	noeud_t * noeud = (noeud_t *) malloc(sizeof(noeud_t));
	noeud->donnee = valeur;
	return noeud;
}

int recherchePrec(noeud_t ** arbre, element_arbre valeur, noeud_t *** retour) {
	*retour = arbre;
	noeud_t * cour = *arbre;

	while(cour != NULL && tolower(cour->donnee) < tolower(valeur)) {
		*retour = &(cour->lh);
		cour = cour->lh;
	}
	return (cour != NULL && tolower(cour->donnee) == tolower(valeur));
}

int rechercheMotif(noeud_t ** arbre, char * motif, noeud_t ** derniereLettre) {
	int i, lettreTrouvee;
	noeud_t ** prec = arbre;
	*derniereLettre = NULL;

	i = 0;
	do {
		lettreTrouvee = recherchePrec(prec, motif[i], &prec);
		if(lettreTrouvee){
			*derniereLettre = *prec;
			prec = &((*prec)->lv);
			++i;
		}
	} while((*derniereLettre) != NULL && (*derniereLettre)->lv != NULL && motif[i] != '\0' && lettreTrouvee);

	return i;
}

int insertionValeur(noeud_t ** prec, element_arbre valeur) {
	noeud_t * nouv = creerNoeud(valeur);
	int ok = (nouv != NULL);

	if(ok) {
		nouv->lh = *prec;
		*prec = nouv;
	}

	return ok;
}

int insertion(noeud_t ** arbre, char * mot) {
	int i;
	int ok = 1;

	noeud_t ** prec = arbre;
	noeud_t * derniereLettre = NULL;


	i = rechercheMotif(arbre, mot, &derniereLettre);
	if(derniereLettre != NULL)
		prec = &(derniereLettre->lv);

	while(mot[i] != '\0' && mot[i] != '\n' && ok) {

		ok = recherchePrec(prec, mot[i], &prec);
		ok = insertionValeur(prec, mot[i]);
		derniereLettre = *prec;
		prec = &((*prec)->lv);
		++i;
	}

	if( derniereLettre != NULL &&derniereLettre->donnee >= 'a' && derniereLettre->donnee <= 'z')
		derniereLettre->donnee = toupper(derniereLettre->donnee);

	return ok; // retourne si l'operation s'est bien passée
}

void affichageMots(noeud_t ** racine) {
	int i;
	pile_t * pile = InitPile(100);
	noeud_t * copie[100];
	int tailleCopie;

	noeud_t * cour = *racine;

	while(cour != NULL || !PILEEstVide(pile)) {
		while(cour != NULL) {
			PILEempiler(pile, cour);

			if(cour->donnee >= 'A' && cour->donnee <= 'Z') {
				tailleCopie = copiePile(pile, copie);

				for(i = 0; i < tailleCopie; i++) {
					printf(FORMAT_ARBRE, tolower(copie[i]->donnee));
				}
				printf("\n");
			}

			cour = cour->lv;
		}
		while(cour == NULL && !PILEEstVide(pile)) {
			PILEdepiler(pile, &cour);
		}
		if(cour != NULL)
			cour = cour->lh;
	}
}

void affichage(noeud_t * racine, char * parentTreeText, int parentTreeTextEnd, int propagateParent) {

	if(propagateParent) {
		parentTreeText[parentTreeTextEnd++] = '|';
	}
	else {
		parentTreeText[parentTreeTextEnd++] = ' ';
	}
	parentTreeText[parentTreeTextEnd++] = ' ';
	parentTreeText[parentTreeTextEnd++] = ' ';
	parentTreeText[parentTreeTextEnd++] = ' ';
	parentTreeText[parentTreeTextEnd++] = ' ';

	while(racine != NULL) {
		propagateParent = (racine->lh != NULL);

		if(propagateParent) {
			printf("%s├─── ", parentTreeText+5);
		}
		else {
			printf("%s└─── ", parentTreeText+5);
		}
		printf(FORMAT_ARBRE, racine->donnee);
		printf("\n");

		affichage(racine->lv, parentTreeText, parentTreeTextEnd, propagateParent);

		racine = racine->lh;
	}

	parentTreeTextEnd -= 5;
	parentTreeText[parentTreeTextEnd] = '\0';

}
