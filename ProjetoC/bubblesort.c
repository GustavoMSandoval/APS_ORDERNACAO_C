#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBERS 100000

void ordenacaoBubbleSort(int numeros[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (numeros[j] > numeros[j + 1]) {
                int temp = numeros[j];
                numeros[j] = numeros[j + 1];
                numeros[j + 1] = temp;
            }
        }
    }
}

int main() {
    int escolha_pasta;
    char arquivo_completo[120];
    double total_tempoGastoExterno = 0;
    double total_tempoGastoInterno = 0;

    int maximoNumero;
    printf("Digite o numero de registros: ");
    scanf("%d", &maximoNumero);
    system("cls");

    printf("Escolha o arquivo para ordenar:\n");
    printf("1. Arquivo com numeros aleatorios de %d \n", maximoNumero);
    printf("2. Arquivo com numeros em ordem crescente de %d \n", maximoNumero);
    printf("3. Arquivo com numeros concv de %d \n", maximoNumero);
    scanf("%d", &escolha_pasta);
    system("cls");

    int *vetor_numeros_satelite = NULL;
    switch (escolha_pasta) {
        case 1:
            sprintf(arquivo_completo, "TESTES_POR_FUNCAO/registros_%d/dados_aleatorio.txt", maximoNumero);
            break;
        case 2:
            sprintf(arquivo_completo, "TESTES_POR_FUNCAO/registros_%d/dados_cresc.txt", maximoNumero);
            break;
        case 3:
            sprintf(arquivo_completo, "TESTES_POR_FUNCAO/registros_%d/dados_concv.txt", maximoNumero);
            break;
        default:
            printf("Opcao invalida.\n");
            return 1;
    }

    printf("\n Ordenando = %s \n", arquivo_completo);
    printf("\n Inicinado....\n\n Vetor Arquivo\n");

    for (int vezes = 1; vezes <= 5; vezes++) {
        FILE *file = fopen(arquivo_completo, "r");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }

        vetor_numeros_satelite = (int*)malloc(maximoNumero * sizeof(int));
        int contador = 0;
        while (fscanf(file, "%d", &vetor_numeros_satelite[contador]) != EOF && contador < maximoNumero) {
            contador++;
        }
        fclose(file);

        clock_t start = clock();
        ordenacaoBubbleSort(vetor_numeros_satelite, contador);
        clock_t end = clock();

        double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Tempo para ordenar pela %i vez: %.9f segundos\n\n", vezes, timeSpent);
        total_tempoGastoExterno += timeSpent;
    }

    printf("\n Vetor Interno: \n");
    for (int vezes = 1; vezes <= 5; vezes++) {
        int *vetor_interno = (int *)malloc(maximoNumero * sizeof(int));
        if (vetor_interno == NULL) {
            printf("Erro ao alocar memoria para vetor interno!\n");
            free(vetor_interno);
            return 1;
        }

        if (escolha_pasta == 1) {
            for (int i = 0; i < maximoNumero; i++) {
                vetor_interno[i] = rand() % maximoNumero;
            }
        } else {
            for (int i = 0; i < maximoNumero; i++) {
                vetor_interno[i] = i;
            }
        }

        clock_t inicio = clock();
        ordenacaoBubbleSort(vetor_interno, maximoNumero);
        clock_t final = clock();

        double tempo_gasto_interno = (double)(final - inicio) / CLOCKS_PER_SEC;
        printf("Tempo gasto para ordenar array interno na %i rodada: %.9f segundos\n\n", vezes, tempo_gasto_interno);
        total_tempoGastoInterno += tempo_gasto_interno;
        free(vetor_interno);
    }

    double tempo_gasto_medio_externo = total_tempoGastoExterno / 5;
    printf("\n\nTempo gasto medio para ordenar vetor externo (arquivo):  %.9f segundos\n", tempo_gasto_medio_externo);

    double tempo_gasto_medio_interno = total_tempoGastoInterno / 5;
    printf("Tempo gasto medio para ordenar vetor interno:  %.9f segundos\n", tempo_gasto_medio_interno);

    char escolha_visualizar;
    printf("\n Deseja visualizar o arquivo ordenado [S/N]:\n");
    scanf(" %c", &escolha_visualizar);
    system("cls");

    switch (escolha_visualizar) {
        case 'S':
            printf("Voce escolheu visualizar o arquivo ordenado.\n");
            printf("Array ordenado:\n");
            for (int i = 0; i < maximoNumero; i++) {
                printf("\n { Posicao: %i | Numero: %d }\n", i+1, vetor_numeros_satelite[i]);
            }
            break;
        case 'N':
            printf("Tudo bem.\n");
            break;
        default:
            printf("Opcao invalida.\n");
            return 1;
    }

    return 0;
}
