#include "include/words.h"

/// comment to disable the debug mode.
#define DEBUG_WORDS
#ifdef DEBUG_WORDS
  #include <stdio.h>
#endif

// CONSTRUCTOR
Words newWords() {
  Words result = malloc(sizeof(*result));
  result->capacity = INIT_CAPACITY;
  result->length = 0;
  result->words = malloc(result->capacity * sizeof(result->words));
  return result;
}

// DESTRUCTOR
void deleteWords(Words* words) {
  for(size_t k = 0; k < (*words)->length; ++k) {
    free((*words)->words[k]);
  }
  free((*words)->words);
  free(*words);
  *words = NULL;
}

// IMPLEMENTATION
void addWord(Words words, unsigned char* w) {
  if (words->length == words->capacity) {
    words->capacity *= 2;
    words->words = realloc(words->words, words->capacity * sizeof(words->words));
  }
  words->words[words->length] = (unsigned char*)w;
  ++words->length;
}
