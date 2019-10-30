#include <stdio.h>
#include "MatroidEvaluator.h"

void single_matroid_evaluate(Matroid *matroid, ...)
{
    int items_length = matroid->items_legth;
    int cant_results = 0;
    
    va_list args;
    va_start(args, matroid);
    va_list args_temp;
    va_start(args_temp, matroid);
    
#pragma omp parallel for shared(cant_results)
    for (int item_index = 0; item_index < items_length; item_index++)
    {
        va_copy(args_temp, args);
        
        if (matroid->evaluateFunction(matroid->options + item_index * matroid->item_size, args_temp)) {

            matroid->copyResultToIndex(matroid->options + item_index * matroid->item_size, matroid->results, cant_results++);
        }
    }

    va_end(args_temp);
    va_end(args);
    matroid->results_length = cant_results;
}

void multiple_matroid_evaluate(Matroid **matroid_array, int cant_matroids)
{
    if (cant_matroids == 0)
        return;

#pragma omp parallel for
    for (int matroid_index = 0; matroid_index < cant_matroids; matroid_index++)
    {
        single_matroid_evaluate(matroid_array[matroid_index]);
    }
}

int matroid_intersection_evaluate(Matroid **matroid_array, int cant_matroids, void* results, void (*addResult)(void*, void*, int), bool (*areEqual)(void*, void*))
{
    if (cant_matroids == 0)
        return 0;
//
    multiple_matroid_evaluate(matroid_array, cant_matroids);
    int lowest_element_count = matroid_array[0]->results_length;;
    int lowest_element_index = 0;

    // Se elige el matroid con menos elementos en su solución
    for (int matroid_index = 1; matroid_index < cant_matroids; matroid_index++)
    {
        if (matroid_array[matroid_index]->results_length < lowest_element_count)
        {
            lowest_element_count = matroid_array[matroid_index]->results_length;
            lowest_element_index = matroid_index;
        }
    }

    int cant_results = 0;

    Matroid* shortest_matroid = matroid_array[lowest_element_index];

#pragma omp parallel for shared(cant_results)
    
    for (int result_index = 0; result_index < lowest_element_count; result_index++) // Recorre cada resultado del matroid más pequeño
    {
        bool found_in_every_other = true;
        void * target = shortest_matroid->results + shortest_matroid->item_size * result_index;
        
        for (int matroid_index = 0; matroid_index < cant_matroids; matroid_index++) {
            if (matroid_index != lowest_element_index) {
                
                Matroid* matroid_to_evaluate = matroid_array[matroid_index];
                bool local_found = false;
                
                for (int item_index = 0; item_index < matroid_to_evaluate->results_length; item_index++)
                {
                    if (areEqual(target, matroid_to_evaluate->results + item_index * matroid_to_evaluate->item_size)) {
                        local_found = true;
                        break;
                    }
                }
                
                if (!local_found) {
                    found_in_every_other = false;
                    break;
                }
            }
        }
        
        if (found_in_every_other)
            addResult(results, target, cant_results++);
    }

    return cant_results;
}