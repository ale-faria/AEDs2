import java.util.Scanner;

public class Is{

    public static boolean verificaFim(String frase){
        return !frase.equals("FIM");
    }

    public static boolean isVogal(String frase){
        boolean resultado = true;
        for(int i = 0; i < frase.length(); i++){
            char c = frase.charAt(i);
            if(!(c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == ' ')){
                resultado = false;
            }
        }

        return resultado;
    }
    
    public static boolean isConsoante(String frase){
        boolean resultado = true;
        for(int i = 0; i < frase.length(); i++){

            int cASCII = frase.charAt(i);
            char c = frase.charAt(i);

            if(!((cASCII >= 65 && cASCII <= 90) || (cASCII >= 97 && cASCII <= 122) || c == ' ') || (c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' || c == 'u' || c == 'U')){
                resultado = false;
            }
        }

        return resultado;
    }

    public static boolean isInteiro(String frase){
        boolean resultado = true;

        for(int i = 0; i < frase.length(); i++){
            int cASCII = frase.charAt(i);

            if(!(cASCII >= 48 && cASCII <= 57)){
                resultado = false;
            }
        }
        
        return resultado;
    }

    public static boolean isReal(String frase){
        boolean resultado = true;
        int cont = 0;

        for(int i = 0; i < frase.length(); i++){
            char c = frase.charAt(i);
            int cASCII = frase.charAt(i);

            if(c == '.' || c == ','){
                cont++;
            }

            if(!(cASCII >= 48 && cASCII <= 57) && c != '.' && c != ','){
                resultado = false;
            }
        }

        if((cont > 1 || cont == 0) || resultado == false){
            return false;
        } else {
            return true;
        }
    }

    public static void main(String[] args) {
        Scanner sc =  new Scanner(System.in);

        String frase;
        frase = sc.nextLine();

        while(verificaFim(frase)){
            String vogal = "NAO", consoante = "NAO", inteiro = "NAO", real = "NAO";

            if(isVogal(frase)){
                vogal = "SIM";
            }
            if(isConsoante(frase)){
                consoante = "SIM";
            }
            if(isInteiro(frase)){
                inteiro = "SIM";
            }
            if(isReal(frase)){
                real = "SIM";
            }

            System.out.println(vogal + " " + consoante + " " + inteiro + " " + real);

            frase = sc.nextLine();
        }

        sc.close();
    }
}