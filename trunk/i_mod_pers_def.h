#ifndef PERS_DEF
#define PERS_DEF

#ifdef PERS_DEF_SERV
#define EXT_PDEF
#else
#define EXT_PDEF extern
#endif

#include "tabela_codigos.h"
#include "i_estruturas.h"

EXT_PDEF int cadastrar_defeito(const struct defeito *dev);
EXT_PDEF int consultar_defeito(struct defeito *dev);
EXT_PDEF int editar_defeito(struct defeito *dev);
EXT_PDEF int remover_defeito(const char *cod);

#endif
