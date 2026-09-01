#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#define EVER ;;

void intHandler(int sinal);
void quitHandler(int sinal);

int main (void)
{
    void (*p)(int); // ponteiro para função que recebe int como
    // parâmetro
    //p = signal(SIGINT, intHandler);
    printf("Endereco do manipulador anterior %p\n", p);

    //p = signal(SIGQUIT, quitHandler);
    printf("Endereco do manipulador anterior %p\n", p);
    puts ("Ctrl-C desabilitado. Use Ctrl-\\ para terminar");

    for(EVER);
}

void intHandler(int sinal)
{
    printf("Você pressionou Ctrl-C (%d) \n", sinal);
}

void quitHandler(int sinal)
{
    printf("Terminando o processo...\n");
    exit (0);
}

// Ao retirar as funções signal, eu não estou mais estebelecendo um handler específico para os sinais que estou recebento (SIGINT e SIGQUIT), 
// portanto o handler default está sendo usado, interrompendo o programado ao teclad CTRL-C e dando quit ao teclar CTRL-\