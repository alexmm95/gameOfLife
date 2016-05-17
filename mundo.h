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
void mundo_print(const struct mundo *m);
struct mundo *mundo_alloc(int posx, int posy);
void mundo_free(struct mundo *m);


#endif
