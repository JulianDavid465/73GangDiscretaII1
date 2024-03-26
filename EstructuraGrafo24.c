#include<assert.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>

#include "EstructuraGrafo24.h"

//  Funcion auxiliar para crear un vertice, debe hacer malloc
vertex *create_vertex(u32 name);

//Ver si un vertice esta en el grafo
bool in_grafo(u32 name);

/*
  Funcion auxiliar para añadir una arista a un grafo, la idea es que mire cuales de los dos vertices
    ya se han añadido al grafo, se crean los que no esten ya creados, y se toma alguno para
    ir a su arreglo de hood y añadir al nuevo vecino, y lo mismo con el otro. 
*/
void add_edge(grafoSt *graf, u32 vert1, u32 vert2);

// Devuelve el grado del vertice de un grafo
u32 grado(u32 vert, grafoSt grafo){
    if(vert < grafo.vertex_amm){
        return grafo.vert[vert]->hood_amm;
    } else {
        return 0;
    }
}

color colour(u32 vert, grafoSt grafo){
    if(vert < grafo.vertex_amm){
        return grafo.vert[vert]->hood_amm;
    } else {
        return (1<<32) - 1;
    }
}

/*
    Devuelve el nombre del j-esimo vecino de vert para acceder a SUS datos, tendra la pinta de
  grafo.vert[j]
*/
u32 vecino(u32 j, u32 vert, grafoSt grafo){
    if(vert < grafo.vertex_amm && j < grado(vert, grafo)){
        return grafo.vert[vert]->hood[j];
    } else {
        return (1<<32) - 1;
    }
}

void asignarColor(color c, u32 vert, grafoSt grafo){
    if(vert < grafo.vertex_amm){
        grafo.vert[vert]->color = c;
    }
}

//Deposita en colour[i] el color del vertice i, colour tiene n lugares
void extraerColor(grafoSt grafo, color *colour){
    for(u32 i = 0; i < grafo.vertex_amm ;i++){
        colour[i] = grafo.vert[i]->color;
    }
}

//Asigna el vertice i el color colour[i]
void importarColores(color *colour, grafoSt grafo){
    for(u32 i = 0; i < grafo.vertex_amm ;i++){
        asignarColor(colour[i], grafo.vert[i], grafo);
    }
}

//  Crea un grafo desde el standard input. En caso de error se devuelve NULL, colorea todos los vertices con 
//  el color 0
grafoSt construirGrafo();

//Debe ser como mucho O(m)
void destruirGrafo(grafoSt grafo);

u32 numeroDeVertices(grafoSt grafo){
    return grafo.vertex_amm;
}

u32 numeroDeLados(grafoSt grafo){
    return grafo.edges_amm;
}

//  Debe ser O(1)
u32 delta(grafoSt grafo){
    return grafo.big_delta;
}