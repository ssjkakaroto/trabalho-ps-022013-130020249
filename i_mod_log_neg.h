#ifndef LOG_NEG
#define LOG_NEG

#ifdef LOGICA_NEGOCIO_SERV
#define EXT_LGNG
#else
#define EXT_LGNG extern
#endif

#include "tabela_codigos.h"
#include "i_estruturas.h"

int check_login(struct desenvolvedor *dev);
int register_new_developer(const struct desenvolvedor *dev);
int number_of_developers(void);
int load_developer(struct desenvolvedor *dev);
int overwrite_developer(const struct desenvolvedor *dev);
int remove_developer(struct desenvolvedor *dev);

int register_new_product(const struct produto *prod);
int load_product(struct produto *prod);
int overwrite_product(const struct produto *prod);
int remove_product(struct produto *prod);

#endif
