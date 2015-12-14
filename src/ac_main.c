#include "include/failif.h"
#include "include/words.h"
#include "include/logger.h"
#include "include/trie.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#define LOG_FILE "log.csv"

// TOOLS PROTOTYPE
void usage(const char* executableName);

// ENTRY POINT
int main(int argc, char** argv) {
  if (argc < 3) {
    usage(argv[0]);
    return EXIT_FAILURE;
  }

  FILE* fText = fopen(argv[2], "r");
  FAIL_IF(fText == NULL, "Open file failed");

  FILE* wordFile = fopen(argv[1], "r");
  FAIL_IF(wordFile == NULL, "Open file failed");

  Words words = newWords();
  int continu = 1;
  while (continu) {
    char* w = NULL;
    size_t len = 0;
    ssize_t nbread;
    if ((nbread = getline(&w, &len, wordFile)) > 0) {
      w[nbread - 1] = '\0';
      addWord(words, (unsigned char*) w);
    } else {
      continu = 0;
    }
  }

  // timer begin
  struct timeval start, end;
  gettimeofday(&start, NULL);

  // algorithm to test
  Trie trie = newTrie();
  insertAll(trie, words->words, words->length);
  size_t count = countInTrie(trie, fText);
  freeTrie(&trie);

  // timer end
  gettimeofday(&end, NULL);
  size_t time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;
  if (argc == 4)
    logInfo(argv[3], argv[0], argv[2], argv[1], count, time);
  else
    logInfo(LOG_FILE, argv[0], argv[2], argv[1], count, time);

  printf("[%s] - count : %zu (time : %zums)\n", argv[0], count, time);
  deleteWords(&words);

  return EXIT_SUCCESS;
}

// TOOLS IMPLEMENTATION
void usage(const char* executableName) {
  fprintf(stderr, "Usage : %s mots texte [logfile]\n", executableName);
}
