#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    //printf("main");
    char *filePath;
    filePath = "/tmp/pokemon.csv";
    PokemonList pokemonList = readPokemonCSV(filePath);

    char entrada[10];
    scanf("%s", entrada);

    while (1) {
           // printf("entrada = %s\n", entrada);

        if (strcmp(entrada, "FIM") == 0) {
            break;
        }

        int id = atoi(entrada);
        Pokemon *pokemon = procuraPokemonPorId(&pokemonList, id);

        if (pokemon != NULL) {
            imprimirPokemon(pokemon);
        }

        scanf("%s", entrada);
    }

    free(pokemonList.pokemons);

   /*FILE *arquivo = fopen(filePath, "r");
   if(!arquivo){
    printf("Erro ao abrir\n");
   } else {
    printf("Arquivo aberto\n");
   }

   fclose(arquivo);*/
    return 0;
}
