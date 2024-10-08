
public class Quicksort {

    public static void arrayDecrescente(int[] array) {
        int tamanho = array.length;
        int j = 0;
        for (int i = tamanho - 1; i >= 0; i--) {
            array[j] = i;
            j++;
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
    /*
    int pivo = array[random.nextInt(dir)];
    random.nextInt(1000)
     */

    public static void main(String[] args) {
        int tamanho = 10000;
        int[] array = new int[tamanho];
        arrayDecrescente(array);

        // Teste pivo no inicio 
        long inicio = System.nanoTime();
        QuickSortFirstPivot(array, 0, tamanho-1);
        long fim = System.nanoTime();
        long tempoExecucao = fim - inicio;
        System.out.println("Tempo de execucao QuickSortFirstPivot: " + tempoExecucao + " nanosegundos");

        // Teste pivo no fim
        arrayDecrescente(array);
        inicio = System.nanoTime();
        QuickSortLastPivot(array, 0, tamanho-1);
        fim = System.nanoTime();
        tempoExecucao = fim - inicio;
        System.out.println("Tempo de execucao QuickSortLastPivot: " + tempoExecucao + " nanosegundos");

        // Teste pivo no meio
        arrayDecrescente(array);
        inicio = System.nanoTime();
        quicksort(array, 0, tamanho-1);
        fim = System.nanoTime();
        tempoExecucao = fim - inicio;
        System.out.println("Tempo de execucao QuickSort: " + tempoExecucao + " nanosegundos");
    }
}
