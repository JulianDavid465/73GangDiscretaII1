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
char GulDukat(Grafo G, u32* Orden){
    u32 orden_i = 0;
    u32 vertices_i = NumeroDeVertices(G);


    u32 colores_cuatro[vertices_i];
    u32 cuatro_i = 0;
    u32 colores_pares[vertices_i];
    u32 pares_i = 0;
    u32 colores_impares[vertices_i];
    u32 impares_i = 0;

    for (u32 i = 0; i < vertices_i; i++){
        if((Color(i, G) % 4) == 0){
            colores_cuatro[cuatro_i] = i;
            cuatro_i++;
        } else if((Color(i, G) % 4) == 2){
            colores_pares[pares_i] = i;
            pares_i++;
        } else if((Color(i, G) % 2) == 1){
            colores_impares[impares_i] = i;
            impares_i++;
        }
    }

    for (u32 j = 0; j < cuatro_i; j++){
        u32 M = 0;
        for (u32 h = 0; h < cuatro_i-1; h++){
            if(colores_cuatro[h] != -1){
                if(Grado(colores_cuatro[h], G) < Grado(colores_cuatro[h+1], G)){
                    M = h+1;
                }
            }
        }
        Orden[orden_i] = colores_cuatro[M];
        orden_i++;
        colores_cuatro[M] = -1;
    }

    for (u32 j = 0; j < pares_i; j++){
        u32 M = 0;
        for (u32 h = 0; h < pares_i-1; h++){
            if(colores_pares[h] != -1){
                if(Grado(colores_pares[h], G) < Grado(colores_pares[h+1], G)){
                    M = h+1;
                }
            }
        }
        Orden[orden_i] = colores_pares[M];
        orden_i++;
        colores_pares[M] = -1;
    }

    for (u32 j = 0; j < impares_i; j++){
        u32 M = 0;
        for (u32 h = 0; h < impares_i-1; h++){
            if(colores_impares[h] != -1){
                if(Grado(colores_impares[h], G) < Grado(colores_impares[h+1], G)){
                    M = h+1;
                }
            }
        }
        Orden[orden_i] = colores_impares[M];
        orden_i++;
        colores_impares[M] = -1;
    }

    return "0";

}

//
char ElimGarak(Grafo G, u32* Orden){
    return "a";
}