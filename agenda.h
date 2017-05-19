#ifndef AGENDA_H_INCLUDED
#define AGENDA_H_INCLUDED
#include "contato.h"
//#include "agenda.h"//duvida

	typedef struct no No;
	typedef struct no* Agenda;
	Agenda agenda_cria(void);
	Agenda agenda_carrega(FILE* fp);
	Agenda agenda_insere(Agenda agenda, Contato *contato);
	Contato* agenda_info(No* no);
	No* agenda_busca(Agenda agenda, char* nome);
	Agenda agenda_remove(Agenda agenda, char* nome);
	void agenda_edita(No* no, char* nome, char* telefone, char* email);
	void agenda_imprime(Agenda agenda);
	void agenda_salva(FILE* fp, Agenda agenda);

#endif // AGENDA_H_INCLUDED
