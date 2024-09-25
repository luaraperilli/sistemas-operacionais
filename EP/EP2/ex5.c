/*
 * Nome do programa: Clone Dentro de uma Thread
 * Objetivo do programa: Demonstrar o que ocorre quando a função clone() é invocada dentro de uma thread.
 * Nome do programador: Luara Perilli 202200841 e Beatriz Nascimento 2023007113
 * Data de criação: 25/09/2024
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <signal.h>

// Função que será executada pela nova thread criada com clone
int child_function(void *arg)
{
    printf("Nova thread criada com clone: PID:%d\n", getpid());
    return 0;
}

// Função da thread principal
void *thread_function(void *arg)
{
    printf("Thread %d: Invocando clone...\n", *(int *)arg);

    // Chama clone para criar uma nova thread
    int child_pid = clone(child_function, malloc(1024 * 1024) + 1024 * 1024, SIGCHLD | CLONE_VM, NULL);

    if (child_pid == -1)
    {
        perror("Erro ao criar nova thread com clone");
        exit(EXIT_FAILURE);
    }

    return NULL;
}

int main()
{
    int thread_arg = 1;

    // Chama a função da thread principal
    thread_function(&thread_arg);

    // Aguarda um tempo para garantir que a nova thread tenha a chance de executar
    sleep(1);

    return 0;
}
