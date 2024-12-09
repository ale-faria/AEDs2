
import java.util.Scanner;

public class Estiagem {

    public static void ordena(int[] consumo, int[] quantMorador, int total) {
        // Ordenando pelo consumo 
        for (int i = 0; i < total - 1; i++) {
            int menor = i;
            for (int j = i + 1; j < total; j++) {
                if (consumo[menor] > consumo[j]) {
                    menor = j;
                }

            }
            swap(consumo, menor, i);
            swap(quantMorador, menor, i);
        }
    }

    public static void swap(int[] consumo, int i, int j) {
        int temp = consumo[i];
        consumo[i] = consumo[j];
        consumo[j] = temp;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int quantImoveis;
        int entrada;
        int cont = 1;

        quantImoveis = sc.nextInt();

        while (quantImoveis != 0) {
            int somaMorador = 0, somaConsumo = 0;

            int[] quantMoradores = new int[quantImoveis];
            int[] consumo = new int[quantImoveis];

            // leitura das entradas de moradores e consumo
            for (int i = 0; i < quantImoveis; i++) {
                entrada = sc.nextInt(); //quant moradores
                somaMorador += entrada;
                quantMoradores[i] = entrada;

                entrada = sc.nextInt(); //consumo
                somaConsumo += entrada;
                consumo[i] = entrada;

                consumo[i] = consumo[i] / quantMoradores[i];
            }


            ordena(consumo, quantMoradores, quantImoveis);

            System.out.println("Cidade# " + cont + ":");
            for (int i = 0; i < quantImoveis; i++) {
                //int calcConsumoPorPessoa = consumo[i] / quantMoradores[i];
                System.out.print(quantMoradores[i] + "-" + consumo[i] + " ");
            }
            cont++;

            System.out.println();

            double consumoMedio = (double)somaConsumo / somaMorador;
            System.out.print("Consumo medio: ");
            System.out.printf("%.2f m3. \n", consumoMedio);

            System.out.println();

            quantImoveis = sc.nextInt();
        }

    }
}
