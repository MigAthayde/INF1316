#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 20

int main(void)
{

    int segmento, *memoria;
    
    //Alocando e atribuindo a memória compartilhada
    segmento = shmget(IPC_PRIVATE, sizeof(int) * N, IPC_CREAT | S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
    memoria = shmat(segmento, 0, 0);
    if (memoria == (int *) -1)
    {
        perror("erro ao anexar a memória compartilhada!");
        exit(1);
    }

    //Valores desordenados
    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        memoria[i] = rand() % 100; 
    }

    for 

    return 0;
}