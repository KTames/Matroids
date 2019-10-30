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