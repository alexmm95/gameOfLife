#include <stdio.h>
#include "mundo.h"


int main()
{
        struct Celula mundo[NUMCOL][NUMFIL];
        struct Celula celulasVivas[] = {{1},{1},{1},{1},{1}};
        iniciaMundo(mundo, celulasVivas);
        printf("\nJuego de la vida, Version 1.0\n\n");
        imprimeMundo(mundo);

        ejecutaMundo(mundo);

        printf("\nMundo evolucionado\n\n");

        imprimeMundo(mundo);
        return 1;
}
