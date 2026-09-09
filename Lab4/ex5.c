#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int soma(int x, int y);
int subtracao(int x, int y);
int multiplicacao(int x, int y);
int divisao(int x, int y);
void signalHandler(int sig);

int main(void)
{
    int x, y;
    signal(SIGFPE, signalHandler);

    printf("Digite o primeiro número: ");
    scanf("%d", &x);
    printf("Digite o segundo número: ");
    scanf("%d", &y);

    printf("Soma: %d\n", soma(x, y));
    printf("Subtração: %d\n", subtracao(x, y));
    printf("Multiplicação: %d\n", multiplicacao(x, y));
    printf("Divisão: %d\n", divisao(x, y));

    return 0;
}

int soma(int x, int y)
{
    return x + y;
}

int subtracao(int x, int y)
{
    return x - y;
}

int multiplicacao(int x, int y)
{
    return x * y;
}

int divisao(int x, int y)
{
    return x / y;
}

void signalHandler(int sig)
{
    if (sig == SIGFPE)
    {
        printf("Erro: divisão por zero!\n");
        exit(1);
    }
}
