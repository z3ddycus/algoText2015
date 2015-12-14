#include <stdlib.h>
#include <string.h>
#include "include/failif.h"
#include "include/sorted_list.h"

/// comment to cancel debug mode
//#define DEBUG_SORTED_LIST

// TOOLS PROTOTYPE
#ifdef DEBUG_SORTED_LIST
#include <stdio.h>
/**
 * Display the SortedList content.
 */
void debug(SortedList l);
#endif


// STRUCTURES
typedef struct _listelem *ListElem;

struct _list {
  ListElem hd;
  ListElem it;
  size_t len;
};

struct _listelem {
  unsigned char c;
  size_t id;
  ListElem nx;
};

typedef struct _list *SortedList;

// CONSTRUCTOR
SortedList newList() {
  SortedList l = malloc(sizeof(struct _list));
  FAIL_IF(l == NULL, "malloc failed");

  l->hd = NULL;
  l->it = NULL;
  l->len = 0;

  #ifdef DEBUG_SORTED_LIST
  debug(l);
  #endif

  return l;
}

// DESTRUCTOR
void freeList(SortedList* l) {
  FAIL_IF(l == NULL || *l == NULL, "List already freed");
  clear(*l);
  free(*l);
  *l = NULL;
}

// GETTERS
size_t length(SortedList l) {
  FAIL_IF(l == NULL, "list is null");
  return l->len;
}

size_t get(SortedList l, unsigned char c) {
  FAIL_IF(l == NULL, "list is null");

  if (l->hd == NULL || l->hd->c > c) {
    l->it = NULL;
    #ifdef DEBUG_SORTED_LIST
      fprintf(stderr, "sortie get %c not found\n", c);
      debug(l);
    #endif
    return GET_ERR;
  }

  ListElem le = l->hd;
  if (l->it != NULL && l->it->c <= c) {
    le = l->it;  // Start from the iterator is a better solution
  }

  while (le->nx != NULL) {
    if (le->c == c) {
      // Element found
      l->it = le;
      return le->id;
    } else if (le->nx->c > c) {
      // le->c < c && le->nx->c > c ==> not in the list
      l->it = le;
      return GET_ERR;
    }
    le = le->nx;
  }

  l->it = le;
  if (le->c == c) {
    return le->id;
  }
  return GET_ERR;
}

// SETTERS
void insert(SortedList l, unsigned char c, size_t id) {
  FAIL_IF(l == NULL, "list is null");

  #ifdef DEBUG_SORTED_LIST
    fprintf(stderr, "insert %c %lu\n", c, id);
    debug(l);
  #endif

  if (get(l, c) == GET_ERR) {
    // getSL puts l->it at the right place to insert
    ListElem le = malloc(sizeof(struct _listelem));
    FAIL_IF(le == NULL, "malloc failed");
    le->c = c;
    le->id = id;
    l->len++;
    if (l->it == NULL) {
      // Empty list or first item
      le->nx = l->hd;
      l->hd = le;
    } else {
      le->nx = l->it->nx;
      l->it->nx = le;
    }
    l->it = le;
  } else {
    // Element exists, update it
    l->it->id = id;
  }
}

void clear(SortedList l) {
  FAIL_IF(l == NULL, "list is null");
  while (l->hd != NULL) {
    ListElem le = l->hd;
    l->hd = le->nx;
    free(le);
    l->len--;
  }
  l->it = NULL;
  FAIL_IF(l->len != 0, "internal error");
}

// TOOLS IMPLEMENTATION
#ifdef DEBUG_SORTED_LIST
void debug(SortedList l) {
  if (l == NULL) {
    fprintf(stderr, "the list is null");
    return;
  }
  fprintf(stderr, "List of %lu element(s) :", l->len);
  if (l->it == NULL) {
    fprintf(stderr, "iterator null\n\t");
  } else {
    fprintf(stderr, "iterator on %c\n\t", l->it->c);
  }

  ListElem cur = l->hd;
  while (cur != NULL) {
    fprintf(stderr, "%c(%lu) ", cur->c, cur->id);
    cur = cur->nx;
  }
  fprintf(stderr, "\n");
}
#endif
