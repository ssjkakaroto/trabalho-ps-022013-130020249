#ifndef PERS_DEV
#define PERS_DEV

#ifdef PERS_DEV_SERV
#define EXT_PDEV
#else
#define EXT_PDEV extern
#endif

#include "tabela_codigos.h"
#include "i_estruturas.h"

EXT_PDEV int cadastrar_desenvolvedor(const struct desenvolvedor *dev,
                                     size_t posicao);
EXT_PDEV int consultar_desenvolvedor(struct desenvolvedor *dev);
EXT_PDEV int editar_desenvolvedor(struct desenvolvedor *dev, size_t posicao);
EXT_PDEV int remover_desenvolvedor(size_t posicao);

#endif
