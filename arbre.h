#ifndef ARBRE_H
#define ARBRE_H

#define FORMAT_ARBRE "%c"
typedef char element_arbre;

#include "file.h"
#include "listeChainee.h"

typedef struct noeud {
	element_arbre donnee;
	struct noeud * lv;
	struct noeud * lh;
} noeud_t;

#include "pile.h"

//int isupper(char c);

noeud_t *	creerNoeud(element_arbre valeur);
int			recherchePrec(noeud_t ** arbre, element_arbre valeur, noeud_t *** retour);
int			insertionValeur(noeud_t ** prec, element_arbre valeur);

int 		rechercheMotif(noeud_t ** arbre, char * motif, noeud_t ** derniereLettre);

int			insertion(noeud_t ** racine, char * mot);
void		affichageMots(noeud_t ** racine);
void		affichageMotif(noeud_t ** racine, char * motif);

void		affichageArbre(noeud_t * racine, char * parentTreeText, int parentTreeTextEnd, int propagateParent);



#endif // ARBRE_H