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
    for (u32 i = 0; i < V_MAX; i++) {
        if (graph->vert[i] != NULL) {
            printf("Vértice %u: Grado %u\n", i, grado(i, graph));
        }
    }

    // Imprimir los colores de cada vértice
    printf("Colores de los vértices:\n");
    for (u32 i = 0; i < V_MAX; i++) {
        if (graph->vert[i] != NULL) {
            printf("Vértice %u: Color %u\n", i, colour(i, graph));
        }
    }

    // Imprimir los vecinos de cada vértice
    printf("Vecinos de los vértices:\n");
    for (u32 i = 0; i < V_MAX; i++) {
        if (graph->vert[i] != NULL) {
            printf("Vértice %u: ", i);
            for (u32 j = 0; j < grado(i, graph); j++) {
                printf("%u ", vecino(j, i, graph));
            }
            printf("\n");
        }
    }

    // Liberar la memoria del grafo
    destruirGrafo(graph);

    return 0; // Salir del programa con éxito
} 