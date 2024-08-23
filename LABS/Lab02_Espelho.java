import java.util.Scanner;

public class Lab02_Espelho{
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        //hasNext - verificar se há algum elemento restante na lista
        while(sc.hasNext()){
            
            int inicio = sc.nextInt();
            int fim = sc.nextInt();

            StringBuilder crescente = new StringBuilder();
            for(int i = inicio; i <= fim; i++){
                crescente.append(i);
            }

            StringBuilder espelho = new StringBuilder(crescente).reverse();

            String resultado = crescente.toString() + espelho.toString();

            System.out.println(resultado);
        }

        sc.close();
    }
}