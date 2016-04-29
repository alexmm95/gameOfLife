#include <stdio.h>
#include "tablero.h"

void imprimeMundo(struct Celula mundo[NUMCOL][NUMFIL])
{
	int i;
	int j;

	for(i = 0; i < NUMCOL; i++){
		for(j = 0; j < NUMFIL; j++){
			if(estaViva(mundo,i,j) == 1){
				printf("* ");
			}
			else{
				printf(". ");
			}
		}
	printf("\n");
	}
}



void iniciaMundo(struct Celula mundo[NUMCOL][NUMFIL], struct Celula celulasVivas[]){
	int i;
	int j;
	int a;

	for(i = 0; i < NUMCOL; i++){
		for(j = 0; j < NUMFIL; j++){
			struct Celula cell = {i,j,0};
			mundo[i][j] = cell;
		}
	}
	mundo[3][3] = celulasVivas[0];
	mundo[4][4] = celulasVivas[1];
	mundo[5][2] = celulasVivas[2];
	mundo[5][3] = celulasVivas[3];
	mundo[5][4] = celulasVivas[4];	
}

int estaViva(struct Celula mundo[NUMCOL][NUMFIL], int posx, int posy){
	struct Celula cell;
	cell = mundo[posx][posy];
	if(cell.estado == 1){
		return 1;
	}
	else{
		return 0;
	}
}




int numVecinosVivos(struct Celula cell, struct Celula mundo[][NUMFIL]){
	
	int posx;
	int posy;
	int res = 0;

	posx = cell.posx;
	posy = cell.posy;

	if(estaViva(mundo, posx-1, posy) == 1){
		res++;
	}
	if(estaViva(mundo, posx-1, posy+1) == 1){
                res++;
        }
	if(estaViva(mundo, posx, posy+1) == 1){
                res++;
        }
	if(estaViva(mundo, posx+1, posy+1) == 1){
                res++;
        }
	if(estaViva(mundo, posx+1, posy) == 1){
                res++;
        }
	if(estaViva(mundo, posx+1, posy-1) == 1){
                res++;
        }
	if(estaViva(mundo, posx, posy-1) == 1){
                res++;
        }
	if(estaViva(mundo, posx-1, posy-1) == 1){
                res++;
        }

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
				if(numVecinosVivos(mundox[i][j], mundox) == 2 || numVecinosVivos(mundox[i][j], mundox) == 3){
					mundo2[i][j] = vive(mundox[i][j]);
            			}
				else{
					mundo2[i][j] = muere(mundox[i][j]);
				}
			}
			else{
				if(numVecinosVivos(mundox[i][j], mundox) == 3){
					mundo2[i][j] = vive(mundox[i][j]);
				}
				else{
					mundo2[i][j] = muere(mundox[i][j]);
				}
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

/*
int main()
{
	struct Celula mundo[NUMCOL][NUMFIL];
	struct Celula celulasVivas[] = {{3,3,1},{4,4,1},{5,2,1},{5,3,1},{5,4,1}};
	iniciaMundo(mundo, celulasVivas);	
	printf("\nJuego de la vida, Version 1.0\n\n");
	imprimeMundo(mundo);

	ejecutaMundo(mundo);

	printf("\nMundo evolucionado\n\n");
	
	imprimeMundo(mundo);
	return 1;
}*/

































