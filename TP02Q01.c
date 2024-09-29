#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    int id;
    int generation;
    char name[50];
    char description[200];
    char types[2][20];
    int quantTypes;
    char abilities[7][30];
    int quantAbilities;
    double weight;
    double height;
    int captureRate;
    int isLegendary;
    struct tm captureDate;
} Pokemon;

typedef struct {
    Pokemon *pokemons;
    int size;
} PokemonList;

void imprimirPokemon(Pokemon *pokemon) {
    char dateStr[11];
    strftime(dateStr, sizeof(dateStr), "%dd/%mm/%YYYY", &pokemon->captureDate);


    printf("[#%d -> %s: %s - ['%s'", pokemon->id, pokemon->name, pokemon->description, pokemon->types[0]);
    if(pokemon->quantTypes == 2){
        printf(", '%s']", pokemon->types[1]);
    }
    int i = 0, j = 1;
    printf("] - [")
    while(i < pokemon->quantAbilities){
        if(j >= 0)
        printf("'%s', ", pokemon->abilities[i]);
        if(j == pokemon->quantAbilities){
            printf("'%s'", pokemon->abilities[i]);
        }
        i++;
        j++;
    }
    printf("] - %.1fkg - %.1fm - %d%% - %s - %d gen]- %s\n", pokemon->weight, pokemon->height, pokemon->captureRate, pokemon->isLegendary ? "true" : "false",
           pokemon->generation, dateStr);
    /*printf("#%d -> %s: %s - ['%s', '%s'] - ['%s', '%s', '%s', '%s', '%s'] - %.1fkg - %.1fm - %d%% - %s - %d gen]- %s\n",
           pokemon->id, pokemon->name, pokemon->description, pokemon->types[0], pokemon->types[1],
           pokemon->abilities[0], pokemon->abilities[1], pokemon->abilities[2], pokemon->abilities[3], pokemon->abilities[4],
           pokemon->weight, pokemon->height, pokemon->captureRate, pokemon->isLegendary ? "true" : "false",
           pokemon->generation, dateStr);*/
}

PokemonList readPokemonCSV(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    PokemonList pokemonList;
    pokemonList.size = 0;
    pokemonList.pokemons = malloc(sizeof(Pokemon) * 1000); // Alocação inicial

    char line[1024];
    fgets(line, sizeof(line), file); // Pular o cabeçalho

    while (fgets(line, sizeof(line), file)) {
        //line[strcspn(line, "\r")] = '\0';
        Pokemon pokemon;
        char abilitiesStr[200];
        char typesStr[200];
        char dateStr[11];

         sscanf(line, "%d,%d,%[^,],%[^,],%[^,],%*[^,],%lf,%lf,%d,%d,%s",
               &pokemon.id, &pokemon.generation, pokemon.name, pokemon.description,
               typesStr, &pokemon.weight, &pokemon.height,
               &pokemon.captureRate, &pokemon.isLegendary, dateStr);

        // Extrair abilitiesStr manualmente
        char *start = strchr(line, '[');
        char *end = strchr(line, ']');
        if (start && end && end > start) {
            strncpy(abilitiesStr, start + 1, end - start - 1);
            abilitiesStr[end - start - 1] = '\0';
        } else {
            abilitiesStr[0] = '\0';
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

        // Parse date
        strftime(dateStr, sizeof(dateStr), "%dd/%mm/%YYYY", &pokemon.captureDate);

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

int main() {
    PokemonList pokemonList = readPokemonCSV("pokemon.csv");

    char entrada[10];
    while (scanf("%s", entrada) != EOF) {
        if (strcmp(entrada, "FIM") == 0) {
            break;
        }

        int id = atoi(entrada);
        Pokemon *pokemon = procuraPokemonPorId(&pokemonList, id);

        if (pokemon != NULL) {
            imprimirPokemon(pokemon);
        }
    }

    free(pokemonList.pokemons);
    return 0;
}
