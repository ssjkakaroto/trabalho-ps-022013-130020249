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
 * Interface do módulo de persistência de desenvolvedores
 *******************************************************************************
 */
 
#ifndef PERS_DEV
#define PERS_DEV

#ifdef PERS_DEV_SERV
#define EXT_PDEV
#else
#define EXT_PDEV extern
#endif

#include "tabela_codigos.h"
#include "i_estruturas.h"

EXT_PDEV int register_developer(const struct desenvolvedor *dev);
EXT_PDEV int read_developer(struct desenvolvedor *dev);
EXT_PDEV int rewrite_developer(const struct desenvolvedor *dev);
EXT_PDEV int delete_developer(struct desenvolvedor *dev);
EXT_PDEV int count_developers(void);

#endif
