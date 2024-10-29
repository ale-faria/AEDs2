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
INICIO LISTA
----------------------------------------------------------
*/

typedef struct {
    Pokemon* pokeLista[MAX_TAMANHO];
    int n;
} ListaDePokemon;

// Funcao para inicializar a lista
void inicializarLista(ListaDePokemon* lista) {
    lista->n = 0;
}

// Funcoes para inserir um Pokemon na lista
void inserirInicio(ListaDePokemon* lista, Pokemon* pokemon) {
    if (lista->n >= MAX_TAMANHO) {
        printf("Erro: Lista cheia!\n");
        return;
    }

    for (int i = lista->n; i > 0; i--) {
        lista->pokeLista[i] = lista->pokeLista[i - 1];
    }

    lista->pokeLista[0] = pokemon;
    lista->n++;
}

void inserirPosicao(ListaDePokemon* lista, Pokemon* pokemon, int pos) {
    if (lista->n >= MAX_TAMANHO || pos < 0 || pos > lista->n) {
        printf("Erro: Posicao invalida!\n");
        return;
    }

    for (int i = lista->n; i > pos; i--) {
        lista->pokeLista[i] = lista->pokeLista[i - 1];
    }

    lista->pokeLista[pos] = pokemon;
    lista->n++;
}

void inserirFim(ListaDePokemon* lista, Pokemon* pokemon) {
    if (lista->n >= MAX_TAMANHO) {
        printf("Erro: Lista cheia!\n");
        return;
    }

    lista->pokeLista[lista->n] = pokemon;
    lista->n++;
}

// Funcoes para remover um Pokemon da lista
Pokemon* removerInicio(ListaDePokemon* lista) {
    if (lista->n == 0) {
        printf("Erro: Lista vazia!\n");
        return NULL;
    }

    Pokemon* removido = lista->pokeLista[0];
    lista->n--;

    for (int i = 0; i < lista->n; i++) {
        lista->pokeLista[i] = lista->pokeLista[i + 1];
    }

    return removido;
}

Pokemon* removerPosicao(ListaDePokemon* lista, int pos) {
    if (lista->n == 0 || pos < 0 || pos >= lista->n) {
        printf("Erro: Posicao invalida!\n");
        return NULL;
    }

    Pokemon* removido = lista->pokeLista[pos];
    lista->n--;

    for (int i = pos; i < lista->n; i++) {
        lista->pokeLista[i] = lista->pokeLista[i + 1];
    }

    return removido;
}

Pokemon* removerFim(ListaDePokemon* lista) {
    if (lista->n == 0) {
        printf("Erro: Lista vazia!\n");
        return NULL;
    }

    return lista->pokeLista[--lista->n];
}

/*
----------------------------------------------------------
FIM LISTA
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
    ListaDePokemon lista;
    inicializarLista(&lista);

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
            inserirFim(&lista, pokemon);
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
            if (pokemon) inserirInicio(&lista, pokemon);

        } else if (strcmp(comando, "I*") == 0) {
            scanf("%d %d", &posicao, &id);
            Pokemon* pokemon = procuraPokemonPorId(&pokemonList, id);
            if (pokemon) inserirPosicao(&lista, pokemon, posicao);

        } else if (strcmp(comando, "IF") == 0) {
            scanf("%d", &id);
            Pokemon* pokemon = procuraPokemonPorId(&pokemonList, id);
            if (pokemon) inserirFim(&lista, pokemon);

        } else if (strcmp(comando, "RI") == 0) {
            Pokemon* removido = removerInicio(&lista);
            if (removido) printf("(R) %s\n", removido->name);

        } else if (strcmp(comando, "R*") == 0) {
            scanf("%d", &posicao);
            Pokemon* removido = removerPosicao(&lista, posicao);
            if (removido) printf("(R) %s\n", removido->name);

        } else if (strcmp(comando, "RF") == 0) {
            Pokemon* removido = removerFim(&lista);
            if (removido) printf("(R) %s\n", removido->name);
        }
    }

    // Exibir lista final de Pokemons apos as operacoes
    for (int i = 0; i < lista.n; i++) {
        printf("[%d] ", i);
        imprimirPokemon(lista.pokeLista[i]);
    }

    return 0;
}

