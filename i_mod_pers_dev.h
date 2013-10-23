#ifndef PERS_DEV
#define PERS_DEV

#ifdef PERS_DEV_SERV
#define EXT_PDEV
#else
#define EXT_PDEV extern
#endif

#include "i_estruturas.h"

EXT_PDEV size_t cadastrar_desenvolvedor(const struct desenvolvedor *dev);
EXT_PDEV size_t consultar_desenvolvedor(struct desenvolvedor *dev);
EXT_PDEV size_t editar_desenvolvedor(struct desenvolvedor *dev);
EXT_PDEV size_t remover_desenvolvedor(const char *email);

#endif
