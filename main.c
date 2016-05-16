#include <stdio.h>
#include "mundo.h"
#include <stdlib.h>


int main()
{	
	struct mundo *m;
	
	int posx = 20;
	int posy = 20;

	m = mundo_alloc(posx,posy);

	mundo_print(m);
	inicia_mundo(m);
	printf("\nJuego de la vida, Version 2.0\n\n");
	imprime_mundo(m);

	ejecuta_mundo(m);
	
        printf("\nMundo evolucionado\n\n");
        imprime_mundo(m);
	
	mundo_free(m);

        return 1;
}
