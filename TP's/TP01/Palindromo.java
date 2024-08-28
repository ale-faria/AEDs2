import java.util.Scanner;

public class Palindromo {
    
    public static boolean verificaFim(String frase){
        if(frase.equals("FIM")){
            return false;
        }
        return true;
    }
    
    public static boolean ehPalindromo(String frase){
        int tamanho = frase.length();
        for(int i = 0; i < tamanho/2; i++){
            if(frase.charAt(i) != frase.charAt(tamanho - 1 - i)){
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        Scanner leitura = new Scanner(System.in);
        
        String frase;
    
        frase = leitura.nextLine();
        
        while(verificaFim(frase)){
            if(ehPalindromo(frase)){
                System.out.println("SIM");
            } else {
                System.out.println("NAO");
            }
            frase = leitura.nextLine();
        }


    }
}