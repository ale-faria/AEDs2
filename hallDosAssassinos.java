
import java.util.List;
import java.util.Scanner;

public class hallDosAssassinos {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String assassino, morto;

        Assassinos [] listaDeAssassinos = new Assassinos();
        Mortos [] listaDeMorridos = new Mortos();


        System.out.println("HALL OF MURDERERS");

        while (sc.hasNext()) {
            assassino = sc.next();
            morto = sc.next();

            listaDeAssassinos.setQuantMortes();

        }

    }

    sc.close;

}

class Assassinos {

    
    public int quantMortes;

    public Assassinos() {
        this.quantMortes = 0;
    }

    public int getQuantMortes() {
        return quantMortes;
    }

    public void setQuantMortes() {
        this.quantMortes = this.quantMortes + 1;
    }

}

class Mortos {

    public List<String> mortos;
    public int quantMorridos;

    public Mortos() {
        this.quantMorridos = 0;
    }

    public void setMorto(String nome) {
        this.mortos.add(nome);
        quantMorridos++;
    }
}
