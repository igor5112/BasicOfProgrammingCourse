
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

void test_popBack_notEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(v.size == 1);
    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 1);
}

void test_atVector() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(*(atVector(&v, 0)) == 10);
    assert(atVector(&v, 1) == NULL);
}

void test_back() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(*(back(&v)) == 10);
    pushBack(&v, 20);
    assert(*(back(&v)) == 20);
}

void test_front() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(*(front(&v)) == 10);
    pushBack(&v, 20);
    assert(*(front(&v)) == 10);
}

void test_atVector_notEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(*(atVector(&v, 0)) == 10);
}

void test_atVector_requestToLastElement() {
    vector v = createVector(0);
    pushBack(&v, 10);
    pushBack(&v, 20);
    assert(*(atVector(&v, v.size - 1)) == 20);
}

void test_back_oneElementInVector() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(*(back(&v)) == 10);
}

void test_front_oneElementInVector() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(*(front(&v)) == 10);
}


void test(){
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_popBack_notEmptyVector();
    test_atVector();
    test_back();
    test_front();
    test_atVector_notEmptyVector();
    test_atVector_requestToLastElement();
    test_back_oneElementInVector();
    test_front_oneElementInVector();
}

int main() {
    vector v = createVector(SIZE_MAX);
    test();

    return 0;
}