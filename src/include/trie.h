#ifndef TRIE_H
#define TRIE_H

#include <stdlib.h>
#include <stdio.h>

/**
 * Trie enable to process the aho-corasick algorithm.
 */
typedef struct _trie *Trie;

// CONSTRUCTOR
/**
 * Create a new empty trie.
 */
extern Trie newTrie();

// DESTRUCTOR
/**
 * Free the memory allocated to the trie.
 */
extern void freeTrie(Trie* trie);

// IMPLEMENTATION

/**
 * Insert the nb words from the array in the trie. 
 * Prepare the fallback to apply the aho corasick algorithm.
 */
extern void insertAll(Trie t, unsigned char** words, const size_t nb);

/**
 * read a text and return the number of word occurence from the trie.
 */
extern size_t countInTrie(Trie t, FILE* f);

#endif // TRIE_H
