import java.util.Random;
import java.util.Scanner;

public class AlteracaoAleatoria{

    public static boolean verificaFim(String frase){
        return !frase.equals("FIM");
    }

    public static String alteraString(String frase, char caracter1, char caracter2){
        StringBuilder resposta = new StringBuilder();

        for(int i = 0; i < frase.length(); i++){
            char c = frase.charAt(i);
            if(c == caracter1){
                resposta.append(caracter2);
            } else {
                resposta.append(c);
            }
        }

        return resposta.toString();
    }
    

    public static void main(String[] args) {
        Random gerador = new Random();
        gerador.setSeed(4);
        char caracter1 = (char)('a' + (Math.abs(gerador.nextInt()) % 26 ));
        char caracter2 = (char)('a' + (Math.abs(gerador.nextInt()) % 26 ));
        //System.out.println("01 = " + caracter1 +  " 02= " + caracter2);

        Scanner sc = new Scanner(System.in);

        String frase;
        frase = sc.nextLine();

        while(verificaFim(frase)){
            String resposta = alteraString(frase, caracter1, caracter2);
            System.out.println(resposta);
            
            caracter1 = (char)('a' + (Math.abs(gerador.nextInt()) % 26 ));
            caracter2 = (char)('a' + (Math.abs(gerador.nextInt()) % 26 ));
            //System.out.println("01 = " + caracter1 +  " 02= " + caracter2);
            frase = sc.nextLine();
        }
        sc.close();
    }
    
}