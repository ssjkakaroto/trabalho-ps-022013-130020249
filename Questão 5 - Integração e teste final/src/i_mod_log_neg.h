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
 * Interface do módulo de lógica do negócio
 *******************************************************************************
 */

#ifndef LOG_NEG
#define LOG_NEG

#ifdef LOGICA_NEGOCIO_SERV
#define EXT_LGNG
#else
#define EXT_LGNG extern
#endif

#include "tabela_codigos.h"
#include "i_estruturas.h"

EXT_LGNG int check_login(struct desenvolvedor *dev);
EXT_LGNG int register_new_developer(struct desenvolvedor *dev);
EXT_LGNG int number_of_developers(void);
EXT_LGNG int load_developer(struct desenvolvedor *dev);
EXT_LGNG int overwrite_developer(const struct desenvolvedor *dev);
EXT_LGNG int remove_developer(struct desenvolvedor *dev);
EXT_LGNG int return_profile(const struct desenvolvedor *dev);
EXT_LGNG int assign_new_project_leader(struct desenvolvedor *dev,
                                       const char *dev_email);

EXT_LGNG int register_new_product(struct produto *prod);
EXT_LGNG int load_product(struct produto *prod);
EXT_LGNG int overwrite_product(const struct produto *prod);
EXT_LGNG int remove_product(struct produto *prod);
EXT_LGNG int assign_product_leader(char *dev_email, char *prod_cod);

EXT_LGNG int register_new_defect(struct defeito *bug);
EXT_LGNG int load_defect(struct defeito *bug);
EXT_LGNG int overwrite_defect(const struct defeito *bug);
EXT_LGNG int associate_defect(struct desenvolvedor *dev, char *cod_def);
EXT_LGNG int assign_defect_to_developer(char *dev_email, char *def_cod);

#endif
