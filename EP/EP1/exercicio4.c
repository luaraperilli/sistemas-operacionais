#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid1, pid2;

    if ((pid1 = fork()) < 0) {
        perror("fork");
        return 1;
    }

    if (pid1 > 0) {
        printf("Processo pai P (PID: %d)\n", getpid());

        wait(NULL);

        printf("Processo pai P (PID: %d) finalizando.\n", getpid());
    } else {
        printf("Processo filho P1 (PID: %d, Pai PID: %d)\n", getpid(), getppid());

        if ((pid2 = fork()) < 0) {
            perror("fork");
            return 1;
        }

        if (pid2 > 0) {
          
            wait(NULL);
            printf("Processo filho P1 (PID: %d) finalizando.\n", getpid());
        } else {
            printf("Processo filho P2 (PID: %d, Pai PID: %d)\n", getpid(), getppid());
            printf("Processo filho P2 (PID: %d) finalizando.\n", getpid());
            exit(0);
        }

        exit(0);
    }
    return 0;
}
