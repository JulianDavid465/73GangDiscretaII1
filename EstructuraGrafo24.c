#include<assert.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>

#include "EstructuraGrafo24.h"

//  Funcion auxiliar para crear un vertice, debe hacer malloc
Vertex *create_vertex() {
    Vertex *vertex = malloc(sizeof(Vertex));
    if (vertex != NULL) {
        vertex->cant_vecinos = 0;
        for(unsigned i = 0; i<1000; i++){
            vertex->vecinos[i] = 0;}
        vertex->color = 0;
    }
    return vertex;
}

void destroy_vertex(Vertex *vertex) {
    if (vertex != NULL) {
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
void add_edge(grafoSt graf, u32 vert1, u32 vert2){
    if(graf->vert[vert1] == NULL){
        graf->vert[vert1] = create_vertex();
        graf->vertex_amm += 1;
    }
    if(graf->vert[vert2] == NULL){
        graf->vert[vert2] = create_vertex();
        graf->vertex_amm += 1;
    }

    u32 next_vecino = graf->vert[vert1]->cant_vecinos;
    graf->vert[vert1]->vecinos[next_vecino] = vert2;
    graf->vert[vert1]->cant_vecinos += 1;

    next_vecino = graf->vert[vert2]->cant_vecinos;
    graf->vert[vert2]->vecinos[next_vecino] = vert1;
    graf->vert[vert2]->cant_vecinos += 1;

    graf->edges_amm += 1;

    if(graf->delta < graf->vert[vert1]->cant_vecinos || graf->delta < graf->vert[vert2]->cant_vecinos){
        graf->delta += 1;
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

    if (graf != NULL) {
        graf->vertex_amm = 0;
        graf->edges_amm = 0;
        graf->delta = 0;
        //graph->vertices = vertex;
        for (u32 i = 0; i < V_MAX; i++) {
            graf->vert[i] = NULL;
        }
    }

    char c;
    char str[4];
    u32 num_vertices, num_edges;
    u32 vert1, vert2; // Variables para almacenar los vértices de las aristas

    // Lee la primera línea para obtener el tipo y el número de vértices y aristas
    u32 escaneados = scanf("%c %s %u %u", &c, str, &num_vertices, &num_edges);
    if(escaneados != 8){
        printf("error");
    }

    graf->vertex_amm = num_vertices;
    graf->edges_amm  = num_edges;


    for(u32 i = 0; i < num_edges ;i++){
        escaneados = scanf("%c %u %u", &c, &vert1, &vert2);
        if(escaneados != 8){
        printf("error");
    }

        add_edge(graf, vert1, vert2);
    }
    
    return graf;
}


//Debe ser como mucho O(m)
void destruirGrafo(grafoSt grafo){
    for(u32 i = 0; i < grafo->vertex_amm ;i++){
        destroy_vertex(grafo->vert[i]);
    }
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


/*
#include "EstructuraGrafo24.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Vertex *create_vertex(u32 number, u32 num_ver) {
    Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));
    if (vertex != NULL) {
        vertex->number = number;
        vertex->hood_amm = 0;
        vertex->hood = (u32 *)malloc(sizeof(u32) * (MAX_VERTICES-1));
        vertex->last_hood = vertex->hood;
        vertex->color = 0;
    }
    return vertex;
}

void destroy_vertex(Vertex *vertex) {
    if (vertex != NULL) {
        free(vertex->hood);
        free(vertex);
    }
}

Graph *create_graph(u32 num_ver) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    //Vertex *vertex = malloc(sizeof(Vertex)*num_ver);   
    if (graph != NULL) {
        graph->vertex_count = 0;
        graph->edge_count = 0;
        graph->delta = 0;
        //graph->vertices = vertex;
        for (u32 i = 0; i < num_ver; i++) {
            graph->vertices[i] = NULL;
        }
    }
    return graph;
}

void destroy_graph(Graph *graph) {
    if (graph != NULL) {
        for (u32 i = 0; i < graph->vertex_count; i++) {
            destroy_vertex(graph->vertices[i]);
        }
        free(graph);
    }
}

void add_edge(Graph *graph, u32 vert1, u32 vert2) {
    // Verifica si los vértices están dentro del rango válido
    if (vert1 >= MAX_VERTICES || vert2 >= MAX_VERTICES) {
        printf("Error: Vértices fuera del rango válido.\n");
        return;
    }

    // Verifica si los vértices ya existen en el grafo, si no, los crea
    if (graph->vertices[vert1] == NULL) {
        graph->vertices[vert1] = create_vertex(vert1);
        graph->vertex_count++;
    }
    if (graph->vertices[vert2] == NULL) {
        graph->vertices[vert2] = create_vertex(vert2);
        graph->vertex_count++;
    }

    // Agrega vert2 al hood de vert1
    Vertex *vertex1 = graph->vertices[vert1];
    if (vertex1->hood_amm < MAX_VERTICES - 1) {
        vertex1->hood[vertex1->hood_amm++] = vert2;
    } else {
        printf("Error: El hood de vert1 está lleno.\n");
        return;
    }

    // Agrega vert1 al hood de vert2
    Vertex *vertex2 = graph->vertices[vert2];
    if (vertex2->hood_amm < MAX_VERTICES - 1) {
        vertex2->hood[vertex2->hood_amm++] = vert1;
    } else {
        printf("Error: El hood de vert2 está lleno.\n");
        return;
    }

    // Incrementa el conteo de aristas
    graph->edge_count++;

    // Actualiza el delta del grafo si es necesario
    u32 degree_v1 = degree(vert1, graph);
    u32 degree_v2 = degree(vert2, graph);
    if (degree_v1 > graph->delta) {
        graph->delta = degree_v1;
    }
    if (degree_v2 > graph->delta) {
        graph->delta = degree_v2;
    }
}




u32 color(u32 vert, Graph *graph) {
    // Verifica si el vértice está dentro del rango válido
    if (vert >= MAX_VERTICES || graph->vertices[vert] == NULL) {
        printf("Error: Vértice fuera del rango válido o no existe en el grafo.\n");
        return 0;
    }

    // Obtiene el vértice del grafo
    Vertex *vertex = graph->vertices[vert];
    
    // Retorna el color del vértice
    return vertex->color;
}


u32 neighbor(u32 j, u32 vert, Graph *graph) {
    // Verifica si el vértice está dentro del rango válido
    if (vert >= MAX_VERTICES || graph->vertices[vert] == NULL) {
        printf("Error: Vértice fuera del rango válido o no existe en el grafo.\n");
        return 0;
    }

    // Obtiene el vértice del grafo
    Vertex *vertex = graph->vertices[vert];
    
    // Verifica si j está dentro del rango válido para los vecinos del vértice
    if (j >= vertex->hood_amm) {
        printf("Error: Vecino fuera del rango válido para el vértice especificado.\n");
        return 0;
    }

    // Retorna el nombre del j-ésimo vecino del vértice
    return vertex->hood[j];
}


void assign_color(u32 c, u32 vert, Graph *graph) {
    // Verifica si el vértice está dentro del rango válido
    if (vert >= MAX_VERTICES || graph->vertices[vert] == NULL) {
        printf("Error: Vértice fuera del rango válido o no existe en el grafo.\n");
        return;
    }

    // Asigna el color al vértice especificado
    graph->vertices[vert]->color = c;
}

void extract_colors(Graph *graph, u32 *colors) {
    // Verifica si el grafo es válido
    if (graph == NULL) {
        printf("Error: Grafo no válido.\n");
        return;
    }

    // Copia los colores de cada vértice al arreglo colors
    for (u32 i = 0; i < MAX_VERTICES; i++) {
        if (graph->vertices[i] != NULL) {
            colors[i] = graph->vertices[i]->color;
        }
    }
}


void import_colors(u32 *colors, Graph *graph) {
    // Verifica si el grafo y el arreglo de colores son válidos
    if (graph == NULL || colors == NULL) {
        printf("Error: Grafo o arreglo de colores no válido.\n");
        return;
    }

    // Copia los colores del arreglo colors a los vértices del grafo
    for (u32 i = 0; i < MAX_VERTICES; i++) {
        if (graph->vertices[i] != NULL) {
            graph->vertices[i]->color = colors[i];
        }
    }
}

Graph *build_graph_from_input_file(const char *filename) {
    // Crea un nuevo grafo


    // Abre el archivo para lectura
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo: %s\n", filename);
        return NULL;
    }

    char type[5]; // Para almacenar el tipo de línea ("p" o "e")
    u32 num_vertices, num_edges;
    u32 vert1, vert2; // Variables para almacenar los vértices de las aristas

    // Lee la primera línea para obtener el tipo y el número de vértices y aristas
    if (fscanf(0, "%s", type) != 1) {
        printf("Error al leer el tipo de línea.\n");
        fclose(file);
    //    destroy_graph(graph);
        return NULL;
    }

    if (strcmp(type, "p") != 0) {
        printf("Formato incorrecto. Se esperaba 'p edge <num_vertices> <num_edges'.\n");
        fclose(file);
     //   destroy_graph(graph);
        return NULL;
    }

    if (fscanf(file, " edge %u %u", &num_vertices, &num_edges) != 2) {
        printf("Error al leer el número de vértices y aristas.\n");
        fclose(file);
     //   destroy_graph(graph);
        return NULL;
    }

    if (num_vertices == 0 || num_edges == 0) {
        printf("Error: Grafo no válido.\n");
        fclose(file);
   //     destroy_graph(graph);
        return NULL;
    }

    Graph *graph = create_graph(num_vertices);
    if (graph == NULL) {
        printf("Error al crear el grafo.\n");
        return NULL;
    }

    // Añade las aristas al grafo
    for (u32 i = 0; i < num_edges; i++) {
        if (fscanf(file, "%s %u %u", type, &vert1, &vert2) != 3) {
            printf("Error al leer la arista número %u.\n", i+1);
            fclose(file);
            destroy_graph(graph);
            return NULL;
        }

        if (strcmp(type, "e") != 0) {
            printf("Formato incorrecto. Se esperaba 'e <vert1> <vert2>'.\n");
            fclose(file);
            destroy_graph(graph);
            return NULL;
        }

        add_edge(graph, vert1, vert2);
    }

    fclose(file);
    return graph;
}




u32 vertex_count(Graph *graph) {
    // Verifica si el grafo es válido
    if (graph == NULL) {
        printf("Error: Grafo no válido.\n");
        return 0;
    }

    // Inicializa el contador de vértices
    u32 count = 0;

    // Recorre todos los posibles vértices en el grafo
    for (u32 i = 0; i < MAX_VERTICES; i++) {
        // Si el vértice en la posición actual no es nulo, incrementa el contador
        if (graph->vertices[i] != NULL) {
            count++;
        }
    }

    return count;
}

u32 edge_count(Graph *graph) {
    // Verifica si el grafo es válido
    if (graph == NULL) {
        printf("Error: Grafo no válido.\n");
        return 0;
    }

    // Retorna el contador de aristas almacenado en el grafo
    return graph->edge_count;
}

u32 delta(Graph *graph) {
    // Verifica si el grafo es válido
    if (graph == NULL) {
        printf("Error: Grafo no válido.\n");
        return 0;
    }

    // Retorna el valor de delta almacenado en el grafo
    return graph->delta;
}




*/