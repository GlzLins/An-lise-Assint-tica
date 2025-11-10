//Gleydson Rodrigues Lins 
/**
 * @file main.c
 * @author ...
 * @brief Avaliação Continuada 03 - Comparação Empírica de Algoritmos de Ordenação
 * @version 1.0
 * @date 2025-11-01
 */

#include <stdio.h>    // Entrada e saída de dados (printf, fopen, fwrite, fread)
#include <stdlib.h>   // Funções gerais (malloc, rand, exit)
#include <time.h>     // Medição de tempo (clock, time)
#include <stdbool.h>  // Tipo booleano (true, false)


//  1. IMPLEMENTAÇÃO DOS ALGORITMOS DE ORDENAÇÃO

// ----------------------------- Bubble Sort -----------------------------------
 //Ordena o vetor A[0..n-1] comparando pares adjacentes.

void BubbleSort(int n, int A[]) {   
    for (int i = 0; i < n - 1; ++i) {   
        for (int j = n - 1; j > i; --j) {
            if (A[j] < A[j - 1]) { 
                int aux = A[j];
                A[j] = A[j - 1];
                A[j - 1] = aux;  
            }
        }
    }
}

// ----------------------------- Insertion Sort --------------------------------
//nsere cada elemento na posição correta do subvetor já ordenado.

void InsertionSort(int n, int A[]) {
    for (int i = 1; i < n; i++) {
        int chave = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > chave) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = chave;
    }
}

// ----------------------------- Selection Sort --------------------------------
//Seleciona o menor elemento do vetor e o coloca na primeira posição.

void SelectionSort(int n, int A[]) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (A[j] < A[min])
                min = j;
        int temp = A[i];
        A[i] = A[min];
        A[min] = temp;
    }
}

// ----------------------------- Merge Sort ------------------------------------
//Função auxiliar do MergeSort: intercala dois subvetores já ordenados.

void merge(int A[], int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = A[inicio + i];
    for (int j = 0; j < n2; j++) R[j] = A[meio + 1 + j];

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) A[k++] = L[i++];
        else A[k++] = R[j++];
    }

    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];
}
//Divide o vetor recursivamente em partes e as combina ordenadas.
void MergeSort(int A[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        MergeSort(A, inicio, meio);
        MergeSort(A, meio + 1, fim);
        merge(A, inicio, meio, fim);
    }
}

// ----------------------------- Quick Sort ------------------------------------
//Função que particiona o vetor para o algoritmo QuickSort.

int particionar(int A[], int baixo, int alto) {
    int pivo = A[alto];
    int i = baixo - 1;
    for (int j = baixo; j < alto; j++) {
        if (A[j] < pivo) {
            i++;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    int temp = A[i + 1];
    A[i + 1] = A[alto];
    A[alto] = temp;
    return i + 1;
}
//Utiliza o conceito de "dividir e conquistar" com particionamento recursivo.
void QuickSort(int A[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(A, baixo, alto);
        QuickSort(A, baixo, pi - 1);
        QuickSort(A, pi + 1, alto);
    }
}

// ----------------------------- Heap Sort -------------------------------------
//Função auxiliar do HeapSort.
void heapify(int A[], int n, int i) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < n && A[esq] > A[maior])
        maior = esq;

    if (dir < n && A[dir] > A[maior])
        maior = dir;

    if (maior != i) {
        int temp = A[i];
        A[i] = A[maior];
        A[maior] = temp;
        heapify(A, n, maior);
    }
}
//Constrói um heap máximo e o reduz progressivamente.

void HeapSort(int n, int A[]) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(A, n, i);
    for (int i = n - 1; i > 0; i--) {
        int temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        heapify(A, i, 0);
    }
}


//  2. FUNÇÕES DE GERAÇÃO E LEITURA DE DADOS

//Gera arquivos binários com números aleatórios para teste.

void gera_dados(int num_iteracoes, const int vetor_tam[]) {
    for (int n = 0; n < num_iteracoes; ++n) {
        for (int semente = 0; semente < 5; semente++) {
            char nome_arquivo[150];
            snprintf(nome_arquivo, sizeof(nome_arquivo),
                     "dados/random%d_%d.dat", n, semente);

            FILE *fout = fopen(nome_arquivo, "wb");
            if (!fout) { perror("Erro ao criar arquivo"); exit(EXIT_FAILURE); }

            srand((unsigned) time(NULL) + semente);
            int tamanho_vetor = vetor_tam[n];
            int r;

// Escreve números aleatórios no arquivo
            for (int i = 0; i < tamanho_vetor; i++) {
                r = rand();
                fwrite(&r, sizeof(r), 1, fout);
            }
            fclose(fout);
        }
    }
}
//Lê um vetor de inteiros de um arquivo binário.
void ler_dados(int n, int A[], const char *nomeArquivo) {
    FILE *input_file = fopen(nomeArquivo, "rb");
    if (!input_file) { perror("Erro ao abrir o arquivo"); exit(EXIT_FAILURE); }
    fread(A, sizeof(int), n, input_file);
    fclose(input_file);
}


//  3. FUNÇÃO MAIN - EXECUÇÃO DOS TESTES E COLETA DE RESULTADOS


int main() {
    const int tam[] = {
        1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000,
        11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000,
        20000, 21000, 22000, 23000, 24000, 25000, 26000, 27000, 28000,
        29000, 30000, 31000, 32000, 33000, 34000, 35000, 36000, 37000,
        38000, 39000, 40000, 41000, 42000, 43000, 44000, 45000, 46000,
        47000, 48000, 49000, 50000, 51000, 52000, 53000, 54000, 55000,
        56000, 57000, 58000, 59000, 60000, 61000, 62000, 63000, 64000,
        65000, 66000, 67000, 68000, 69000, 70000, 71000, 72000, 73000,
        74000, 75000, 76000, 77000, 78000, 79000, 80000, 81000, 82000,
        83000, 84000, 85000, 86000, 87000, 88000, 89000, 90000, 91000,
        92000, 93000, 94000, 95000, 96000, 97000, 98000, 99000
    };

    const int TOTAL_N = sizeof(tam)/sizeof(tam[0]);

    printf("Gerando arquivos de dados...\n");
    gera_dados(TOTAL_N, tam);
    printf("Arquivos gerados com sucesso!\n\n");
// Estrutura que mapeia o nome e função de cada algoritmo
    struct {
        const char *nome;
        void (*alg)(int, int[]);
        int tipo; // 0 = normal, 1 = recursivo
    } algoritmos[] = {
        {"Bubble", BubbleSort, 0},
        {"Insertion", InsertionSort, 0},
        {"Selection", SelectionSort, 0},
        {"Merge", NULL, 1},
        {"Quick", NULL, 1},
        {"Heap", HeapSort, 0}
    };

    int total_alg = sizeof(algoritmos)/sizeof(algoritmos[0]);
    
// Loop de execução dos algoritmos
    for (int a = 0; a < total_alg; a++) {
        char nome_saida[150];
        snprintf(nome_saida, sizeof(nome_saida), "resultados/resultado%s.txt", algoritmos[a].nome);
        FILE *out = fopen(nome_saida, "w");
        if (!out) { perror("Erro ao criar arquivo de resultado"); exit(EXIT_FAILURE); }

        printf("Executando %sSort...\n", algoritmos[a].nome);
 // Testa cada tamanho de vetor
        for (int iter = 0; iter < TOTAL_N; iter++) {
            long double duracao_media = 0.0;
            int tamanho_vetor = tam[iter];
            int vetor[tamanho_vetor];

            for (int semente = 0; semente < 5; semente++) {
                char nome_arquivo[150];
                snprintf(nome_arquivo, sizeof(nome_arquivo), "dados/random%d_%d.dat", iter, semente);
                ler_dados(tamanho_vetor, vetor, nome_arquivo);

                clock_t ini = clock();

                if (algoritmos[a].tipo == 0)
                    algoritmos[a].alg(tamanho_vetor, vetor);
                else if (a == 3)
                    MergeSort(vetor, 0, tamanho_vetor - 1);
                else if (a == 4)
                    QuickSort(vetor, 0, tamanho_vetor - 1);

                clock_t fim = clock();

                long double duracao = (double)(fim - ini) * 1e6 / CLOCKS_PER_SEC;
                duracao_media += duracao;
            }

            duracao_media /= 5.0;
            printf("[%s] N = %d, tempo médio = %.2Lf µs\n",
                   algoritmos[a].nome, tamanho_vetor, duracao_media);
            fprintf(out, "%d %Lf\n", tamanho_vetor, duracao_media);
        }

        fclose(out);
        printf("%sSort concluído!\n\n", algoritmos[a].nome);
    }

    printf("✅ Todos os testes concluídos e resultados salvos na pasta 'resultados/'.\n");
    return 0;
}

