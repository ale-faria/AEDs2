import java.util.Scanner;

public class CifraDeCesarRecursivo{

    public static boolean verificaFim(String frase){
        return !frase.equals("FIM");
    }

    public static String cifraFrase(String frase, int tamanho, int indice){
    
       if(indice == tamanho){
        return "";
       }

        char c = frase.charAt(indice);
        if(c >= 0 && c <= 127){
            int temp = c;
            temp += 3;
            c = (char)temp;
        }

        return c + cifraFrase(frase, tamanho, indice+1);
    }  

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        String frase;
        frase = sc.nextLine();

        while(verificaFim(frase)){
            String fraseCifrada = cifraFrase(frase, frase.length(), 0);
            System.out.println(fraseCifrada);

            frase = sc.nextLine();
        }

        sc.close();
    }
}