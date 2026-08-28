#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main (void)
{
    char mensagem[100];
    int segmento, pid;
    char  *memoria; // Não vou chamar de *p pra ficar mais claro que esse é o ponteiro que aponta para a área de memória compartilhada

    printf("Digite sua mensagem do dia: ");
    fgets(mensagem, sizeof(mensagem), stdin);

    // Alocando a memória compartilhada
    segmento = shmget(8752, sizeof(mensagem), IPC_CREAT | S_IRUSR | S_IWUSR | S_IROTH);
    memoria = shmat(segmento, 0, 0);
    if (memoria == (char *) -1)
    {
        perror("erro ao anexar a memória compartilhada!");
        exit(1);
    }

    strcpy(memoria, mensagem);

    shmdt(memoria);

    return 0;
}