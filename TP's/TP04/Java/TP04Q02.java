
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

/*class No {

    public Pokemon elemento;
    public No esq, dir;

    public No(Pokemon elemento) {
        this.elemento = elemento;
        this.esq = this.dir = null;
    }

    public No(Pokemon elemento, No esq, No dir) {
        this.elemento = elemento;
        this.esq = esq;
        this.dir = dir;
    }
}*/

class No {

    public Pokemon elemento;
    public No esq;
    public No dir;
    public No2 outro;

    public No(Pokemon elemento) {
        this.elemento = elemento;
        this.esq = this.dir = null;
        this.outro = null;
    }

    public No(Pokemon elemento, No esq, No dir) {
        this.elemento = elemento;
        this.esq = esq;
        this.dir = dir;
        this.outro = null;
    }
}

class No2{
    public Pokemon elemento;
    public No2 esq;
    public No2 dir;

    public No2(Pokemon elemento){
        this.elemento = elemento;
        this.esq = this.dir = null;
    }

    public No2(Pokemon elemento, No2 esq, No2 dir){
        this.elemento = elemento;
        this.esq = esq;
        this.dir = dir;
    }

}

class ArvoreArvore{
    private No raiz;

    public ArvoreArvore(){
        raiz = null;
    }

    public void inserir(int mod) throws Exception {
        raiz = inserir(mod, raiz);
    }

    private No inserir(int mod, No i) throws Exception {
        if (i == null) {
            i = new No(pokemon); // Insere o Pokemon

        } else if (pokemon.getName().compareTo(i.elemento.getName()) < 0) {
            i.esq = inserir(pokemon, i.esq); // Insere na subarvore esquerda

        } else if (pokemon.getName().compareTo(i.elemento.getName()) > 0) {
            i.dir = inserir(pokemon, i.dir); // Insere na subarvore direita

        } else {
            throw new Exception("Erro ao inserir!"); // Pokemon ja existe na arvore
        }

        return i;
    }
}

class ArvoreBinaria {

    private No raiz;

    public ArvoreBinaria() {
        raiz = null;
    }

    // Metodo para pesquisar um Pokemon na arvore
    // Chave de pesquisa name
    public boolean pesquisar(String name) {
        return pesquisar(name, raiz);
    }

    private boolean pesquisar(String name, No i) {
        boolean resp;

        if (i == null) {
            resp = false; // Pokemon nao encontrado

        } else if (name.equals(i.elemento.getName())) {
            resp = true; // Pokemon encontrado

        } else if (name.compareTo(i.elemento.getName()) < 0) {
            System.out.print("esq ");
            resp = pesquisar(name, i.esq); // Pesquisar na subarvore esquerda

        } else {
            System.out.print("dir ");
            resp = pesquisar(name, i.dir); // Pesquisar na subarvore direita
        }
        return resp;
    }

    // Metodo para mostrar os elementos da arvore em pre-ordem
    public void caminharPre() {
        caminharPre(raiz);
    }

    private void caminharPre(No i) {
        if (i != null) {
            //System.out.print(i.elemento.getName() + " "); // Conteudo do no
            caminharPre(i.esq); // Elementos da esquerda
            caminharPre(i.dir); // Elementos da direita
        }
    }

    // Metodo para inserir um Pokemon na arvore
    public void inserir(Pokemon pokemon) throws Exception {
        raiz = inserir(pokemon, raiz);
    }

    private No inserir(Pokemon pokemon, No i) throws Exception {
        if (i == null) {
            i = new No(pokemon); // Insere o Pokemon

        } else if (pokemon.getName().compareTo(i.elemento.getName()) < 0) {
            i.esq = inserir(pokemon, i.esq); // Insere na subarvore esquerda

        } else if (pokemon.getName().compareTo(i.elemento.getName()) > 0) {
            i.dir = inserir(pokemon, i.dir); // Insere na subarvore direita

        } else {
            throw new Exception("Erro ao inserir!"); // Pokemon ja existe na arvore
        }

        return i;
    }

}

public class TP04Q02 {

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

    public static void main(String[] args) throws Exception {
        PokemonCSVReader reader = new PokemonCSVReader();
        //String filePath = "pokemon.csv"; // Caminho para o arquivo CSV
        String filePath = "/tmp/pokemon.csv"; // No Verde 

        List<Pokemon> pokemonList = reader.readPokemonCSV(filePath);
        ArvoreBinaria arvore = new ArvoreBinaria();

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
                arvore.inserir(pokemon);
            }
        }

        while (sc.hasNext()) {
            entrada = sc.next();

            if (entrada.equals("FIM")) {
                break;
            }

            System.out.println(entrada);
            System.out.print("=>raiz ");
            boolean pesquisa;
            pesquisa = arvore.pesquisar(entrada);

            if (pesquisa) {
                System.out.println("SIM");
            } else {
                System.out.println("NAO");
            }
        }

        sc.close();
    }
}
