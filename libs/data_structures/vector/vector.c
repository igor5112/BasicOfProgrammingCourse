#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

vector createVector(size_t n) {
    vector v;
    v.data = malloc(sizeof(int) * n);

    if (n > 0 && v.data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }

    v.size = 0;
    v.capacity = n;

    return v;
}

void reserve(vector *v, size_t newCapacity) {

    if (newCapacity == 0) {
        free(v->data);
        v->data == NULL;
    } else {
        int *newData = realloc(v->data, sizeof(int) * newCapacity);
        if (newData == NULL) {
            fprintf(stderr, "bad alloc");
            exit(1);
        } else {
            v->data = newData;
        }
    }
    v->capacity = newCapacity;

    if (newCapacity < v->size) {
        v->size = newCapacity;
    }
}

void clear(vector *v){
    v->size = 0;
}

void shrinkToFit(vector *v) {
    v->data = realloc(v->data, (v->size = v->capacity) * sizeof(int));
}

void deleteVector(vector *v){
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}
