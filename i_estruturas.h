#ifndef ESTRUTURAS
#define ESTRUTURAS

#ifdef ESTRUTURAS_SERV
#define EXT_STRT
#else
#define EXT_STRT extern
#endif

#include <stdint.h>

/**
 * Estrutura de Desenvolvedor
 *
 * Nome: 15 caracteres (letra, espaço)
 * Email(id) 20 caracteres: RFC 822
 * Senha: 5 digitos (sem repetição)
 * É lider de projeto: não = 0, sim = 1
 * É lider de produto: # de produtos que é lider (0 a 5)
 * É candidato a solução de defeito: # de produtos que é candidato (0 a 2)
 * Está solucionando defeito: # de produtos que está solucionando (0 a 1)
 */
struct desenvolvedor {
	char    nome[16];
	char    email[21];
	char    senha[6];
	uint8_t lid_proj;
	uint8_t lid_prod;
	uint8_t cand_def;
	uint8_t sol_def;
};

/**
 * Estrutura de Produto
 *
 * Nome: 15 caracteres (letra, espaço)
 * Codigo(id): 4 letras
 * Versao: XX.YY
 * Lider: id do lider = email
 */
struct produto {
	char nome[16];
	char cod[5];
	char versao[6];
	char lider[21];
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
 * Candidatos para solucionar: emails(ids)
 */
struct defeito {
	char    cod[5];
	char    desc[31];
	uint8_t est;
	uint8_t votos;
	char    dt_ab[11];
	char    dt_fc[11];
	char    des_sel[21];
	char    **cands;
};

EXT_STRT uint8_t verificar_email(const char *email);

#endif
