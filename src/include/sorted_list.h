#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdlib.h>

#define GET_ERR 0

/**
 * Generic SortedList type, can support NULL element.
 */
typedef struct _list *SortedList;

// CONSTRUCTOR

/**
 * Create and allocate a new empty SortieList.
 */
SortedList newList();

// FREE
/**
 * Free the memory allocated from the SortedList.
 */
void freeList(SortedList* l);

// GETTERS

/**
 * Get SortedList's length
 */
size_t length(SortedList l);

/**
 * Get element in SortedList
 */
size_t get(SortedList l, unsigned char c);

// SETTERS

/**
 * Insert element in SortedList
 */
void insert(SortedList l, unsigned char c, size_t id);

/**
 * Clear SortedList
 */
void clear(SortedList l);

#endif // SORTED_LIST_H
