#include "include/logger.h"
#include "include/failif.h"
#include <stdlib.h>

// IMPLEMENTATION
void logInfo(char* filename, char* nomExec, char* fichierTexte,
    char* fichierMots, size_t nbOccurences, size_t time) {
  FILE* f = fopen(filename, "a");
  FAIL_IF(f == NULL, "unable to open file");
  if (ftell(f) == SEEK_SET) {
    fprintf(f, "%s\n", HEADER);
  }
  fprintf(f, "%s, %s, %s, %lu, %zums\n", nomExec, fichierTexte, fichierMots,
    nbOccurences, time);
  fclose(f);
}
