// no-comment.c
// Reseni IJC-DU1, priklad b), 23.3.2024
// Autor: Denys Pylypenko, FIT
// Prelozeno: gcc 13.2.1

#include <stdio.h>
#include <stdlib.h>
#include "error.h"

int main(int argc, char *argv[]) {
    FILE *fp = stdin; // Standardne cteme ze stdin, pokud nic jineho neni receno

    // Kdyz mame argument, zkousime otevrit soubor
    if (argc > 1) {
        fp = fopen(argv[1], "r");
        if (!fp) {
            error_exit("Chyba pri otevirani souboru");
        }
    }

    int stav = 0; 
    int c;

    while ((c = fgetc(fp)) != EOF) {
        switch (stav) {
        case 0: // Zacatek
            if (c == '/') stav = 1;
            else if (c == '"') { stav = 4; putchar(c); } // Zacatek retezce
            else if (c == '\'') { stav = 6; putchar(c); } // Zacatek znaku
            else putchar(c);
            break;
        case 1: // Nasleduje '/'
            if (c == '*') stav = 2; // Zacina viceradkovy komentar
            else if (c == '/') stav = 7; // Zacina jednoradkovy komentar
            else { stav = 0; putchar('/'); putchar(c); } // Falesny poplach, pokracujeme
            break;
        case 2: // Uvnitr viceradkoveho komentare
            if (c == '*') stav = 3;
            break;
        case 3: // Mozny konec viceradkoveho komentare
            if (c == '/') { stav = 0; putchar(' '); } // Konec komentare, davame mezernik
            else if (c != '*') stav = 2;
            break;
        case 4: // Uvnitr retezce
            if (c == '\\') stav = 5; // Escape sekvence
            else if (c == '"') stav = 0; // Konec retezce
            putchar(c);
            break;
        case 5: // Po escape sekvenci v retezci
            stav = 4;
            putchar(c);
            break;
        case 6: // Uvnitr znaku
            if (c == '\\') stav = 8; // Escape sekvence
            else if (c == '\'') stav = 0; // Konec znaku
            putchar(c);
            break;
        case 7: // Uvnitr jednoradkoveho komentare
            if (c == '\n') { stav = 0; putchar(c); } // Konec radky, konec komentare
            break;
        case 8: // Po escape sekvenci v znaku
            stav = 6;
            putchar(c);
            break;
        }
    }

    if (fp != stdin) fclose(fp); // Pokud jsme otevreli soubor, zavreme ho

    if (stav != 0) fprintf(stderr, "Chyba: Neuzavreny komentar nebo retezec\n");

    return 0;
}
