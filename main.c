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

void replace(char *source, char *w1, char *w2) {
    size_t w1Size = strlen1(w1); // Предполагается, что функция strlen1 определена и работает как strlen
    size_t w2Size = strlen1(w2);
    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};
    char *readPtr, *recPtr;
    char _stringBuffer[1024];

    if (w1Size >= w2Size) {
        readPtr = source;
        recPtr = source;
    } else {
        recPtr = copy(source, getEndOfString(source), _stringBuffer);
        readPtr = _stringBuffer;
    }

    while (*readPtr != '\0') {
        if (isWordAt(readPtr, word1)) {
            recPtr = copy(word2.begin, word2.end, recPtr);
            readPtr += w1Size;
        } else {
            *recPtr++ = *readPtr++;
        }
    }
    *recPtr = '\0';
}

int areWordsEqual(WordDescriptor w1, WordDescriptor w2) {
    while (w1.begin < w1.end && w2.begin < w2.end) {
        if (*w1.begin != *w2.begin) {
            return *w1.begin < *w2.begin ? -1 : 1;
        }
        w1.begin++;
        w2.begin++;
    }
    if (w1.begin == w1.end && w2.begin == w2.end) {
        return 0; // Слова равны
    }
    return w1.begin == w1.end ? -1 : 1;
}

bool isLexicographicallyOrdered(const char *sentence) {
    const char *ptr = sentence;
    WordDescriptor prevWord = {NULL, NULL}, currentWord;

    while (*ptr && isspace(*ptr)) ptr++;
    if (!*ptr) return true;

    prevWord.begin = ptr;
    while (*ptr && !isspace(*ptr)) ptr++;
    prevWord.end = ptr;


    while (*ptr) {
        while (*ptr && isspace(*ptr)) ptr++;
        if (!*ptr) break;

        currentWord.begin = ptr;
        while (*ptr && !isspace(*ptr)) ptr++;
        currentWord.end = ptr;

        if (areWordsEqual(prevWord, currentWord) > 0) {
            return false;
        }
        prevWord = currentWord;
    }
    return true;
}