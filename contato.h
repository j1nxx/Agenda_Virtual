#ifndef CONTATO_H_INCLUDED
#define CONTATO_H_INCLUDED
//#include "contato.h"//duvida


	typedef struct contato Contato;
	Contato* contato_cria(char* nome, char* telefone, char* email);
	void contato_imprime(Contato* contato);
	void contato_edita(Contato* contato, char* nome, char* telefone, char* email);
	char* contato_nome(Contato* contato);
	char* contato_telefone(Contato* contato);
	char* contato_email(Contato* contato);
	void contato_libera(Contato* contato);

#endif // CONTATO_H_INCLUDED
