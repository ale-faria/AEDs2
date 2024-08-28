import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Scanner;

public class Arquivo{

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String fileName = "valores.txt";

        try {
            // Criar um arquivo de texto e abrir para escrita
            RandomAccessFile file = new RandomAccessFile(fileName, "rw");

            // Ler o número inteiro n
            int n = scanner.nextInt();

            // Ler n valores reais e escrevê-los no arquivo
            for (int i = 0; i < n; i++) {
                double valor = scanner.nextDouble();
                file.writeDouble(valor);
            }

            file.close();

            file = new RandomAccessFile(fileName, "r");

            // Ler os valores de trás para frente
            for (int i = n - 1; i >= 0; i--) {
                // Mover o ponteiro de arquivo para a posição do i-ésimo valor
                file.seek(i * 8); // Cada double ocupa 8 bytes
                double valor = file.readDouble();
                System.out.println(valor);
            }

            file.close();

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            scanner.close();
            // Apagar o arquivo após o uso (opcional)
            File fileToDelete = new File(fileName);
            if (fileToDelete.exists()) {
                fileToDelete.delete();
            }
        }
    }
}
