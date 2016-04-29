#include <stdio.h>
#include "tablero.h"


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
}
