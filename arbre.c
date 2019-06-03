#include "arbre.h"

noeud_t * creerNoeud(element_arbre valeur) {
	noeud_t * noeud = (noeud_t *) malloc(sizeof(noeud_t));
	noeud->donnee = valeur;
	return noeud;
}

int recherchePrec(noeud_t ** arbre, element_arbre valeur, noeud_t *** retour) {
	// recherche d'un precedant dans une liste chainee, sans differencier les majuscules des minuscules dEEFD+
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
	*derniereLettre = NULL; // pointeur sur la derniere lettre commune entre l'arbre et le motif

	i = 0;
	do { // on parcourt l'arbre tant que le motif entier n'a pas été trouvé et qu'on continue
		// de trouver une correspondance dans l'arbre
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
	// insertion d'une nouvelle valeur dans la liste chainée des lh d'un noeud d'un arbre
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


	i = rechercheMotif(arbre, mot, &derniereLettre); // on se place sur la derniere lettre commune
													// entre le contenu de l'arbre et le mot à inserer
	if(derniereLettre != NULL) // cas spécial si on doit créer une nouvelle racine
		prec = &(derniereLettre->lv);

	while(mot[i] != '\0' && mot[i] != '\n' && ok) { // toutes les lettres suivantes dans le mot
													// sont à inserer dans l'arbre
		ok = recherchePrec(prec, mot[i], &prec); // on recherche l'endroit où inserer une lettre en respectant l'alphabet
		ok = insertionValeur(prec, mot[i]); // on insere la lettre au bon endroit de l'arbre
		derniereLettre = *prec;
		prec = &((*prec)->lv);
		++i;
	}

	if( derniereLettre != NULL && derniereLettre->donnee >= 'a' && derniereLettre->donnee <= 'z')
		derniereLettre->donnee = toupper(derniereLettre->donnee); // on met la derniere lettre en majuscule

	return ok; // retourne si l'operation s'est bien passéeS
}

void affichageMots(noeud_t ** racine) {
	int i; // compteur boucles
	pile_t * pile = InitPile(100); // pile de noeuds
	noeud_t * copie[100]; // copie de la pile pour l'affichage des lettres d'un mot
	int tailleCopie; // nombrede noeuds de la copie

	noeud_t * cour = *racine; // variable de parcours de l'arbre

	while(cour != NULL || !PILEEstVide(pile)) { // on faitun parcour en profondeur de l'arbre
		while(cour != NULL) {
			PILEempiler(pile, cour);

			if(cour->donnee >= 'A' && cour->donnee <= 'Z') { // la lettre venant d'être empilée
															// marque la fin d'un mot, on affiche
															// donc le mot
				tailleCopie = copiePile(pile, copie); // on copie la pile des noeuds pour pouvoir afficher leurs lettres

				for(i = 0; i < tailleCopie; i++) { // on affiche la lettre de tous les noeuds encommencant par la racine
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

	PILEliberer(pile);
}

void affichageMotif(noeud_t ** racine, char * motif) {
	int tailleMotif = 0;
	pile_t * pile = InitPile(100);
	noeud_t * derniereLettre;
	noeud_t * cour;
	noeud_t * copie[100];
	int tailleCopie;
	int i;

	while(motif[tailleMotif] != '\0') tailleMotif++;

	int tailleRecherche = rechercheMotif(racine, motif , &derniereLettre);
	if(derniereLettre == NULL)
		cour = *racine;
	else
		cour = derniereLettre->lv; // on veut parcourir les lettres suivant le motif dans l'arbre

	if(tailleMotif == tailleRecherche) { // le motif a bien été trouvé

		if(cour == NULL) // cas spécial dans le cas où le motif cherché n'aurait aucun fils dans l'arbre
			printf("%s\n", motif);

		while(cour != NULL || !PILEEstVide(pile)) { // on parcours l'arbre en profondeur pour afficher les mots
			while(cour != NULL) {
				PILEempiler(pile, cour);

				if(cour->donnee >= 'A' && cour->donnee <= 'Z') {
					tailleCopie = copiePile(pile, copie);

					printf("%s", motif); // la pile ne contient pas le motif, on l'ajoute manuellement

					for(i = 0; i < tailleCopie; i++) {
						printf(FORMAT_ARBRE, tolower(copie[i]->donnee)); // on affiche la suite du mot
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

	PILEliberer(pile);
}

void affichageArbre(noeud_t * racine, char * parentTreeText, int parentTreeTextEnd, int propagateParent) {

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

		affichageArbre(racine->lv, parentTreeText, parentTreeTextEnd, propagateParent);

		racine = racine->lh;
	}

	parentTreeTextEnd -= 5;
	parentTreeText[parentTreeTextEnd] = '\0';

}

void libererArbre(noeud_t * racine) {
	pile_t * pile = InitPile(100); // pile de noeuds

	noeud_t * cour = racine; // variable de parcours de l'arbre
	noeud_t * prec;

	while(cour != NULL || !PILEEstVide(pile)) { // on faitun parcour en profondeur de l'arbre
		while(cour != NULL) {
			PILEempiler(pile, cour);

			cour = cour->lv;
		}
		while(cour == NULL && !PILEEstVide(pile)) {
			PILEdepiler(pile, &cour);
		}
		if(cour != NULL) {
			prec = cour;
			free(prec);
			cour = cour->lh;
		}
	}

	PILEliberer(pile);
}
