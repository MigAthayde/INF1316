#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile int segundos = 0;
volatile int emLigacao = 0;

void handlerAlarm(int sig)
{
    if (emLigacao)
    {
        segundos++;
        alarm(1);
    }
}

void handlerUSR1(int sig)
{
    segundos = 0;
    emLigacao = 1;
    alarm(1);
    printf("Chamada iniciada (PID %d)\n", getpid());
    fflush(stdout);
}

void handlerUSR2(int sig)
{
    float custo;

    if (!emLigacao)
    {
        printf("Nenhuma chamada em andamento\n");
        fflush(stdout);
        return;
    }

    emLigacao = 0;
    alarm(0);

    if (segundos <= 60)
        custo = segundos * 0.02;
    else
        custo = 60 * 0.02 + (segundos - 60) * 0.01;

    printf("Chamada encerrada: %d segundo(s), custo R$ %.2f\n", segundos, custo);
    fflush(stdout);
}

int main(void)
{
    signal(SIGUSR1, handlerUSR1);
    signal(SIGUSR2, handlerUSR2);
    signal(SIGALRM, handlerAlarm);

    printf("Monitor de chamadas iniciado (PID %d)\n", getpid());
    fflush(stdout);

    while (1)
        pause();

    return 0;
}
