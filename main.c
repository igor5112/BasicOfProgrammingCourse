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

void getBagOfWords(char *s) {
    _bag.size = 0;
    char *beginWord = s;
    char *endWord;

    while (*beginWord != '\0') {
        getWord(&beginWord, &endWord);
        if (beginWord == endWord) {
            break; // Нет больше слов
        }
        if (_bag.size < MAX_N_WORDS_IN_STRING) {
            _bag.words[_bag.size].begin = beginWord;
            _bag.words[_bag.size].end = endWord;
            _bag.size++;
        }
        beginWord = endWord;
    }
}

void printWordsInReverseOrder(char *s) {
    getBagOfWords(s);

    for (int i = _bag.size - 1; i >= 0; --i) {
        for (char *c = _bag.words[i].begin; c != _bag.words[i].end; ++c) {
            putchar(*c);
        }
        putchar('\n');
    }
} //                 //ЗАДАЧА 7

bool isPalindrome(const char *start, const char *end) {
    while (start < end) {
        if (*start != *end) {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

int countPalindromes(const char *s) {
    int count = 0;
    const char *wordStart = s;
    const char *wordEnd;

    while (*s) {
        if (*s == ',' || *s == '\0') {
            wordEnd = s - 1;

            while (wordEnd > wordStart && isspace(*wordEnd)) {
                wordEnd--;
            }

            if (isPalindrome(wordStart, wordEnd)) {
                count++;
            }

            s++;
            while (*s && isspace(*s)) {
                s++;
            }
            wordStart = s;
        } else {
            s++;
        }
    }

    if (wordStart < s) {
        wordEnd = s - 1;
        if (isPalindrome(wordStart, wordEnd)) {
            count++;
        }
    }

    return count;
}

void mergeStrings(const char *s1, const char *s2, char *result) {
    WordDescriptor word1, word2;
    bool isW1Found, isW2Found;
    char *beginSearch1 = (char *)s1, *beginSearch2 = (char *)s2;

    while ((isW1Found = getWord(beginSearch1, &word1)),
            (isW2Found = getWord(beginSearch2, &word2)),
            isW1Found || isW2Found) {
        if (isW1Found) {
            while (word1.begin != word1.end) {
                *result++ = *word1.begin++;
            }
            beginSearch1 = word1.end;
            if (isW2Found) {
                *result++ = ' ';
            }
        }
        if (isW2Found) {
            while (word2.begin != word2.end) {
                *result++ = *word2.begin++;
            }
            beginSearch2 = word2.end;
            if (isW1Found && *(word1.end) != '\0') {
                *result++ = ' ';
            }
        }
    }
    *result = '\0';
}

bool isSpace(char c) {
    return c == ' ' || c == '\n' || c == '\t';
}


void reverseWordsInString(char *str) {
    size_t length = strlen1(str);
    char buffer[length + 1];
    char *bufferEnd = copy(str, str + length, buffer);
    *bufferEnd = '\0';

    char *wordEnd = buffer + length;
    char *dest = str;


    while (wordEnd > buffer) {
        if (isSpace(*(wordEnd - 1))) {
            wordEnd--;
        } else {
            char *wordStart = wordEnd - 1;
            while (wordStart > buffer && !isSpace(*(wordStart - 1))) {
                wordStart--;
            }
            dest = copy(wordStart, wordEnd, dest);
            *dest++ = ' ';
            wordEnd = wordStart;
        }
    }
    if (dest > str) {
        *(dest - 1) = '\0';
    } else {
        *dest = '\0';
    }
}   //                                  ЗАДАЧА 10

bool hasLetterA(const char *begin, const char *end) {
    while (begin != end) {
        if (*begin == 'a' || *begin == 'A') {
            return true;
        }
        begin++;
    }
    return false;
}

// Функция для вывода слова перед первым словом с буквой 'a'
void printWordBeforeFirstWordWithA(char *s) {
    const char *begin = s;
    const char *end;
    const char *wordBefore = NULL;
    size_t wordBeforeLength = 0;

    while (*begin) {
        // Пропускаем пробелы
        while (*begin == ' ') {
            begin++;
        }
        if (*begin == '\0') {
            break;
        }
        end = begin;

        // Находим конец слова
        while (*end != ' ' && *end != '\0') {
            end++;
        }

        // Проверяем, содержит ли слово букву 'a'
        if (hasLetterA(begin, end)) {
            // Если это первое слово с 'a', выводим предыдущее слово, если оно есть
            if (wordBefore) {
                for (const char *c = wordBefore; c != wordBefore + wordBeforeLength; c++) {
                    putchar(*c);
                }
                putchar('\n');
            } else {
                printf("No word before the first word with 'a'.\n");
            }
            return;
        }


        wordBefore = begin;
        wordBeforeLength = end - begin;


        begin = end;
    }

    printf("No word with 'a' found.\n");
}

void wordDescriptorToString(WordDescriptor word, char *destination) {
    while (word.begin != word.end) {
        *destination++ = *word.begin++;
    }
    *destination = '\0';
}


bool isWordInString(const char *str, WordDescriptor word) {
    const char *current = str;
    while (*current) {
        const char *begin = current;
        // Находим конец слова
        while (*current && !isspace((unsigned char)*current)) {
            current++;
        }

        const char *wordIter = word.begin;
        const char *strIter = begin;
        while (wordIter != word.end && strIter != current && *wordIter == *strIter) {
            wordIter++;
            strIter++;
        }
        if (wordIter == word.end && (strIter == current || isspace((unsigned char)*strIter))) {
            return true;
        }

        while (*current && isspace((unsigned char)*current)) {
            current++;
        }
    }
    return false;
}