// Instituto de Matemática e Computação
// SRSC02 – Sistemas Operacionais
// Exercício Prático 03 – EP03 02/10/2024
// Programadores: Juan Pablo Conti da Silva - 2019007592 e Luara Perilli 2022004841

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NumeroMaximoFans 10 // número máximo de fãs no auditório

int contadorFans = 0; // contador de fãs no auditório

sem_t mutex;          // semáforo para proteger o contador de fãs
sem_t demonstrador;   // semáforo para controlar a exibição do filme
sem_t sincronizaFila; // semáforo para sincronizar a fila de fãs
sem_t salaCheia;      // semáforo para garantir que a sala está cheia antes de exibir o filme

// Função que simula assistir ao filme
void assisteFilme()
{
    printf("Fan entrou na sala...\n");
    sleep(2); // Simula o tempo de duração do filme
}

// Função que simula telefonar para casa
void telefona()
{
    printf("Fan está telefonando para casa...\n");
    sleep(1); // Simula o tempo do telefonema
}

// Função do processo fã
void *fan(void *arg)
{
    while (1)
    {
        sem_wait(&mutex);
        contadorFans++;
        if (contadorFans == NumeroMaximoFans)
        {
            // Avisa o demonstrador que a sala está cheia
            sem_post(&salaCheia);
        }
        sem_post(&mutex);

        sem_post(&demonstrador);   // Avança o contador do demonstrador
        sem_wait(&sincronizaFila); // Espera para assistir o filme

        assisteFilme();
        telefona(); // Telefona após o filme
    }
}

// Função que simula exibir o filme
void exibeFilme()
{
    printf("Demonstrador está exibindo o filme...\n");
    sleep(2); // Simula o tempo de duração do filme (igual ao do fã)
}

// Função do processo demonstrador
void *demonstradorFilme(void *arg)
{
    // Primeiro o demonstrador aguarda a primeira sessão com exatamente 10 pessoas
    sem_wait(&salaCheia); // O demonstrador aguarda até a primeira sala estar cheia

    while (1)
    {
        // Libera a fila para N fãs assistirem ao filme
        for (int i = 0; i < NumeroMaximoFans; i++)
        {
            sem_post(&sincronizaFila);
        }

        // Espera até que todos os fãs tenham entrado e estão prontos para o filme
        for (int i = 0; i < NumeroMaximoFans; i++)
        {
            sem_wait(&demonstrador);
        }

        exibeFilme();

        // Atualiza o número de fãs após a exibição
        sem_wait(&mutex);
        contadorFans -= NumeroMaximoFans; // Reseta o número de fãs após exibição
        sem_post(&mutex);

        // Após a exibição, aguarda até que mais 10 fãs estejam prontos
        sem_post(&salaCheia); // Recomeça o ciclo para a próxima sessão
    }
}

int main()
{
    pthread_t fans[20]; // Criamos mais que N fãs (20 fãs neste exemplo)
    pthread_t demonstra;

    // Inicializa os semáforos
    sem_init(&mutex, 0, 1);
    sem_init(&demonstrador, 0, 0);
    sem_init(&sincronizaFila, 0, 0);
    sem_init(&salaCheia, 0, 0); // Semáforo para controlar quando a sala está cheia

    // Cria a thread do demonstrador
    pthread_create(&demonstra, NULL, demonstradorFilme, NULL);

    // Cria as threads dos fãs
    for (int i = 0; i < 20; i++)
    {
        pthread_create(&fans[i], NULL, fan, NULL);
    }

    // Espera as threads dos fãs
    for (int i = 0; i < 20; i++)
    {
        pthread_join(fans[i], NULL);
    }

    // Espera a thread do demonstrador (também um loop infinito)
    pthread_join(demonstra, NULL);

    // Destrói os semáforos
    sem_destroy(&mutex);
    sem_destroy(&demonstrador);
    sem_destroy(&sincronizaFila);
    sem_destroy(&salaCheia);

    return 0;
}
