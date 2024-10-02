#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 10          // Número de fãs por exibição
#define NUM_FANS 30   // Número total de fãs
#define NUM_SESSOES 3 // Número de sessões de filme permitidas

int nFans = 0;             // Contador de fãs no auditório
int exibindoFilme = 0;     // Flag para saber se o filme está sendo exibido
int sessoesRealizadas = 0; // Contador de sessões
sem_t mutex, dem, fila;    // Semáforos para controle

// Função para simular o fã assistindo ao filme
void assisteFilme()
{
    printf("Fã está assistindo o filme...\n");
    sleep(2); // Simula a duração do filme
}

// Função para simular o fã telefonando para a mãe
void telefona()
{
    printf("Fã está telefonando para a mãe...\n");
    sleep(1); // Simula o tempo de telefonar
}

// Função para simular o demonstrador exibindo o filme
void exibeFilme()
{
    printf("Demonstrador está exibindo o filme para %d fãs...\n", N);
    sleep(2); // Simula a duração do filme (mesmo tempo que os fãs)
}

// Função para os fãs
void *fan(void *arg)
{
    while (sessoesRealizadas < NUM_SESSOES)
    {
        sem_wait(&mutex); // Acesso ao contador de fãs
        if (nFans < N && !exibindoFilme)
        { // Verifica se há espaço e se não está exibindo
            nFans++;
            printf("Fã chegou ao auditório. Total de fãs: %d\n", nFans);
            sem_post(&mutex); // Libera o mutex
            sem_post(&dem);   // Notifica o demonstrador que há um fã a mais
            sem_wait(&fila);  // Espera sua vez para assistir ao filme
            assisteFilme();   // O fã assiste ao filme
            telefona();       // O fã telefona para a mãe
        }
        else
        {
            sem_post(&mutex); // Libera o mutex se não puder entrar
            sleep(1);         // Aguarda um pouco antes de tentar novamente
        }
    }
    return NULL;
}

// Função para o demonstrador
void *demonstrator(void *arg)
{
    while (sessoesRealizadas < NUM_SESSOES)
    {
        // Espera até que haja N fãs no auditório
        while (nFans < N)
        {
            sem_wait(&dem); // Espera até que haja fãs suficientes
        }

        sem_wait(&mutex);    // Acesso ao contador de fãs
        exibindoFilme = 1;   // Inicia a exibição do filme
        nFans -= N;          // Remove os fãs que vão assistir
        sessoesRealizadas++; // Incrementa o número de sessões realizadas
        printf("Sessão número %d de %d\n", sessoesRealizadas, NUM_SESSOES);
        sem_post(&mutex); // Libera o mutex

        for (int i = 0; i < N; i++)
        {
            sem_post(&fila); // Libera N fãs para assistir ao filme
        }

        exibeFilme(); // O demonstrador exibe o filme

        sem_wait(&mutex);  // Acesso ao contador de fãs
        exibindoFilme = 0; // Termina a exibição do filme
        sem_post(&mutex);  // Libera o mutex
    }

    printf("Todas as sessões foram concluídas. O demonstrador encerrou a exibição.\n");
    return NULL;
}

int main()
{
    pthread_t fans[NUM_FANS], demo;

    // Inicializa os semáforos
    sem_init(&mutex, 0, 1);
    sem_init(&dem, 0, 0);
    sem_init(&fila, 0, 0);

    // Cria a thread do demonstrador
    pthread_create(&demo, NULL, demonstrator, NULL);

    // Cria as threads dos fãs
    for (int i = 0; i < NUM_FANS; i++)
    {
        pthread_create(&fans[i], NULL, fan, NULL);
    }

    // Junta as threads
    pthread_join(demo, NULL);
    for (int i = 0; i < NUM_FANS; i++)
    {
        pthread_join(fans[i], NULL);
    }

    // Destroi os semáforos
    sem_destroy(&mutex);
    sem_destroy(&dem);
    sem_destroy(&fila);

    return 0;
}
