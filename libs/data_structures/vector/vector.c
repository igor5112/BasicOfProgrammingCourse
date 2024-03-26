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

bool isEmpty(vector *v){
    return v->size == 0;
}

bool isFull(vector *v){
    return v->size == v->capacity;
}

int getVectorValue(vector *v, size_t i){
    return v->data[i];

}

void pushBack(vector *v, int x){

    if (isFull(v)){
        reserve(v, v->capacity * 2);
    }

    v->data[v->size] = x;
    v->size ++;
}

void popBack(vector *v){
    if (isEmpty(v)){
        fprintf(stderr, "bad alloc");
        exit(1);
    }else{
        v->size --;
    }
}

int *atVector(vector *v, size_t index){
    if (v->size < index){
        fprintf(stderr, "IndexError: a[index] is not exists");
        return NULL;
    }else{
        return &(v->data[index]);
    }
}

int *back(vector *v){
    if (isEmpty(v)){
        fprintf(stderr, "IndexError: vector is empty");
        return NULL;
    }else{
        return &(v->data[v->size - 1]);
    }
}

int *front(vector *v){
    if (isEmpty(v)){
        fprintf(stderr, "IndexError: vector is empty");
        return NULL;
    }else{
        return &(v->data[0]);
    }
}