import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.RandomAccessFile;

public class Arquivo {
    public static void main(String[] args) {
        String fileName = "valores.txt";
        int n;
        double valor;

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            // Lendo o número inteiro
            // System.out.print("Digite a quantidade de valores: ");
            n = Integer.parseInt(reader.readLine());

            try (DataOutputStream dos = new DataOutputStream(new FileOutputStream(fileName))) {
                // Lendo valores e escrevendo no arquivo
                for (int i = 0; i < n; i++) {
                    valor = Double.parseDouble(reader.readLine());
                    dos.writeDouble(valor);
                }
            }

            try (RandomAccessFile raf = new RandomAccessFile(fileName, "r")) {
                // Lendo valores do arquivo de trás para frente
                for (int i = n - 1; i >= 0; i--) {
                    // Mover o ponteiro de arquivo para a posição do i-ésimo valor
                    raf.seek(i * Double.BYTES);
                    valor = raf.readDouble();
             
                    if(valor == (int)valor){
                        System.out.println((int)valor);
                    } else {
                        System.out.println(valor);
                    }
                    
                }
            }
        } catch (IOException e) {
            System.err.println("Erro ao abrir o arquivo: " + e.getMessage());
        }
    }
}
