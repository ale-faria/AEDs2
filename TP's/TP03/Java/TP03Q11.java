
import java.util.Scanner;

class Celula {

    public int elemento;
    public Celula inf, sup, esq, dir;

    public Celula() {
        this.elemento = 0;
        this.esq = this.dir = this.sup = this.inf = null;
    }
}

class Matriz {

    private Celula inicio;
    private int linha, coluna;

    public Matriz(int coluna, int linha) {
        this.coluna = coluna;
        this.linha = linha;

        // Cria o inicio da matriz
        this.inicio = new Celula();

        Celula[][] matriz = new Celula[linha][coluna];

        // Aloca as celulas e conecta os ponteiros
        for (int i = 0; i < linha; i++) {
            for (int j = 0; j < coluna; j++) {
                matriz[i][j] = new Celula(); // Cria uma nova celula

                // Conectando os ponteiros das celulas
                if (i > 0) {
                    matriz[i][j].sup = matriz[i - 1][j]; // Celula superior
                    matriz[i - 1][j].inf = matriz[i][j]; // Celula inferior
                }

                if (j > 0) {
                    matriz[i][j].esq = matriz[i][j - 1]; // Celula a esquerda
                    matriz[i][j - 1].dir = matriz[i][j]; // Celula a direita
                }
            }
        }

        // Definindo o inicio como a celula [0][0]
        this.inicio = matriz[0][0];
    }

    public void mostrarDiagonalPrincipal() {
        if (isQuadrada()) {
            Celula atual = inicio; // Comeca no topo esquerdo
            //System.out.print("Diagonal Principal: ");
            while (atual != null) {
                System.out.print(atual.elemento + " ");
                // Move para a direita e depois para baixo (diagonal principal)
                if(atual.dir != null){
                    atual = atual.dir;
                    if(atual.inf != null){
                        atual = atual.inf;
                    }
                } else{
                    atual = null;
                }
            }
            System.out.println();
        } else {
            System.out.println("A matriz nao é quadrada. Nao ha diagonal principal.");
        }
    }

    public void mostrarDiagonalSecundaria() {
        if (isQuadrada()) {
            // Move para o canto superior direito
            Celula atual = inicio;
            while (atual.dir != null) {
                atual = atual.dir;
            }

            //System.out.print("Diagonal Secundária: ");
            while (atual != null) {
                System.out.print(atual.elemento + " ");
                // Move para a esquerda e depois para baixo (diagonal secundaria)
                if(atual.esq != null){
                    atual = atual.esq;
                    if(atual.inf != null){
                        atual = atual.inf;
                    }
                } else{
                    atual = null;
                }
            }
            System.out.println();
        } else {
            System.out.println("A matriz nao é quadrada. Nao ha diagonal secundaria.");
        }
    }

// Método auxiliar para verificar se a matriz é quadrada
    private boolean isQuadrada() {
        return linha == coluna;
    }

    public void setElemento(int linha, int coluna, int valor) {
        Celula atual = navegarPara(linha, coluna);
        if (atual != null) {
            atual.elemento = valor;
        }
    }

    private Celula navegarPara(int linha, int coluna) {
        Celula atual = inicio;
        for (int i = 0; i < linha; i++) {
            atual = atual.inf;
        }
        for (int j = 0; j < coluna; j++) {
            atual = atual.dir;
        }
        return atual;
    }

    public Matriz soma(Matriz m) {
        Matriz resp = null;

        // Verifica se as matrizes sao quadradas
        if (this.linha == m.linha && this.coluna == m.coluna) {
            // Cria uma nova matriz para armazenar o resultado
            resp = new Matriz(this.coluna, this.linha);

            // "Ponteiros" para percorrer as matrizes
            Celula a = this.inicio;
            Celula b = m.inicio;
            Celula c = resp.inicio;

            for (int i = 0; i < this.linha; i++) {
                Celula ptrA = a;
                Celula ptrB = b;
                Celula ptrC = c;

                for (int j = 0; j < this.coluna; j++) {
                    // Soma os elementos das celulas correspondentes
                    ptrC.elemento = ptrA.elemento + ptrB.elemento;

                    // Avanca os "ponteiros" nas colunas
                    ptrA = ptrA.dir;
                    ptrB = ptrB.dir;
                    ptrC = ptrC.dir;
                }

                // Avanca os "ponteiros" para a proxima linha
                a = a.inf;
                b = b.inf;
                c = c.inf;
            }
        }

        return resp;
    }

    public Matriz multiplicacao(Matriz m) {
        Matriz resp = null;

        // Verifica se a multiplicacao e possivel
        if (this.coluna == m.linha) {
            // Cria uma matriz para armazenar o resultado
            resp = new Matriz(m.coluna, this.linha);

            // Ponteiros para percorrer as matrizes
            Celula aLinha = this.inicio; // Percorre as linhas de 'this'
            Celula bColuna = m.inicio;  // Percorre as colunas de 'm'

            // Percorre cada celula da matriz resultante
            Celula cLinha = resp.inicio; // Linha da matriz resultado

            for (int i = 0; i < this.linha; i++) {
                Celula c = cLinha; // Celula da matriz resultado na linha atual
                for (int j = 0; j < m.coluna; j++) {
                    Celula a = aLinha; // Ponteiro para percorrer a linha da primeira matriz
                    Celula b = bColuna; // Ponteiro para percorrer a coluna da segunda matriz
                    int soma = 0;

                    // Multiplica e soma os elementos correspondentes
                    for (int k = 0; k < this.coluna; k++) {
                        soma += a.elemento * b.elemento;
                        a = a.dir; // Avança na linha da primeira matriz
                        b = b.inf; // Avança na coluna da segunda matriz
                    }

                    // Define o valor calculado na matriz resultado
                    c.elemento = soma;

                    // Avança para a próxima célula na linha da matriz resultado
                    c = c.dir;

                    // Move o ponteiro inicial da coluna da segunda matriz
                    bColuna = bColuna.dir;
                }

                // Avança para a próxima linha da matriz resultado
                cLinha = cLinha.inf;

                // Avança para a próxima linha da primeira matriz
                aLinha = aLinha.inf;

                // Reseta o ponteiro de coluna da segunda matriz
                bColuna = m.inicio;
            }
        }

        return resp;
    }

    public void mostrar() {
        Celula linhaAtual = inicio;

        while (linhaAtual != null) {
            Celula colunaAtual = linhaAtual; 

            // Percorre as colunas da linha atual
            while (colunaAtual != null) {
                System.out.print(colunaAtual.elemento + " ");
                colunaAtual = colunaAtual.dir; // Avanca para a proxima celula na linha
            }

            System.out.println(); // Quebra de linha para proxima linha da matriz
            linhaAtual = linhaAtual.inf; // Avanca para a proxima linha
        }
    }

}

public class TP03Q11 {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int quant;
        int l1, c1, l2, c2;
        int elemento;

        quant = sc.nextInt(); // Numero de casos de teste

        for (int k = 0; k < quant; k++) {

            // Leitura das dimensoes da matriz
            l1 = sc.nextInt();
            c1 = sc.nextInt();

            // Leitura da primeira matriz
            Matriz matriz1 = new Matriz(c1, l1);
            for (int i = 0; i < l1; i++) {
                for (int j = 0; j < c1; j++) {
                    elemento = sc.nextInt();
                    matriz1.setElemento(i, j, elemento);
                }
            }

            // Leitura das dimensoes da matriz
            l2 = sc.nextInt();
            c2 = sc.nextInt();

            // Leitura da segunda matriz 
            Matriz matriz2 = new Matriz(c2, l2);
            for (int i = 0; i < l2; i++) {
                for (int j = 0; j < c2; j++) {
                    elemento = sc.nextInt();
                    matriz2.setElemento(i, j, elemento);
                }
            }

            // Mostrar diagonais da primeira matriz
            matriz1.mostrarDiagonalPrincipal();
            matriz1.mostrarDiagonalSecundaria();

            // Calcular e mostrar a soma das matrizes
            if (l1 == l2 && c1 == c2) {
                Matriz soma = matriz1.soma(matriz2);
                soma.mostrar();
            } else {
                System.out.println("As matrizes não têm dimensões iguais. Não é possível somar.");
            }

            // Calcular e mostrar a multiplicacao das matrizes
            if (c1 == l2) {
                Matriz multiplicacao = matriz1.multiplicacao(matriz2);
                multiplicacao.mostrar();
            } else {
                System.out.println("As matrizes não têm dimensões compatíveis. Não é possível multiplicar.");
            }

        }
        sc.close();
    }

}
