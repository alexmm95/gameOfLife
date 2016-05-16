#include <stdio.h>
#include "mundo.h"
#include <stdint.h>
#include <stdlib.h>
#define ATTR_SET(flags, attr) (flags) |= (1<<(attr))
#define ATTR_IS_SET(flags, attr) ((flags) & (1<<(attr)))

struct mundo{
	int posx;
	int posy;
	int tabl_actual;
	struct Celula *tablero1;
	struct Celula *tablero2;
	uint32_t flags;
};

enum mundo_attr{
	POSX,
	POSY,
	TABL_ACTUAL,
	TABLERO1,
	TABLERO2
};

int mundo_set_posx(struct mundo *m, int tamx){
	int res;
	if (tamx <= 0 || tamx >80)
		res = 0;
	else{
		m->posx = tamx;
		ATTR_SET(m->flags, POSX);
		res = 1;
	}
	return res;
}

int mundo_set_posy(struct mundo *m, int tamy){
	int res;
	if (tamy <= 0 || tamy >80)
		res = 0;
	else{
		m->posy = tamy;
		ATTR_SET(m->flags, POSY);
		res = 1;
	}
	return res;
}

int mundo_set_tabl_actual(struct mundo *m, int act){
	m->tabl_actual = act;
	ATTR_SET(m->flags, TABL_ACTUAL);
	return 1;	
}

void mundo_set_tablero1(struct mundo *m, struct Celula *tablero){
	m->tablero1 = tablero;
	ATTR_SET(m->flags, TABLERO1);
}

void mundo_set_tablero2(struct mundo *m, struct Celula *tablero){
	m->tablero2 = tablero;
	ATTR_SET(m->flags, TABLERO2);
}

int mundo_get_posx(const struct mundo *m){
	if(ATTR_IS_SET(m->flags, POSX))
		return m->posx;
	else
		return -1;
}

int mundo_get_posy(const struct mundo *m){
	if(ATTR_IS_SET(m->flags, POSY))
		return m->posy;
	else
		return -1;
}

int mundo_get_tabl_actual(const struct mundo *m){
	if(ATTR_IS_SET(m->flags, TABL_ACTUAL))
		return m->tabl_actual;
	else
		return -1;
}

struct Celula* mundo_get_tablero1(const struct mundo *m){
	if(ATTR_IS_SET(m->flags, TABLERO1))
		return m->tablero1;
	else
		return -1;
}

struct Celula* mundo_get_tablero2(const struct mundo *m){
	if(ATTR_IS_SET(m->flags, TABLERO2))
		return m->tablero2;
	else
		return -1;
}

struct mundo *mundo_alloc(int posx, int posy){
	struct mundo *m;
	int i, j;
	struct Celula *tablero1;
	struct Celula *tablero2;	
	struct Celula vacia = {0};	

	m = (struct mundo *)malloc(sizeof(struct mundo));
	m->flags = 0;

	mundo_set_posx(m, posx);
	mundo_set_posy(m, posy);
	mundo_set_tabl_actual(m, 0);

	tablero1 = (struct Celula *)malloc(posx * posy * sizeof(struct Celula));
	if(!tablero1){
		printf("No se pudo reservar en memoria el tablero\n");
		return NULL;
	}

	for(i=0; i<posx; i++)
		for(j=0; j<posy; j++)
			*(tablero1 + i * posx + j) = vacia;	

	mundo_set_tablero1(m, tablero1);	

	tablero2 = (struct Celula *)malloc(posx * posy * sizeof(struct Celula));
	if(!tablero2){
		printf("No se pudo reservar en memoria el tablero2\n");
		return NULL;
	}

	for(i=0; i<posx; i++)
		for(j=0; j<posy; j++)
			*(tablero2 + i * posx + j) = vacia;	

	mundo_set_tablero2(m, tablero2);	

	return m;
}

void mundo_free(struct mundo *m){
	free(m);
}

void mundo_print(const struct mundo *m){
	printf("Mundo {");

	if(ATTR_IS_SET(m->flags, POSX))
		printf("\n\tTamaño de la X = \"%i\"", m->posx);
	if(ATTR_IS_SET(m->flags, POSY))
		printf("\n\tTamaño de la Y = \"%i\"\n", m->posy);
	printf("}\n");
}

struct Celula *get_tablero_lectura(const struct mundo *m){
	if(m->tabl_actual == 0)
		return m->tablero1;
	else
		return m->tablero2;
}

struct Celula *get_tablero_escritura(const struct mundo *m){
	if(m->tabl_actual == 1)
		return m->tablero1;
	else
		return m->tablero2;
}

static void fix_coords(const struct mundo *m, int *x, int *y)
{
	int maxX = m->posx;
	int maxY = m->posy;	

    	if (*x >= maxX)
        	*x = 0;
    	else if (*x < 0)
        	*x = maxX - 1;

    	if (*y >= maxY)
        	*y = 0;
    	else if (*y < 0)
        	*y = maxY - 1;
}

static struct Celula *get_casilla(const struct mundo *m, int x, int y, struct Celula *tablero){
	fix_coords(m, &x,&y);
	
	struct Celula *cell = tablero + x * m->posy + y;
	return cell;	
}	

void imprime_mundo(const struct mundo *m)
{
	int i;
	int j;
	int posx;
	int posy;
	struct Celula *tabl_lect;

	posx = m->posx;
	posy = m->posy;
	tabl_lect = get_tablero_lectura(m);

	for(i=0; i<posx; i++){
		for(j=0; j<posy; j++){
			if(get_casilla(m,i,j,tabl_lect)->estado == 0)
				printf(". ");
			else
				printf("* ");
		}
		printf("\n");
	}
}

void inicia_mundo(const struct mundo *m)
{
	struct Celula *t;
	t = get_tablero_lectura(m);

	get_casilla(m,3,3,t)->estado = 1;	
	get_casilla(m,4,4,t)->estado = 1;
	get_casilla(m,5,2,t)->estado = 1;
	get_casilla(m,5,3,t)->estado = 1;
	get_casilla(m,5,4,t)->estado = 1;	

}

int esta_viva(const struct mundo *m, int posx, int posy){
        struct Celula *t;
	t = get_tablero_lectura(m);
	fix_coords(m, &posx, &posy);
	struct Celula *cell = get_casilla(m, posx, posy, t);
        return cell->estado;
}

int num_vecinos_vivos(const struct mundo *m, int posix, int posiy){

        int res = 0;
        int posx = posix;
        int posy = posiy;

        if(esta_viva(m, posx-1, posy) == 1)
                res++;
        if(esta_viva(m, posx-1, posy+1) == 1)
                res++;
        if(esta_viva(m, posx, posy+1) == 1)
                res++;
        if(esta_viva(m, posx+1, posy+1) == 1)
                res++;
        if(esta_viva(m, posx+1, posy) == 1)
                res++;
        if(esta_viva(m, posx+1, posy-1) == 1)
                res++;
        if(esta_viva(m, posx, posy-1) == 1)
                res++;
        if(esta_viva(m, posx-1, posy-1) == 1)
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

void evoluciona(struct mundo *m)
{
int i,j;
struct Celula *tab_leer, *tab_escb;

tab_leer = get_tablero_lectura(m);
tab_escb = get_tablero_escritura(m);

	for(i = 0; i < m->posx; i++){
		for(j = 0; j < m->posy; j++){
			if(get_casilla(m,i,j,tab_leer)->estado == 1){
				if(num_vecinos_vivos(m,i,j) == 2 || num_vecinos_vivos(m,i,j) == 3){
					struct Celula *cell = get_casilla(m,i,j,tab_escb);
					cell->estado=1;
				}
				else{
					struct Celula *cell = get_casilla(m,i,j,tab_escb);
					cell->estado=0;
				}
			}
			else{
				if(num_vecinos_vivos(m,i,j) == 3){
					struct Celula *cell = get_casilla(m,i,j,tab_escb);
					cell->estado=1;
				}
				else{
					struct Celula *cell = get_casilla(m,i,j,tab_escb);
					cell->estado=0;
				}
			}
		}
	}

if(m->tabl_actual == 0)
	m->tabl_actual = 1;
else
	m->tabl_actual = 0;

}

void ejecuta_mundo(struct mundo *m)
{
	int i;
	for(i = 0; i < NUMITER; i++){
		evoluciona(m);
	}
}
