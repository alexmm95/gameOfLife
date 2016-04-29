#ifndef _TABLERO_H_
#define _TABLERO_H_

#define NUMCOL 20
#define NUMFIL 20
#define NUMITER 20

struct Celula{
	int posx;
	int posy;
	int estado;
};

void imprimeMundo(struct Celula mundo[NUMCOL][NUMFIL]);
void iniciaMundo(struct Celula mundo[NUMCOL][NUMFIL], struct Celula celulasVivas[]);
int estaViva(struct Celula mundo[NUMCOL][NUMFIL], int posx, int posy);
int numVecinosVivos(struct Celula cell, struct Celula mundo[NUMCOL][NUMFIL]);
struct Celula vive(struct Celula cell);
struct Celula muere(struct Celula cell);
void evoluciona(struct Celula mundo[NUMCOL][NUMFIL]);
void ejecutaMundo(struct Celula mundo[NUMCOL][NUMFIL]);

#endif
