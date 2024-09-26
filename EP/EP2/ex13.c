/*
 * Nome do programa: Média e Mediana com Threads
 * Objetivo do programa: Calcular a média e a mediana de um vetor de 20 inteiros usando threads.
 * Nome do programador: Luara Perilli 202200841 e Beatriz Nascimento 2023007113
 * Data de criação: 25/09/2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 20

int vetor[SIZE]; // Vetor global de inteiros
double media = 0;
double mediana = 0;

// Função para comparar elementos (usada no qsort)
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// Função que calcula a média dos elementos do vetor
void *calcular_media(void *arg)
{
    int soma = 0;
    for (int i = 0; i < SIZE; i++)
    {
        soma += vetor[i];
    }
    media = (double)soma / SIZE;
    pthread_exit(NULL);
}

// Função que calcula a mediana dos elementos do vetor
void *calcular_mediana(void *arg)
{
    // Ordena o vetor para calcular a mediana
    qsort(vetor, SIZE, sizeof(int), compare);

    if (SIZE % 2 == 0)
    {
        // Se o número de elementos for par, a mediana é a média dos dois elementos centrais
        mediana = (vetor[SIZE / 2 - 1] + vetor[SIZE / 2]) / 2.0;
    }
    else
    {
        // Se for ímpar, a mediana é o elemento central
        mediana = vetor[SIZE / 2];
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread1, thread2;

    // Semente para geração de números aleatórios
    srand(time(NULL));

    // Preenche o vetor com 20 números inteiros aleatórios entre 0 e 100
    printf("Vetor: ");
    for (int i = 0; i < SIZE; i++)
    {
        vetor[i] = rand() % 101; // Números de 0 a 100
        printf("%d ", vetor[i]);
    }
    printf("\n");

    // Cria a primeira thread para calcular a média
    if (pthread_create(&thread1, NULL, calcular_media, NULL))
    {
        fprintf(stderr, "Erro ao criar a thread para calcular a média\n");
        return 1;
    }

    // Cria a segunda thread para calcular a mediana
    if (pthread_create(&thread2, NULL, calcular_mediana, NULL))
    {
        fprintf(stderr, "Erro ao criar a thread para calcular a mediana\n");
        return 1;
    }

    // Aguarda a primeira thread (média) finalizar
    pthread_join(thread1, NULL);

    // Aguarda a segunda thread (mediana) finalizar
    pthread_join(thread2, NULL);

    // Exibe os resultados
    printf("Média: %.2f\n", media);
    printf("Mediana: %.2f\n", mediana);

    return 0;
}
