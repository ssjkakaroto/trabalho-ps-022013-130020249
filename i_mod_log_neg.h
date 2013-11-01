#ifndef LOG_NEG
#define LOG_NEG

#ifdef LOGICA_NEGOCIO_SERV
#define EXT_LGNG
#else
#define EXT_LGNG extern
#endif

#include "tabela_codigos.h"

int cadastrar_desenvolvedor(const struct desenvolvedor *dev);

#endif
