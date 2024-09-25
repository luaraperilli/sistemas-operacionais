/*
 * Nome do programa: Finalização de Threads sem pthread_exit()
 * Objetivo do programa: Mostrar o comportamento quando a função principal finaliza sem aguardar as threads criadas com pthread_create().
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
        printf("Thread %ld: Executando... (%d)\n", (long)arg, i + 1);
        sleep(1);
    }
    printf("Thread %ld: Finalizando...\n", (long)arg);
    return NULL;
}

int main()
{
    pthread_t thread;
    long thread_id = 1;

    // Cria uma nova thread
    pthread_create(&thread, NULL, thread_function, (void *)thread_id);

    // Aguarda a thread secundária terminar
    pthread_join(thread, NULL);

    printf("Thread principal: Finalizando após a thread secundária...\n");
    return 0;
}
