#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "interacao.h"


void apresenta_programa(char *msg)
{
    printf ("%s\n", msg);
}

void msg_despedida(char *msg)
{
    printf("%s\n", msg);
}

void limpa_tela(void)
{
    system("cls || clear");
}

void limpa_buffer(void)
{
    setbuf(stdin, NULL);//coloca null no buffer do teclado
}

int le_opcao(int menor_valor, int maior_valor)
{

    printf("\n\nDigite a opcao desejada: ");
    char *op = le_string();

    /**if(validacao_opcao(op))  // se for verdade quer dizer que deu erro.
    {
        printf("\nNumero invalido.");
        free(op);
        return le_opcao(menor_valor, maior_valor);
    }**/

    int opcao = atoi(op);
    free(op);

    if((opcao < menor_valor) || (opcao > maior_valor))
    {
        printf("\nOpcao invalida.");
        return le_opcao(menor_valor, maior_valor);
    }

    return opcao;
}

char* le_string(void)
{
    char *caracteres = (char*)malloc(86*sizeof(char));

    if(caracteres == NULL)
    {
        printf("Erro\n");
        exit (1);
    }

    fgets(caracteres,85,stdin);
    limpa_buffer();

    return caracteres;
}

void apresenta_menu(int n_itens, int menor_opcao,...)
{
    va_list menu;
    int i;

    va_start(menu,menor_opcao);

    for(i=0; i<n_itens; i++)
    {
        printf("\n%d - %s", menor_opcao++, va_arg(menu, char*));
    }

    va_end(menu);
}
