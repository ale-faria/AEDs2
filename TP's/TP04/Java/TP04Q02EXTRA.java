
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Scanner;

class Pokemon {

    // Atributos privados
    private int id;
    private int generation;
    private String name;
    private String description;
    private List<String> types;
    private List<String> abilities;
    private double weight;
    private double height;
    private int captureRate;
    private boolean isLegendary;
    private Date captureDate;

    // Construtor padrao
    public Pokemon() {
    }

    // Construtor com parametros 
    public Pokemon(int id, int generation, String name, String description, List<String> types, List<String> abilities, double weight, double height, int captureRate, boolean isLegendary, Date captureDate) {
        this.id = id;
        this.generation = generation;
        this.name = name;
        this.description = description;
        this.types = types;
        this.abilities = abilities;
        this.weight = weight;
        this.height = height;
        this.captureRate = captureRate;
        this.isLegendary = isLegendary;
        this.captureDate = captureDate;
    }

    // getters e setters
    public int getId() {
        return id;
    }

    public int getGeneration() {
        return generation;
    }

    public String getName() {
        return name;
    }

    public String getDescription() {
        return description;
    }

    public List<String> getTypes() {
        return types;
    }

    public List<String> getAbilities() {
        return abilities;
    }

    public double getWeight() {
        return weight;
    }

    public double getHeight() {
        return height;
    }

    public int getCaptureRate() {
        return captureRate;
    }

    public boolean isIsLegendary() {
        return isLegendary;
    }

    public Date getCaptureDate() {
        return captureDate;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setGeneration(int generation) {
        this.generation = generation;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setTypes(List<String> types) {
        this.types = types;
    }

    public void setAbilities(List<String> abilities) {
        this.abilities = abilities;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    public void setCaptureRate(int captureRate) {
        this.captureRate = captureRate;
    }

    public void setIsLegendary(boolean isLegendary) {
        this.isLegendary = isLegendary;
    }

    public void setCaptureDate(Date captureDate) {
        this.captureDate = captureDate;
    }

    // Metodo para imprimir os detalhes do Pokemon
    public void imprimir() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");

        String typesFormat = types.toString().replace("[", "['").replace("]", "']").replace(", ", "', '");
        String abilitiesFormat = abilities.toString().replace("[", "['").replace("]", "']").replace(", ", "', '");

        System.out.println("[#" + id + " -> " + name + ": " + description + " - "
                + typesFormat + " - " + abilitiesFormat + " - " + weight + "kg - "
                + height + "m - " + captureRate + "%" + " - "
                + (isLegendary ? "true" : "false")
                + " - " + generation + " gen" + "] - " + dateFormat.format(captureDate));
    }

    public Pokemon clone(Pokemon pokemon) {
        return pokemon;
    }
}

class PokemonCSVReader {

    // Metodo para ler o CSV e retornar uma lista de Pokemon
    public List<Pokemon> readPokemonCSV(String filePath) {
        List<Pokemon> pokemonList = new ArrayList<>();
        // Define o formato da data
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");

        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line;
            br.readLine(); // Pular o cabecalho

            while ((line = br.readLine()) != null) {
                String[] values = parseLine(line);

                int id = Integer.parseInt(values[0]);
                int generation = Integer.parseInt(values[1]);
                String name = values[2];
                String description = values[3];
                List<String> types = new ArrayList<>();
                if (!values[4].isEmpty()) {
                    types.add(values[4]);
                }
                if (!values[5].isEmpty()) {
                    types.add(values[5]);
                }
                List<String> abilities = parseAbilities(values[6]);
                double weight = values[7].isEmpty() ? 0 : Double.parseDouble(values[7]);
                double height = values[8].isEmpty() ? 0 : Double.parseDouble(values[8]);
                int captureRate = Integer.parseInt(values[9]);
                boolean isLegendary = Integer.parseInt(values[10]) == 1;
                Date captureDate = dateFormat.parse(values[11]);

                Pokemon pokemon = new Pokemon(id, generation, name, description, types, abilities, weight, height, captureRate, isLegendary, captureDate);
                pokemonList.add(pokemon);
            }
        } catch (IOException | ParseException | NumberFormatException e) {
            e.printStackTrace();
        }

        return pokemonList;
    }

    // Metodo para dividir uma linha do CSV em valores individuais
    private String[] parseLine(String line) {
        List<String> values = new ArrayList<>();
        StringBuilder current = new StringBuilder();
        boolean inQuotes = false;

        for (char ch : line.toCharArray()) {
            if (ch == '"') {
                inQuotes = !inQuotes;
            } else if (ch == ',' && !inQuotes) {
                values.add(current.toString().trim());
                current.setLength(0);
            } else {
                current.append(ch);
            }
        }
        values.add(current.toString().trim());

        return values.toArray(new String[0]);
    }

    // Metodo para converter a string de habilidades em uma lista de habilidades
    private List<String> parseAbilities(String abilitiesStr) {
        abilitiesStr = abilitiesStr.replace("[", "").replace("]", "").replace("'", "");
        String[] abilitiesArray = abilitiesStr.split(", ");
        List<String> abilities = new ArrayList<>();
        for (String ability : abilitiesArray) {
            abilities.add(ability);
        }
        return abilities;
    }
}

class NoFilho{
	Pokemon pokemon;
    NoFilho esq, dir;

    NoFilho(Pokemon p){
        this.pokemon = p;
        esq = dir = null;
    }

}

class No{
    int elemento;
    No esq, dir;
    NoFilho raizFilho;

    No(int x){
        this.elemento = x % 15;
        esq = dir = null;
        raizFilho = null;
    }
}


class ArvoreArvore {
    No raiz;

    public ArvoreArvore() {
        raiz = null;
        
    }

    public void inserir(int x) {
        raiz = inserir(raiz, x);
    }

    public void inserirPokemon(Pokemon pokemon) {
        int place = pokemon.getCaptureRate() % 15;
        inserirPokemon(raiz, pokemon, place);
    }

    public void caminharCentral() {
        caminharCentral(raiz);
    }

    public void pesquisa(String nome) {
        boolean flag;
        System.out.print( "raiz ");
        flag = pesquisa(raiz, nome);
        if (flag) {
            System.out.println(" NAO");
        } else {
            System.out.println(" SIM");
        }
    }

    public void mostra() {
        mostra(raiz);
    }

    private No inserir(No i, int x) {
        if (i == null) {
            i = new No(x);
        } else if (x > i.elemento) {
            i.dir = inserir(i.dir, x);
        } else if (x < i.elemento) {
            i.esq = inserir(i.esq, x);
        } else {
            System.out.println("Erro ao inserir");
        }

        return i;
    }

    private void inserirPokemon(No i, Pokemon pokemon, int place) {
        if (i == null) {
            System.out.println("ERRO ao inserir pokemon");
        } else if (place > i.elemento) {
            inserirPokemon(i.dir, pokemon, place);
        } else if (place < i.elemento) {
            inserirPokemon(i.esq, pokemon, place);
        } else {
            i.raizFilho = insercao(i.raizFilho, pokemon);
        }
    }

    private NoFilho insercao(NoFilho i, Pokemon pokemon) {
        if (i == null) {
            i = new NoFilho(pokemon);
        } else if (compare(pokemon, i.pokemon) > 0) {
            i.dir = insercao(i.dir, pokemon);
        } else if (compare(pokemon, i.pokemon) < 0) {
            i.esq = insercao(i.esq, pokemon);
        } else {
            System.out.println("Erro ao inserir");
        }

        return i;
    }

    private boolean pesquisa(No i, String nome) {
        boolean flag = true;
        if (i != null) {
            if (i.raizFilho != null) {
                flag = pesquisaNaSubArvore(i.raizFilho, nome);
            }

            if (flag) {
                System.out.print(" ESQ ");
                flag = pesquisa(i.esq, nome);
            }
            if (flag) {
                System.out.print(" DIR ");
                flag = pesquisa(i.dir, nome);
            }
        }

        return flag;
    }

    private boolean pesquisaNaSubArvore(NoFilho i, String nome) {
        boolean flag;
        if (i == null) {
            flag = true;
        } else if (compare(nome, i.pokemon) > 0) {
            System.out.print("dir ");
            flag = pesquisaNaSubArvore(i.dir, nome);
        } else if (compare(nome, i.pokemon) < 0) {
            System.out.print("esq ");
            flag = pesquisaNaSubArvore(i.esq, nome);
        } else {
            flag = false;
        }

        return flag;
    }

    private int compare(Pokemon a, Pokemon b) {
        return a.getName().compareTo(b.getName());
    }

    private int compare(String nome, Pokemon a) {
        return nome.compareTo(a.getName());
    }

    private void caminharCentral(No i) {
        if (i != null) {
            caminharCentral(i.esq);
            System.out.println(i.elemento);
            caminharCentral(i.dir);
        }
    }

    private void mostra(No i) {
        if (i != null) {
            mostra(i.esq);
            mostraPokemonsDoNo(i.raizFilho);
            mostra(i.dir);
        }
    }

    private void mostraPokemonsDoNo(NoFilho i) {
        if (i != null) {
            mostraPokemonsDoNo(i.esq);
            i.pokemon.toString();
            System.out.println();
            mostraPokemonsDoNo(i.dir);
        }
    }
}

public class TP04Q02EXTRA {

    public static Pokemon procuraPokemonPorId(List<Pokemon> pokemonList, int id) {
        int tamanho = pokemonList.size();
        Pokemon pokemon;
        for (int i = 0; i < tamanho; i++) {
            pokemon = pokemonList.get(i);
            if (pokemon.getId() == id) {
                return pokemon;
            }
        }
        return null;
    }

    public static Pokemon procuraPokemonPorNome(List<Pokemon> pokemonList, String name) {
        int tamanho = pokemonList.size();
        Pokemon pokemon;
        for (int i = 0; i < tamanho; i++) {
            pokemon = pokemonList.get(i);
            if (pokemon.getName().equals(name)) {
                return pokemon;
            }
        }
        return null;
    }

    public static void main(String[] args) throws Exception {
        PokemonCSVReader reader = new PokemonCSVReader();
        //String filePath = "pokemon.csv"; // Caminho para o arquivo CSV
        String filePath = "/tmp/pokemon.csv"; // No Verde 

        List<Pokemon> pokemonList = reader.readPokemonCSV(filePath);
        ArvoreArvore arvore = new ArvoreArvore();

        int[] ordemInsercao = {7, 3, 11, 1, 5, 9, 13, 0, 2, 4, 6, 8, 10, 12, 14};
        for (int i : ordemInsercao) {
            arvore.inserir(i);
        }

        Scanner sc = new Scanner(System.in);
        String entrada;

        while (sc.hasNext()) {
            entrada = sc.next();

            if (entrada.equals("FIM")) {
                break;
            }

            int id = Integer.parseInt(entrada);
            Pokemon pokemon = procuraPokemonPorId(pokemonList, id);

            if (pokemon != null) {
                arvore.inserirPokemon(pokemon);
            }
        }

        while (sc.hasNext()) {
            entrada = sc.next();

            if (entrada.equals("FIM")) {
                break;
            }

           System.out.print("=> " + entrada + "\n");
			arvore.pesquisa(entrada);

        }

        sc.close();
    }
}