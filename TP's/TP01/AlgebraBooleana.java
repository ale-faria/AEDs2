import java.util.Scanner;

public class AlgebraBooleana{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int quant;
        int num, num2, num3;
        String frase;

        quant = sc.nextInt();

        //altera a operacao dependendo da quantidade de variaveis que serao lidas
        while (quant != 0) {
            if (quant == 2) {
                num = sc.nextInt();
                num2 = sc.nextInt();
                frase = sc.nextLine();
                frase = modificaString(frase, num, num2, 0);
                System.out.println(algebra(frase));
            } else if (quant == 3) {
                num = sc.nextInt();
                num2 = sc.nextInt();
                num3 = sc.nextInt();
                frase = sc.nextLine();
                frase = modificaString(frase, num, num2, num3);
                System.out.println(algebra(frase));
            }
            quant = sc.nextInt();
        }
    }

    public static String modificaString(String frase, int num, int num2, int num3) {
        StringBuilder modificada = new StringBuilder();

        for (int i = 0; i < frase.length(); i++) {
            char c = frase.charAt(i);

            /*
               dependendo da inicial de cada comando, and, or, not, ira adicionar a inicial encontrada
               na String criada, logo apos ele ira verificar as variaveis A, B, C e substituindo pelo
               valor inteiros, 0 ou 1, respectivamente lidas na entrada de dados
            */
            if (c == 'a') {
                modificada.append(c);
                i += 2;
            } else if (c == 'o') {
                modificada.append(c);
                i += 1;
            } else if (c == 'n') {
                modificada.append(c);
                i += 2;
            } else if (c == 'A') {
                modificada.append(num);
            } else if (c == 'B') {
                modificada.append(num2);
            } else if (c == 'C') {
                modificada.append(num3);
            } else {
                modificada.append(c);
            }
        }
        return modificada.toString();
    }

    public static int algebra(String frase){
        //passa os dados existentes na String frase para uma cadeia de caracteres
        char[] fraseArray = frase.toCharArray();
        StringBuilder resultado = new StringBuilder();

        //varre a cadeia de caracteres procurando um ")" e chamando a funcao pilha para fazer a operacao binaria
        for (int i = 0; i < frase.length(); i++){
            if (fraseArray[i] == ')') {
                fraseArray = pilha(fraseArray, i);
            }
        }

        //varre a cadeia caracter por caracter e verifica se for 0 ou 1 o resultado final adiciona na String
        for (char c : fraseArray){
            if (c == '0' || c == '1'){
                resultado.append(c);
            }
        }

        //converte para uma String e retorna o primeiro caracter
        String finalResult = resultado.toString();
        return finalResult.isEmpty() ? 0 : Character.getNumericValue(finalResult.charAt(0));
    }

    public static char[] pilha(char[] frase, int i) {
        char[] resultado = new char[300];
        int aux = 0;

        //varre a frase de tras pra frente como uma pilha, desempilhando em na variavel resultado
        for (int j = i; j >= 0; j--){
            resultado[aux] = frase[j];
            frase[j] = '\u0000'; //atribui um caracter nulo no valor do topo da pilha que acabou de ser retirado

            /*
            se encontrar um "(", verifica o proximo caracter da pilha e compara
            se as letras encontradas correspondem as iniciais de and, or e not,
            chamando as funcoes para as operacoes binaria e retornando um valor inteiro, 1 ou 0
            */
            if (resultado[aux] == '(') {
                resultado[aux + 1] = frase[j - 1];
                int num;
                if (resultado[aux + 1] == 'a'){
                    num = And(resultado);
                } else if (resultado[aux + 1] == 'o'){
                    num = Or(resultado);
                } else if (resultado[aux + 1] == 'n'){
                    num = Not(resultado);
                } else{
                    continue;
                }
                frase[j - 1] = (char) (num + 48);
                return frase;
            }
            aux++;
        }
        return frase;
    }

    //se encontrar 0 retorna 1, pois o AND so retorna 1 se os numeros presentes forem somente 1
    public static int And(char[] resultado) {
        return new String(resultado).contains("0") ? 0 : 1;
    }

    //se encontrar 1 retorna 1, pois o OR so retorna 0 se os numeros presentes forem somente 0
    public static int Or(char[] resultado) {
        return new String(resultado).contains("1") ? 1 : 0;
    }

    //se encontrar 1 retorna 0, se nao encontrar continua retornando 1
    public static int Not(char[] resultado) {
        return new String(resultado).contains("1") ? 0 : 1;
    }
}
