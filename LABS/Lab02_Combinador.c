#include <stdio.h>
#include <string.h>

int main(void){
    char frase1[100];
    char frase2[100];

    while(scanf("%s", frase1) != EOF && scanf("%s", frase2) != EOF){
        int tamanho = strlen(frase1) + strlen(frase2);
        char resultado[tamanho];

        int i = 0, j = 0, k = 0;
        while(frase1[i] != '\0' && frase2[j] != '\0'){
            resultado[k] = frase1[i];
            k++, i++;
            resultado[k] = frase2[j];
            k++, j++;
        }

        while(frase1[i] != '\0'){
            resultado[k] = frase1[i];
            k++, i++;
        }

        while(frase2[j] != '\0'){
            resultado[k] = frase2[j];
            k++, j++;
        }

        resultado[k] = '\0';

        printf("%s\n", resultado);
    }
return 0;
}
