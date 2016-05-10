#include <stdio.h>
#include "mundo.h"

void imprimeMundo(struct Celula mundo[NUMCOL][NUMFIL])
{
	int i;
	int j;

	for(i = 0; i < NUMCOL; i++){
		for(j = 0; j < NUMFIL; j++){
			if(estaViva(mundo,i,j) == 1)
				printf("* ");
			else
				printf(". ");
			
		}
	printf("\n");
	}
}



void iniciaMundo(struct Celula mundo[NUMCOL][NUMFIL], struct Celula celulasVivas[]){
	int i;
	int j;

	for(i = 0; i < NUMCOL; i++){
		for(j = 0; j < NUMFIL; j++){
			struct Celula cell = {0};
			mundo[i][j] = cell;
		}
	}
	mundo[3][3] = celulasVivas[0];
	mundo[4][4] = celulasVivas[1];
	mundo[5][2] = celulasVivas[2];
	mundo[5][3] = celulasVivas[3];
	mundo[5][4] = celulasVivas[4];	
}

static void fix_coords(int *x, int *y)
{
    if (*x >= NUMCOL)
        *x = 0;
    else if (*x < 0)
        *x = NUMCOL - 1;

    if (*y >= NUMFIL)
        *y = 0;
    else if (*y < 0)
        *y = NUMFIL - 1;
}

int estaViva(struct Celula mundo[NUMCOL][NUMFIL], int posx, int posy){
	fix_coords(&posx, &posy);
	return mundo[posx][posy].estado;
}

int numVecinosVivos(int posix, int posiy, struct Celula mundo[][NUMFIL]){
	
	int res = 0;
	int posx = posix;
	int posy = posiy;
	
	if(estaViva(mundo, posx-1, posy) == 1)
		res++;
	if(estaViva(mundo, posx-1, posy+1) == 1)
       	 	res++;
	if(estaViva(mundo, posx, posy+1) == 1)
                res++;
	if(estaViva(mundo, posx+1, posy+1) == 1)
       	        res++;
	if(estaViva(mundo, posx+1, posy) == 1)
                res++;
	if(estaViva(mundo, posx+1, posy-1) == 1)
                res++;
	if(estaViva(mundo, posx, posy-1) == 1)
                res++;
	if(estaViva(mundo, posx-1, posy-1) == 1)
       	        res++;
	
	return res;
}

struct Celula vive(struct Celula cell){
	cell.estado = 1;
	return cell;
}

struct Celula muere(struct Celula cell){
	cell.estado = 0;
	return cell;
}

void evoluciona(struct Celula mundox[NUMCOL][NUMFIL])
{
int i,j;

struct Celula mundo2[NUMCOL][NUMFIL];

	for(i = 0; i < NUMCOL; i++){
		for(j = 0; j < NUMFIL; j++){
			if(mundox[i][j].estado == 1){
				if(numVecinosVivos(i,j, mundox) == 2 || numVecinosVivos(i,j, mundox) == 3)
					mundo2[i][j] = vive(mundox[i][j]);
				else
					mundo2[i][j] = muere(mundox[i][j]);
			}
			else{
				if(numVecinosVivos(i,j, mundox) == 3)
					mundo2[i][j] = vive(mundox[i][j]);
				else
					mundo2[i][j] = muere(mundox[i][j]);
			}
		}
	}
	for(i = 0; i < NUMCOL; i++){
		for(j = 0; j < NUMFIL; j++){
			mundox[i][j] = mundo2[i][j];
		}
	}
}

void ejecutaMundo(struct Celula mundo[NUMCOL][NUMFIL])
{
	int i;
	for(i = 0; i < NUMITER; i++){
		evoluciona(mundo);
	}
}
