
import java.util.Scanner;

public class IsRecursivo{

    public static boolean verificaFim(String frase){
        return !frase.equals("FIM");
    }

    public static boolean isVogal(String frase, int indice){
        if(indice == frase.length()){
            return true;
        }

        char c = frase.charAt(indice);
        if(!(c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == ' ')){
                return false;
            }

        return isVogal(frase, indice+1);
    }

    public static boolean isConsoante(String frase, int indice){
        if(indice == frase.length()){
            return true;
        }

            int cASCII = frase.charAt(indice);
            char c = frase.charAt(indice);

            if(!((cASCII >= 65 && cASCII <= 90) || (cASCII >= 97 && cASCII <= 122) || c == ' ') || (c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' || c == 'u' || c == 'U')){
                return false;
            }

        return isConsoante(frase, indice+1);
    }

    public static boolean isInteiro(String frase, int indice){
        if(indice == frase.length()){
            return true;
        }

            int cASCII = frase.charAt(indice);

            if(!(cASCII >= 48 && cASCII <= 57)){
                return false;
            }

        return isInteiro(frase, indice+1);
    }

    public static boolean isReal(String frase, int indice, int cont){
        if(indice == frase.length()){
            return cont == 1;
        }

        char c = frase.charAt(indice);
        int cASCII = frase.charAt(indice);

        if(c == '.' || c == ','){
            cont++;
        }

        if(!(cASCII >= 48 && cASCII <= 57) && c != '.' && c != ','){
            return false;
        }

        return isReal(frase, indice+1, cont);
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        String frase;
        frase = sc.nextLine();

        while(verificaFim(frase)){

            String vogal = isVogal(frase, 0) ? "SIM" : "NAO";
            String consoante = isConsoante(frase, 0) ? "SIM" : "NAO";
            String inteiro = isInteiro(frase, 0) ? "SIM" : "NAO";
            String real = isReal(frase, 0, 0) ? "SIM" : "NAO";

            System.out.println(vogal + " " + consoante + " " + inteiro + " " + real);

            frase = sc.nextLine();
        }

        sc.close();
    }
}