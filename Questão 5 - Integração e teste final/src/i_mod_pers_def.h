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
 * Interface do m�dulo de persist�ncia de defeitos
 *******************************************************************************
 */

#ifndef PERS_DEF
#define PERS_DEF

#ifdef PERS_DEF_SERV
#define EXT_PDEF
#else
#define EXT_PDEF extern
#endif

#include "tabela_codigos.h"
#include "i_estruturas.h"

EXT_PDEF int register_defect(const struct defeito *bug);
EXT_PDEF int read_defect(struct defeito *bug);
EXT_PDEF int rewrite_defect(const struct defeito *bug);
EXT_PDEF int delete_defect(struct defeito *bug);
EXT_PDEF int count_defects(void);
EXT_PDEF int remove_product_defects(char *cod_prod);

#endif
