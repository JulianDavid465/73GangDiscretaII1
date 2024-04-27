#include <stdio.h>
#include "APIG24.h"
#include "API2024Parte2.h"

int main() {
    // Construir el grafo desde el archivo de entrada
    Grafo graph = ConstruirGrafo();
    if (graph == NULL) {
        printf("Error al construir el grafo desde el archivo de entrada.\n");
        return 1; // Salir del programa con código de error
    }

    // Imprimir información básica sobre el grafo
    printf("Número de vértices: %u\n", NumeroDeVertices(graph));
    printf("Número de aristas: %u\n", NumeroDeLados(graph));
    printf("Delta: %u\n", Delta(graph));

    //u32 orden[NumeroDeVertices(graph)];
    
    u32 orden[5] = {4, 3, 2, 1, 0};

    u32 cantColores = Greedy(graph, orden);

    // Imprimir los colores de cada vértice
    printf("Colores de los vértices:\n");
    printf("La cantidad de colores es %d\n", cantColores);
    for (u32 i = 0; i < graph->cant_vertices; i++) {
        if (graph->vert[i] != NULL) {
            //AsignarColor(i%10, i, graph);
            printf("Vértice %u: Color %u\n", i, Color(i, graph));
        }
    }

    // Liberar la memoria del grafo
    DestruirGrafo(graph);

    return 0; // Salir del programa con éxito
} 