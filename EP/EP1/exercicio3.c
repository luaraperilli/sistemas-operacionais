#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("Processo pai (PID: %d)\n", getpid());

    if (fork() == 0) {
        // Código do filho 1
        printf("Processo filho 1 (PID: %d, Pai PID: %d)\n", getpid(), getppid());
        return 0;
    }

    if (fork() == 0) {
        // Código do filho 2
        printf("Processo filho 2 (PID: %d, Pai PID: %d)\n", getpid(), getppid());
        return 0;
    }

    // Espera ambos os filhos terminarem
    wait(NULL);
    wait(NULL);

    printf("Processo pai (PID: %d) finalizando.\n", getpid());

    return 0;
}
