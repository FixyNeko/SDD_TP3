#include "file.h"

/************************************************************************************************/
/*																								*/
/*InitFile		Initialise la sdd d'une file													*/
/*																								*/
/*En entree: TailleMax la taille maximum de la file												*/
/*																								*/
/*En sortie: une file vide																		*/
/*																								*/
/*Principe: on alloue la place pour la structure de gestion de la file.							*/
/*			s'il n'y a pas eu d'erreur, on alloue la place por les données.						*/
/*			s'il n'y a pas eu d'erreurs, onpeut initialiser les variables de gestion de la file	*/
/*			sinon, on libère la file															*/  
/*																								*/
/************************************************************************************************/

file_t * InitFile(int TailleMax) {
	file_t * file = (file_t *) malloc(sizeof(file_t));
	if(file != NULL) {
		file->donnees = (element_file *) malloc(TailleMax * sizeof(element_file));
		if(file->donnees == NULL) {
			free(file);
			file = NULL;
		}
		else {
			file->TailleMax = TailleMax;
			file->compteur = 0;
			file->RangPremier = 0;
			file->RangDernier = 0;
		}
	}
	return file;
}

/* retourne si la file est vide */

int FILEEstVide(file_t * file) {
	return file->compteur == 0;
}

/* retourne si la file est pleine */

int FILEEstPleine(file_t * file) {
	return file->compteur == file->TailleMax;
}

/************************************************************************************************/
/*																								*/
/*FILEentree		entrée d'une donnée dans la file												*/
/*																								*/
/*En entree: file la file dans laquelle entrer la donnee, val la donnee							*/
/*																								*/
/*En sortie: ok dit si la donnee a bien été rentrée dans la file								*/
/*																								*/
/*Principe: si la fil en'est pas pleine, on peut introduire la donnee au bon endroit, qui est	*/
/*			file->RangDernier.																	*/
/*			on doit ensuite incrementer la position du dernier element, en faisant attention	*/
/*			à boucler sur le debut de l'espace de données si nécessaire							*/
/*																								*/
/************************************************************************************************/

int FILEentree(file_t * file, element_file val) {
	int ok = !FILEEstPleine(file);
	if(ok) {
		file->donnees[file->RangDernier] = val;
		file->RangDernier = (file->RangDernier + 1) % file->TailleMax;
		file->compteur++;
	}
	return ok;
}

/************************************************************************************************/
/*																								*/
/*FILEsortie		sortie d'une donnée de la file												*/
/*																								*/
/*En entree: file la fille à lire																*/
/*																								*/
/*En sortie: res l'adresse d'un element où stocker le resultat, ok dit s'il n'y a pas eu d'erreur*/
/*																								*/
/*Principe: si la file n'est pas vide, on lit le bas de la file à la position file->RangPremier	*/
/*			ensuite, on incremente la position du bas de la file en faisant attention à boucler	*/
/*			si necessaire																		*/
/*																								*/
/************************************************************************************************/


int FILEsortie(file_t * file, element_file * res) {
	int ok = !FILEEstVide(file);
	if(ok) {
		*res = file->donnees[file->RangPremier];
		file->RangPremier = (file->RangPremier + 1) % file->TailleMax;
		file->compteur--;
	}
	return ok;
}

/************************************************************************************************/
/*																								*/
/*FILEsommet		renvoie la valeur en bas de la pile sans la supprimer						*/
/*																								*/
/*En entree: file la fille à lire																*/
/*																								*/
/*En sortie: res l'adresse d'un element où stocker le resultat, ok dit s'il n'y a pas eu d'erreur*/
/*																								*/
/*Principe: si la file n'est pas vide, on lit le bas de la file à la position file->RangPremier	*/
/*																								*/
/************************************************************************************************/

int FILEsommet(file_t * file, element_file * res) {
	int ok = !FILEEstVide(file);
	if(ok) {
		*res = file->donnees[file->RangPremier];
	}
	return ok;
}

void FILEliberer(file_t * file) {
	free(file->donnees);
	free(file);
}
