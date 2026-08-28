#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include<time.h>

#define N 20

int main(void)
{

    int segmento, *memoria, chave;
    int pids[4];
    
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
        memoria[i] = rand() % 21; 
    }

    printf("Escolha uma chave a ser encontrada (entre 0 e 20): ");
    scanf("%d", &chave);

    for (int i = 0; i < 4; i++)
    {
        pids[i] = fork();

        if(pids[i] == 0)
        {
            int inicio = i * (N/4);
            int fim = (i+1) * (N/4);
            for (int j = inicio; j < fim; j++)
            {
                if (memoria[j] == chave)
                {
                    printf("Chave %d encontrada no processo %d na posicao %d\n", chave, getpid(), j);
                }
            }

            exit(0);
        }
    }

    waitpid(pids[0], NULL, 0);
    waitpid(pids[1], NULL, 0);
    waitpid(pids[2], NULL, 0);
    waitpid(pids[3], NULL, 0);
    shmctl(segmento, IPC_RMID, 0);
    shmdt(memoria);

    return 0;
}