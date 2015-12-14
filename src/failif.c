/*
 * Imported code from Christophe Hancart.
 */
#include <stdio.h>
#include <stdlib.h>
#include "include/failif.h"

void fail_if(
    const char *file, int line, const char *func,
    int expr, const char *code, const char *cause) {
  if (! expr) {
    return;
  }
  fprintf(stderr,
      "*** Abnormal program termination: %s\n"
      "*** file: %s, line: %d, function: %s\n"
      "*** code: %s\n",
      cause, file, line, func, code);
  exit(EXIT_FAILURE);
}
