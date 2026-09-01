#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>


int main(void)
{

    int pid1, pid2, *m1, *m2, segmento1, segmento2, seq1, seq2;
    char buf1[12], buf2[12];
    int resultado;

    segmento1 = shmget(IPC_PRIVATE, sizeof(int) * 2, IPC_CREAT | S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
    segmento2 = shmget(IPC_PRIVATE, sizeof(int) * 2, IPC_CREAT | S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
    m1 = shmat(segmento1, 0, 0);
    m2 = shmat(segmento2, 0, 0);
    if (m1 == (int *) -1 || m2 == (int *) -1)
    {
        perror("Erro ao anexar o segmento de memoria compartilhada");
        exit(1);
    }

    sprintf(buf1, "%d", segmento1);
    sprintf(buf2, "%d", segmento2);

    pid1 = fork();
    if (pid1 == 0)
    {
        execl("./lab2_4b", "lab2_4b", buf1, NULL);
        perror("Erro na execucao do filho 1");
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0)
    {
        execl("./lab2_4c", "lab2_4c", buf2, NULL);
        perror("Erro na execucao do filho 2");
        exit(1);
    }

    seq1 = 0;
    seq2 = 0;
    while(seq1 == 0 || seq2 == 0)
    {
        if(m1[1] != 0)
        {
            seq1 = m1[1];
        }
        if(m2[1] != 0)
        {
            seq2 = m2[1];
        }
    }

    resultado = m1[0] * m2[0];
    printf("Resultado: %d\n", resultado);

    shmctl(segmento1, IPC_RMID, NULL);
    shmctl(segmento2, IPC_RMID, NULL);
    shmdt(m1);
    shmdt(m2);

    return 0;
}