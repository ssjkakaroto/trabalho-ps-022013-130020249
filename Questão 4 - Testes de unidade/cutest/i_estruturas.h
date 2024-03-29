/*
 *******************************************************************************
 * Universidade de Bras�lia
 * Instituto de Ci�ncias Exatas
 * Departamento de Ci�ncia da Computa��o
 * Mat�ria: Programa��o Sistem�tica
 * Professor: Fernando Albuquerque
 * Aluno: Aaron Sue
 * Matr�cula: 13/0020249
 * Trabalho Pr�tico
 * Header com as estruturas de dados utilizadas e valida��es de formato
 *******************************************************************************
 */

#ifndef ESTRUTURAS
#define ESTRUTURAS

#ifdef ESTRUTURAS_SERV
#define EXT_STRT
#else
#define EXT_STRT extern
#endif

#include "tabela_codigos.h"
#include <stddef.h>

/**
 * Estrutura de Desenvolvedor
 *
 * Nome: 15 caracteres (letra, espa�o)
 * Email(id) 20 caracteres: RFC 822
 * Senha: 5 digitos (sem repeti��o) APENAS NUMEROS
 * � lider de projeto: n�o = 0, sim = 1
 * � lider de produto: # de produtos que � lider (0 a 5)
 * � candidato a solu��o de defeito: # de produtos que � candidato (0 a 2)
 * cand1 e cand2: strings de ids dos defeitos ao qual � candidato
 * Est� solucionando defeito: # de produtos que est� solucionando (0 a 1)
 * Defeito que est� solucionando: c�digo do defeito
 * Foi excluido do cadastro: 1 = sim, 0 = n�o
 */
struct desenvolvedor {
	char   nome[NAME_SIZE];
	char   email[EMAIL_SIZE];
	char   senha[PASS_SIZE];
	size_t lid_proj;
	size_t lid_prod;
	size_t cand_def;
	char   cand1[CODE_SIZE];
	char   cand2[CODE_SIZE];
	size_t sol_def;
	char   def[CODE_SIZE];
	size_t excluido;
};

/**
 * Estrutura de Produto
 *
 * Nome: 15 caracteres (letra, espa�o)
 * Codigo(id): 4 letras
 * Versao: XX.YY
 * Lider: id do lider = email
 * Foi excluido do cadastro: 1 = sim, 0 = n�o
 */
struct produto {
	char   nome[NAME_SIZE];
	char   cod[CODE_SIZE];
	char   versao[VERSION_SIZE];
	char   lider[EMAIL_SIZE];
	size_t excluido;
};

/**
 * Estrutura de Defeito
 *
 * Codigo(id): 4 letras
 * Descricao: 30 caracteres
 * Estado: 1 - Novo, 2 - Confirmado, 3 - Em reparo, 4 - Reparado,
 *         5 - Encerrado, 6 - Confirmado)
 * Votos: 0 a 100 (inteiro)
 * Data_abertura: DD-MM-AAAA
 * Data_fechamento: DD-MM-AAAA
 * Desenvolvedor solucionando: email(id)
 * Produto ao qual o defeito esta associado: codigo(id)
 * Foi excluido do cadastro: 1 = sim, 0 = n�o
 */
struct defeito {
	char   cod[CODE_SIZE];
	char   desc[DESC_SIZE];
	size_t est;
	size_t votos;
	char   dt_ab[DATE_SIZE];
	char   dt_fc[DATE_SIZE];
	char   des_sel[EMAIL_SIZE];
	char   prod[CODE_SIZE];
	size_t excluido;
};


EXT_STRT void get_string(char *str, size_t size);
EXT_STRT void get_password(char *pass, size_t size);
EXT_STRT int  validate_email(const char *email);
EXT_STRT int  validate_name(const char *nome);
EXT_STRT int  validate_code(const char *cod);
EXT_STRT int  validate_version(const char *versao);

#endif
