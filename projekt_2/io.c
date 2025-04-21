/*
*    Autor: Denys Pylypenko
*    Fakulta: FIT
*    IJC-DU2, zadani 1 b)
*    Soubor: io.c
*    Datum: 23.4.2024
*/

#include <stdio.h>
#include <ctype.h>  // Pro isspace
#include <string.h> // Pro strncpy a memset

int read_word(char *s, int max, FILE *f) {
    int c, len = 0;
    static int warning_printed = 0; // flag pro tisk varovani pouze jednou

    // Preskakujeme prazdne znaky
    while ((c = fgetc(f)) != EOF && isspace(c));

    if (c == EOF) {
        return EOF; // Konec souboru
    }

    // Cteni znaku do dalsiho prazdneho znaku nebo EOF
    do {
        if (len < max - 1) {
            s[len++] = c;
        } else if (!warning_printed) {
            // Pokud je slovo prilis dlouhe a varovani jeste nebylo vypsano
            fprintf(stderr, "Varovani: delka slova prekracuje %d znaku. Zkracuji.\n", max - 1);
            warning_printed = 1;
        }
    } while ((c = fgetc(f)) != EOF && !isspace(c));

    s[len] = '\0'; // Ukocujeme retezec nulovym znakem
    return len; // Vracime delku slova
}
