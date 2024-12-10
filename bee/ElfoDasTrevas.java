
import java.util.ArrayList;
import java.util.Scanner;

class Rena {

    public String name;
    public int peso;
    public int idade;
    public double altura;

    public Rena(String name, int peso, int idade, double altura) {
        this.name = name;
        this.peso = peso;
        this.idade = idade;
        this.altura = altura;
    }

    public String getName() {
        return name;
    }

}

public class ElfoDasTrevas {

    public static void ordena(ArrayList<Rena> renas, int quant) {
          // Implementação do Bubble Sort
        for (int i = 0; i < quant - 1; i++) {
            for (int j = 0; j < quant - i - 1; j++) {
                // Critério 1: Peso (decrescente)
                if (renas.get(j).peso < renas.get(j + 1).peso ||
                    // Critério 2: Idade (crescente, em caso de empate no peso)
                    (renas.get(j).peso == renas.get(j + 1).peso && renas.get(j).idade > renas.get(j + 1).idade)) {

                    // Trocar renas de posição
                    Rena temp = renas.get(j);
                    renas.set(j, renas.get(j + 1));
                    renas.set(j + 1, temp);
                }
            }
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int cont = 1;

        int casos;
        casos = sc.nextInt();

        int totalRenas, renasPuxarTreno;

        while (sc.hasNext()) {
            totalRenas = sc.nextInt();
            renasPuxarTreno = sc.nextInt();

            ArrayList<Rena> renas = new ArrayList<>();

            String name;
            int peso, idade;
            double altura;

            for (int i = 0; i < totalRenas; i++) {
                name = sc.next();
                peso = sc.nextInt();
                idade = sc.nextInt();
                altura = Double.parseDouble(sc.next().replace(",", "."));

                renas.add(new Rena(name, peso, idade, altura));
            }

            ordena(renas, totalRenas);

            System.out.println("CENARIO {" + cont + "}");
            for(int i = 1; i <= renasPuxarTreno; i++){
                System.out.println(i + " - " + renas.get(i-1).name);
            }

        }

    }
}
