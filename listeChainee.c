#include "listeChainee.h"

/**************************************************************************************************/
/*																								  */
/* InitLCH	initialise une liste chainée														  */
/*																								  */
/*	En entrée:	liste un pointeur sur une structure liste										  */
/*																								  */
/**************************************************************************************************/

void InitLCH(liste_t * liste) {
	/* on teste si la liste a bien été allouée précédament */
	if(liste == NULL) {
		exit(EXIT_FAILURE);
	}

	/* la liste est vide, le pointeur de tete doit pointer sur NULL */
	liste->premier = NULL;
}

/**************************************************************************************************/
/*																								  */
/* CreerCellule	crée une cellule de liste chainée à partir des donéées à stocker				  */
/*																								  */
/*	En entrée:	DebutValidite, FinValidite, texte les données à stocker dans la cellule			  */
/*																								  */
/*	En sortie:	retourne l'adresse de la cellule crée											  */
/*																								  */
/*	Principe:	on alloue un espace mémoire qui contiendra un élément, et on le remplit 		  */
/*				avec les valeurs données														  */
/*																								  */
/**************************************************************************************************/

message_t *CreerCellule(int DebutValidite, int FinValidite, char * texte) {
	message_t * cellule = (message_t *) malloc(sizeof(message_t)); /* adresse de la cellule crée */

	if(cellule == NULL) { /* on teste si l'allocation s'est bien passé */
		exit(EXIT_FAILURE);
	}
	cellule->DebutValidite = DebutValidite;
	cellule->FinValidite = FinValidite;
	cellule->texte = texte;
	cellule->suivant = NULL; /* par defaut, la cellule n'a pas de suivant */
	return cellule;
}

/**************************************************************************************************/
/*																								  */
/* InsertionApres	insere une cellule dans la liste chainée apres une cellule de la liste donnée */
/*																								  */
/*	En entrée:	message un pointeur vers la cellule à ajouter à la liste						  */
/*				prec un pointeur sur l'attribut suivant d'une cellule de la liste				  */
/*																								  */
/**************************************************************************************************/

void InsertionApres(message_t * message, message_t ** prec) {
	message->suivant = *prec;
	*prec = message;
}

/**************************************************************************************************/
/*																								  */
/* RecherchePrec	recherche le precedent d'une valeur dans une liste chainée					  */
/*					selon la date de debut des messages											  */
/*																								  */
/*	En entrée:	liste un pointeur sur une structure liste initialisée							  */
/*				valeur la date pour laquelle on cherche le precedant							  */
/*																								  */
/*	En sortie:	retourne le précédant de la valeur												  */
/*																								  */
/*	Principe: on cherche le dernier message de la liste chainée ayant une date de début			  */
/*		inferieure à celle donnée. La liste étant triée, on la parcourt depuis son début en		  */
/*		testant chaque élément																	  */
/*																								  */
/**************************************************************************************************/

message_t **RecherchePrec(liste_t * liste, int valeur) {
	message_t  * cour = liste->premier; /* pointeur sur le message traité */
	message_t ** prec = &(liste->premier); /* pointeur sur son précedant */
	
	/* tant que le message n'est pas apres la date cherchée et qu'il reste des messages dans
	la liste, on teste le message suivant*/
	while(cour != NULL && cour->DebutValidite < valeur) {
		prec = &(cour->suivant);
		cour = cour->suivant;
	}
	
	return prec;
}

/**************************************************************************************************/
/*																								  */
/* SupprimerCellule	supprime une  cellule de la liste chainée et libère la mémoire				  */
/*																								  */
/*	En entrée:	prec le precedant de la cellule à supprimer										  */
/*																								  */
/**************************************************************************************************/

void SupprimerCellule(message_t ** prec) {
	message_t * cour = *prec; /* pointeur sur le message à supprimer */

	if(cour != NULL) {
		*prec = (*prec)->suivant;
		free(cour->texte); /* on libere d'abord le texte du message */
		free(cour); /* puis on libere le message */
	}
}

/**************************************************************************************************/
/*																								  */
/* ParcoursLCH	afficher tout le contenu de la list chainée										  */
/*																								  */
/*	En entrée:	liste un pointeur sur une structure liste initialisée							  */
/*																								  */
/**************************************************************************************************/

void ParcoursLCH(liste_t * liste) {
	message_t * cour = liste->premier; /* pointeur sur le message traité */

	while(cour != NULL) { /* tant qu'il reste des messages à afficher */
		printf("%d %d %s\n", cour->DebutValidite, cour->FinValidite, cour ->texte); /* on affiche */
		cour = cour->suivant;
	}
}

/**************************************************************************************************/
/*																								  */
/* SupprimerLCH	supprime tous les éléments de la liste chainée 									  */
/*																								  */
/*	En entrée:	liste un pointeur sur une structure liste initialisée							  */
/*																								  */
/**************************************************************************************************/

void SupprimerLCH(liste_t * liste) {
	while(liste->premier != NULL) { /* tant qu'il reste des messages dans la liste chainée */
		SupprimerCellule(&(liste->premier)); /* on supprime le premier message */
	}
}
