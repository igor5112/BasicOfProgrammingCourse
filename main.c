
#include <stdint.h>
#include "libs/data_structures/vector/vector.h"
#include <assert.h>

void test_pushBack_emptyVector() {
    vector v = createVector(0);
    pushBack(&v, 123);
    assert(v.size == 1);
    assert(v.data[0] == 123);
    deleteVector(&v);
}

void test_pushBack_fullVector() {
    vector v = createVector(1);
    pushBack(&v, 123);
    pushBack(&v, 456);
    assert(v.size == 2);
    assert(v.data[0] == 123);
    assert(v.data[1] == 456);
    deleteVector(&v);
}

void test(){
    test_pushBack_emptyVector();
    test_pushBack_fullVector();

}

int main() {
    vector v = createVector(SIZE_MAX);
    test();

    return 0;
}