#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "contato.h"

struct contato
{
    char nome[121],
         email[31],
         telefone[12];
};

Contato* contato_cria(char* nome, char* telefone, char* email)
{
    Contato *novo= (Contato*)malloc(sizeof(Contato));

    if(novo==NULL)
    {
        printf("Erro de alocacao\n");
        exit (1);
    }

    strcpy(novo->nome,nome);
    strcpy(novo->telefone,telefone);
    strcpy(novo->email,email);

    return novo;
}

void contato_imprime(Contato* contato)
{
    printf("\nNome: %s"
           "\nTelefone: %s"
           "\nEmail: %s",
           contato->nome, contato->telefone, contato->email);
}

void contato_edita(Contato* contato, char* nome, char* telefone, char* email)
{
    strcpy(contato->nome,nome);
    strcpy(contato->telefone,telefone);
    strcpy(contato->email,email);
}

char* contato_nome(Contato* contato)
{
    return contato->nome;
}

char* contato_telefone(Contato* contato)
{
    return contato->telefone;
}

char* contato_email(Contato* contato)
{
    return contato->email;
}

void contato_libera(Contato* contato)
{
    free(contato);
}

