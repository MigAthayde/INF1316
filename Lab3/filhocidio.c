#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


void childhandler(int signo);
int delay;
int main (int argc, char *argv[])
{
    pid_t pid;
    signal(SIGCHLD, childhandler);
    if ((pid = fork()) < 0)
    {
        fprintf(stderr, "Erro ao criar filho\n");
        exit(-1);
    }
    if (pid == 0) /* child */
        execve(argv[2], 0, 0); /* ou sleep(3);*/
    else /* parent */
    {
        sscanf(argv[1], "%d", &delay); /* read delay from command line */
        sleep(delay);
        printf("Program %s exceeded limit of %d seconds!\n", argv[2], delay);
        kill(pid, SIGKILL);
        sleep(1); /* necessary for SIGCHLD to arrive */
    }
    return 0;
}

void childhandler(int signo) /* Executed if child dies before parent */
{
    int status;
    pid_t pid = wait(&status);
    printf("Child %d terminated within %d seconds com estado %d.\n", pid, delay, status);
    exit(0);
}

// O primeiro filho tem execução que dmeora 5 segundos, portando ele finaliza antes do limite, e o pai tem o sleep
// interrompido pelo sinal SIGCHLD, chamando o handler logo em seguida sem matar o filho

// No caso do segundo fiho, ele demora mais que o tempo limite de 10 segundos, portando o pai acorda do sleep e emite
// o sinal SIGKILL para matar o processo filho ainda em execução. Logo em seguida o pai dorme por mais 1 segundo
// para garantir que o sinal SIGCHLD seja recebido para então chamar o handler.