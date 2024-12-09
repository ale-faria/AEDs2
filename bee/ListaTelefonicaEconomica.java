import java.util.Scanner;

public class ListaTelefonicaEconomica {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNext()) {
            int n = sc.nextInt(); // Número de telefones na lista
            sc.nextLine(); // Consumir a quebra de linha após o número

            String[] telefones = new String[n];
            for (int i = 0; i < n; i++) {
                telefones[i] = sc.nextLine();
            }

            // Calcular o número de caracteres economizados
            int economizados = 0;
            for (int i = 1; i < n; i++) {
                economizados += calcularPrefixoComum(telefones[i - 1], telefones[i]);
            }

            System.out.println(economizados);
        }

        sc.close();
    }

    /**
     * Calcula o número de caracteres iniciais iguais entre duas strings consecutivas.
     * 
     * @param s1 Primeira string
     * @param s2 Segunda string
     * @return Número de caracteres iniciais iguais
     */
    private static int calcularPrefixoComum(String s1, String s2) {
        int t1, t2;
        int comprimento;
        t1 = s1.length();
        t2 = s2.length();
        if(t1 < t2){
            comprimento = t1;
        } else {
            comprimento = 12;
        }
        //int comprimento = Math.min(s1.length(), s2.length());
        int comum = 0;
        for (int i = 0; i < comprimento; i++) {
            if (s1.charAt(i) == s2.charAt(i)) {
                comum++;
            } else {
                break; // Parar ao encontrar o primeiro caractere diferente
            }
        }
        return comum;
    }
}
