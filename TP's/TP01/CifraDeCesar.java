import java.util.Scanner;

public class CifraDeCesar{

    public static boolean verificaFim(String frase){
        if(frase.equals("FIM")){
            return false;
        }
        return true;
    }

    public static String cifraFrase(String frase){
        StringBuilder fraseCifrada = new StringBuilder();

        for(int i = 0; i < frase.length(); i++){
            char c = frase.charAt(i);

            if(c >= 0 && c <= 127){
                int temp = c;
                temp += 3;
                c = (char)temp;
            }
            //adiciona o caracter cifrado a string
            fraseCifrada.append(c);
        } 

        return fraseCifrada.toString();
        
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        String frase;

        frase = sc.nextLine();

        while(verificaFim(frase)){
            String fraseCifrada = cifraFrase(frase);
            System.out.println(fraseCifrada);

            frase = sc.nextLine();
        }

        sc.close();

    }
}