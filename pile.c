#include "pile.h"

/************************************************************************************************/
/*																								*/
/*InitPile		Initialise la sdd d'une pile													*/
/*																								*/
/*En entree: TailleMax la taille maximum de la pile												*/
/*																								*/
/*En sortie: une pile vide																		*/
/*																								*/
/*Principe: on alloue la place pour la structure de gestion de la pile.							*/
/*			s'il n'y a pas eu d'erreur, on alloue la place por les données.						*/
/*			s'il n'y a pas eu d'erreurs, on peut initialiser les variables de gestion de la pile	*/
/*			sinon, on libère la pile															*/
/*																								*/
/************************************************************************************************/

pile_t * InitPile(int TailleMax) {
	pile_t * pile = (pile_t *) malloc(sizeof(pile_t));
	if(pile != NULL) {
		pile->TailleMax = TailleMax;
		pile->RangSommet = 0;
		pile->donnees = (element_pile *) malloc(TailleMax * sizeof(element_pile));
		if(pile->donnees == NULL) {
			free(pile);
			pile = NULL;
		}
	}
	return pile;
}

/* retourne si la pile est vide */

int PILEEstVide(pile_t * pile) {
	return pile->RangSommet == 0;
}

/* retourne si la pile est pleine */

int PILEEstPleine(pile_t * pile) {
	return pile->RangSommet == pile->TailleMax;
}

/************************************************************************************************/
/*																								*/
/*PILEempiler		entrée d'une donnée dans la pile												*/
/*																								*/
/*En entree: pile la pile dans laquelle entrer la donnee, val la donnee							*/
/*																								*/
/*En sortie: ok dit si la donnee a bien été rentrée dans la pile								*/
/*																								*/
/*Principe: si la fil  en'est pas pleine, on peut introduire la donnee au bon endroit, qui est	*/
/*			pile->RangSommet.																	*/
/*			on doit ensuite incrementer la position du dernier element							*/
/*																								*/
/************************************************************************************************/

int PILEempiler(pile_t * pile, element_pile val) {
	int ok = !PILEEstPleine(pile);
	if(ok) {
		pile->donnees[pile->RangSommet] = val;
		pile->RangSommet++;
	}
	return ok;
}

/************************************************************************************************/
/*																								*/
/*PILEdepiler		sortie d'une donnée de la pile												*/
/*																								*/
/*En entree: pile la pile à lire																*/
/*																								*/
/*En sortie: res l'adresse d'un element où stocker le resultat, ok dit s'il n'y a pas eu d'erreur*/
/*																								*/
/*Principe: si la pile n'est pas vide, lit le haut de la pile à l'adresse pile-RangSommet - 1	*/
/*			ensuite, on decremente la position du sommet de la pile								*/
/*																								*/
/************************************************************************************************/

int PILEdepiler(pile_t * pile, element_pile * res) {
	int ok = !PILEEstVide(pile);
	if(ok) {
		pile->RangSommet--;
		*res = pile->donnees[pile->RangSommet];
	}
	return ok;
}

/************************************************************************************************/
/*																								*/
/*PILEsommet		renvoie la valeur au sommet de la pile sans la supprimer					*/
/*																								*/
/*En entree: pile la pile à lire																*/
/*																								*/
/*En sortie: res l'adresse d'un element où stocker le resultat, ok dit s'il n'y a pas eu d'erreur*/
/*																								*/
/*Principe: si la pile n'est pas vide, on lit le sommet de la pile à la position				*/
/*			pile->RangSommet - 1																*/
/*																								*/
/************************************************************************************************/

int PILEsommet(pile_t * pile, element_pile * res) {
	int ok = !PILEEstVide(pile);
	if(ok) {
		*res = pile->donnees[pile->RangSommet - 1];
	}
	return ok;
}

void PILEliberer(pile_t * pile) {
	free(pile->donnees);
	free(pile);
}

int copiePile(pile_t * pile, element_pile * retour) {
	int i;
	for(i = 0; i < pile->RangSommet; i++) {
		retour[i] = pile->donnees[i];
	}
	return i;
}
