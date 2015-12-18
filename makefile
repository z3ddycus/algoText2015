CC       = gcc
CFLAGS   = -Wall -pedantic -std=c11 -O2 -ffunction-sections -fdata-sections -D_XOPEN_SOURCE=700

LFLAGS   = -Wl,--gc-sections

SRCDIR   = src
OBJDIR   = obj
BINDIR	 = bin

TARGETS := $(BINDIR)/gen_text $(BINDIR)/gen_words $(BINDIR)/ac-matrice $(BINDIR)/ac-liste $(BINDIR)/ac-mixte
MAINOBJ	:= $(OBJDIR)/main.o

SOURCES  := $(wildcard $(SRCDIR)/*.c)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OTHERS 	 := $(OBJDIR)/gen_text.o $(OBJDIR)/gen_words.o $(OBJDIR)/ac_main.o $(OBJDIR)/mixed_trie.o $(OBJDIR)/list_trie.o $(OBJDIR)/matrix_trie.o

all: objects $(BINDIR)/genere-texte $(BINDIR)/genere-mots $(BINDIR)/ac-liste $(BINDIR)/ac-matrice $(BINDIR)/ac-mixte
	@echo "Construction du projet terminée.\n"

$(BINDIR)/genere-texte: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $(OBJDIR)/gen_text.o $(filter-out $(OTHERS), $(OBJECTS)) $(LFLAGS)
	@echo "Construction de $@ teminée."
	@echo "----------"

$(BINDIR)/genere-mots: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $(OBJDIR)/gen_words.o $(filter-out $(OTHERS), $(OBJECTS)) $(LFLAGS)
	@echo "Construction de $@ teminée."
	@echo "----------"

$(BINDIR)/ac-matrice: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $(OBJDIR)/ac_main.o $(OBJDIR)/matrix_trie.o $(filter-out $(OTHERS), $(OBJECTS)) $(LFLAGS)
	@echo "Construction de $@ teminée."
	@echo "----------"

$(BINDIR)/ac-liste: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $(OBJDIR)/ac_main.o $(OBJDIR)/list_trie.o $(filter-out $(OTHERS), $(OBJECTS)) $(LFLAGS)
	@echo "Construction de $@ teminée."
	@echo "----------"

$(BINDIR)/ac-mixte: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $(OBJDIR)/ac_main.o $(OBJDIR)/mixed_trie.o $(filter-out $(OTHERS), $(OBJECTS)) $(LFLAGS)
	@echo "Construction de $@ teminée."
	@echo "----------"

objects: $(OBJECTS)
	@echo "Compilation des sources terminée."
	@echo "----------"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR)
	@echo "----------"
	@echo "Nettoyage des objets terminé."
	@echo "NB : Pour nettoyer complètement le projet, utiliser \"make cleaner\".\n"

cleaner:
	$(RM) -r $(OBJDIR) $(BINDIR)
	@echo "----------"
	@echo "Nettoyage du projet terminé.\n"
