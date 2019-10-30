#ifndef MatroidEvaluator_h
#define MatroidEvaluator_h

#include <omp.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

typedef struct {
    bool (*evaluateFunction)(void*, va_list);     // Función que evalúa cada elemento
    void (*copyResultToIndex)(void*, void*, int); // Copia el valor de un puntero a un índice en el array de resultados
    int items_legth;                              // Cantidad de elementos a evaluar
    int item_size;                                // Tamaño del tipo de datos del Matroid en bytes
    void *options;                                // Elementos a evaluar
    void *results;                                // Array con los resultados
    int results_length;                           // Cantidad de resultados del matroid
} Matroid;


void single_matroid_evaluate(Matroid *, ...);                                                                            // Evalúa en paralelo todos los elementos del matroid
void multiple_matroid_evaluate(Matroid **, int);                                                                         // Evalúa en paralelo todos los matroids
int matroid_intersection_evaluate(Matroid **, int, void*, void (*addResult)(void*, void*, int), bool (*)(void*, void*)); // Evalúa los matroids y saca en paralelo la intersección entre sus resultados


#endif /* MatroidEvaluator_h */