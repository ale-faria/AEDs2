import java.util.Scanner;

public class AlgebraBooleanaRecursivo{
    public static void main(String[] args) {
        Scanner ler = new Scanner(System.in);
        int variaveis, A = 0, B = 0, C = 0;
        char resultado;
        String linha;

        variaveis = ler.nextInt();

        while (variaveis != 0) {
            if (variaveis == 1) {
                A = ler.nextInt();
            } else if (variaveis == 2) {
                A = ler.nextInt();
                B = ler.nextInt();
            } else {
                A = ler.nextInt();
                B = ler.nextInt();
                C = ler.nextInt();
            }

            linha = ler.next();  // Use next() em vez de nextLine() para capturar a linha corretamente
            resultado = avaliarExpressao(A, B, C, linha, 0)[0];
            System.out.println(resultado);
            variaveis = ler.nextInt();
        }
    }

    static char[] avaliarExpressao(int A, int B, int C, String linha, int index) {
        if (index >= linha.length()) return new char[]{'0', (char) index};

        char atual = linha.charAt(index);

        if (atual == 'A') {
            return new char[]{(char) (A + '0'), (char) (index + 1)};
        } else if (atual == 'B') {
            return new char[]{(char) (B + '0'), (char) (index + 1)};
        } else if (atual == 'C') {
            return new char[]{(char) (C + '0'), (char) (index + 1)};
        } else if (atual == 'n') {
            char[] resultado = avaliarExpressao(A, B, C, linha, index + 3);
            return new char[]{trataNot(resultado[0]), resultado[1]};
        } else if (atual == 'a') {
            char[] esq = avaliarExpressao(A, B, C, linha, index + 3);
            char[] dir = avaliarExpressao(A, B, C, linha, esq[1]);
            return new char[]{trataAnd(esq[0], dir[0]), dir[1]};
        } else if (atual == 'o') {
            char[] esq = avaliarExpressao(A, B, C, linha, index + 2);
            char[] dir = avaliarExpressao(A, B, C, linha, esq[1]);
            return new char[]{trataOr(esq[0], dir[0]), dir[1]};
        } else if (atual == '(') {
            return avaliarExpressao(A, B, C, linha, index + 1);
        } else if (atual == ')') {
            return new char[]{linha.charAt(index - 1), (char) (index + 1)};
        }

        return new char[]{'0', (char) index};
    }

    static char trataAnd(char a, char b) {
        return (a == '1' && b == '1') ? '1' : '0';
    }

    static char trataOr(char a, char b) {
        return (a == '1' || b == '1') ? '1' : '0';
    }

    static char trataNot(char a) {
        return (a == '1') ? '0' : '1';
    }
}
