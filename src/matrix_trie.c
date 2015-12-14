#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "include/failif.h"
#include "include/trie.h"
#include "include/sorted_list.h"

#define INIT_CAPACITY 1024

/// comment to cancel debug mode
//#define DEBUG_TRIE

// STRUCTURE
struct _trie {
  size_t max;
  size_t next;
  size_t **trans;
  unsigned *finite;
  size_t *fallback;
};

// TOOLS PROTOTYPE
size_t getNext(Trie t, unsigned char c, size_t cur);
bool substitute(Trie t, unsigned char* w, size_t len, size_t lins);
void doubleCapacity(Trie t);
size_t insertLetter(Trie t, unsigned char c, size_t last);

// CONSTRUCTOR
Trie newTrie() {
  #ifdef DEBUG_TRIE
    fprintf(stderr, "----------------\n");
    fprintf(stderr, "debug: new trie.\n");
    fprintf(stderr, "----------------\n");
  #endif

  Trie result = malloc(sizeof(*result));
  FAIL_IF(result == NULL, "trie : malloc failed");

  result->next = 0;
  result->max = INIT_CAPACITY;

  result->trans = calloc(INIT_CAPACITY, sizeof(size_t*));
  FAIL_IF(result->trans == NULL, "trie->trans : malloc failed");

  result->finite = calloc(INIT_CAPACITY, sizeof(size_t));
  FAIL_IF(result->finite == NULL, "trie->finite : malloc failed");

  result->fallback = calloc(INIT_CAPACITY, sizeof(size_t));
  FAIL_IF(result->fallback == NULL, "trie->fallback : malloc failed");


  return result;
}

// DESTRUCTOR
void freeTrie(Trie* trie) {
  FAIL_IF(trie == NULL, "trie is null");

  for(size_t i = 0; i < (*trie)->next - 1; i++) {
    if ((*trie)->trans[i] != NULL) {
      free((*trie)->trans[i]);
    }
  }
  free((*trie)->trans);
  free((*trie)->finite);
  free((*trie)->fallback);
  free(*trie);
  *trie = NULL;

  #ifdef DEBUG_TRIE
    fprintf(stderr, "----------------\n");
    fprintf(stderr, "debug: trie freed.\n");
    fprintf(stderr, "----------------\n");
  #endif
}

// GETTERS
// Lit un texte et renvoie le nombre d'occurences des mots.
size_t countInTrie(Trie t, FILE* f) {
  FAIL_IF(t == NULL, "trie is null");
  FAIL_IF(t == NULL, "trie is null");

  #ifdef DEBUG_TRIE
    fprintf(stderr, "----------------\n");
    fprintf(stderr, "debug: count.\n");
    fprintf(stderr, "----------------\n");
  #endif

  size_t cur = 0;
  unsigned count = 0u;
  char c = fgetc(f);

  // Lecture de chaque lettre
  while (c != EOF) {
    cur = getNext(t, c, cur);

    #ifdef DEBUG_TRIE
      fprintf(stderr, "letter: %c (current node : %zu, count : %u, "
      "finite states : %u)\n", c, cur, count, t->finite[cur]);
    #endif

    count += t->finite[cur];
    c = fgetc(f);
  }

  #ifdef DEBUG_TRIE
    fprintf(stderr, "----------------\n");
    fprintf(stderr, "count done : %u.\n", count);
    fprintf(stderr, "----------------\n");
  #endif
  return count;
}

// Insère et ajoute les fallbacks
void insertAll(Trie t, unsigned char** words, const size_t nb) {
  FAIL_IF(t == NULL, "trie is null");
  FAIL_IF(words == NULL, "words is null");
  FAIL_IF(nb <= 0, "illegal argument");

  #ifdef DEBUG_TRIE
    fprintf(stderr, "----------------\n");
    fprintf(stderr, "debug: insert.\n");
    fprintf(stderr, "----------------\n");
  #endif

  size_t pos = 0;
  size_t rem = nb;

  bool* ended = calloc(nb, sizeof(bool));
  size_t* lpref = calloc(nb, sizeof(size_t));
  size_t* lins = calloc(nb, sizeof(size_t));
  FAIL_IF(ended == NULL || lpref == NULL || lins == NULL, "malloc failed");

  // Mots vides
  for (size_t i = 0; i < nb; i++) {
    if (words[i][0] == '\0') {
      ended[i] = true;
      rem--;

      #ifdef DEBUG_TRIE
        fprintf(stderr, "\tword is empty.\n");
      #endif

    }
  }

  // Tant qu'il reste des mots
  while (rem > 0) {
    // Ajout de la prochaine lettre sur chaque mot
    for (size_t i = 0; i < nb; i++) {
      if (ended[i] == true) {
        continue;
      }
      unsigned char* w = words[i];

      #ifdef DEBUG_TRIE
        fprintf(stderr, "word %4zu : %s (currently at node %4zu)\n",
          i, w, lins[i]);
      #endif

      lins[i] = insertLetter(t, w[pos], lins[i]);
      // Si le mot est fini
      if (w[pos + 1] == '\0') { //prendre le cas où l mot est vide

        #ifdef DEBUG_TRIE
          fprintf(stderr, "\tword %s ended.\n", w);
          fprintf(stderr, "\tfinite node added at node %4zu\n", lins[i]);
        #endif

        if (lins[i] != 0)
          t->finite[lins[i]] = 1;
        ended[i] = true;
        rem--;
      }
      // Ajout des fallbacks
      while (lpref[i] <= pos && !substitute(t, w + lpref[i] + 1,
          pos - lpref[i], lins[i])) {
        lpref[i]++;
      }
    }
    pos++;
    #ifdef DEBUG_TRIE
      fprintf(stderr, "----------------\n");
      fprintf(stderr, "next pos  : %4zu\n", pos);
      fprintf(stderr, "----------------\n");
    #endif
  }

  #ifdef DEBUG_TRIE
    fprintf(stderr, "insertion done.\n");
    fprintf(stdern r, "----------------\n");
  #endif
  // Libération des tableaux
  free(ended);
  free(lpref);
  free(lins);
}

// TOOLS IMPLEMENTATION
/**
 * Insert le caractère c à l'automate et renvoit la nouvelle node.
 */
size_t getNext(Trie t, unsigned char c, size_t cur) {
  size_t next = 0;
  size_t* tab = t->trans[cur];
  if (tab == NULL || (next = tab[c]) == 0) {
    if (cur == 0) {
      return 0;
    }
    // On regarde dans le fallback du fallback
    return getNext(t, c, t->fallback[cur]);
  }
  // On a trouvé le prochain noeud
  return next;
}

/**
 * Create the fallback of the
 */
bool substitute(Trie t, unsigned char* w, size_t len, size_t lins) {
  size_t cur = 0;
  size_t i = 0;

  while (i < len) {
    size_t* tab = t->trans[cur];
    if (tab == NULL)
      return false;
    size_t next = tab[w[i]];
    if (next == 0) {
      return false;
    } else {
      cur = next;
    }
    i++;
  }

  // Si le fallback n'a pas déjà été créé
  if (t->fallback[lins] != cur) {
    t->fallback[lins] = cur;
    t->finite[lins] += t->finite[cur];

    #ifdef DEBUG_TRIE
      char* suf = malloc(sizeof(len));
      strncpy(suf, (const char*) w, len);
      fprintf(stderr, "\tfallback to index %4zu   for node %4zu (suffix %23s)\n",
        cur, lins, suf);
      if (t->finite[cur] != 0) {
        fprintf(stderr, "\tadding %u finite states   to node %4zu (total %u)\n",
          t->finite[cur], lins, t->finite[lins]);
      }
      free(suf);
    #endif

  }
  return true;
}

/**
 * Move the automate from last to c.
 */
size_t insertLetter(Trie t, unsigned char c, size_t last) {
  if (t->trans[last] == NULL) {
    t->trans[last] = calloc(UCHAR_MAX, sizeof(size_t));
    FAIL_IF(t->trans[last] == NULL, "malloc failed");
  }
  size_t next = t->trans[last][c];
  if (next == 0) {
    // Nouvelle transition
    t->next++;
    if (t->next >= t->max) {
      doubleCapacity(t);
    }

    #ifdef DEBUG_TRIE
      fprintf(stderr, "\tnew node at index %4zu  from node %4zu (character %20c)\n",
        t->next, last, c);
    #endif

    t->trans[last][c] = t->next;
    next = t->next;
  }
  return next;
}

void doubleCapacity(Trie t) {
  size_t oldCapacity = t->max;
  t->max *= 2;

  t->trans = realloc(t->trans, t->max * 2 * sizeof(*(t->trans)));
  FAIL_IF(t->trans == NULL, "realloc failure");
  for (size_t k = oldCapacity; k < t->max; ++k) {
    t->trans[k] = NULL;
  }

  t->finite = realloc(t->finite, t->max * 2 * sizeof(*(t->finite)));
  FAIL_IF(t->finite == NULL, "realloc failure");
  for (size_t k = oldCapacity; k < t->max; ++k) {
    t->finite[k] = 0;
  }

  t->fallback = realloc(t->fallback, t->max * 2 * sizeof(*(t->fallback)));
  FAIL_IF(t->fallback == NULL, "realloc failure");
  for (size_t k = oldCapacity; k < t->max; ++k) {
    t->fallback[k] = 0;
  }
}
