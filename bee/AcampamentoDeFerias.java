
import java.util.ArrayList;
import java.util.Scanner;

class Crianca {

    String nome;
    int valor;

    Crianca(String nome, int valor) {
        this.nome = nome;
        this.valor = valor;
    }
}

public class AcampamentoDeFerias {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (true) {
            int n = sc.nextInt(); // Número de crianças no círculo
            if (n == 0) {
                break; // Fim da entrada
            }
            // Criar a lista de crianças
            ArrayList<Crianca> criancas = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                String nome = sc.next();
                int valor = sc.nextInt();
                criancas.add(new Crianca(nome, valor));
            }

            // Iniciar o processo de eliminação
            int index = 0; // Começamos da primeira criança
            while (criancas.size() > 1) {
                Crianca atual = criancas.get(index);
                int valorFicha = atual.valor;

                // Remover a criança atual
                criancas.remove(index);

                // Ajustar o índice para a próxima contagem
                if (valorFicha % 2 == 0) { // Sentido horário
                    index = (index + (valorFicha - 1)) % criancas.size();
                } else { // Sentido anti-horário
                    index = (index - valorFicha) % criancas.size();
                    if (index < 0) {
                        index += criancas.size(); // Ajustar índice negativo
                    }
                }
            }

            // Imprimir o vencedor
            System.out.println("Vencedor(a): " + criancas.get(0).nome);
        }

        sc.close();
    }
}
