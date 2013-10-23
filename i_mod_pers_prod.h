#ifndef PERS_PROD
#define PERS_PROD

#ifdef PERS_PROD_SERV
#define EXT_PPROD
#else
#define EXT_PPROD extern
#endif

#include "i_estruturas.h"

EXT_PPROD size_t cadastrar_produto(const struct produto *dev);
EXT_PPROD size_t consultar_produto(struct produto *dev);
EXT_PPROD size_t editar_produto(struct produto *dev);
EXT_PPROD size_t remover_produto(const char *cod);

#endif
