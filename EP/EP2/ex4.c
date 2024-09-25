/*
 * Nome do programa: Fork Dentro de uma Thread
 * Objetivo do programa: Analisar o comportamento da função fork() quando invocada por uma thread.
 * Nome do programador: Luara Perilli 202200841 e Beatriz Nascimento 2023007113
 * Data de criação: 25/09/2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg)
{
    printf("Thread %d: Executando...\n", *(int *)arg);
    fork(); // Apenas a thread que chama o fork será duplicada
    printf("Thread %d após fork: PID:%d\n", *(int *)arg, getpid());
    return NULL;
}

int main()
{
    pthread_t thread;
    int thread_arg = 1;

    pthread_create(&thread, NULL, thread_function, &thread_arg);
    pthread_join(thread, NULL); // Aguarda a thread terminar
    return 0;
}
