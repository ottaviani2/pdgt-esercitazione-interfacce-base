#include <iostream>
#include <stdio.h>

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
    
    
    for(int i=0;i<30;i++){
        z[i]=char(toupper(c[i]));
        printf ("%c",z[i]);
    }
}
