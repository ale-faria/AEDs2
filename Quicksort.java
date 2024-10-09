
import java.util.Random;

public class Quicksort {

    // Meotodo que cria um array com elementos em ordem crescente - indo de 0 até tamanho-1
    public static void arrayCrescente(int[] array) {
        int tamanho = array.length;
        int j = 0;
        for (int i = 0; i < tamanho; i++) {
            array[j] = i;
            j++;
        }
    }

    // Meotodo que cria um array com elementos em ordem decrescente - indo de tamanho-1 até 0
    public static void arrayDecrescente(int[] array) {
        int tamanho = array.length;
        int j = 0;
        for (int i = tamanho - 1; i >= 0; i--) {
            array[j] = i;
            j++;
        }
    }

    public static void arrayAleatorio(int[] array) {
        int tamanho = array.length;
        Random random = new Random();
        for (int i = 0; i < tamanho; i++) {
            array[i] = random.nextInt(1000);
        }
    }

    public static void arrayParcialOrdenado(int[] array){
        int tamanho = array.length;
        // Ordenado de forma crescente até a metade
        for (int i = 0; i < tamanho/2; i++) {
            array[i] = i;
        }

        // Decrescente da metade até o final
        int j = tamanho-1;
        for(int i = tamanho/2; i < tamanho; i++){
            array[i] = j;
            j--;
        }
    }

    public static void imprimeArray(int[] array) {
        int tamanho = array.length;
        for (int i = 0; i < tamanho; i++) {
            System.out.println(array[i]);
        }
    }

    // Metodo para trocar dois elementos no array
    public static void swap(int[] array, int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    // Quicksort - pivo no meio
    public static void quicksort(int[] array, int esq, int dir) {
        int i = esq, j = dir;
        int pivo = array[(esq + dir) / 2];

        while (i <= j) {
            while (array[i] < pivo) {
                i++;
            }
            while (array[j] > pivo) {
                j--;
            }
            if (i <= j) {
                swap(array, i, j);
                i++;
                j--;
            }
        }

        if (esq < j) {
            quicksort(array, esq, j);
        }
        if (i < dir) {
            quicksort(array, i, dir);
        }
    }

    // Quicksort - primeiro elemento como pivo
    public static void QuickSortFirstPivot(int[] array, int esq, int dir) {
        int i = esq, j = dir;
        int pivo = array[esq]; // Primeiro elemento do array como pivo

        while (i <= j) {
            while (array[i] < pivo) {
                i++;
            }
            while (array[j] > pivo) {
                j--;
            }
            if (i <= j) {
                swap(array, i, j);
                i++;
                j--;
            }
        }

        if (esq < j) {
            quicksort(array, esq, j);
        }
        if (i < dir) {
            quicksort(array, i, dir);
        }
    }

    // Quicksort - ultimo elemento como pivo
    public static void QuickSortLastPivot(int[] array, int esq, int dir) {
        int i = esq, j = dir;
        int pivo = array[dir]; // Ultimo elemento do array como pivo

        while (i <= j) {
            while (array[i] < pivo) {
                i++;
            }
            while (array[j] > pivo) {
                j--;
            }
            if (i <= j) {
                swap(array, i, j);
                i++;
                j--;
            }
        }

        if (esq < j) {
            quicksort(array, esq, j);
        }
        if (i < dir) {
            quicksort(array, i, dir);
        }
    }

    // Quicksort - pivo aleatorio 
    public static void QuickSortRandomPivot(int[] array, int esq, int dir) {
        int i = esq, j = dir;
        int pivo = array[escolhePivoAleatorio(esq, dir)]; // Gerando pivo aleatorio

        while (i <= j) {
            while (array[i] < pivo) {
                i++;
            }
            while (array[j] > pivo) {
                j--;
            }
            if (i <= j) {
                swap(array, i, j);
                i++;
                j--;
            }
        }

        if (esq < j) {
            quicksort(array, esq, j);
        }
        if (i < dir) {
            quicksort(array, i, dir);
        }
    }

    // Funcao que gera o pivo aleatorio 
    public static int escolhePivoAleatorio(int esq, int dir) {
        Random random = new Random();
        return esq + random.nextInt(dir - esq + 1);
    }

    /*
    int pivo = array[random.nextInt(dir)];
    random.nextInt(1000)
     */
    // Quicksort - mediana do inicio, meio e fim como pivo
    public static void QuickSortMedianOfThree(int[] array, int esq, int dir) {
        int i = esq, j = dir;
        int pivo = array[escolhePivoMedianaDeTres(array, esq, dir)];

        while (i <= j) {
            while (array[i] < pivo) {
                i++;
            }
            while (array[j] > pivo) {
                j--;
            }
            if (i <= j) {
                swap(array, i, j);
                i++;
                j--;
            }
        }

        if (esq < j) {
            quicksort(array, esq, j);
        }
        if (i < dir) {
            quicksort(array, i, dir);
        }
    }

    // Funcao que retorna a mediana de tres valores
    public static int escolhePivoMedianaDeTres(int[] array, int esq, int dir) {
        int meio = (esq + dir) / 2;
        int a = array[esq];
        int b = array[meio];
        int c = array[dir];

        // Retorna a mediana de a, b e c
        if ((a > b) == (a < c)) {
            return esq;
        } else if ((b > a) == (b < c)) {
            return meio;
        } else {
            return dir;
        }
    }

    public static void main(String[] args) {
        int tamanho = 100;
        int[] array = new int[tamanho];
        //arrayCrescente(array);
        //arrayParcialOrdenado(array);
        arrayAleatorio(array);

        // Teste pivo no inicio 
        long inicio = System.nanoTime();
        QuickSortFirstPivot(array, 0, tamanho - 1);
        long fim = System.nanoTime();
        long tempoExecucao = fim - inicio;
        System.out.println("Tempo de execucao QuickSortFirstPivot: " + tempoExecucao + " nanosegundos");

        // Teste pivo no fim
        //arrayCrescente(array);
        //arrayParcialOrdenado(array);
        arrayAleatorio(array);
        inicio = System.nanoTime();
        QuickSortLastPivot(array, 0, tamanho - 1);
        fim = System.nanoTime();
        tempoExecucao = fim - inicio;
        System.out.println("Tempo de execucao QuickSortLastPivot: " + tempoExecucao + " nanosegundos");

        // Teste pivo aleatorio
        //arrayCrescente(array);
        //arrayParcialOrdenado(array);
        arrayAleatorio(array);
        inicio = System.nanoTime();
        QuickSortRandomPivot(array, 0, tamanho - 1);
        fim = System.nanoTime();
        tempoExecucao = fim - inicio;
        System.out.println("Tempo de execucao QuickSortRandomPivot: " + tempoExecucao + " nanosegundos");

        // Teste pivo mediana
        //arrayCrescente(array);
        //arrayParcialOrdenado(array);
        arrayAleatorio(array);
        inicio = System.nanoTime();
        QuickSortMedianOfThree(array, 0, tamanho - 1);
        fim = System.nanoTime();
        tempoExecucao = fim - inicio;
        System.out.println("Tempo de execucao QuickSortMedianOfThree: " + tempoExecucao + " nanosegundos");

        // Teste pivo no meio
        //arrayCrescente(array);
        //arrayParcialOrdenado(array);
        arrayAleatorio(array);
        inicio = System.nanoTime();
        quicksort(array, 0, tamanho - 1);
        fim = System.nanoTime();
        tempoExecucao = fim - inicio;
        System.out.println("Tempo de execucao QuickSort: " + tempoExecucao + " nanosegundos");

    }
}
