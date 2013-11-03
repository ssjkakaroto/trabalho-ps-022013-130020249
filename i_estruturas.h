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
 * Nome: 15 caracteres (letra, espaço)
 * Email(id) 20 caracteres: RFC 822
 * Senha: 5 digitos (sem repetição) APENAS NUMEROS
 * É lider de projeto: não = 0, sim = 1
 * É lider de produto: # de produtos que é lider (0 a 5)
 * É candidato a solução de defeito: # de produtos que é candidato (0 a 2)
 * cand1 e cand2: strings de ids dos defeitos ao qual é candidato
 * Está solucionando defeito: # de produtos que está solucionando (0 a 1)
 * Foi excluido do cadastro: 1 = sim, 0 = não
 */
struct desenvolvedor {
	char   nome[NAME_SIZE];
	char   email[EMAIL_SIZE];
	char   senha[PASS_SIZE];
	size_t lid_proj;
	size_t lid_prod;
	size_t cand_def;
	char   cand1[5];
	char   cand2[5];
	size_t sol_def;
	size_t excluido;
};

/**
 * Estrutura de Produto
 *
 * Nome: 15 caracteres (letra, espaço)
 * Codigo(id): 4 letras
 * Versao: XX.YY
 * Lider: id do lider = email
 * Foi excluido do cadastro: 1 = sim, 0 = não
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
 *         5 - Encerrado, 6 - Confirmado, 7 - Descontinuado)
 * Votos: 0 a 100 (inteiro)
 * Data_abertura: DD-MM-AAAA
 * Data_fechamento: DD-MM-AAAA
 * Desenvolvedor solucionando: email(id)
 * Candidatos para solucionar: emails(ids) REMOVER ESTE CAMPO
 * Produto ao qual o defeito esta associado: codigo(id)
 * Foi excluido do cadastro: 1 = sim, 0 = não
 */
struct defeito {
	char   cod[5];
	char   desc[31];
	size_t est;
	size_t votos;
	char   dt_ab[11];
	char   dt_fc[11];
	char   des_sel[NAME_SIZE];
	char   prod[CODE_SIZE];
	/* char   *cands[21]; */
	size_t excluido;
};


EXT_STRT void get_string(char *str, size_t size);
EXT_STRT void get_password(char *pass, size_t size);
EXT_STRT int verificar_email(const char *email);

#endif
