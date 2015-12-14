#!/bin/bash

function ac {
  echo "Éxécution des 3 Aho-corasick sur les mots $1 et le texte $2"
  ./bin/ac-matrice $1 $2
  ./bin/ac-liste $1 $2
  ./bin/ac-mixte $1 $2
  echo "----------"
}

function gen_alpha {
  echo "Génération des mots et textes d'alphabets de taille $1"
  ./bin/genere-texte 5000000 $1 > gen/texte_a$1
  ./bin/genere-mots 100 5 15 $1 > gen/mots_a$1_l5
  ./bin/genere-mots 100 15 30 $1 > gen/mots_a$1_l15
  ./bin/genere-mots 100 30 60 $1 > gen/mots_a$1_l30
  echo "----------"
}

function ac_run_one {
  echo "Éxécution des 3 Aho-corasick sur des alphabets de taille $1"
  ac gen/mots_a$1_l5 gen/texte_a$1
  ac gen/mots_a$1_l15 gen/texte_a$1
  ac gen/mots_a$1_l30 gen/texte_a$1
  echo "----------"
}

function gen {
  echo "Génération des mots et textes"
  mkdir -p gen
  gen_alpha 2
  gen_alpha 4
  gen_alpha 20
  gen_alpha 70
  echo "----------"
  echo "Génération terminée."
}

function ac_run {
  echo "Éxécution des algorithmes sur les textes"
  ac_run_one 2
  ac_run_one 4
  ac_run_one 20
  ac_run_one 70
  echo "----------"
  echo "Éxécution terminée."
}

#rm -f log.csv
#make
#make clean
gen
ac_run
exit
