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