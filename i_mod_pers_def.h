#ifndef PERS_DEF
#define PERS_DEF

#ifdef PERS_DEF_SERV
#define EXT_PDEF
#else
#define EXT_PDEF extern
#endif

#include "i_estruturas.h"

EXT_PDEF size_t cadastrar_defeito(const struct defeito *dev);
EXT_PDEF size_t consultar_defeito(struct defeito *dev);
EXT_PDEF size_t editar_defeito(struct defeito *dev);
EXT_PDEF size_t remover_defeito(const char *cod);

#endif
