#include <stdio.h>
#include "EstructuraGrafo24.h"

int main() {
    // Construir el grafo desde el archivo de entrada
    grafoSt graph = construirGrafo();
    if (graph == NULL) {
        printf("Error al construir el grafo desde el archivo de entrada.\n");
        return 1; // Salir del programa con código de error
    }

    // Imprimir información básica sobre el grafo
    printf("Número de vértices: %u\n", numeroDeVertices(graph));
    printf("Número de aristas: %u\n", numeroDeLados(graph));
    printf("Delta: %u\n", delta(graph));

    // Imprimir los grados de cada vértice
    printf("Grados de los vértices:\n");
    for (u32 i = 0; i < graph->cant_vertices; i++) {
        if (graph->vert[i] != NULL) {
            printf("Vértice %u: Grado %u\n", i, grado(i, graph));
        }
    }

    // Imprimir los colores de cada vértice
    printf("Colores de los vértices:\n");
    for (u32 i = 0; i < graph->cant_vertices; i++) {
        if (graph->vert[i] != NULL) {
            asignarColor(i%10, i, graph);
            printf("Vértice %u: Color %u\n", i, colour(i, graph));
        }
    }

    color colour1[numeroDeVertices(graph)];
    

    // Imprimir los vecinos de cada vértice
    printf("Vecinos de los vértices:\n");
    for (u32 i = 0; i < graph->cant_vertices; i++) {
        if (graph->vert[i] != NULL) {
            printf("Vértice %u: ", i);
            for (u32 j = 0; j < grado(i, graph); j++) {
                printf("%u ", vecino(j, i, graph));
            }
            printf("\n");
        }
    }

    extraerColor(graph, colour1);
    printf("Todos los colores son: \n");
    for(u32 i = 0; i < numeroDeVertices(graph) ;i++){
        printf("Color de vertice %d es %d\n", i, colour1[i]);
    }

    color colour2[numeroDeVertices(graph)];
    for(u32 i = 0; i < numeroDeVertices(graph) ;i++){
        colour2[i] = i%15;
    }

    importarColores(colour2, graph);
    printf("Los colores nuevos son: \n");
    for(u32 i = 0; i < numeroDeVertices(graph) ;i++){
        printf("Color de vertice %d es %d\n", i, colour2[i]);
    }
    asignarColor(999, numeroDeVertices(graph)-1, graph);
    printf("color de %d es %d\n", numeroDeVertices(graph)-1, colour(numeroDeVertices(graph)-1, graph));

    // Liberar la memoria del grafo
    destruirGrafo(graph);

    return 0; // Salir del programa con éxito
} 