#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#define EVER ;;

void killhandler(int sinal);

int main(void)
{

    printf("Tentando captar tentativas de assassinato");
    signal(SIGKILL, killhandler);
    
    for(EVER);

    return 0;
}

void killhandler(int sinal)
{
    printf("ALERTA: Tentaram me assassinar! (%d)\n", sinal);
}

// O sistema operacional mata o processo a força, e por conta disso, mesmo tentando desviar com meu handler, ele nunca é alcançado pois o processo morre imediatamente