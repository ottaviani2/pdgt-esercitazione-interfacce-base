#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
char c[30];
char z[30];
int l;


int main() {
    fprintf(stdout, "Test output\n");
    fprintf(stderr, "Test errore\n");
    

    printf("Inserire la frase da convertire in maiusolo\n"); 
    printf("Massimo 30 caratteri\n"); 
    gets(c);
    l = strlen(c);
    
    
    for(int i=0;i<l;i++){
        z[i]=char(toupper(c[i]));
        printf ("%c",z[i]);
    }
}
