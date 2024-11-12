#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBERS 100000

void selectionSort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (*(arr + j) < *(arr + minIndex)) {
                minIndex = j;
            }
        }
        int temp = *(arr + i);
        *(arr + i) = *(arr + minIndex);
        *(arr + minIndex) = temp;
    }
}

int main() {
    int choice;
    char arquivo_completo[120];
    double total_tempoGastoExterno = 0;
    double total_tempoGastoInterno = 0;
    int maxNumbers;

    printf("Digite o numero de registros: ");
    scanf("%d", &maxNumbers);
    system("cls");

    printf("Escolha o arquivo para ordenar:\n");
    printf("1. Arquivo com numeros aleatorios de %d \n", maxNumbers);
    printf("2. Arquivo com numeros em ordem crescente de %d \n", maxNumbers);
    printf("3. Arquivo com numeros concv de %d \n", maxNumbers);
    scanf("%d", &choice);
    system("cls");

    int *vetor_numeros_satelite = NULL;
    switch (choice) {
        case 1:
            sprintf(arquivo_completo, "TESTES_POR_FUNCAO/registros_%d/dados_aleatorio.txt", maxNumbers);
            break;
        case 2:
            sprintf(arquivo_completo, "TESTES_POR_FUNCAO/registros_%d/dados_cresc.txt", maxNumbers);
            break;
        case 3:
            sprintf(arquivo_completo, "TESTES_POR_FUNCAO/registros_%d/dados_concv.txt", maxNumbers);
            break;
        default:
            printf("Opcao invalida.\n");
            return 1;
    }

    printf("\n Ordenando = %s \n", arquivo_completo);
    printf("\n Iniciando....\n\n Vetor Arquivo\n");

    for (int vezes = 1; vezes <= 5; vezes++) {
        FILE *file = fopen(arquivo_completo, "r");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }

        vetor_numeros_satelite = (int*)malloc(maxNumbers * sizeof(int));
        int count = 0;
        while (fscanf(file, "%d", &vetor_numeros_satelite[count]) != EOF && count < maxNumbers) {
            count++;
        }
        fclose(file);

        clock_t start = clock();
        selectionSort(vetor_numeros_satelite, count);
        clock_t end = clock();

        double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Tempo para ordenar pela %i vez: %.9f segundos\n\n", vezes, timeSpent);
        total_tempoGastoExterno += timeSpent;
    }

    printf("\n Vetor Interno: \n");
    for (int vezes = 1; vezes <= 5; vezes++) {
        int *vetor_interno = (int *)malloc(maxNumbers * sizeof(int));
        if (vetor_interno == NULL) {
            printf("Erro ao alocar memória para vetor interno!\n");
            free(vetor_interno);
            return 1;
        }

        if (choice == 1) {
            for (int i = 0; i < maxNumbers; i++) {
                vetor_interno[i] = rand() % maxNumbers;
            }
        } else {
            for (int i = 0; i < maxNumbers; i++) {
                vetor_interno[i] = i;
            }
        }

        clock_t inicio = clock();
        selectionSort(vetor_interno, maxNumbers);
        clock_t final = clock();

        double tempo_gasto_interno = (double)(final - inicio) / CLOCKS_PER_SEC;
        printf("Tempo gasto para ordenar array interno na %i rodada: %.9f segundos\n\n", vezes, tempo_gasto_interno);
        total_tempoGastoInterno += tempo_gasto_interno;
        free(vetor_interno);
    }

    double tempo_gasto_medio_externo = total_tempoGastoExterno / 5;
    printf("\n\nTempo gasto medio para ordenar vetor externo (arquivo):  %.9f segundos\n", tempo_gasto_medio_externo);

    double tempo_gasto_medio_interno = total_tempoGastoInterno / 5;
    printf("Tempo gasto medio para ordenar vetor interno (gerado):  %.9f segundos\n", tempo_gasto_medio_interno);

    char choice_v2;
    printf("Deseja visualizar o arquivo ordenado [S/N]:\n");
    scanf(" %c", &choice_v2);
    system("cls");

    switch (choice_v2) {
        case 'S':
            printf("Voce escolheu visualizar o arquivo ordenado.\n");
            printf("Array ordenado:\n");
            for (int i = 0; i < maxNumbers; i++) {
                printf("{ Posicao: %i | Numero: %d }\n", i + 1, vetor_numeros_satelite[i]);
            }
            break;
        case 'N':
            printf("Tudo bem.\n");
            break;
        default:
            printf("Opcao invalida.\n");
            return 1;
    }

    free(vetor_numeros_satelite);
    return 0;
}
