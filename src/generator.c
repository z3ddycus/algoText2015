#include "include/generator.h"
#include <time.h>

// TOOLS PROTOTYPE
/**
 * Return an int randomize between min and max.
 */
int alea(int min, int max);

/**
 * Add a word to the file f on the alphabet
 * {FiRST_CHAR ... FIRST_CHAR + sizeAlphabet} with the lenght sizeWord.
 */
void addWordToFile(FILE * f, unsigned sizeAlphabet, size_t sizeWord);


// IMPLEMENTATION
int generateSomeRandomLengthWords(FILE* f, unsigned sizeAlphabet,
    size_t minWordSize, size_t maxWordSize, size_t nbWord) {

  while (nbWord > 0) {
    addWordToFile(f, sizeAlphabet, alea(minWordSize, maxWordSize));
    fputc('\n', f);
    --nbWord;
  }
  /*if (nbWord > 0) {
    addWordToFile(f, sizeAlphabet, alea(minWordSize, maxWordSize));
  }*/

  return EXIT_SUCCESS;
}

int generateSomeFixedLengthWords(FILE* f, unsigned sizeAlphabet,
    size_t sizeWord, size_t nbWord) {

  while (nbWord > 1) {
    addWordToFile(f, sizeAlphabet, sizeWord);
    fputc('\n', f);
    --nbWord;
  }
  if (nbWord > 0) {
    addWordToFile(f, sizeAlphabet, sizeWord);
  }

  return EXIT_SUCCESS;
}


// TOOLS IMPLEMENTATION
int alea(int min, int max) {
  return rand() % (max - min + 1) + min;
}

void addWordToFile(FILE * f, unsigned sizeAlphabet, size_t sizeWord) {
  if (sizeWord != 0) {
    fputc(alea(FIRST_CHAR, sizeAlphabet + FIRST_CHAR - 1), f);
    addWordToFile(f, sizeAlphabet, sizeWord - 1);
  }
}
