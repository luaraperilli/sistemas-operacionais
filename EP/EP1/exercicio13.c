#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
    pid_t p1, p2;

    p1 = fork();
    if (p1 == 0) {
        printf("Filho 1 executando (PID: %d)\n", getpid());
        return 0;
    }

    p2 = fork();
    if (p2 == 0) {
        printf("Filho 2 executando (PID: %d)\n", getpid());
        return 0;
    }

    wait(NULL); // Espera o primeiro filho
    wait(NULL); // Espera o segundo filho
    printf("Pai encerrando (PID: %d)\n", getpid());

    return 0;
}
