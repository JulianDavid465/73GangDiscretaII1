#include<assert.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "APIG24.h"


//  Funcion auxiliar para crear un vertice, debe hacer malloc
Vertice *crear_vertice() {
    Vertice *vertice = malloc(sizeof(Vertice));
    vertice->cantidad = 20;
    if (vertice != NULL) {
        vertice->cant_vecinos = 0;
        vertice->vecinos = malloc(vertice->cantidad*sizeof(u32));
        //memset(vertice->vecinos, 0, sizeof(vertice->vecinos));
    }
    return vertice;
}

void destruir_vertice(Vertice *vertice) {
    if (vertice != NULL) {
        free(vertice->vecinos);
        free(vertice);
    }
}

/*
  Funcion auxiliar para añadir una arista a un grafo, la idea es que mire cuales de los dos vertices
    ya se han añadido al grafo, se crean los que no esten ya creados, y se toma alguno para
    ir a su arreglo de hood y añadir al nuevo vecino, y lo mismo con el otro. 
*/

void anadir_lado(Grafo graf, u32 vert1, u32 vert2) {

    if (graf->vert[vert1] == NULL) {
        graf->vert[vert1] = crear_vertice();
    }
    if (graf->vert[vert2] == NULL) {
        graf->vert[vert2] = crear_vertice();
    }

    u32 next_vecino = graf->vert[vert1]->cant_vecinos;
    if (graf->vert[vert1]->cant_vecinos == graf->vert[vert1]->cantidad) {
        graf->vert[vert1]->cantidad *= 2;
        u32 *nuevos_vecinos = realloc(graf->vert[vert1]->vecinos, graf->vert[vert1]->cantidad * sizeof(u32));
        if (nuevos_vecinos == NULL) {
            // Manejo de error (liberar memoria previa, etc.)
            return;
        }
        graf->vert[vert1]->vecinos = nuevos_vecinos;
    }
    graf->vert[vert1]->vecinos[next_vecino] = vert2;
    graf->vert[vert1]->cant_vecinos++;

      u32 next_vecino_ = graf->vert[vert2]->cant_vecinos;
    if (graf->vert[vert2]->cant_vecinos == graf->vert[vert2]->cantidad) {
        graf->vert[vert2]->cantidad += 1000;
        u32 *nuevos_vecinos_ = realloc(graf->vert[vert2]->vecinos, graf->vert[vert2]->cantidad * sizeof(u32));
        if (nuevos_vecinos_ == NULL) {
            // Manejo de error (liberar memoria previa, etc.)
            return;
        }
        graf->vert[vert2]->vecinos = nuevos_vecinos_;
    }
    graf->vert[vert2]->vecinos[next_vecino_] = vert1;
    graf->vert[vert2]->cant_vecinos++;

    // Repetir el mismo proceso para el segundo vértice...

    if (graf->delta < graf->vert[vert1]->cant_vecinos || graf->delta < graf->vert[vert2]->cant_vecinos) {
        graf->delta++;
    }
}

// Devuelve el grado del vertice de un grafo
u32 Grado(u32 vert, Grafo grafo){
    if(vert < grafo->cant_vertices){
        return grafo->vert[vert]->cant_vecinos;
    } else {
        return 0;
    }
}

color Color(u32 vert, Grafo grafo){
    if(vert < grafo->cant_vertices){
        return grafo->vert[vert]->color;
    } else {
        return (1<<30) - 1;
    }
}

/*
    Devuelve el nombre del j-esimo vecino de vert para acceder a SUS datos, tendra la pinta de
  grafo.vert[j]
*/
u32 Vecino(u32 j, u32 vert, Grafo grafo){
    if(vert < grafo->cant_vertices && j < Grado(vert, grafo)){
        return grafo->vert[vert]->vecinos[j];
    } else {
        return (1<<30) - 1;
    }
}

void AsignarColor(color c, u32 vert, Grafo grafo){
    if(vert < grafo->cant_vertices){
        grafo->vert[vert]->color = c;
    }
}

//Deposita en colour[i] el color del vertice i, colour tiene n lugares
void ExtraerColores(Grafo grafo, color *colour){
    for(u32 i = 0; i < grafo->cant_vertices ;i++){
        colour[i] = grafo->vert[i]->color;
    }
}

//Asigna el vertice i el color colour[i]
void ImportarColores(color *colour, Grafo grafo){
    for(u32 i = 0; i < grafo->cant_vertices ;i++){
        AsignarColor(colour[i], i, grafo);
    }
}

//  Crea un grafo desde el standard input. En caso de error se devuelve NULL, colorea todos los vertices con 
//  el color 0
Grafo ConstruirGrafo(){
    Grafo graf = malloc(sizeof(GrafoSt));

    char c;
    char str[4];
    u32 num_vertices, num_lados;
    u32 vert1, vert2; // Variables para almacenar los vértices de las aristas

    // Lee la primera línea para obtener el tipo y el número de vértices y aristas
    u32 escaneados = scanf("%c %s %u %u", &c, str, &num_vertices, &num_lados);
    if(escaneados != 4){
        printf("error");
        return NULL;
    }

    if (graf != NULL) {
        graf->cant_vertices = 0;
        graf->cant_lados = 0;
        graf->delta = 0;
        //graf->vertices = vertice;
        graf->vert = malloc(num_vertices * sizeof(Vertice *));

        for (u32 i = 0; i < num_vertices; i++) {
            graf->vert[i] = NULL;
        }

        graf->cant_vertices = num_vertices;
        graf->cant_lados  = num_lados;


        for(u32 i = 0; i < num_lados ;i++){
            escaneados = scanf(" %c %u %u", &c, &vert1, &vert2);
            if(escaneados != 3){
            printf("error");
            }

            anadir_lado(graf, vert1, vert2);
        }
        
    }
    return graf;
}


//Debe ser como mucho O(m)
void DestruirGrafo(Grafo grafo){
    for(u32 i = 0; i < grafo->cant_vertices ;i++){
        destruir_vertice(grafo->vert[i]);
    }
    free(grafo->vert);
    free(grafo);
}

u32 NumeroDeVertices(Grafo grafo){
    return grafo->cant_vertices;
}

u32 NumeroDeLados(Grafo grafo){
    return grafo->cant_lados;
}

//  Debe ser O(1)
u32 Delta(Grafo grafo){
    return grafo->delta;
}

