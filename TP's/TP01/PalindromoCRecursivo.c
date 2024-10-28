#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool verificaFim(char *frase){
    if(strcmp(frase, "FIM") == 0){
        return false;
    }
    return true;
}


bool ehPalindromo(char* frase, int inicio, int fim){
    if(inicio >= fim){
        return true; //true
    }


    if(frase[inicio] != frase[fim]){
        return false; //false
    } else {
        return ehPalindromo(frase, inicio+1, fim-1);
    }
}

int main(void){
    char frase[500];
    fgets(frase, sizeof(frase), stdin);
    frase[strcspn(frase, "\n")] = '\0';

    while(verificaFim(frase)){
        if(ehPalindromo(frase, 0, strlen(frase)-1)){
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }
        fgets(frase, sizeof(frase), stdin);
        frase[strcspn(frase, "\n")] = '\0';
    }
return 0;
}
