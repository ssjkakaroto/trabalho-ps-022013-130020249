/*
 *******************************************************************************
 * Universidade de Brasília
 * Instituto de Ciências Exatas
 * Departamento de Ciência da Computação
 * Matéria: Programação Sistemática
 * Professor: Fernando Albuquerque
 * Aluno: Aaron Sue
 * Matrícula: 13/0020249
 * Trabalho Prático
 * Arquivo com as funções de validação de formato
 *******************************************************************************
 */

#define ESTRUTURAS_SERV

#include "tabela_codigos.h"
#include "i_estruturas.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/**
 * Função auxiliar para capturar strings, que recebe a string e seu tamanho.
 * O último caracter será sempre '\0'.
 */
void get_string(char *str, size_t size)
{
	char lixo[16];

	fgets(str, size, stdin);

	/* Limpa o buffer do stdin, caso necessário */
    if (str[strlen(str)-1] != '\n') {
		do {
			fgets(lixo, 16, stdin);
		} while (lixo[strlen(lixo)-1] != '\n');
	} else {
		str[strlen(str)-1] = '\0';
	}
}


/**
 * Função auxiliar para capturar senhas, que recebe a string da senha e o
 * tamanho da senha.
 * O último caracter será sempre '\0', por isso o tamanho máximo da senha é
 * (size - 1)
 * Não da echo dos caracteres e termina automaticamente quando chega no tamanho
 * (size - 1).
 */
void get_password(char *pass, size_t size)
{
	size_t i;

	pass[size - 1] = '\0';
	for (i = 0; i < (size - 1); i++) {
		pass[i] = getch();

		if (pass[i] == '\n') {
			pass[i] = '\0';
			break;
		}
	}
}


/**
 * Função que faz a validação básica do formato do email.
 * Não permite que o caracter digitado no email seja menor que 32 (espaço) ou
 * maior que 126 (~), nem que seja igual aos caracteres proibidos pelo RFC 822.
 *
 * Valor de retorno: SUCCESS se o email for valido e INVALID_EMAIL se for
 * invalido.
 */
int validate_email(const char *email)
{
	size_t cont = 0;
	const char *c, *dominio;
	static char *rfc822_specials = "()<>@,;:\\\"[]";

	for (c = email; *c; c++) {
		if (*c == '@')
			break;
		if (*c <= ' ' || *c >= 126)
			return INVALID_EMAIL;
		if (strchr(rfc822_specials, *c))
			return INVALID_EMAIL;
	}

	if (!*(dominio = ++c))
		return INVALID_EMAIL;
	do {
		if (*c <= ' ' || *c >= 126)
			return INVALID_EMAIL;
		if (strchr(rfc822_specials, *c))
			return INVALID_EMAIL;
		cont++;
	} while (*++c);

	return(cont >= SUCCESS);
}


int validate_name(const char *nome)
{
	const char *c;
	
	for (c = nome; *c; c++) {
		if ((*c < 'A' || *c > 'Z') && (*c < 'a' || *c > 'z') && (*c != ' '))
			return INVALID_NAME;
	}

	return SUCCESS;
}


int validate_code(const char *cod)
{
	const char *c;

	for (c = cod; *c; c++) {
		if ((*c < 'A' || *c > 'Z') && (*c < 'a' || *c > 'z'))
			return INVALID_CODE;
	}

	return SUCCESS;
}


int validate_version(const char *versao)
{
	const char *c;

	c = versao;

	if (c[2] != '.')
		return INVALID_VERSION;
	if (c[0] < '0' || c[0] > '9')
		return INVALID_VERSION;
	if (c[1] < '0' || c[1] > '9')
		return INVALID_VERSION;
	if (c[3] < '0' || c[3] > '9')
		return INVALID_VERSION;
	if (c[4] < '0' || c[4] > '9')
		return INVALID_VERSION;

	return SUCCESS;
}
