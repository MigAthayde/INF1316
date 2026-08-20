#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

void ler_vetor(int* vetor, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("Digite o elemento %d: ", i);
        scanf("%d", &vetor[i]);
    }
}

void print_vetor(int *vetor, int tamanho)
{
    printf("[");
    for (int i = 0; i < tamanho; i++)
    {
        printf("%d,", vetor[i]);
    }
    printf("]\n");
}

int main(void)
{

    int mypid, pid, status; // Pid é o número identificador de um processo e em execução
    int x = 1;
    int vetor[10];
    ler_vetor(vetor, 10);

    printf("Valor da variavel de teste: %d\n", x);
    print_vetor(vetor, 10);
    pid = fork(); //-> Criação de um novo processo (sub-processo) filho tendo o processo principal como pai.O retorno do fork é o Pid do filho, somente com acesso pelo pai.
    if (pid != 0) // Pai
    {
        // Exercicio 1:
        waitpid(-1, &status, 0);
        mypid = getppid();
        printf("Mypid do pai: %d\n", mypid);

        // Exercicio 2:
        printf("Valor da variavel de teste no pai após mod no filho: %d\n", x);
    }
    else // Filho
    {
        // Exercicio 1:
        mypid = getpid();
        printf("Mypid do filho: %d\n", mypid);

        // Exericio 2:
        x = 5;
        printf("Valor da variavel de teste no filho: %d\n", x);
        exit(3);
    }

    return 0;
}