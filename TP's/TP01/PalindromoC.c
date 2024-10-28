#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool verificaFim(char frase[]){
    if(strcmp(frase, "FIM") == 0){
        return false;
    }
    return true;
}

bool ehPalindromo(char frase[], int inicio, int fim){

    while(inicio < fim){
        if(frase[inicio] != frase[fim]){
            return false;
        }
        inicio++;
        fim--;
    }

    return true;
}

int main(void){
    char frase[500];
    fgets(frase, 500, stdin);
    //remove o \n do final da string e coloca \0
    frase[strcspn(frase, "\n")] = '\0';

    while(verificaFim(frase)){
        int tamanho = strlen(frase)-1;
        if(ehPalindromo(frase, 0, tamanho)){
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }
        fgets(frase, 500, stdin);
        frase[strcspn(frase, "\n")] = '\0';
    }

return 0;
}
