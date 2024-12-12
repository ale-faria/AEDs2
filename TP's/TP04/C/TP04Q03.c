#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


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

/*
--------------------------------------
Arvore AVL inicio
--------------------------------------
*/
typedef struct No{
    Pokemon elemento;
    struct No* esq;
    struct No* dir;
    int nivel;
} No;

// Funcao para criar um novo no
No* novoNo(Pokemon elemento) {
    No* novo = (No*)malloc(sizeof(No));
    novo->elemento = elemento;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->nivel = 1;
    return novo;
}

// Funcao para obter o nivel de um no
int getNivel(No* no) {
    return (no == NULL) ? 0 : no->nivel;
}

// Funcao para atualizar o nivel de um no
void setNivel(No* no) {
    if (no != NULL) {
        no->nivel = 1 + (getNivel(no->esq) > getNivel(no->dir) ? getNivel(no->esq) : getNivel(no->dir));
    }
}

// Rotacao para a direita
No* rotacionarDir(No* no) {
    No* noEsq = no->esq;
    No* noEsqDir = noEsq->dir;

    noEsq->dir = no;
    no->esq = noEsqDir;

    setNivel(no);
    setNivel(noEsq);

    return noEsq;
}

// Rotacao para a esquerda
No* rotacionarEsq(No* no) {
    No* noDir = no->dir;
    No* noDirEsq = noDir->esq;

    noDir->esq = no;
    no->dir = noDirEsq;

    setNivel(no);
    setNivel(noDir);

    return noDir;
}

// Funcao para balancear um no
No* balancear(No* no) {
    if (no != NULL) {
        setNivel(no);
        int fator = getNivel(no->dir) - getNivel(no->esq);

        // Balanceamento
        if (fator == 2) {
            if (getNivel(no->dir->dir) < getNivel(no->dir->esq)) {
                no->dir = rotacionarDir(no->dir);
            }
            no = rotacionarEsq(no);
        } else if (fator == -2) {
            if (getNivel(no->esq->dir) > getNivel(no->esq->esq)) {
                no->esq = rotacionarEsq(no->esq);
            }
            no = rotacionarDir(no);
        }
    }
    return no;
}

No* inserir(No* no, Pokemon elemento){
    if (no == NULL){
        return novoNo(elemento);
    }else if (strcmp(elemento.name, no->elemento.name) < 0){
        no->esq = inserir(no->esq, elemento);
    }else if (strcmp(elemento.name, no->elemento.name) > 0){
        no->dir = inserir(no->dir, elemento);
    }else{
        printf("Erro ao inserir: elemento ja existe!\n");
    }
    return balancear(no);
}


// Funcao para pesquisar um elemento na arvore AVL
No* pesquisar(No* no, char* name) {
    if (no == NULL || strcmp(no->elemento.name, name) == 0) {
        return no;
    }
    if (strcmp(name, no->elemento.name) < 0) {
        printf("esq ");
        return pesquisar(no->esq, name);
    } else {
        printf("dir ");
        return pesquisar(no->dir, name);
    }
}

/*
--------------------------------------
Arvore AVL fim
--------------------------------------
*/

int main(void) {
    char *filePath;
    //filePath = "pokemon.csv";
    filePath = "/tmp/pokemon.csv"; // Caminho no Verde

    PokemonList pokemonList = readPokemonCSV(filePath); // Leitura do arquivo csv

    No* raiz = NULL;

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
                raiz = inserir(raiz, *pokemon);
        }
    }

    while(1){
        scanf("%s", entrada);

        if (strcmp(entrada, "FIM") == 0) {
            break;
        }

        printf("%s \nraiz ", entrada);
        No* resultado = pesquisar(raiz, entrada);

        if(resultado != NULL){
            printf("SIM");
        } else{
            printf("NAO");
        }

        printf("\n");
    }

    return 0;
}
