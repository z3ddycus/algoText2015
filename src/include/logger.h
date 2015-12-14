#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#define HEADER "Log concernant les analyses d'aho-corasick.\nÉxécutable, Fichier texte, Fichier mots, Nb occurences, Temps d'éxécution"

/**
 * Log in the file filename the information extract from a text algorithm.
 */
extern void logInfo(char* filename, char* nomExec, char* fichierTexte,
  char* fichierMots, size_t nbOccurences, size_t time);

#endif
