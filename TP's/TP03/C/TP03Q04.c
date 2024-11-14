#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
INICIO FILA CIRCULAR
----------------------------------------------------------
*/

typedef struct {
    Pokemon* pokeFilaCircular[MAX_TAMANHO];
    int primeiro, ultimo;
} FilaCircularDePokemon;

// Funcao para inicializar a fila circular
void inicializarFilaCircular(FilaCircularDePokemon* filaCircular) {
    filaCircular->primeiro = filaCircular->ultimo = 0;
}

void inserir(FilaCircularDePokemon* fila, Pokemon* pokemon){
    if (((fila->ultimo + 1) % MAX_TAMANHO) == fila->primeiro){
        Pokemon* removido = remover(fila);
        if (removido) printf("(R) %s\n", removido->name);

    }

    fila->pokeFilaCircular[fila->ultimo] = pokemon;
    fila->ultimo = (fila->ultimo + 1) % MAX_TAMANHO;
}

Pokemon* remover(FilaCircularDePokemon *fila){
    if (fila->primeiro == fila->ultimo){
        exit(1);
    }

    Pokemon* resp = fila->pokeFilaCircular[fila->primeiro];
    fila->primeiro = (fila->primeiro + 1) % MAX_TAMANHO;
    return resp;
}


/*
----------------------------------------------------------
FIM FILA CIRCULAR
----------------------------------------------------------
*/

int calculaMediaCaptureRate(FilaCircularDePokemon* fila){
    int soma = 0;
    int resp = -1;
    for (int i = 0; i < MAX_TAMANHO; i++) {
        if (fila->pokeFilaCircular[i] != NULL) {
            soma += fila->pokeFilaCircular[i]->captureRate;
        }
    }

    resp = soma / MAX_TAMANHO;
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
    filePath = "pokemon.csv";
    //filePath = "/tmp/pokemon.csv"; // Caminho no Verde

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

        } else if (strcmp(comando, "R") == 0) {
            Pokemon* removido = remover(&fila);
            if (removido) printf("(R) %s\n", removido->name);
        }
    }

    // Exibir fila final de Pokemons após as operações
    int i = fila.primeiro;
    while (i != fila.ultimo){
        printf("[%d] ", i);
        imprimirPokemon(fila.pokeFilaCircular[i]);
        i = (i + 1) % MAX_TAMANHO;
    }
    return 0;
}

