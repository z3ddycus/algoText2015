#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdlib.h>
#include <stdio.h>

#define FIRST_CHAR '0'

/**
 * Generate words with fixed length
 */
extern int generateSomeFixedLengthWords(FILE* f,
  unsigned sizeAlphabet, size_t length, size_t nb);

/**
 * Generate words with random length
 */
extern int generateSomeRandomLengthWords(FILE* f, unsigned sizeAlphabet,
  size_t minlength, size_t maxlength, size_t nb);
  
#endif // GENERATOR_H
