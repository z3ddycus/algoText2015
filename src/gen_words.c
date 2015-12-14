#include "include/generator.h"
#include <stdio.h>
#include <limits.h>
#include <sys/time.h>

// TOOLS PROTOTYPE
void usage();

// ENTRY POINT
int main(int argc, char* argv[]) {
  if (argc != 5) {
    usage();
    return EXIT_FAILURE;
  }

  unsigned sizeAlphabet = atoi(argv[4]);
  size_t minWordSize = atoi(argv[2]);
  size_t maxWordSize = atoi(argv[3]);
  size_t nbWord = atoi(argv[1]);

  if (sizeAlphabet <= 0 || minWordSize <= 0 || minWordSize > maxWordSize
  || nbWord <= 0 || UCHAR_MAX <= sizeAlphabet + FIRST_CHAR) {
    usage();
    return EXIT_FAILURE;
  }

  struct timeval now;
  gettimeofday(&now, NULL);
  srand(now.tv_usec);

  return generateSomeRandomLengthWords(stdout, sizeAlphabet,
    minWordSize, maxWordSize, nbWord);
}

// TOOLS IMPLEMENTATION
void usage() {
  fprintf(stderr, "Usage : genere-mots nbWord minWordSize maxWordSize sizeAlphabet\n");
}
