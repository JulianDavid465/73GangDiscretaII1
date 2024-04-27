#ifndef APIG24_H_2
#define APIG24_H_2


#include <stdio.h>
#include <stdlib.h>
#include "APIG24.h"

//Colorea los vertices de un grafo dado un orden por "Orden"
u32 Greedy(Grafo G,u32* Orden);

//
char GulDukat(Grafo G,u32* Orden);

//
char ElimGarak(Grafo G,u32* Orden);
#endif