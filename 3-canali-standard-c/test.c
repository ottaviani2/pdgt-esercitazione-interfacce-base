#include <stdio.h>

int main() {
    fprintf(stdout, "Test output\n");
    fprintf(stderr, "Test errore\n");

    printf("Leggo il primo carattere di input...\n"); // equivalente a fprintf(stdin...)
    char c = fgetc(stdin);
    printf("Hai scritto %c\n", c);
}
