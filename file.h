#ifndef FILE_H
#define FILE_H

#include <stdlib.h>

#define FORMAT_FILE "%d"
typedef int element_file;

typedef struct {
	int TailleMax;
	int compteur;
	int RangPremier;
	int RangDernier;
	element_file * donnees;
} file_t;

file_t * InitFile(int TailleMax);
int FILEEstVide(file_t * file);
int FILEEstPleine(file_t * file);
int FILEentree(file_t * file, element_file val);
int FILEsortie(file_t * file, element_file * res);
int FILEsommet(file_t * file, element_file * res);
void FILEliberer(file_t * file);

#endif /* FILE_H */
