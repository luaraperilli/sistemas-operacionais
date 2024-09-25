/*
 * Nome do programa: Finalização da Função Principal com Threads Ativas
 * Objetivo do programa: Demonstrar o comportamento quando a função principal encerra enquanto threads ainda estão ativas.
 * Nome do programador: Luara Perilli 202200841 e Beatriz Nascimento 2023007113
 * Data de criação: 25/09/2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        printf("Thread %d: Executando...\n", *(int *)arg);
        sleep(1); // Simula trabalho da thread
    }
    return NULL;
}

int main()
{
    pthread_t thread1, thread2;
    int arg1 = 1, arg2 = 2;

    pthread_create(&thread1, NULL, thread_function, &arg1);
    pthread_create(&thread2, NULL, thread_function, &arg2);

    // Thread principal finaliza sem esperar as outras threads
    printf("Thread principal finalizando...\n");
    return 0; // O processo termina aqui, mas as threads ainda podem continuar
}
