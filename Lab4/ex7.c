#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{

    int pid1, pid2, pid3;
    pid1 = fork();
    if (pid1 < 0)
    {
        perror("Erro ao criar o processo 1");
        exit(1);
    }
    else if (pid1 == 0)
    {
        execl("./prog1", "prog1", NULL);
        perror("Erro ao executar o processo 1");
        exit(1);
    }

    pid2 = fork();
    if (pid2 < 0)
    {
        perror("Erro ao criar o processo 2");
        exit(1);
    }
    else if (pid2 == 0)
    {
        execl("./prog2", "prog2", NULL);
        perror("Erro ao executar o processo 2");
        exit(1);
    }

    pid3 = fork();
    if (pid3 < 0)
    {
        perror("Erro ao criar o processo 3");
        exit(1);
    }
    else if (pid3 == 0)
    {
        execl("./prog3", "prog3", NULL);
        perror("Erro ao executar o processo 3");
        exit(1);
    }

    kill(pid2, SIGSTOP);
    kill(pid3, SIGSTOP);
    while(1)
    {
        sleep(1);
        printf("Pai> Pausando o processo 1 e retomando o processo 2\n");
        kill(pid1, SIGSTOP);
        kill(pid2, SIGCONT);

        sleep(2);
        printf("Pai> Pausando o processo 2 e retomando o processo 3\n");
        kill(pid2, SIGSTOP);
        kill(pid3, SIGCONT);

        sleep(2);
        printf("Pai> Pausando o processo 3 e retomando o processo 1\n");
        kill(pid3, SIGSTOP);
        kill(pid1, SIGCONT);
    }
    
    return 0;
}