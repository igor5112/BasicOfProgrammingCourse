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
}

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
    char *beginSearch1 = (char *) s1, *beginSearch2 = (char *) s2;

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
}

bool hasLetterA(const char *begin, const char *end) {
    while (begin != end) {
        if (*begin == 'a' || *begin == 'A') {
            return true;
        }
        begin++;
    }
    return false;
}

void printWordBeforeFirstWordWithA(char *s) {
    const char *begin = s;
    const char *end;
    const char *wordBefore = NULL;
    size_t wordBeforeLength = 0;

    while (*begin) {

        while (*begin == ' ') {
            begin++;
        }
        if (*begin == '\0') {
            break;
        }
        end = begin;


        while (*end != ' ' && *end != '\0') {
            end++;
        }


        if (hasLetterA(begin, end)) {

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

        while (*current && !isspace((unsigned char) *current)) {
            current++;
        }

        const char *wordIter = word.begin;
        const char *strIter = begin;
        while (wordIter != word.end && strIter != current && *wordIter == *strIter) {
            wordIter++;
            strIter++;
        }
        if (wordIter == word.end && (strIter == current || isspace((unsigned char) *strIter))) {
            return true;
        }

        while (*current && isspace((unsigned char) *current)) {
            current++;
        }
    }
    return false;
}

WordDescriptor lastWordInFirstStringInSecondString(const char *s1, const char *s2) {
    WordDescriptor lastWord = {NULL, NULL};
    const char *current = s1;
    while (*current) {

        while (*current && isspace((unsigned char) *current)) {
            current++;
        }
        if (*current == '\0') {
            break;
        }
        WordDescriptor word = {current, NULL};

        while (*current && !isspace((unsigned char) *current)) {
            current++;
        }
        word.end = current;

        if (isWordInString(s2, word)) {
            lastWord = word;
        }

        while (*current && isspace((unsigned char) *current)) {
            current++;
        }
    }
    return lastWord;
}

bool hasSameWords(char *str) {
    WordDescriptor currentWord, compareWord;
    char *current = str;
    char *compare;

    while (getWord(&current, &currentWord)) {
        compare = current;


        while (getWord(&compare, &compareWord)) {
            if (areWordsEqual(currentWord, compareWord) == 0) {
                return true;
            }
        }
    }
    return false;
}

void sortLettersInWord(char *begin, char *end) {
    for (char *i = begin; i < end; i++) {
        for (char *j = i + 1; j < end; j++) {
            if (*i > *j) {
                char temp = *i;
                *i = *j;
                *j = temp;
            }
        }
    }
}


bool hasAnagramPair(char *str) {
    size_t length = strlen1(str);
    char buffer[length + 1];
    copy(str, str + length, buffer);
    buffer[length] = '\0';

    char *beginSearch = buffer;
    WordDescriptor currentWord, compareWord;

    while (getWord(&beginSearch, &currentWord)) {
        sortLettersInWord(currentWord.begin, currentWord.end);

        char *beginCompare = beginSearch;
        while (getWord(&beginCompare, &compareWord)) {
            sortLettersInWord(compareWord.begin, compareWord.end);
            if (areWordsEqual(currentWord, compareWord) == 0) {
                return true;
            }
        }
    }
    return false;
}

void getStringOfWordsDifferentFromLast(char *str, char *result) {
    WordDescriptor lastWord = {NULL, NULL};
    const char *tempStr = str;
    WordDescriptor tempWord;


    while (getWord(&tempStr, &tempWord)) {
        lastWord = tempWord;
    }

    if (lastWord.begin == NULL) {
        // В строке нет слов
        *result = '\0';
        return;
    }


    tempStr = str;
    *result = '\0';


    while (getWord(&tempStr, &tempWord)) {
        if (tempWord.begin == lastWord.begin) {
            continue;
        }
        if (areWordsEqual(tempWord, lastWord) != 0) {
            result = copy(tempWord.begin, tempWord.end, result);
            *result++ = ' ';
        }
    }
    if (result != str) {
        *(result - 1) = '\0';
    } else {
        *result = '\0';
    }
}

WordDescriptor findPrecedingWord(const char *s1, const char *s2) {
    const char *current = s1;
    WordDescriptor currentWord, precedingWord = {NULL, NULL}, firstCommonWord = {NULL, NULL};

    while (getWord(&current, &currentWord)) {
        if (isWordInString(s2, currentWord)) {
            firstCommonWord = currentWord;
            break;
        }
        precedingWord = currentWord;
    }

    return precedingWord;
}

void removePalindromes(char *str) {
    char *result = str;
    const char *begin = str;
    const char *end;

    while (*begin) {

        while (*begin && isspace((unsigned char) *begin)) {
            begin++;
        }
        end = begin;

        while (*end && !isspace((unsigned char) *end)) {
            end++;
        }
        if (begin < end && !isPalindrome(begin, end)) {

            result = copy(begin, end, result);
            *result++ = ' ';
        }
        begin = end;
    }
    if (result != str) {
        *(result - 1) = '\0';
    } else {
        *result = '\0';
    }
}

int countWords(const char *str) {
    int count = 0;
    while (*str) {

        while (*str && isspace((unsigned char) *str)) {
            str++;
        }

        if (*str) {
            count++;

            while (*str && !isspace((unsigned char) *str)) {
                str++;
            }
        }
    }
    return count;
}

void appendWordsFromLongerToString(char *s1, char *s2) {
    int n1 = countWords(s1);
    int n2 = countWords(s2);


    char *sourceStr = (n1 > n2) ? s1 : s2;
    char *destStr = (n1 > n2) ? s2 : s1;
    int wordsToCopy = (n1 > n2) ? n1 - n2 : n2 - n1;


    const char *wordStart = sourceStr;
    for (int i = 0; i < wordsToCopy; i++) {
        while (*wordStart) wordStart++;
        while (wordStart > sourceStr && !isspace((unsigned char) *(wordStart - 1))) wordStart--;
    }


    while (*destStr) destStr++;
    if (destStr != s1 && destStr != s2) {
        *destStr++ = ' ';
    }
    while (*wordStart) {
        *destStr++ = *wordStart++;
    }
    *destStr = '\0';
}

int areAllCharsPresent(char *str, char *word) {
    int count[NO_OF_CHARS] = {0};
    int i;

    for (i = 0; *(word + i); i++)
        count[*(word + i)]++;

    for (i = 0; *(str + i); i++) {
        if (count[*(str + i)] > 0)
            count[*(str + i)]--;
    }

    for (i = 0; i < NO_OF_CHARS; i++)
        if (count[i])
            return 0;

    return 1;
}

void testRemoveNonLetters() {
    char test1[] = "Hello, World!";
    removeNonLetters(test1);
    assertString("Hello,World!", test1, __FILE__, "testRemoveNonLetters", __LINE__);

    char test2[] = "1234 5678";
    removeNonLetters(test2);
    assertString("12345678", test2, __FILE__, "testRemoveNonLetters", __LINE__);

    char test3[] = "1@#$%^&*( )";
    removeNonLetters(test3);
    assertString("1@#$%^&*()", test3, __FILE__, "testRemoveNonLetters", __LINE__);
}

void testRemoveExtraSpaces() {
    char test1[] = "This   is  a test.";
    removeExtraSpaces(test1);
    assertString("This is a test.", test1, __FILE__, "testRemoveExtraSpaces", __LINE__);

    char test2[] = "Leading  and trailing spaces";
    removeExtraSpaces(test2);
    assertString("Leading and trailing spaces", test2, __FILE__, "testRemoveExtraSpaces", __LINE__);

    char test3[] = "Multiple     spaces     between     words.";
    removeExtraSpaces(test3);
    assertString("Multiple spaces between words.", test3, __FILE__, "testRemoveExtraSpaces", __LINE__);
}

void testStringModernization() {
    char test1[] = "a123 и456";
    stringModernization(test1);
    assertString("321abc 654def", test1, __FILE__, "testStringModernization", __LINE__);

    char test2[] = "hello2world";
    stringModernization(test2);
    assertString("2helloworld", test2, __FILE__, "testStringModernization", __LINE__);

    char test3[] = "abc03 def90";
    stringModernization(test3);
    assertString("30abc 654def", test3, __FILE__, "testStringModernization", __LINE__);
}

void testTakeEveryNumberToCountOfSpaces() {
    char test1[MAX_STRING_SIZE + 1] = "a1b2c3";
    takeEveryNumberToCountOfSpaces(test1);
    assertString("a b  c   ", test1, __FILE__, "testTakeEveryNumberToCountOfSpaces", __LINE__);

    char test2[MAX_STRING_SIZE + 1] = "4d5e6f";
    takeEveryNumberToCountOfSpaces(test2);
    assertString("    d     e      f", test2, __FILE__, "testTakeEveryNumberToCountOfSpaces", __LINE__);

    char test3[MAX_STRING_SIZE + 1] = "123";
    takeEveryNumberToCountOfSpaces(test3);
    assertString("      ", test3, __FILE__, "testTakeEveryNumberToCountOfSpaces", __LINE__);
}

void testReplace() {
    char source1[1024] = "the quick brown fox jumps over the lazy dog";
    replace(source1, "the", "a");
    assertString("a quick brown fox jumps over a lazy dog", source1, __FILE__, "testReplace", __LINE__);

    char source2[1024] = "hello world, hello universe";
    replace(source2, "hello", "hi");
    assertString("hi world, hi universe", source2, __FILE__, "testReplace", __LINE__);

    char source3[1024] = "foo bar foo";
    replace(source3, "foo", "bar");
    assertString("bar bar bar", source3, __FILE__, "testReplace", __LINE__);
}

void assertLexicographicallyOrdered(const char *sentence, bool expected, char const *fileName, char const *funcName,
                                    int line) {
    bool result = isLexicographicallyOrdered(sentence);
    if (result != expected) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Sentence: \"%s\"\n", sentence);
        fprintf(stderr, "Expected to be %s\n\n", expected ? "ordered" : "not ordered");
    } else {
        fprintf(stderr, "%s - OK\n", funcName);
    }
}

void testIsLexicographicallyOrdered() {
    assertLexicographicallyOrdered("apple banana cherry", true, __FILE__, "testIsLexicographicallyOrdered", __LINE__);
    assertLexicographicallyOrdered("banana apple cherry", false, __FILE__, "testIsLexicographicallyOrdered", __LINE__);
    assertLexicographicallyOrdered("cherry cherry cherry", true, __FILE__, "testIsLexicographicallyOrdered", __LINE__);
    assertLexicographicallyOrdered("", true, __FILE__, "testIsLexicographicallyOrdered", __LINE__);
    assertLexicographicallyOrdered("a", true, __FILE__, "testIsLexicographicallyOrdered", __LINE__);
}

void assertOutput(const char *expected, char *input, char const *fileName, char const *funcName, int line) {
    char buffer[1024] = {0};
    setbuf(stdout, buffer);


    printWordsInReverseOrder(input);

    setbuf(stdout, NULL);


    if (strcmp(expected, buffer) != 0) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected:\n%s\n", expected);
        fprintf(stderr, "Got:\n%s\n\n", buffer);
    } else {
        fprintf(stderr, "%s - OK\n", funcName);
    }
}

void testPrintWordsInReverseOrder() {
    const char *input = "This is a test";
    const char *expected = "test\na\nis\nThis\n";
    assertOutput(expected, input, __FILE__, "testPrintWordsInReverseOrder", __LINE__);
}

void testCountPalindromes() {
    char result[50];

    // Тест 1: Проверка строки без палиндромов
    sprintf(result, "%d", countPalindromes("cat, dog, fish"));
    assertString("0", result, __FILE__, __func__, __LINE__);

    // Тест 2: Проверка строки с одним палиндромом
    sprintf(result, "%d", countPalindromes("madam, dog, fish"));
    assertString("1", result, __FILE__, __func__, __LINE__);

    // Тест 3: Проверка строки с несколькими палиндромами
    sprintf(result, "%d", countPalindromes("level, deed, noon, refer, fish"));
    assertString("4", result, __FILE__, __func__, __LINE__);
}


void testMergeStrings() {
    char result[1000];


    mergeStrings("", "", result);

    assertString("", result, __FILE__, __func__, __LINE__);

    mergeStrings("Hello", "", result);
    assertString("Hello", result, __FILE__, __func__, __LINE__);


    mergeStrings("", "World", result);
    assertString("World", result, __FILE__, __func__, __LINE__);


    mergeStrings("Hello", "World", result);
    assertString("Hello World", result, __FILE__, __func__, __LINE__);


    mergeStrings("Hello there", "General Kenobi", result);
    assertString("Hello General there Kenobi", result, __FILE__, __func__, __LINE__);
}

void testReverseWordsInString() {
    char testString1[] = "Hello World";
    reverseWordsInString(testString1);
    assertString("World Hello", testString1, __FILE__, __func__, __LINE__);

    char testString2[] = "one two three";
    reverseWordsInString(testString2);
    assertString("three two one", testString2, __FILE__, __func__, __LINE__);

    char testString3[] = "  leading and trailing spaces  ";
    reverseWordsInString(testString3);
    assertString("spaces trailing and leading", testString3, __FILE__, __func__, __LINE__);

    char testString4[] = "single";
    reverseWordsInString(testString4);
    assertString("single", testString4, __FILE__, __func__, __LINE__);

    char testString5[] = "";
    reverseWordsInString(testString5);
    assertString("", testString5, __FILE__, __func__, __LINE__);
}


void clearBuffer(char *buffer, size_t size) {
    for (size_t i = 0; i < size; i++) {
        buffer[i] = 0;
    }
}

void testPrintWordBeforeFirstWordWithA() {

    char buffer[1024];
    clearBuffer(buffer, sizeof(buffer));
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buffer);


    char testStr1[] = "This is an apple";
    printWordBeforeFirstWordWithA(testStr1);
    assertString("is", buffer, __FILE__, __func__, __LINE__);

    // Очищаем буфер.
    clearBuffer(buffer, sizeof(buffer));


    char testStr2[] = "an apple a day";
    printWordBeforeFirstWordWithA(testStr2);
    assertString("No word before the first word with 'a'.\n", buffer, __FILE__, __func__, __LINE__);


    clearBuffer(buffer, sizeof(buffer));


    char testStr3[] = "Hello world";
    printWordBeforeFirstWordWithA(testStr3);
    assertString("No word with 'a' found.\n", buffer, __FILE__, __func__, __LINE__);


    freopen("/dev/tty", "a", stdout);
}

void testHasSameWords() {

    char testStr1[] = "hello world hello";
    bool result1 = hasSameWords(testStr1);
    assertString("true", result1 ? "true" : "false", __FILE__, "testHasSameWords", __LINE__);

    char testStr2[] = "power and power";
    bool result2 = hasSameWords(testStr1);
    assertString("true", result1 ? "true" : "false", __FILE__, "testHasSameWords", __LINE__);

    char testStr3[] = "juice or or";
    bool result3 = hasSameWords(testStr1);
    assertString("true", result1 ? "true" : "false", __FILE__, "testHasSameWords", __LINE__);
}

void testHasAnagramPair() {

    char testStr1[] = "listen silent";
    bool result1 = hasAnagramPair(testStr1);
    assertString("true", result1 ? "true" : "false", __FILE__, "testHasAnagramPair", __LINE__);

    char testStr2[] = "ball labb";
    bool result2 = hasAnagramPair(testStr1);
    assertString("true", result1 ? "true" : "false", __FILE__, "testHasAnagramPair", __LINE__);

    char testStr3[] = "gramm margm";
    bool result3 = hasAnagramPair(testStr1);
    assertString("true", result1 ? "true" : "false", __FILE__, "testHasAnagramPair", __LINE__);

}

void testGetStringOfWordsDifferentFromLast() {
    char result[256];


    char testStr1[] = "hello world sd";
    getStringOfWordsDifferentFromLast(testStr1, result);
    assertString("hello world", result, __FILE__, "testGetStringOfWordsDifferentFromLast", __LINE__);


    char testStr2[] = "test test test";
    getStringOfWordsDifferentFromLast(testStr2, result);
    assertString("", result, __FILE__, "testGetStringOfWordsDifferentFromLast", __LINE__);


    char testStr3[] = "single";
    getStringOfWordsDifferentFromLast(testStr3, result);
    assertString("", result, __FILE__, "testGetStringOfWordsDifferentFromLast", __LINE__);
}

void testFindPrecedingWord() {
    char resultString[256];

    const char *testStr1 = "hello world hello";
    const char *testStr2 = "hello planet";
    WordDescriptor result1 = findPrecedingWord(testStr1, testStr2);
    wordDescriptorToString(result1, resultString);
    assertString("world", resultString, __FILE__, "testFindPrecedingWord", __LINE__);


    const char *testStr3 = "hello world from the sea";
    const char *testStr4 = "hello there";
    WordDescriptor result2 = findPrecedingWord(testStr3, testStr4);
    wordDescriptorToString(result2, resultString);
    assertString("", resultString, __FILE__, "testFindPrecedingWord", __LINE__);


    const char *testStr5 = "unique words here";
    const char *testStr6 = "no matching words";
    WordDescriptor result3 = findPrecedingWord(testStr5, testStr6);
    wordDescriptorToString(result3, resultString);
    assertString("words", resultString, __FILE__, "testFindPrecedingWord", __LINE__);
}

void testRemovePalindromes() {
    char testStr1[] = "level madam racecar hello";
    removePalindromes(testStr1);
    assertString("level madam racecar hello", testStr1, __FILE__, "testRemovePalindromes", __LINE__);

    char testStr2[] = "noon civic deed rotor";
    removePalindromes(testStr2);
    assertString("noon civic deed rotor", testStr2, __FILE__, "testRemovePalindromes", __LINE__);

    char testStr3[] = "hello world";
    removePalindromes(testStr3);
    assertString("hello world noon civic deed rotor", testStr3, __FILE__, "testRemovePalindromes", __LINE__);
}

void testAppendWordsFromLongerToString() {
    char testStr1[256] = "This is a test";
    char testStr2[256] = "This is a longer test string";
    appendWordsFromLongerToString(testStr1, testStr2);
    assertString("This is a test string", testStr1, __FILE__, "testAppendWordsFromLongerToString", __LINE__);

    char testStr3[256] = "Another test string";
    char testStr4[256] = "Short";
    appendWordsFromLongerToString(testStr3, testStr4);
    assertString("Short string", testStr4, __FILE__, "testAppendWordsFromLongerToString", __LINE__);

    char testStr5[256] = "Any other string";
    char testStr6[256] = "Short";
    appendWordsFromLongerToString(testStr3, testStr4);
    assertString("Short string string", testStr4, __FILE__, "testAppendWordsFromLongerToString", __LINE__);
}

void testAreAllCharsPresent() {
    char str1[] = "a quick brown fox jumps over the lazy dog";
    char word1[] = "quick";
    assert(areAllCharsPresent(str1, word1) == 1);

    char str2[] = "some random text";
    char word2[] = "example";
    assert(areAllCharsPresent(str2, word2) == 0);

    char str3[] = "another example";
    char word3[] = "";
    assert(areAllCharsPresent(str3, word3) == 1);

    char str4[] = "";
    char word4[] = "word";
    assert(areAllCharsPresent(str4, word4) == 0);

}

int main() {
    testRemoveNonLetters();
    testRemoveExtraSpaces();
    testTakeEveryNumberToCountOfSpaces();
    testReplace();
    testIsLexicographicallyOrdered();
    testCountPalindromes();
    testMergeStrings();
    testHasSameWords();
    testHasAnagramPair();
    testAppendWordsFromLongerToString();
    testRemovePalindromes();
    testAreAllCharsPresent();
    testFindPrecedingWord();
    testGetStringOfWordsDifferentFromLast();
    testReverseWordsInString();
    testPrintWordBeforeFirstWordWithA();
    testPrintWordsInReverseOrder();
    testStringModernization();
    return 0;
}