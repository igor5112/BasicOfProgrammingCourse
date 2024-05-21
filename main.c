#include <stdio.h>
#include <ctype.h>
#include "libs/data_structures/string/string_.h"
#include <stdbool.h>
#define NO_OF_CHARS 256
#include <assert.h>

void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line) {
    if (strcmp(expected, got) != 0) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else {
        fprintf(stderr, "%s - OK\n", funcName);
    }
}



void removeNonLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

void removeExtraSpaces(char *s) {
    char *d = s;
    int inWord = 0;

    while (*s) {
        if (*s != ' ') {
            *d++ = *s;
            inWord = 1;
        } else if (inWord) {
            *d++ = *s;
            inWord = 0;
            while (*(s + 1) == ' ') s++;
        }
        s++;
    }
    *d = '\0';
}

int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}



void digitToStart(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end,
                                 _stringBuffer);
    char *recPosition = copyIfReverse(endStringBuffer - 1,
                                      _stringBuffer - 1,
                                      word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}


void stringModernization(char *s) {
    char *begin = s;
    char *end;
    char *wordBegin;
    char *digitEnd;

    while (*begin) {
        begin = findNonSpace(begin);
        if (*begin == '\0') {
            break;
        }
        wordBegin = begin;
        end = findWordEnd(begin);
        digitEnd = end;


        while (begin < end) {
            if (isdigit(*begin)) {
                char temp = *begin;
                while (begin > wordBegin) {
                    *begin = *(begin - 1);
                    begin--;
                }
                *wordBegin = temp;
                begin = wordBegin + 1;
                digitEnd++;
            } else {
                begin++;
            }
        }


        reverseDigits(wordBegin, digitEnd - 1);

        begin = end;
    }
}

void takeEveryNumberToCountOfSpaces(char *s) {
    char buffer[MAX_STRING_SIZE + 1];
    char *dst = buffer;
    char *src = s;


    while (*src && (dst - buffer) < MAX_STRING_SIZE) {
        *dst++ = *src++;
    }
    *dst = '\0';


    src = buffer;
    dst = s;

    while (*src) {
        if (isdigit((unsigned char) *src)) {
            int spaces = *src - '0';
            while (spaces-- > 0 && (dst - s) < MAX_STRING_SIZE) {
                *dst++ = ' ';
            }
        } else {
            if ((dst - s) < MAX_STRING_SIZE) {
                *dst++ = *src;
            }
        }
        src++;
    }
    *dst;
}