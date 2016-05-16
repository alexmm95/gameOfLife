#ifndef _MUNDO_H_
#define _MUNDO_H_

#define NUMCOL 20
#define NUMFIL 20
#define NUMITER 20

struct mundo;

struct Celula{
	int estado;
};

void imprime_mundo(const struct mundo *m);
void inicia_mundo(const struct mundo *m);
int esta_viva(const struct mundo *m, int posx, int posy);
int num_vecinos_vivos(const struct mundo *m, int posix, int posiy);
struct Celula vive(struct Celula cell);
struct Celula muere(struct Celula cell);
void evoluciona(struct mundo *m);
void ejecuta_mundo(struct mundo *m);
int mundo_set_posx(struct mundo *m, int tamx);
int mundo_set_posy(struct mundo *m, int tamy);
int mundo_set_tabl_actual(struct mundo *m, int act);
void mundo_set_tablero1(struct mundo *m, struct Celula *tablero);
void mundo_set_tablero2(struct mundo *m, struct Celula *tablero);
int mundo_get_posx(const struct mundo *m);
int mundo_get_posy(const struct mundo *m);
int mundo_get_tabl_actual(const struct mundo *m);
struct Celula* mundo_get_tablero1(const struct mundo *m);
struct Celula* mundo_get_tablero2(const struct mundo *m);
struct mundo *mundo_alloc(int posx, int posy);
void mundo_free(struct mundo *m);
void mundo_print(const struct mundo *m);
struct Celula *get_tablero_lectura(const struct mundo *m);
struct Celula *get_tablero_escritura(const struct mundo *m);

#endif
