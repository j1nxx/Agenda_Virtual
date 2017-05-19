#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

// Seu programa compila e fecha bem depois quando eu adiciono os arquivos .c
// Veja o que está acontecendo ou converse com Thiago para solucionar esses erros de biblioteca
// O certo é adicionar o arquivo .h e não o arquivo .c
#include "contato.h"
#include "interacao.h"
#include "agenda.h"
#define OP1 "Adicionar contato"
#define OP2 "Remover contato"
#define OP3 "Modificar contato"
#define OP4 "Buscar contato"
#define OP5 "Listar contatos"
#define OP6 "Sair do programa"
#define APRESENTACAO "\n\nBem-vind@ a lista telefônica virtual.\nAuthor: Déborah Assunção da Silva Alves\nDate: 10/05/2017"
#define DESPEDIDA "\n\t\tObrigad@, espero ter sido útil.\n\n"

int main(void)
{

    setlocale(LC_ALL,"");

    char *nome, *email, *telefone;
    int op;

    Agenda agenda;
    //Agenda aux;
    Contato *contato;
    No *busca; //caso nao der certo, troque No por Agenda

    FILE *fp = fopen("Agenda.txt","a");

    if(fp==NULL)
    {
        printf("Erro de arq\n");
    }

    agenda = agenda_carrega(fp);

    apresenta_programa(APRESENTACAO);

    do
    {
        apresenta_menu(6,1,OP1,OP2,OP3,OP4,OP5,OP6);
        op = le_opcao(1,6);
        limpa_tela();

        //limpa_tela();
        switch(op)
        {
        case 1:
            printf("\n\nAdicionando contato na agenda...\n");
            do
            {
                printf("\nDigite o nome: ");
                nome = le_string();
                busca = agenda_busca(agenda,nome);

                if(busca!=NULL)
                {
                    printf("Nome ja existente, digite novamente.");
                    limpa_tela();
                }
            }
            while(busca!=NULL);

            printf("\nDigite o telefone: ");
            telefone = le_string();
            printf("\nDigite o email: ");
            email = le_string();
            limpa_tela();

            //FALTA VERIFICAR

            contato = contato_cria(nome,telefone,email);
            agenda = agenda_insere(agenda, contato);

            free(nome);
            free(telefone);
            free(email);

            break;

        case 2:
            printf ("\n\nRemovendo contato da agenda...\n");

            if(agenda==NULL)
            {
                printf("Agenda vazia\n");
            }
            else
            {
                /**char escolha;

                printf("\nDeseja ver a lista de contatos na agenda?(S/N) : ");
                scanf("%c", &escolha);
                limpa_buffer();
                limpa_tela();

                if((escolha == 's') || (escolha == 'S'))
                {
                    agenda_imprime(agenda);
                }**/

                printf("\n\nDigite o nome que deseja remover: ");
                nome = le_string();
                busca= agenda_busca(agenda, nome);
                if(busca==NULL)
                {
                    printf("Nenhum contato cadastrado com esse nome!\n Por favor tente novamente!\n");
                    break;
                }
                else
                {
                    agenda= agenda_remove(agenda, nome);
                    printf("\nContato removido com exito!\n\n");
                }
                free(nome);
            }
            break;

        case 3:
            printf("\n\nMofificando contato...\n");

            if(agenda==NULL)
            {
                printf("Agenda vazia\n");
            }
            else
            {
                /**char escolha;

                printf("\nDeseja ver a lista de contatos na agenda?(S/N) : ");
                scanf("%c", &escolha);
                limpa_buffer();

                if((escolha == 's') || (escolha == 'S'))
                {
                    agenda_imprime(agenda);
                }**/

                printf("\nDigite o nome do contato que deseja modificar: ");
                limpa_tela();
                nome = le_string();
                busca= agenda_busca(agenda, nome);
                if(busca==NULL)
                {
                    printf("Contato inexistente! Por favor, tente novamente!\n");
                    break;
                }
                else
                {
                    printf("\nNovo nome: ");
                    nome = le_string();
                    printf("Novo telefone: ");
                    telefone = le_string();
                    printf("Novo email: ");
                    email = le_string();
                    agenda_edita(busca, nome, telefone, email);
                }

                printf("\n\nContato modificado.");
                limpa_tela();

                free(nome);
            }
            break;

        case 4:

            if(agenda==NULL)
            {
                printf("Agenda vazia\n");
            }
            else
            {
                /**char escolha;

                printf("\nDeseja ver a lista de contatos na agenda?(S/N) : ");
                scanf("%c", &escolha);
                limpa_buffer();
                limpa_tela();

                if((escolha == 's') || (escolha == 'S'))
                {
                    agenda_imprime(agenda);
                }**/
                printf("\nListando os contatos...\n");

                printf("\nDigite o nome do contato: ");
                nome = le_string();

                busca = agenda_busca(agenda,nome);
                if(busca==NULL)
                {
                    printf("Contato inexistente!\nPor favor, tente novamente!\n");
                    break;
                }
                else
                {
					Contato* contatobusca = agenda_info(busca);
                    contato_imprime(contatobusca); //VERIFICAR SE ESTA CERTO
                    break;
                }
                limpa_tela();
                free(nome);
            }
            break;

        case 5:
            if(agenda!=NULL)
            {
                printf("\nListando contatos...");
                agenda_imprime(agenda);
            }
            else
            {
                printf("\nAgenda vazia.");
            }
            break;

        case 6:
            msg_despedida(DESPEDIDA);
            break;

        }
    }while(op!=6);


        FILE *salva = fopen("Agenda.txt","w");

        if(salva == NULL)
        {
            printf("\nErro ao criar arquivo.");
            exit(1);
        }

        agenda_salva(salva,agenda);

        fclose(fp);
        fclose(salva);

        return 0;


}
