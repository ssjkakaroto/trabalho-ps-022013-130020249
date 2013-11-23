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
 * Interface do módulo de persistência de produtos
 *******************************************************************************
 */

#ifndef PERS_PROD
#define PERS_PROD

#ifdef PERS_PROD_SERV
#define EXT_PPROD
#else
#define EXT_PPROD extern
#endif

#include "tabela_codigos.h"
#include "i_estruturas.h"

EXT_PPROD int register_product(const struct produto *prod);
EXT_PPROD int read_product(struct produto *prod);
EXT_PPROD int rewrite_product(const struct produto *prod);
EXT_PPROD int delete_product(struct produto *prod);
EXT_PPROD int count_products(void);
EXT_PPROD int remove_product_leader(char *dev_email);

#endif
