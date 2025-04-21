/*
*    Autor: Denys Pylypenko
*    Fakulta: FIT
*    IJC-DU2, zadani 1 a)
*    Soubor: tail.c
*    Datum: 17.4.2024
*/

#define _POSIX_C_SOURCE 200809L // pro funkci strdup
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define LIMIT_MAX 2047

typedef struct {
    bool number_flag;
    char * filename;
    int numberOfLines;
} config_t;

/* GLOBALNI KONFIGURACE */
config_t config = {
    .number_flag = false,
    .filename = NULL, // Zadny soubor neni zadan ve vychozim nastaveni
    .numberOfLines = 10
};

bool parse_args(int argc, char **argv){

    for (int i = 1; i < argc; i++) {
        
        if (strcmp(argv[i], "-n") == 0) {
            config.number_flag = true;
            if (i + 1 < argc && (i + 2 < argc || i + 2 == argc)) {  // Kontrolujeme, ze za -n nasleduje cislo a mozna jmeno souboru
                config.numberOfLines = atoi(argv[i + 1]);  // Prevedeme nasledujici argument na cislo
                if (config.numberOfLines < 1) {
                    fprintf(stderr, "Chyba: spatne cislo radku '%s'\n", argv[i + 1]);
                    return false;
                }
                i++;  // Preskocime cislo
                if (i + 1 < argc) { // Pokud je za cislem jeste jeden argument, predpokladame, ze je to jmeno souboru
                    config.filename = argv[i + 1];
                    i++;
                }
            } else {
                fprintf(stderr, "Chyba: Pocet radku po -n neni urcen \n");
                return false;
            }
        }
        else {
            // Pokud argument neni '-n', bereme ho jako nazev souboru
            config.filename = argv[1];
        }
    }

    return true;
}

typedef struct {
    char **buffer;
    int capacity;
    int count;
    int head;
} CircularBuffer;

CircularBuffer* cbuf_create(int n) {
    CircularBuffer *cb = malloc(sizeof(CircularBuffer));
    if (!cb) {
        fprintf(stderr, "Chyba pri vyhrazovani pameti pro kruhovy buffer\n");
        return NULL;
    }
    cb->buffer = malloc(sizeof(char*) * n);
    if (!cb->buffer) {
        free(cb);
        fprintf(stderr, "Chyba pri vyhrazovani pameti pro buffer radku\n");
        return NULL;
    }
    cb->capacity = n;
    cb->count = 0;
    cb->head = 0;
    return cb;
}

void cbuf_put(CircularBuffer *cb, const char *line) {
    char *line_to_store = strdup(line);
    if (strlen(line_to_store) > LIMIT_MAX) {
        fprintf(stderr, "Varovani: Delka radku prekracuje maximalne povolene (%d znaku). Radek bude orezan.\n", LIMIT_MAX);
        line_to_store[LIMIT_MAX] = '\0';  // Orezavame radek do maximalne povolene delky
    }
    
    int index = (cb->head + cb->count) % cb->capacity;
    if (cb->count == cb->capacity) {
        free(cb->buffer[cb->head]);
        cb->buffer[cb->head] = line_to_store;
        cb->head = (cb->head + 1) % cb->capacity;
    } else {

        cb->buffer[index] = line_to_store;
        cb->count++;
    }
}

char* cbuf_get(CircularBuffer *cb, int index) {
    if (index >= 0 && index < cb->count) {
        return cb->buffer[(cb->head + index) % cb->capacity];
    }
    return NULL;
}

void cbuf_free(CircularBuffer *cb) {
    for (int i = 0; i < cb->count; i++) {
        free(cb->buffer[(cb->head + i) % cb->capacity]);
    }
    free(cb->buffer);
    free(cb);
}

void read_input_and_process(FILE *input, CircularBuffer *cb) {
    char line[LIMIT_MAX + 2]; // Dalsi znaky pro znak nove radky a nulovy terminator
    while (fgets(line, sizeof(line), input)) {
        if (line[strlen(line) - 1] != '\n' && !feof(input)) {
            fprintf(stderr, "Varovani: Radek je prilis dlouhy a bude orezan.\n");
            // Preskakujeme zbytek radku
            int c;
            while ((c = fgetc(input)) != '\n' && c != EOF) {}
        }
        cbuf_put(cb, line);
    }
}

int main(int argc, char *argv[]) {

    if (!parse_args(argc, argv)) return 42;

    FILE *input = stdin;  // Ve vychozim nastaveni cteme ze stdin
    if (config.filename != NULL) {
        input = fopen(config.filename, "r");
        if (input == NULL) {
            fprintf(stderr, "Chyba: otevreni souboru %s\n", config.filename);
            return 0;
        }
    }

    CircularBuffer *cb = cbuf_create(config.numberOfLines > 0 ? config.numberOfLines : 10);
    read_input_and_process(input, cb);

    for (int i = 0; i < cb->count; i++) {
        printf("%s", cbuf_get(cb, i));
    }

    cbuf_free(cb);
    if (input != stdin) {
        fclose(input); // Zavirame soubor, pokud byl otevren
    }
    return 0;
}
