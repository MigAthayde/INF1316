#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(void)
{

    int pid1, pid2;

    pid1 = fork();
    if (pid1 < 0)
    {
        perror("Erro ao criar filho 1\n");
        exit(1);
    }
    if (pid1 == 0) // Filho 1
    {
        while(1)
        {
            printf("Filho 1> Executando...\n");
            sleep(1);
        }
    }

    pid2 = fork();
    if (pid2 < 0)
    {
        perror("Erro ao criar filho 2\n");
        exit(1);
    }
    if (pid2 == 0) // Filho 2
    {
        while(1)
        {
            printf("Filho 2> Executando...\n");
            sleep(1);
        }
    }

    printf("Pai> Filhos criados com PID %d e %d\n", pid1, pid2);
    sleep(2);

    printf("Pai> Pausando a execucao do filho 2\n");
    kill(pid2, SIGSTOP);
    int ativo = pid1;
    int pausado = pid2;
    int num_ativo = 1;
    int num_pausado = 2;

    for (int i = 1; i <= 10; i++) {
        sleep(2);

        printf("Pai>>> [Troca %d/10]: Pausando Filho %d e Retomando Filho %d <<<\n", i, num_ativo, num_pausado);

        kill(ativo, SIGSTOP);
        kill(pausado, SIGCONT);

        int temp_pid = ativo;
        ativo = pausado;
        pausado = temp_pid;

        int temp_num = num_ativo;
        num_ativo = num_pausado;
        num_pausado = temp_num;
    }
    sleep(1);

    printf("Pai> Finalizando os filhos\n");
    kill(pid1,SIGKILL);
    kill(pid2,SIGKILL);
    waitpid(pid1, 0, 0);
    waitpid(pid2, 0, 0);

    printf("Pai> Finalizando o processo pai\n");
    return 0;
}