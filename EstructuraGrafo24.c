#include<assert.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "EstructuraGrafo24.h"


//  Funcion auxiliar para crear un vertice, debe hacer malloc
Vertex *create_vertex() {
    Vertex *vertex = malloc(sizeof(Vertex));
    vertex->cantidad = 20;
    if (vertex != NULL) {
        vertex->cant_vecinos = 0;
        vertex->vecinos = malloc(vertex->cantidad*sizeof(u32));
        //memset(vertex->vecinos, 0, sizeof(vertex->vecinos));
    }
    return vertex;
}

void destroy_vertex(Vertex *vertex) {
    if (vertex != NULL) {
        free(vertex->vecinos);
        free(vertex);
    }
}    



void destroy_graph(grafoSt graph) {
    if (graph != NULL) {
        for (u32 i = 0; i < graph->vertex_amm; i++) {
            destroy_vertex(graph->vert[i]);
        }
        free(graph);
    }
}

//Ver si un vertice esta en el grafo
//bool in_grafo(u32 vert, grafoSt grafo);

/*
  Funcion auxiliar para añadir una arista a un grafo, la idea es que mire cuales de los dos vertices
    ya se han añadido al grafo, se crean los que no esten ya creados, y se toma alguno para
    ir a su arreglo de hood y añadir al nuevo vecino, y lo mismo con el otro. 
*/

void add_edge(grafoSt graf, u32 vert1, u32 vert2) {

    if (graf->vert[vert1] == NULL) {
        graf->vert[vert1] = create_vertex();
    }
    if (graf->vert[vert2] == NULL) {
        graf->vert[vert2] = create_vertex();
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
u32 grado(u32 vert, grafoSt grafo){
    if(vert < grafo->vertex_amm){
        return grafo->vert[vert]->cant_vecinos;
    } else {
        return 0;
    }
}

color colour(u32 vert, grafoSt grafo){
    if(vert < grafo->vertex_amm){
        return grafo->vert[vert]->color;
    } else {
        return (1<<30) - 1;
    }
}


/*
    Devuelve el nombre del j-esimo vecino de vert para acceder a SUS datos, tendra la pinta de
  grafo.vert[j]
*/
u32 vecino(u32 j, u32 vert, grafoSt grafo){
    if(vert < grafo->vertex_amm && j < grado(vert, grafo)){
        return grafo->vert[vert]->vecinos[j];
    } else {
        return (1<<30) - 1;
    }
}

void asignarColor(color c, u32 vert, grafoSt grafo){
    if(vert < grafo->vertex_amm){
        grafo->vert[vert]->color = c;
    }
}

//Deposita en colour[i] el color del vertice i, colour tiene n lugares
void extraerColor(grafoSt grafo, color *colour){
    for(u32 i = 0; i < grafo->vertex_amm ;i++){
        colour[i] = grafo->vert[i]->color;
    }
}

//Asigna el vertice i el color colour[i]
void importarColores(color *colour, grafoSt grafo){
    for(u32 i = 0; i < grafo->vertex_amm ;i++){
        asignarColor(colour[i], i, grafo);
    }
}

//  Crea un grafo desde el standard input. En caso de error se devuelve NULL, colorea todos los vertices con 
//  el color 0
grafoSt construirGrafo(){
    grafoSt graf = malloc(sizeof(Grafo__St));

    char c;
    char str[4];
    u32 num_vertices, num_edges;
    u32 vert1, vert2; // Variables para almacenar los vértices de las aristas

    // Lee la primera línea para obtener el tipo y el número de vértices y aristas
    u32 escaneados = scanf("%c %s %u %u", &c, str, &num_vertices, &num_edges);
    if(escaneados != 4){
        printf("error");
    }

    if (graf != NULL) {
        graf->vertex_amm = 0;
        graf->edges_amm = 0;
        graf->delta = 0;
        //graph->vertices = vertex;
        graf->vert = malloc(num_vertices * sizeof(Vertex *));

        for (u32 i = 0; i < num_vertices; i++) {
            graf->vert[i] = NULL;
        }

        graf->vertex_amm = num_vertices;
        graf->edges_amm  = num_edges;


        for(u32 i = 0; i < num_edges ;i++){
            escaneados = scanf(" %c %u %u", &c, &vert1, &vert2);
            if(escaneados != 3){
            printf("error");
            }

            add_edge(graf, vert1, vert2);
        }
        
    }
    return graf;
}


//Debe ser como mucho O(m)
void destruirGrafo(grafoSt grafo){
    for(u32 i = 0; i < grafo->vertex_amm ;i++){
        destroy_vertex(grafo->vert[i]);
    }
    free(grafo->vert);
    free(grafo);
}

u32 numeroDeVertices(grafoSt grafo){
    return grafo->vertex_amm;
}

u32 numeroDeLados(grafoSt grafo){
    return grafo->edges_amm;
}

//  Debe ser O(1)
u32 delta(grafoSt grafo){
    return grafo->delta;
}

