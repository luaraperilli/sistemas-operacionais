/*
 * Nome do programa: Função Clone
 * Objetivo do programa: Verificar o retorno da função clone() ao criar um processo/thread filho.
 * Nome do programador: Luara Perilli 202200841 e Beatriz Nascimento 2023007113
 * Data de criação: 25/09/2024
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>

int child_function(void *arg)
{
    return 0;
}

int main()
{
    // Atribuindo um espaço de pilha para a nova thread
    void *stack = malloc(1024 * 1024); // Alocando 1MB para a pilha
    if (stack == NULL)
    {
        perror("Falha ao alocar memória");
        exit(EXIT_FAILURE);
    }

    // Criação da nova thread usando clone()
    int child_pid = clone(child_function, stack + 1024 * 1024, SIGCHLD, NULL);
    if (child_pid == -1)
    {
        perror("Clone falhou");
        exit(EXIT_FAILURE);
    }
    printf("Clone retornou PID do filho: %d\n", child_pid);

    // Espera o filho terminar
    wait(NULL);
    free(stack); // Libera a memória da pilha
    return 0;
}
