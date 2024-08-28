#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int verificaFim(char *frase){
    if(frase[0] != 'F' && frase[1] != 'I' && frase[0] != 'M'){
        return 1;
    } else {
        return 0;
    }
}

int ehPalindromo(char *frase){
    int tamanho = strlen(frase);
    for(int i = 0; i < tamanho/2; i++){
        if(frase[i] != frase[tamanho-1-i]){
            return 0;
        }
    }
    return 1;
}

int main(void){
    char frase[100];
    fgets(frase, sizeof(frase), stdin);
    //remove o \n do final da string e coloca \0
    frase[strcspn(frase, "\n")] = '\0';

    while(verificaFim(frase)){
        if(ehPalindromo(frase) == 1){
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }
        fgets(frase, sizeof(frase), stdin);
        frase[strcspn(frase, "\n")] = '\0';
    }

return 0;
}
