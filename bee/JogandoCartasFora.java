
import java.util.ArrayList;
import java.util.Scanner;

// remove do topo
// adiciona o novo topo na base e depois remove ele do topo
public class JogandoCartasFora {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int entrada;
        entrada = sc.nextInt();

        while (entrada != 0) {
            ArrayList<Integer> pilha = new ArrayList<>();
            ArrayList<Integer> descartados = new ArrayList<>();

            // criando a pilha de cartas inicial 
            for (int i = 1; i <= entrada; i++) {
                pilha.add(i);
            }

            while (pilha.size() > 1) {
                descartados.add(pilha.remove(0)); // remove topo

                pilha.add(pilha.remove(0)); // adiciona o novo topo a base da pilha, ao msm tempo que remove este topo
            }

            // printando elementos descartados
            System.out.print("Discarded cards: ");
            for (int i = 0; i < descartados.size(); i++) {
                System.out.print(descartados.get(i) + ", ");
            }

            // printando oque sobrou na pilha final
            System.out.println();
            System.out.println("Remaining card: " + pilha.get(0));

            entrada = sc.nextInt();
        }
    }
}
