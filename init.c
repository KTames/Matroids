#include <stdio.h>
#include "MatroidEvaluator.h"

bool are_equal_int(void* a, void* b) {
    return *(int*) a == *(int*)b;
}

void copy_result_int(void* element, void* array, int index) {
    int* int_array = array;
    int number = *(int*)element;
    
    int_array[index] = number;
}

void copy_result_double(void* element, void* array, int index) {
    double* double_array = array;
    double number = *(double*)element;
    
    double_array[index] = number;
}

void copy_result_char(void* element, void* array, int index) {
    char* char_array = array;
    char _char = *(char*)element;
    
    char_array[index] = _char;
}

bool isEven(void* number, va_list args) {
    return *(int*)number % 2 == 0;
}

bool isLessThan100(void* number, va_list args) {
    return *(double*)number < 100;
}

bool isLowerCase(void* _char, va_list args) {
    return *(char*) _char <= 'z' && *(char*) _char >= 'a';
}

void firstPartTest()
{
    int opciones1[] = {1, 2, 3, 4, 5, 6};
    int resultados1[6];
    Matroid m1 = {isEven, copy_result_int, 6, sizeof(int), opciones1, resultados1};
    
    double opciones2[] = {100.1, 24.5, 302.4, 423.0, 56.123, 61.765};
    double resultados2[6];
    Matroid m2 = {isLessThan100, copy_result_double, 6, sizeof(double), opciones2, resultados2};
    
    char opciones3[] = {'a', 'A', 'b', 'B', 'c', 'C'};
    char resultados3[6];
    Matroid m3 = {isLowerCase, copy_result_char, 6, sizeof(char), opciones3, resultados3};
    
    Matroid *matroid_array[] = {&m1, &m2, &m3};
    
    multiple_matroid_evaluate(matroid_array, 3);
    

    printf("--------------- PART A TEST ---------------\n");

    printf("First matroid results:\n[\t");
    for (int i = 0; i < m1.results_length; i++) {
        printf("%d\t", resultados1[i]);
    }

    printf("]\n\nSecond matroid results:\n[\t");
    for (int i = 0; i < m2.results_length; i++) {
        printf("%f\t", resultados2[i]);
    }

    printf("]\n\nThird matroid results:\n[\t");
    for (int i = 0; i < m3.results_length; i++) {
        printf("%c\t", resultados3[i]);
    }
    
    printf("]\n\n");
}

void add_result_int(void* array, void* result, int index) {
    int* array_int = array;
    array_int[index] = *(int*) result;
}

void secondPartTest()
{
    // Se va a evaluar con la función de números pares
    int matroid1data[] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15}; // Resultado: 0, 2, 4, 6, 8, 10, 12, 14
    int matroid2data[] = { 2,  4,  8,  7,  1,  3, 12, 11, 28, 27,  0};                     // Resultado: 0, 2, 4, 8, 12, 28
    int matroid3data[] = {12,  0,  2,  6,  4, 28,  3,  7,  9,  1, 11};                     // Resultado: 0, 2, 4, 6, 12, 28
    int matroid4data[] = { 0,  1,  2,  3,  4, 11, 12, 13, 26, 27, 28};                     // Resultado: 0, 2, 4, 12, 26, 28
    int matroid5data[] = { 0, 13,  4, 12,  2, 11, 13,  7,  9, 14};                         // Resultado: 0, 2, 4, 12, 14

    // Intersección final esperada: 0, 2, 4, 12
    int matroid1length = 16;
    int matroid2length = 11;
    int matroid3length = 11;
    int matroid4length = 11;
    int matroid5length =  10;
    
    int minLength = 10; // La longitud del matroid más corto

    int resultsMatroid1[matroid1length];
    Matroid m1  = {isEven, copy_result_int, matroid1length, sizeof(int), matroid1data, resultsMatroid1};

    int resultsMatroid2[matroid2length];
    Matroid m2  = {isEven, copy_result_int, matroid2length, sizeof(int), matroid2data, resultsMatroid2};

    int resultsMatroid3[matroid3length];
    Matroid m3  = {isEven, copy_result_int, matroid3length, sizeof(int), matroid3data, resultsMatroid3};

    int resultsMatroid4[matroid4length];
    Matroid m4  = {isEven, copy_result_int, matroid4length, sizeof(int), matroid4data, resultsMatroid4};

    int resultsMatroid5[matroid5length];
    Matroid m5  = {isEven, copy_result_int, matroid5length, sizeof(int), matroid5data, resultsMatroid5};

    Matroid *matroid_array[] = {&m1, &m2, &m3, &m4, &m5};

    int intersection[minLength];
    
    int cant_results = matroid_intersection_evaluate(matroid_array, 5, intersection, add_result_int, are_equal_int);

    printf("\n--------------- PART B TEST ---------------\n");

    printf("Results per matroid:\n");
    for (int matroid_index = 0; matroid_index < 5; matroid_index++) {
        Matroid* m = matroid_array[matroid_index];
        printf("%d: [\t", matroid_index + 1);
        for (int item_index = 0; item_index < m->results_length; item_index++) {
            printf("%d\t", ((int*)(m->results))[item_index]);
        }
        printf("]\n");
    }
    

    printf("\nIntersection result:\n[\t");
    for (int result_index = 0; result_index < cant_results; result_index++) {
        printf("%d\t", intersection[result_index]);
    }
    printf("]\n\n");
}

int main()
{
    firstPartTest();
    secondPartTest();
    
}
