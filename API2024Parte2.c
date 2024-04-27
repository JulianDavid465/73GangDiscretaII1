#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//el .h de abajo debe tener definida GrafoSt, u32 y color.
#include "API2024Parte2.h"

//Colorea los vertices de un grafo dado un orden por "Orden"

/*
    Declara dos arreglos, estos arreglos contienen valores en las posiciones i
    que indican si el color i está disponible.
    El primero es para ver las disponibilidades de los colores para pintar un vertice dado, 
    el otro es un registro de todos los colores usados
    Establece el valor de los arreglos en cero.
    Para cada vertice mira sus vecinos y les mira los colores:
        Toma el color i de un vecino y establece a coloresDisponibles en -1
        indicando que el color i ya está usado por un vecino.
    El color 0 no debe estar disponible para colorear y busca en coloresDisponibles
    el primer, el menor, color disponible y lo colores.
    Luego mira el registro de colores usados y los cuenta y retorna la cantidad
    
*/

u32 Greedy(Grafo G, u32* Orden){
    //Verificar que es un orden. Me falta
    u32 n = NumeroDeVertices(G);
    color coloresDisponibles[n];
    color coloresFinal[n];
    memset(coloresFinal, 0, sizeof(coloresFinal));
    for(u32 i = 0; i < n ;i++){
        memset(coloresDisponibles,0 , sizeof(coloresDisponibles));
        for(u32 j = 0; j < Grado(Orden[i], G) ; j++){
            coloresDisponibles[Color(Vecino(j, Orden[i], G), G)] = -1;
        }
        u32 k = 0;
        coloresDisponibles[0] = -1;
        while(coloresDisponibles[k] == -1){
            k++;
        }
        AsignarColor(k, Orden[i], G);
        coloresFinal[k] = -1;
    }
    u32 l = 1;
    while(coloresFinal[l] == -1){
        l++;
    }

    return l-1;
    
}

//
char GulDukat(Grafo G,u32* Orden){
    return "a";
}

//
char ElimGarak(Grafo G,u32* Orden){
    return "a";
}