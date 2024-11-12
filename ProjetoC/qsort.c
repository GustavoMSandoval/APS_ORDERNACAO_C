#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMEROS 100000

// Função de comparação para qsort
int comparar(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int opcao_arquivo;
    char caminho_arquivo[120];
    double tempo_total_externo = 0;
    double tempo_total_interno = 0;
    int maximoNumero;

    // Entrada para o número de registros
    printf("Digite o numero de registros: ");
    scanf("%d", &maximoNumero);
    system("cls");

    // Menu de seleção de arquivo
    printf("Escolha o arquivo para ordenar:\n");
    printf("1. Arquivo com numeros aleatorios de %d\n", maximoNumero);
    printf("2. Arquivo com numeros em ordem crescente de %d\n", maximoNumero);
    printf("3. Arquivo com numeros decrescentes de %d\n", maximoNumero);
    scanf("%d", &opcao_arquivo);
    system("cls");

    // Definir o caminho do arquivo com base na seleção do usuário
    switch (opcao_arquivo) {
        case 1:
            sprintf(caminho_arquivo, "TESTES_POR_FUNCAO/registros_%d/dados_aleatorio.txt", maximoNumero);
            break;
        case 2:
            sprintf(caminho_arquivo, "TESTES_POR_FUNCAO/registros_%d/dados_cresc.txt", maximoNumero);
            break;
        case 3:
            sprintf(caminho_arquivo, "TESTES_POR_FUNCAO/registros_%d/dados_concv.txt", maximoNumero);
            break;
        default:
            printf("Opcao invalida.\n");
            return 1;
    }

    printf("\nOrdenando = %s\n", caminho_arquivo);
    printf("\nIniciando...\n\nArquivo de Vetor\n");

    int *vetor_externo = NULL;
    for (int i = 1; i <= 5; i++) {
        FILE *arquivo = fopen(caminho_arquivo, "r");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }

        // Alocar memória para o vetor externo
        vetor_externo = (int *)malloc(maximoNumero * sizeof(int));
        int contador = 0;

        // Ler os números do arquivo
        while (fscanf(arquivo, "%d", &vetor_externo[contador]) != EOF && contador < maximoNumero) {
            contador++;
        }
        fclose(arquivo);

        // Medir o tempo de ordenação usando qsort
        clock_t inicio = clock();
        qsort(vetor_externo, contador, sizeof(int), comparar);
        clock_t fim = clock();

        double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Tempo para ordenar pela %d vez: %.9f segundos\n\n", i, tempo_gasto);
        tempo_total_externo += tempo_gasto;
    }

    // Ordenando o vetor interno com dados aleatórios ou ordenados
    printf("\nVetor Interno:\n");
    for (int i = 1; i <= 5; i++) {
        int *vetor_interno = (int *)malloc(maximoNumero * sizeof(int));
        if (vetor_interno == NULL) {
            printf("Erro ao alocar memoria para vetor interno!\n");
            free(vetor_interno);
            return 1;
        }

        // Preencher o vetor interno com dados
        if (opcao_arquivo == 1) {
            for (int j = 0; j < maximoNumero; j++) {
                vetor_interno[j] = rand() % maximoNumero;
            }
        } else {
            for (int j = 0; j < maximoNumero; j++) {
                vetor_interno[j] = j;
            }
        }

        // Medir o tempo de ordenação usando qsort
        clock_t inicio = clock();
        qsort(vetor_interno, maximoNumero, sizeof(int), comparar);
        clock_t fim = clock();

        double tempo_gasto_interno = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Tempo gasto para ordenar vetor interno na %d rodada: %.9f segundos\n\n", i, tempo_gasto_interno);
        tempo_total_interno += tempo_gasto_interno;
        free(vetor_interno);
    }

    // Calcular o tempo médio de ordenação
    double tempo_medio_externo = tempo_total_externo / 5;
    printf("\n\nTempo medio para ordenar vetor externo (arquivo): %.9f segundos\n", tempo_medio_externo);

    double tempo_medio_interno = tempo_total_interno / 5;
    printf("Tempo medio para ordenar vetor interno: %.9f segundos\n", tempo_medio_interno);

    // Opção para visualizar dados ordenados
    char opcao_visualizar;
    printf("\nDeseja visualizar o arquivo ordenado [S/N]:\n");
    scanf(" %c", &opcao_visualizar);
    system("cls");

    switch (opcao_visualizar) {
        case 'S':
            printf("Voce escolheu visualizar o arquivo ordenado.\n");
            printf("Array ordenado:\n");
            for (int i = 0; i < maximoNumero; i++) {
                printf("\n{ Posicao: %d | Numero: %d }\n", i + 1, vetor_externo[i]);
            }
            break;
        case 'N':
            printf("Tudo bem.\n");
            break;
        default:
            printf("Opcao invalida.\n");
            return 1;
    }

    // Liberar memória alocada
    free(vetor_externo);

    return 0;
}
