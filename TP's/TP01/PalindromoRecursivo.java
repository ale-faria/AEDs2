import java.util.Scanner;

public class PalindromoRecursivo{

    public static boolean verificaFim(String frase){
        return !frase.equals("FIM");
    }

    public static boolean ehPalindromo(String frase, int inicio, int fim){
        if(inicio >= fim){
            return true;
        }
            
        if(frase.charAt(inicio) != frase.charAt(fim)){
            return false;
        } else {
            return ehPalindromo(frase, inicio+1, fim-1);
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String frase;
        frase = sc.nextLine();

        while(verificaFim(frase)){
            
            if(ehPalindromo(frase, 0, frase.length()-1)){
                System.out.println("SIM");
            } else{
                System.out.println("NAO");
            }

            frase = sc.nextLine();
        }

        sc.close();
    }
}