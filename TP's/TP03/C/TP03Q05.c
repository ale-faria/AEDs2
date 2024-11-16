#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAMANHO 100


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
INICIO LISTA DINAMICA SIMPLES
----------------------------------------------------------
*/

typedef struct Celula {
	Pokemon* elemento;
	struct Celula* prox;
} Celula;

Celula* novaCelula(Pokemon* elemento) {
   Celula* nova = (Celula*) malloc(sizeof(Celula));
   nova->elemento = elemento;
   nova->prox = NULL;
   return nova;
}

Celula* primeiro;
Celula* ultimo;

void start() {
   primeiro = novaCelula(-1);
   ultimo = primeiro;
}

// Funcoes para inserir um Pokemon na lista
void inserirInicio(Pokemon* x) {
   Celula* tmp = novaCelula(x);
   tmp->prox = primeiro->prox;
   primeiro->prox = tmp;
   if (primeiro == ultimo) {
      ultimo = tmp;
   }
   tmp = NULL;
}

void inserirFim(Pokemon* x) {
   ultimo->prox = novaCelula(x);
   ultimo = ultimo->prox;
}

Pokemon* removerInicio() {
    if (primeiro == ultimo){
        printf("Erro ao remover (lista vazia)!\n");
        return NULL;
    }

   Celula* tmp = primeiro;
   primeiro = primeiro->prox;
   Pokemon* resp = primeiro->elemento;
   tmp->prox = NULL;
   free(tmp);
   tmp = NULL;
   return resp;
}

Pokemon* removerFim() {
    if (primeiro == ultimo){
        printf("Erro ao remover (lista vazia)!\n");
        return NULL;
    }

   // Caminhar ate a penultima celula:
   Celula* i;
   for(i = primeiro; i->prox != ultimo; i = i->prox);

   Pokemon* resp = ultimo->elemento;
   ultimo = i;
   free(ultimo->prox);
   i = ultimo->prox = NULL;

   return resp;
}

int tamanho() {
   int tamanho = 0;
   Celula* i;
   for(i = primeiro; i != ultimo; i = i->prox, tamanho++);
   return tamanho;
}

void inserir(Pokemon* x, int pos) {
   int tam = tamanho();

   if(pos < 0 || pos > tam){
      printf("Erro ao inserir na posicao (%d)! Tamanho atual: %d\n", pos, tam);
   } else if (pos == 0){
      inserirInicio(x);
   } else if (pos == tam){
      inserirFim(x);
   } else {
      // Caminhar ate a posicao anterior a insercao
      int j;
      Celula* i = primeiro;
      for(j = 0; j < pos; j++, i = i->prox);

      Celula* tmp = novaCelula(x);
      tmp->prox = i->prox;
      i->prox = tmp;
      tmp = i = NULL;
   }
}

Pokemon* remover(int pos) {
   Pokemon* resp;
   int tam = tamanho();

   if (primeiro == ultimo){
      printf("Erro ao remover (vazia)!");
   } else if(pos < 0 || pos >= tam){
      printf("Erro ao remover na posicao (%d)! Tamanho atual: %d\n", pos, tam);
   } else if (pos == 0){
      resp = removerInicio();
   } else if (pos == tam - 1){
      resp = removerFim();
   } else {
      // Caminhar ate a posicao anterior a insercao
      Celula* i = primeiro;
      int j;
      for(j = 0; j < pos; j++, i = i->prox);

      Celula* tmp = i->prox;
      resp = tmp->elemento;
      i->prox = tmp->prox;
      tmp->prox = NULL;
      free(tmp);
      i = tmp = NULL;
   }
   return resp;
}

/*
----------------------------------------------------------
FIM LISTA DINAMICA SIMPLES
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

    int numComandos; // Quantidade de comandos a processar
    scanf("%d", &numComandos);

    for (int i = 0; i < numComandos; i++) {
        char comando[3];
        int posicao, id;
        scanf("%s", comando); // Ler comando

        if (strcmp(comando, "II") == 0) {
            scanf("%d", &id);
            Pokemon* pokemon = procuraPokemonPorId(&pokemonList, id);
            if (pokemon) inserirInicio(pokemon);

        } else if (strcmp(comando, "I*") == 0) {
            scanf("%d %d", &posicao, &id);
            Pokemon* pokemon = procuraPokemonPorId(&pokemonList, id);
            if (pokemon) inserir(pokemon, posicao);

        } else if (strcmp(comando, "IF") == 0) {
            scanf("%d", &id);
            Pokemon* pokemon = procuraPokemonPorId(&pokemonList, id);
            if (pokemon) inserirFim(pokemon);

        } else if (strcmp(comando, "RI") == 0) {
            Pokemon* removido = removerInicio();
            if (removido) printf("(R) %s\n", removido->name);

        } else if (strcmp(comando, "R*") == 0) {
            scanf("%d", &posicao);
            Pokemon* removido = remover(posicao);
            if (removido) printf("(R) %s\n", removido->name);

        } else if (strcmp(comando, "RF") == 0) {
            Pokemon* removido = removerFim();
            if (removido) printf("(R) %s\n", removido->name);
        }
    }

    // Exibir lista final de Pokemons apos as operacoes
    int index = 0;
    for (Celula* i = primeiro->prox; i != NULL; i = i->prox) {
        printf("[%d] ", index);
        imprimirPokemon(i->elemento);
        index++;
    }

    return 0;
}

