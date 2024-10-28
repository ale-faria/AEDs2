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

void swap(Pokemon poke[], int i, int j) {
        Pokemon temp = poke[i];
        poke[i] = poke[j];
        poke[j] = temp;
}

// Função de construção do heap (heapify) considerando height e desempate por name
void construir(Pokemon poke[], int n, int i) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    // Comparação da altura do filho esquerdo
    if (esq < n && (poke[esq].height > poke[maior].height ||
        (poke[esq].height == poke[maior].height && strcmp(poke[esq].name, poke[maior].name) > 0))) {
        maior = esq;
    }

    // Comparação da altura do filho direito
    if (dir < n && (poke[dir].height > poke[maior].height ||
        (poke[dir].height == poke[maior].height && strcmp(poke[dir].name, poke[maior].name) > 0))) {
        maior = dir;
    }

    // Se o maior não é o nó raiz, trocar e continuar o heapify
    if (maior != i) {
        swap(poke, i, maior);
        construir(poke, n, maior);
    }
}

// Função heapsort parcial
void heapsort(Pokemon poke[], int n, int k) {
    // Construção do heap com os k primeiros elementos
    for (int i = k / 2 - 1; i >= 0; i--) {
        construir(poke, k, i);
    }

    // Processamento dos demais elementos
    for (int i = k; i < n; i++) {
        if (poke[i].height < poke[0].height ||
            (poke[i].height == poke[0].height && strcmp(poke[i].name, poke[0].name) < 0)) {
            swap(poke, 0, i);
            construir(poke, k, 0);
        }
    }

    // Ordenação final do heap parcial
    for (int i = k - 1; i >= 0; i--) {
        swap(poke, 0, i);
        construir(poke, i, 0);
    }
}

int main(void) {
    char *filePath;
    //filePath = "pokemon.csv";
    filePath = "/tmp/pokemon.csv"; // Caminho no Verde

    PokemonList pokemonList = readPokemonCSV(filePath);
    Pokemon poke[100];

    int position = 0;
    char entrada[30];

    while (1) {
        scanf("%s", entrada);

        if (strcmp(entrada, "FIM") == 0) {
            break;
        }

        int id = atoi(entrada);
        Pokemon *pokemon = procuraPokemonPorId(&pokemonList, id);
        poke[position] = *pokemon;
        position++;
    }

    heapsort(poke, position, 10);

    int cont = 0;
    while (cont < 10) {
        imprimirPokemon(&poke[cont]);
        cont++;
    }

    free(pokemonList.pokemons);

    return 0;
}


