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
INICIO FILA CIRCULAR FLEXIVEL
----------------------------------------------------------
*/

typedef struct Celula {
    Pokemon* elemento;
    struct Celula* prox;
} Celula;

typedef struct {
    Celula* primeiro;
    Celula* ultimo;
    int tamanho; // Contador para o numero de elementos na fila
} FilaCircularDePokemon;

Celula* novaCelula(Pokemon* elemento) {
    Celula* nova = (Celula*)malloc(sizeof(Celula));
    nova->elemento = elemento;
    nova->prox = NULL;
    return nova;
}

// Declaracoes das funcoes
Pokemon* remover(FilaCircularDePokemon* fila);
int calculaMediaCaptureRate(FilaCircularDePokemon* fila);

// Metodo para inicializar a fila circular
void inicializarFilaCircular(FilaCircularDePokemon* fila) {
    fila->primeiro = fila->ultimo = NULL;
    fila->tamanho = 0;
}

// Metodo para inserir um Pokemon na fila circular
void inserir(FilaCircularDePokemon* fila, Pokemon* pokemon) {
    Celula* nova = novaCelula(pokemon);

    if (fila->tamanho == MAX_TAMANHO) {
        remover(fila); // Remove o fila estiver cheia
    }

    if (fila->tamanho == 0) {
        fila->primeiro = fila->ultimo = nova;
        fila->ultimo->prox = fila->primeiro; // Liga o ultimo ao primeiro
    } else {
        fila->ultimo->prox = nova;
        fila->ultimo = nova;
        fila->ultimo->prox = fila->primeiro; // Mantem a circularidade
    }

    fila->tamanho++;
    printf("M\u00E9dia: %d\n", calculaMediaCaptureRate(fila));
}

// Funcao para remover um Pokemon da fila circular
Pokemon* remover(FilaCircularDePokemon* fila) {
    if (fila->tamanho == 0) {
        printf("Erro: Fila esta vazia!\n");
        exit(1);
    }

    Celula* tmp = fila->primeiro;
    Pokemon* resp = tmp->elemento;

    if (fila->tamanho == 1) {
        fila->primeiro = fila->ultimo = NULL;
    } else {
        fila->primeiro = fila->primeiro->prox;
        fila->ultimo->prox = fila->primeiro; // Mantem a circularidade
    }

    free(tmp);
    fila->tamanho--;
    return resp;
}

/*
----------------------------------------------------------
FIM FILA CIRCULAR FLEXIVEL
----------------------------------------------------------
*/

// Funcao para calcular a media dos captureRates dos Pokemons na fila
int calculaMediaCaptureRate(FilaCircularDePokemon* fila){
    int soma = 0;
    int resp = 0;
    int cont = 0;
    for (Celula* atual = fila->primeiro; cont < fila->tamanho; atual = atual->prox, cont++) {
       soma += atual->elemento->captureRate;
    }

    if(fila->tamanho > 0){
        resp = (int)round((double)soma / fila->tamanho);
    }
    return resp;
}

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
    FilaCircularDePokemon fila;
    inicializarFilaCircular(&fila);

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
            inserir(&fila, pokemon);
        }
    }

    int numComandos; // Quantidade de comandos a processar
    scanf("%d", &numComandos);

    for (int i = 0; i < numComandos; i++) {
        char comando[3];
        int posicao, id;
        scanf("%s", comando); // Ler comando

        if (strcmp(comando, "I") == 0) {
            scanf("%d", &id);
            Pokemon* pokemon = procuraPokemonPorId(&pokemonList, id);
            if (pokemon) inserir(&fila, pokemon);
            // media arredondada do captureRate dos Pokemons contidos na fila no momento
            //printf("M\u00E9dia: %d\n", calculaMediaCaptureRate(&fila));

        } else if (strcmp(comando, "R") == 0) {
            Pokemon* removido = remover(&fila);
            if (removido) printf("(R) %s\n", removido->name);
        }
    }

    printf("\n");

    // Exibir fila final de Pokemons apos as operacoes
    Celula* atual = fila.primeiro;
    for (int i = 0; i < fila.tamanho;i++) {
        printf("[%d] ", i);
        imprimirPokemon(atual->elemento);
        atual = atual->prox;
    }

    return 0;
}
