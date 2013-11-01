#ifndef LOG_NEG
#define LOG_NEG

#ifdef LOGICA_NEGOCIO_SERV
#define EXT_LGNG
#else
#define EXT_LGNG extern
#endif

#include "tabela_codigos.h"

int check_login(struct desenvolvedor *dev);
int register_new_developer(const struct desenvolvedor *dev);
int number_of_developers(void);
int load_developer(struct desenvolvedor *dev);

#endif
