#ifndef WORDS_H
#define WORDS_H

#include <stdlib.h>

#define INIT_CAPACITY 100;

/**
 * Struct to stack all words in an array.
 */
struct _words {
  size_t capacity;
  size_t length;
  unsigned char** words;
};

typedef struct _words * Words;

// CONSTRUCTOR
/**
 * Create a new empty Words with an initial capacity of INIT_CAPACITY.
 */
extern Words newWords();

// DESTRUCTOR
/**
 * Free the memory allocated to the Words.
 */
extern void deleteWords(Words* words);

// COMMANDS
/**
 * Add a word to the Words structure.
 */
extern void addWord(Words words, unsigned char* w);

#endif
