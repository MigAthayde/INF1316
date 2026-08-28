#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include<time.h>

// Esse aqui é o P2!
int main(int argc, char *argv[])
{
    srand(getpid()); // Só explicando que o getpid aqui é para não correr o risco de gerar números aleatórios com a mesma seed nos scripts 4b e 4c!
    int y = rand() % 11;
    int *m2;

    m2 = shmat(atoi(argv[1]), 0, 0);
    if (m2 == (int *) -1)
    {
        perror("Erro ao anexar o segmento de memoria compartilhada");
        exit(1);
    }
    
    sleep(y);

    m2[0] = y;
    m2[1]++;

}