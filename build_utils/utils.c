#include "utils.h"
#include <stdio.h>
int get_file_size(FILE* f) {
    fseek(f, 0, SEEK_END);
    int size = ftell(f); 
    fseek(f, 0, SEEK_SET);
    return size;
}