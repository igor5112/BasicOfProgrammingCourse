#include <stdio.h>
#include <assert.h>
#include "libs/data_structures/string/string_.h"



int main() {
//тесты для функции strlen1
    char *emptyString = "";
    assert(strlen1(emptyString) == 0);

    char *singleChar = "a";
    assert(strlen1(singleChar) == 1);

    char *standardString = "String";
    assert(strlen1(standardString) == 6);

    char *spaceString = "Hi, i'm from Russia";
    assert(strlen1(spaceString) == 19);

//тесты для функции find

    emptyString = "";
    assert(find(emptyString, emptyString, 'a') == emptyString);

    char *testString = "Wonderful";
    assert(find(testString, testString + 7, 'x') == testString + 7);

    assert(find(testString, testString + 7, 'o') == testString + 1);

    assert(find(testString,testString + 5, 'r') == testString + 5);

//тесты для функции findSpace

    emptyString = "";
    assert(findSpace(emptyString) == emptyString + strlen1(emptyString));


    char *noSpace = "NoSpaces";
    assert(findSpace(noSpace) == noSpace + 8);


    char *singleSpace = " ";
    assert(findSpace(singleSpace) == singleSpace);


    // Строка с пробелом посередине
    char *middleSpace = "Middle space here";
    assert(findSpace(middleSpace) == middleSpace + 6);



    char str[] = "abcdefg hi";


    middleSpace = str + strlen1(str) - 1;
    assert(findSpaceReverse(middleSpace, str) == str + 7);


    noSpace = "NoSpace";
    char *end = noSpace + strlen1(noSpace) - 1;
    assert(findSpaceReverse(end, noSpace) == noSpace);


    char strWithTrailingSpace[] = "Trailing space ";
    char *trailingSpace = strWithTrailingSpace + strlen1(strWithTrailingSpace) - 1;
    assert(findSpaceReverse(trailingSpace, strWithTrailingSpace) == strWithTrailingSpace + 14);


    assert(strcmp("abcd", "abcd") == 0);

    assert(strcmp("Alpha", "Bravo") < 0);
    
    assert(strcmp("Charlie", "Bravo") > 0);

    assert(strcmp("Help", "He") > 0);

    assert(strcmp("", "Moscow") < 0);

    assert(strcmp("Copilot", "") > 0);

    return 0;
}