#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "agenda.h"
#include "contato.h"

struct no
{
    struct no *anterior;
    Contato *info;
    struct no *proximo;
};

Contato* agenda_info(No* no)
{
    if(no == NULL)
	return NULL;
    return no->info;
}

Agenda agenda_cria(void)
{
    return NULL;
}

Agenda agenda_carrega(FILE* fp)
{

    Agenda nova_agenda = agenda_cria();
    char *nome = (char*) malloc(121*sizeof(char)), *email = (char*) malloc(31*sizeof(char)), *telefone = (char*) malloc(12*sizeof(char));

    if(nome==NULL)
    {
        printf("Erro nome\n");
        exit (1);
    }

    if(email==NULL)
    {
        printf("Erro email\n");
        exit (1);
    }

    if(telefone==NULL)
    {
        printf("Erro telefone\n");
        exit (1);
    }

    while(fscanf(fp, "%*s %[^\n]s", nome) != EOF)
    {
        fscanf(fp,"%*s %s\n"
               "%*s %s\n", telefone, email);

        Contato *novo = contato_cria(nome,telefone, email);

        nova_agenda = agenda_insere(nova_agenda,novo);
    }
    return nova_agenda;

}

Agenda agenda_insere(Agenda agenda, Contato* contato)
{
    Agenda novo = (Agenda) malloc(sizeof(No));
    if(novo == NULL)
    {
        printf("Erro de alocacao\n");
        exit (1);
    }
    if(agenda == NULL)
    {
        novo->anterior = NULL;
        novo->info = contato;
        novo->proximo = NULL;
        return novo;
    }

    Agenda aux = agenda, ultimo;

    while(strcmp(contato_nome(contato), contato_nome(aux->info)) > 0)
    {
        ultimo = aux;
        aux = aux->proximo;

        if(aux == NULL)
            break;
    }

    if(aux == agenda)  // caso seja para inserir como primeiro da lista
    {
        novo->anterior = NULL;
        novo->info = contato;
        novo->proximo = aux;
        aux->anterior = novo;
        return novo;
    }
    else if(aux == NULL)    // caso seja para inserir como ultimo da lista
    {
        novo->info = contato;
        novo->anterior = ultimo;
        novo->proximo = NULL;
        ultimo->proximo = novo;
    }
    else
    {
        novo->info = contato;
        novo->anterior = aux->anterior;
        novo->proximo = aux;
        aux->anterior->proximo = novo;
        aux->anterior = novo;
    }

    return agenda;
}

No* agenda_busca(Agenda agenda, char* nome)
{
    No* aux = agenda;

    if(agenda == NULL)
        return NULL;

    while((strcmp(contato_nome(aux->info), nome)) != 0)
    {
        aux = aux->proximo;

        if(aux == NULL) // quer dizer que não achou
            return NULL;
    }

    return aux;
}

Agenda agenda_remove(Agenda agenda, char* nome)
{
    Agenda aux = agenda;

    while((strcmp(contato_nome(aux->info), nome)) != 0)
    {
        aux = aux->proximo;

        if(aux == NULL)
        {
            printf("\nContato nao existente");
            return agenda;
        }
    }
    if(aux == agenda)  //caso seja a primeira posição da lista.
    {
        agenda = aux->proximo;
        contato_libera(aux->info);
        free(aux);
    }
    else if(aux->proximo == NULL)    //caso seja a ultima posição da lista.
    {
        aux->anterior->proximo = NULL;
        contato_libera(aux->info);
        free(aux);
    }
    else
    {
        aux->anterior->proximo = aux->proximo;
        aux->proximo->anterior = aux->anterior;
        contato_libera(aux->info);
        free(aux);
    }
    return agenda;
}

void agenda_edita(No* no, char* nome, char* telefone, char* email)
{
    contato_edita(no->info, nome, telefone, email);
}

void agenda_imprime(Agenda agenda)
{
    while(agenda != NULL)
    {
        printf("\n---------------------\n");
        contato_imprime(agenda->info);

        agenda = agenda->proximo;
    }
}

void agenda_salva(FILE* fp, Agenda agenda)
{
    while(agenda != NULL)
    {
        fprintf(fp,"\n-------------------------\n");
        fprintf(fp,"Nome: %s"
                "\nTelefone: %s"
                "\nEmail: %s", contato_nome(agenda->info), contato_telefone(agenda->info),contato_email(agenda->info));
        agenda = agenda->proximo;
    }
}
