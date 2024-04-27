#ifndef GRAPH_24
#define GRAPH_24

#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>

//Definicion del tipo u32, uso u_int32_t porque ya está hecho y, según leí, unsigned int o long unsigned int no siempre
//  tienenel largo pensado y le reduce portabilidad 
typedef unsigned int u32;

//Definicion segun la consigna
typedef u32 color;

/*
    Cada vertice tendrá su número que lo identifique, la cantidad de vecinos, el vecindario o hood,
  Un arreglo de punteros a los vertices a los que es adyacente menos el ultimo. La consigna dice que
  ConstruirGrafo() debe ser O(m) y si lo pongo a recorrer todo el arreglo del hood queda O(m^2) aprox, 
  entonces cada vertice tiene un puntero al punto del arreglo donde está la dirección de la ultima
  arista en añadirse, y un color para pintarlo

p edge 5 5
e 3 0
e 4 1
e 2 4
e 1 2
e 3 1

*/

typedef struct vertexSt{
    u32     cant_vecinos;
    u32     *vecinos;
    color   color;
    u32     cantidad;
} Vertice;

//  Los grafos tienen su lista de vertices la cantidad de vertices y aristas y el Delta del grafo.


typedef struct Grafo{
    Vertice **vert;
    u32     cant_vertices;
    u32     cant_lados;
    u32     delta;
}GrafoSt;

//  Funcion auxiliar para crear un vertice, debe hacer malloc
Vertice *crear_vertice();
  

/*
  Funcion auxiliar para añadir una arista a un grafo, la idea es que mire cuales de los dos vertices
    ya se han añadido al grafo, se crean los que no esten ya creados, y se toma el primero para
    añadir al segundo a sus vecinos y luego añadir al primero a los vecinos del segundo
*/
void anadir_lado(GrafoSt *graf, u32 vert1, u32 vert2);

#endif