/*
 * Nome do programa: Exec Dentro de uma Thread
 * Objetivo do programa: Explorar o comportamento da função exec() ao ser chamada por uma thread.
 * Nome do programador: Luara Perilli 202200841 e Beatriz Nascimento 2023007113
 * Data de criação: 25/09/2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg)
{
    printf("Thread %d: invocando exec...\n", *(int *)arg);
    char *args[] = {"ls", NULL};
    execvp(args[0], args);
    perror("exec falhou");
    return NULL; // Esta linha nunca será alcançada
}

int main()
{
    pthread_t thread;
    int thread_arg = 1;

    pthread_create(&thread, NULL, thread_function, &thread_arg);
    pthread_join(thread, NULL);
    return 0;
}
