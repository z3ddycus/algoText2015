#include "include/generator.h"
#include <stdio.h>
#include <limits.h>
#include <sys/time.h>

// TOOLS PROTOTYPE
void usage();

// ENTRY POINT
int main(int argc, char* argv[]) {
  if (argc != 3) {
    // nombre d'arguments incorrects
    usage();
    return EXIT_FAILURE;
  }

  // transformation des arguments
  unsigned sizeAlphabet = atoi(argv[2]);
  size_t sizeWord = atoi(argv[1]);
  struct timeval now;
  gettimeofday(&now, NULL);
  srand(now.tv_usec);

  if (sizeAlphabet <= 0 || sizeWord <= 0 || UCHAR_MAX <= sizeAlphabet + FIRST_CHAR) {
    // arguments invalides
    usage();
    return EXIT_FAILURE;
  }

  return generateSomeFixedLengthWords(stdout, sizeAlphabet, sizeWord, 1);
}

// TOOLS IMPLEMENTATION
void usage() {
  fprintf(stderr, "Usage : genere-texte sizeText sizeAlphabet\n");
}
