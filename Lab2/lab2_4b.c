#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include<time.h>

// Esse aqui é o P1
int main(int argc, char *argv[])
{
    srand(getpid());
    int x = rand() % 11;
    int *m1;

    m1 = shmat(atoi(argv[1]), 0, 0);
    if (m1 == (int *) -1)
    {
        perror("Erro ao anexar o segmento de memoria compartilhada");
        exit(1);
    }
    
    sleep(x);

    m1[0] = x;
    m1[1]++;

}