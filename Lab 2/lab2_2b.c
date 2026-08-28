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

    int segmento;
    char *memoria;

    segmento = shmget(8752, 100 * sizeof(char), IPC_CREAT | S_IRUSR | S_IWUSR | S_IROTH);
    memoria = shmat(segmento, 0, 0);
    if (memoria == (char *) -1)
    {
        perror("erro ao anexar a memória compartilhada!");
        exit(1);
    }

    printf("Mensagem do dia no programa cliente: %s", memoria);

    shmdt(memoria);

    shmctl(segmento, IPC_RMID, 0);

    return 0;
}