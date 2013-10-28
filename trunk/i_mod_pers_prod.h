#ifndef PERS_PROD
#define PERS_PROD

#ifdef PERS_PROD_SERV
#define EXT_PPROD
#else
#define EXT_PPROD extern
#endif

#include "tabela_codigos.h"
#include "i_estruturas.h"

EXT_PPROD int cadastrar_produto(const struct produto *dev);
EXT_PPROD int consultar_produto(struct produto *dev);
EXT_PPROD int editar_produto(struct produto *dev);
EXT_PPROD int remover_produto(const char *cod);

#endif
