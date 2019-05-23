#ifndef PILE_H
#define PILE_H

#include <stdlib.h>
#include <stdio.h>
#include "arbre.h"

#define FORMAT_PILE "%p"
typedef noeud_t* element_pile;

typedef struct {
	int TailleMax;
	int RangSommet;
	element_pile * donnees;
} pile_t;

pile_t * InitPile(int TailleMax);
int PILEEstVide(pile_t * pile);
int PILEEstPleine(pile_t * pile);
int PILEempiler(pile_t * pile, element_pile val);
int PILEdepiler(pile_t * pile, element_pile * res);
int PILEsommet(pile_t * pile, element_pile * res);
void PILEliberer(pile_t * pile);
int copiePile(pile_t * pile, element_pile * retour);


#endif /* PILE_H */
