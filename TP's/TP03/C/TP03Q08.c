#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_TAMANHO 5


char *strsep(char **stringp, const char *delim) {
    char *start = *stringp;
    char *p;

    if (start == NULL) {
        return NULL;
    }

    p = strpbrk(start, delim);
    if (p) {
        *p = '\0';
        *stringp = p + 1;
    } else {
        *stringp = NULL;
    }

    return start;
}

typedef struct {
    int id;
    int generation;
    char name[50];
    char description[200];
    char types[2][20];
    int quantTypes;
    char abilities[6][30];
    int quantAbilities;
    double weight;
    double height;
    int captureRate;
    int isLegendary;
    char captureDate[11];
} Pokemon;

typedef struct {
    Pokemon *pokemons;
    int size;
} PokemonList;

/*
----------------------------------------------------------
INICIO LISTA DUPLAMENTE ENCADEADA
----------------------------------------------------------
*/

typedef struct CelulaDupla{
    Pokemon* elemento;
    struct CelulaDupla* prox;
    struct CelulaDupla* ant;
} CelulaDupla;

CelulaDupla* novaCelulaDupla(Pokemon* elemento) {
   CelulaDupla* nova = (CelulaDupla*) malloc(sizeof(CelulaDupla));
   nova->elemento = elemento;
   nova->ant = nova->prox = NULL;
   return nova;
}

CelulaDupla* primeiro;
CelulaDupla* ultimo;

void start() {
   primeiro = novaCelulaDupla(NULL);
   ultimo = primeiro;
}

void inserirInicio(Pokemon* x) {
   CelulaDupla* tmp = novaCelulaDupla(x);

   tmp->ant = primeiro;
   tmp->prox = primeiro->prox;
   primeiro->prox = tmp;
   if (primeiro == ultimo) {
      ultimo = tmp;
   } else {
      tmp->prox->ant = tmp;
   }
   tmp = NULL;
}

void inserirFim(Pokemon* x) {
   ultimo->prox = novaCelulaDupla(x);
   ultimo->prox->ant = ultimo;
   ultimo = ultimo->prox;
}

Pokemon* removerInicio() {
   if (primeiro == ultimo) {
      printf("Erro ao remover (vazia)!");
      return NULL;
   }

   CelulaDupla* tmp = primeiro;
   primeiro = primeiro->prox;
   Pokemon* resp = primeiro->elemento;
   tmp->prox = primeiro->ant = NULL;
   free(tmp);
   tmp = NULL;
   return resp;
}

Pokemon* removerFim() {
   if (primeiro == ultimo) {
      printf("Erro ao remover (vazia)!");
      return NULL;
   }
   Pokemon* resp = ultimo->elemento;
   ultimo = ultimo->ant;
   ultimo->prox->ant = NULL;
   free(ultimo->prox);
   ultimo->prox = NULL;
   return resp;
}

int tamanho() {
   int tamanho = 0;
   CelulaDupla* i;
   for(i = primeiro; i != ultimo; i = i->prox, tamanho++);
   return tamanho;
}

void inserir(Pokemon* x, int pos) {

   int tam = tamanho();

   if(pos < 0 || pos > tam){
      printf("Erro ao remover (posicao %d/%d invalida!", pos, tam);
      return;
   } else if (pos == 0){
      inserirInicio(x);
   } else if (pos == tam){
      inserirFim(x);
   } else {
      // Caminhar ate a posicao anterior a insercao
      CelulaDupla* i = primeiro;
      int j;
      for(j = 0; j < pos; j++, i = i->prox);

      CelulaDupla* tmp = novaCelulaDupla(x);
      tmp->ant = i;
      tmp->prox = i->prox;
      tmp->ant->prox = tmp->prox->ant = tmp;
      tmp = i = NULL;
   }
}

Pokemon* remover(int pos) {
   Pokemon* resp;
   int tam = tamanho();

   if (primeiro == ultimo){
      printf("Erro ao remover (vazia)!");
      return NULL;
   } else if(pos < 0 || pos >= tam){
      printf("Erro ao remover (posicao %d/%d invalida!", pos, tam);
      return NULL;
   } else if (pos == 0){
      resp = removerInicio();
   } else if (pos == tam - 1){
      resp = removerFim();
   } else {
      // Caminhar ate a posicao anterior a insercao
      CelulaDupla* i = primeiro->prox;
      int j;
      for(j = 0; j < pos; j++, i = i->prox);

      i->ant->prox = i->prox;
      i->prox->ant = i->ant;
      resp = i->elemento;
      i->prox = i->ant = NULL;
      free(i);
      i = NULL;
   }

   return resp;
}
/*
----------------------------------------------------------
FIM LISTA DUPLAMENTE ENCADEADA
----------------------------------------------------------
*/

void imprimirPokemon(Pokemon *pokemon) {

    printf("[#%d -> %s: %s - ['%s'", pokemon->id, pokemon->name, pokemon->description, pokemon->types[0]);

    // Tipos (types)
    if(pokemon->quantTypes == 2){
        printf(", '%s']", pokemon->types[1]);
    }

    if(pokemon->quantTypes == 1){
        printf("]");
    }

    // Habilidades (abilities)
    printf(" - ");
    int i = 0, j = 1;
    while(i < pokemon->quantAbilities){
        if(j >= 0 && j < pokemon->quantAbilities)
        printf("%s, ", pokemon->abilities[i]);
        if(j == pokemon->quantAbilities){
            printf("%s", pokemon->abilities[i]);
        }
        i++;
        j++;
    }

    printf(" - %.1fkg - %.1fm - %d%% - %s - %d gen] - %s\n", pokemon->weight, pokemon->height, pokemon->captureRate, pokemon->isLegendary ? "true" : "false",
           pokemon->generation, pokemon->captureDate);
}

PokemonList readPokemonCSV(char *filePath) {

    //printf("entrou na leitura de arquivo\n");
    FILE *file = fopen(filePath, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    PokemonList pokemonList;
    pokemonList.size = 0;
    pokemonList.pokemons = malloc(1000* sizeof(Pokemon)); // Alocacao inicial

    char line[1024];
    fgets(line, sizeof(line), file); // Pular o cabecalho

    while (fgets(line, sizeof(line), file)) {
        Pokemon pokemon;
        char abilitiesStr[200];
        char typesStr[200];

        char *token = NULL;
        char *lineCopy = line;

        // Parse ID
        token = strsep(&lineCopy, ",");
        pokemon.id = atoi(token);

        // Parse generation
        token = strsep(&lineCopy, ",");
        pokemon.generation = atoi(token);

        // Parse name
        token = strsep(&lineCopy, ",");
        strcpy(pokemon.name, token);

        // Parse description
        token = strsep(&lineCopy, ",");
        strcpy(pokemon.description, token);

        // Parse types
        token = strsep(&lineCopy, "\"");
        strcpy(typesStr, token);

        // Parse abilities
        token = strsep(&lineCopy, "\"");
        strcpy(abilitiesStr, token);

        // Parse weight
        token = strsep(&lineCopy, ",");
        token = strsep(&lineCopy, ",");
        if (token == NULL) {
            pokemon.weight = 0;
        } else {
            pokemon.weight = atof(token);
        }

        // Parse height
        token = strsep(&lineCopy, ",");
        if (token == NULL) {
            pokemon.height = 0;
        } else {
            pokemon.height = atof(token);
        }

        // Parse captureRate
        token = strsep(&lineCopy, ",");
        pokemon.captureRate = atoi(token);

        // Parse isLegendary
        token = strsep(&lineCopy, ",");
        pokemon.isLegendary = atoi(token);

        // Parse captureDate
        token = strsep(&lineCopy, "\n");
        if (token != NULL) {
            strcpy(pokemon.captureDate, token);
        } else {
            strcpy(pokemon.captureDate, "N/A");
        }

        // Parse types
        char *tokenTypes = strtok(typesStr, ",");
        int i = 0;
        while(tokenTypes != NULL && i < 2){
            strcpy(pokemon.types[i++], tokenTypes);
            tokenTypes = strtok(NULL, ",");
        }
        pokemon.quantTypes = i;

        // Parse abilities
        char *tokenAbilities = strtok(abilitiesStr, ",");
        i = 0;
        while (tokenAbilities != NULL && i < 7) {
            strcpy(pokemon.abilities[i++], tokenAbilities);
            tokenAbilities = strtok(NULL, ",");
        }
        pokemon.quantAbilities = i;

        // Adicionar o pokemon na lista
        pokemonList.pokemons[pokemonList.size++] = pokemon;
    }

    fclose(file);
    return pokemonList;
}

Pokemon *procuraPokemonPorId(PokemonList *pokemonList, int id) {
    for (int i = 0; i < pokemonList->size; i++) {
        if (pokemonList->pokemons[i].id == id) {
            return &pokemonList->pokemons[i];
        }
    }
    return NULL;
}

// Funcao para particionar a lista duplamente encadeada
CelulaDupla* particionar(CelulaDupla* inicio, CelulaDupla* fim) {
    Pokemon* pivo = fim->elemento; // Escolhemos o pivo como o elemento no final
    CelulaDupla* i = inicio->ant; // Menor parte da lista

    for (CelulaDupla* j = inicio; j != fim; j = j->prox) {
        // Comparacao por geracao e, em caso de empate, por nome
        if ((j->elemento->generation < pivo->generation) ||
            (j->elemento->generation == pivo->generation &&
             strcmp(j->elemento->name, pivo->name) < 0)) {
            i = (i == NULL) ? inicio : i->prox; // Avanca o menor
            Pokemon* temp = i->elemento;
            i->elemento = j->elemento;
            j->elemento = temp; // Troca elementos
        }
    }

    i = (i == NULL) ? inicio : i->prox; // Posiciona o pivo
    Pokemon* temp = i->elemento;
    i->elemento = fim->elemento;
    fim->elemento = temp;

    return i; // Retorna a celula do pivo
}

// Funcao recursiva do quicksort para listas duplamente encadeadas
void quicksortLista(CelulaDupla* inicio, CelulaDupla* fim) {
    if (inicio != NULL && fim != NULL && inicio != fim && inicio != fim->prox) {
        CelulaDupla* pivo = particionar(inicio, fim);
        quicksortLista(inicio, pivo->ant); // Ordena a parte a esquerda do pivo
        quicksortLista(pivo->prox, fim);  // Ordena a parte a direita do pivo
    }
}

// Funcao auxiliar para encontrar a ultima celula da lista
CelulaDupla* encontrarUltimo(CelulaDupla* inicio) {
    CelulaDupla* atual = inicio;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    return atual;
}

int main(void) {
    char *filePath;
    //filePath = "pokemon.csv";
    filePath = "/tmp/pokemon.csv"; // Caminho no Verde

    PokemonList pokemonList = readPokemonCSV(filePath); // Leitura do arquivo csv
    start();

    int position = 0;
    char entrada[30];

    while (1) {
        scanf("%s", entrada);

        if (strcmp(entrada, "FIM") == 0) {
            break;
        }

        int id = atoi(entrada);
        Pokemon *pokemon = procuraPokemonPorId(&pokemonList, id);
        if (pokemon != NULL) {
            inserirFim(pokemon);
        }
    }

    // Ordena a lista duplamente encadeada
    CelulaDupla* fim = encontrarUltimo(primeiro->prox);
    quicksortLista(primeiro->prox, fim);

    // Imprime a lista ordenada
    for (CelulaDupla* i = primeiro->prox; i != NULL; i = i->prox) {
        imprimirPokemon(i->elemento);
    }

    return 0;
}
