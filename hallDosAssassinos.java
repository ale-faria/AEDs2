
import java.util.Scanner;

public class hallDosAssassinos {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String[] listaDeMortos = new String[20];
        int[] listaQuantidadeDeMortos = new int[20];
        String[] listaDeAssassinos = new String[20];

        int contaAssassino = 0;
        int contaMortos = 0;

        System.out.println("HALL OF MURDERERS");
        int x = 0;
        while (x < 6) {
            String assassinoNome = sc.next();
            String mortoNome = sc.next();

            listaDeMortos[contaMortos] = mortoNome;
            contaMortos++;

            // Procurar se o assassino já está na lista
            int index = -1;
            for (int i = 0; i < contaAssassino; i++) {
                if (listaDeAssassinos[i].equals(assassinoNome)) {
                    index = i;
                    break;
                }
            }


            if (index == -1) {
            // adiciona assassino na lista caso o assassino n exista
                listaDeAssassinos[contaAssassino] = assassinoNome;
                listaQuantidadeDeMortos[contaAssassino] = 1;
                contaAssassino++;
            } else {
                // se o assassino já existe, incrementa a lista de quantMortos na posicao certa do assassino
                listaQuantidadeDeMortos[index]++;
            }
            x++;
        } //fecha while

        String[] resultadoAssassinos = new String[contaAssassino];
        int[] resultadoAssassinatos = new int[contaAssassino];
        int resultadoCount = 0;

        for (int i = 0; i < contaAssassino; i++) {
            boolean encontrado = true;
            for (int j = 0; j < contaMortos; j++) {
                if (listaDeAssassinos[i].equals(listaDeMortos[j])) {
                    encontrado = false;
                    break;
                }
            }
            if (encontrado) {
                resultadoAssassinos[resultadoCount] = listaDeAssassinos[i];
                resultadoAssassinatos[resultadoCount] = listaQuantidadeDeMortos[i];
                resultadoCount++;
            }

        }
        // Imprimir o resultado
        System.out.println("HALL OF MURDERERS");
        for (int i = 0; i < resultadoCount; i++) {
            System.out.println(resultadoAssassinos[i] + " " + resultadoAssassinatos[i]);
        }

    }

}
