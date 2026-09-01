#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define LINHAS 3
#define COLUNAS 3

int main(void)
{
    int segA, segB, segC;
    int *A, *B, *C;
    int pid;

    segA = shmget(IPC_PRIVATE, sizeof(int) * LINHAS * COLUNAS, IPC_CREAT | S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
    segB = shmget(IPC_PRIVATE, sizeof(int) * LINHAS * COLUNAS, IPC_CREAT | S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
    segC = shmget(IPC_PRIVATE, sizeof(int) * LINHAS * COLUNAS, IPC_CREAT | S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);

    A = shmat(segA, 0, 0);
    B = shmat(segB, 0, 0);
    C = shmat(segC, 0, 0);

    if (A == (int *) -1 || B == (int *) -1 || C == (int *) -1)
    {
        perror("erro ao anexar memoria compartilhada");
        exit(1);
    }

    for( int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            A[i * COLUNAS + j] = i + j;
            B[i * COLUNAS + j] = i - j;
            C[i * COLUNAS + j] = 0;
        }
    }

    for (int i = 0; i < LINHAS; i++)
    {
        pid = fork();

        if (pid == 0)
        {
            for (int j = 0; j < COLUNAS; j++)
            {
                C[i * COLUNAS + j] = A[i * COLUNAS + j] + B[i * COLUNAS + j];
            }
            exit(0);
        }
    }

    for (int i = 0; i < LINHAS; i++)
    {
        wait(NULL);
    }

    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            printf("%d ", C[i * COLUNAS + j]);
        }
        printf("\n");
    }

    shmctl(segA, IPC_RMID, NULL);
    shmctl(segB, IPC_RMID, NULL);
    shmctl(segC, IPC_RMID, NULL);
    shmdt(A);
    shmdt(B);
    shmdt(C);

    return 0;
}
