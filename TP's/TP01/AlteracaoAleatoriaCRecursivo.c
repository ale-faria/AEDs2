#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int verificaFim(char *frase){
    if(frase[0] != 'F' && frase[1] != 'I' && frase[2] != 'M'){
        return 1;
    } else {
        return 0;
    }
}

char* alteraString(char* frase, char caracter1, char caracter2, int indice, int tamanho){
    if(indice == tamanho){
        return frase;
    }

    if(frase[indice] == caracter1){
        frase[indice] = caracter2;
    }

    alteraString(frase, caracter1, caracter2, indice+1, tamanho);

}

int main(void){
    srand(4);  // Define a semente para o gerador de números aleatórios
    char caracter1 = 'a' + (rand() % 26);
    char caracter2 = 'a' + (rand() % 26);
    //printf(" %c, %c\n", caracter1, caracter2);

    char frase[100];
    char* resposta;

    // Lê a primeira linha de entrada
    fgets(frase, sizeof(frase), stdin);
    frase[strcspn(frase, "\n")] = '\0';  // Remove o '\n' do final

    while(verificaFim(frase)){

        resposta = alteraString(frase, caracter1, caracter2, 0, strlen(frase));
        printf("%s\n", resposta);

        caracter1 = 'a' + (rand() % 26);
        caracter2 = 'a' + (rand() % 26);
        //printf(" %c, %c\n", caracter1, caracter2);

        fgets(frase, sizeof(frase), stdin);
        frase[strcspn(frase, "\n")] = '\0';
    }

return 0;
}
